/*-----------------------------------------------------------------------------
* TITLE: API_I2C_SLAVE.C
*
* Author : Dino
*
* History : 
* ------------------------------
* Version : 1.00
* ------------------------------
*
* Note : To link [api_xxx.o] if related api function be used.
*
*---------------------------------------------------------------------------*/

//*****************************************************************************
// Include all header file
#include <CORE_INCLUDE.H>
#include <API_INCLUDE.H>
//
//*****************************************************************************
#if API_I2C_SLAVE_SUPPORT

#if I2C_SLAVE_A_SUPPORT
ECReg 	Slave_A_RW_Buf[Slave_A_Buff_Size]			_at_ 0xA00;
#endif

#if I2C_SLAVE_B_SUPPORT
ECReg 	Slave_B_RW_Buf[Slave_B_Buff_Size]			_at_ 0xB00;
#endif

//*****************************************************************************
//
// global variables for I2C slave api
//
//*****************************************************************************
#if I2C_SLAVE_A_SUPPORT
BYTE Slave_Cmd_A;
BYTE Slave_Start_A;
#endif

#if I2C_SLAVE_B_SUPPORT
BYTE Slave_Cmd_B;
BYTE Slave_Start_B;
#endif

BYTE *g_i2c_slave_a_byte_buffer_pointer;
BYTE *g_i2c_slave_b_byte_buffer_pointer;

FUNCT_PTR_V_V g_i2c_slave_a_stop_condition_hook_func;
FUNCT_PTR_V_V g_i2c_slave_b_stop_condition_hook_func;
FUNCT_PTR_V_V g_i2c_slave_a_stop_condition_hook_func_addr2;
FUNCT_PTR_V_V g_i2c_slave_b_stop_condition_hook_func_addr2;
FUNCT_PTR_V_V g_i2c_slave_a_timeout_hook_func;
FUNCT_PTR_V_V g_i2c_slave_b_timeout_hook_func;

//*****************************************************************************
//
// example for I2C slave api
//
//*****************************************************************************
// 
//  Initialization : 
//  I2C_Slave_A_OEM_Init((BYTE *)0xA00, &func1, &func2, &func3 );
//  I2C_Slave_B_OEM_Init((BYTE *)0xB00, &func4, &func5, &func6 );
//  I2C_Slave_Initialization(_I2C_Slave_at_Channel_A, _I2C_Slave_at_Channel_NULL, 0x52, 0x00, 0x00, 0x00);
//
//  ISR : 
//  I2C_Slave_A_ISR in Hook_IRQ_INT9_SMBusA
//  I2C_Slave_B_ISR in Hook_IRQ_INT10_SMBusB
//
//  *** Note *** : 
//  remeber re-Initialization function I2C_Slave_A_OEM_Init and I2C_Slave_B_OEM_Init
//  and call I2C_Slave_x_Variables_Reset to reset buffer index after upgrade EC firmware
//

//*****************************************************************************
//
// config table for I2C slave api
//
//*****************************************************************************
const sI2CSlaveConfig code asI2CSlaveConfig[]=
{
	{ &GPCRB3, &GPCRB4  },  // SMCLK0/SMDAT0
	{ &GPCRC1, &GPCRC2  },  // SMCLK1/SMDAT1
};

//*****************************************************************************
//
//  oem init function for I2C slave A.
//
//  parameter :
//      p_byte_rw_buffer            : pointer for I2C slave ram
//      p_stop_condition_func       : function pointer for stop condition
//      p_stop_condition_func_addr2 : function pointer for stop condition (address 2 match)
//      p_timeout_func              : function pointer for timeout condition
//
//  return :
//      none
//
//  note : 1. To ready all pointer before enable slave channel.
//         2. all hook function are executed in isr, please consider the content of oem hook function.
//
//*****************************************************************************
void I2C_Slave_A_OEM_Init(BYTE *p_byte_rw_buffer,FUNCT_PTR_V_V p_stop_condition_func 
                                ,FUNCT_PTR_V_V p_stop_condition_func_addr2, FUNCT_PTR_V_V p_timeout_func)
{
    //
    // to store the address of oem byte write buffer
    //
    g_i2c_slave_a_byte_buffer_pointer = p_byte_rw_buffer;

    //
    // to store the address of oem hook function for stop condition occurs
    //
	g_i2c_slave_a_stop_condition_hook_func = p_stop_condition_func;
	
    //
    // to store the address of oem hook function for stop condition occurs (address 2 match)
    //
    g_i2c_slave_a_stop_condition_hook_func_addr2 = p_stop_condition_func_addr2;
	
    //
    // to store the address of oem hook function for timeout occurs
    //
    g_i2c_slave_a_timeout_hook_func = p_timeout_func;
}

//*****************************************************************************
//
//  oem init function for I2C slave B.
//
//  parameter :
//      p_byte_rw_buffer            : pointer for I2C slave ram
//      p_stop_condition_func       : function pointer for stop condition
//      p_stop_condition_func_addr2 : function pointer for stop condition (address 2 match)
//      p_timeout_func              : function pointer for timeout condition
//
//  return :
//      none
//
//  note : 1. To ready all pointer before enable slave channel.
//         2. all hook function are executed in isr, please consider the content of oem hook function.
//
//*****************************************************************************
void I2C_Slave_B_OEM_Init(BYTE *p_byte_rw_buffer, FUNCT_PTR_V_V p_stop_condition_func 
                                ,FUNCT_PTR_V_V p_stop_condition_func_addr2, FUNCT_PTR_V_V p_timeout_func)
{
    //
    // to store the address of oem byte write buffer
    //
    g_i2c_slave_b_byte_buffer_pointer = p_byte_rw_buffer;

    //
    // to store the address of oem hook function for stop condition occurs
    //
    g_i2c_slave_b_stop_condition_hook_func = p_stop_condition_func;

    //
    // to store the address of oem hook function for stop condition occurs (address 2 match)
    //
    g_i2c_slave_b_stop_condition_hook_func_addr2 = p_stop_condition_func_addr2;

    //
    // to store the address of oem hook function for timeout occurs
    //
    g_i2c_slave_b_timeout_hook_func = p_timeout_func;
}

//*****************************************************************************
//
//  Initialization for SMBus slave x.
//
//  parameter :
//      p_slave_a_at_channel : 
//      p_slave_b_at_channel : 
//                              _I2C_Slave_at_Channel_A
//                              _I2C_Slave_at_Channel_B
//                              _I2C_Slave_at_Channel_NULL
//
//      p_slave_a_addr      :   7 bit address for slave A
//      p_slave_a_addr2     :   7 bit address for salve A (address 2)
//      p_slave_b_addr      :   7 bit address for slave B
//      p_slave_b_addr2     :   7 bit address for salve B (address 2)
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_Initialization(BYTE p_slave_a_at_channel, BYTE p_slave_b_at_channel
                                ,BYTE p_slave_a_addr, BYTE p_slave_a_addr2, BYTE p_slave_b_addr, BYTE p_slave_b_addr2)
{
    //
    // SMBus slave A is located at SMCLKx/SMDATx
    //
    I2C_Slave_Interface_Select(_I2C_Slave_A, p_slave_a_at_channel);

    //
    // SMBus slave B is located at SMCLKx/SMDATx
    //
    I2C_Slave_Interface_Select(_I2C_Slave_B, p_slave_b_at_channel);

    //
    // to enable slave A
    //
    if(p_slave_a_at_channel <= _I2C_Slave_at_Channel_B)
    {
        I2C_Slave_A_Enable(p_slave_a_addr, p_slave_a_addr2);
    }

    //
    // to enable slave B
    //
    if(p_slave_b_at_channel <= _I2C_Slave_at_Channel_B)
    {
        I2C_Slave_B_Enable(p_slave_b_addr, p_slave_b_addr2);
    }

    //
    // slave global setting for 100K
    //
    SMB25MS = 0x19;

}

//*****************************************************************************
//
//  To decide which interface the slave A or B is located at.
//
//  parameter :
//      p_slave_module  :   _I2C_Slave_A || _I2C_Slave_B
//
//      p_local_channel :   _I2C_Slave_at_Channel_A --> slave interface is located at SMCLK0/SMDAT0
//                          _I2C_Slave_at_Channel_B --> slave interface is located at SMCLK1/SMDAT1
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_Interface_Select(BYTE p_slave_module, BYTE p_local_channel)
{
    //
    // selection for slave A
    //
    if(p_slave_module == _I2C_Slave_A)
    {
        //
        // the parameter is valided.
        //
        if(p_local_channel <= _I2C_Slave_at_Channel_B)
        {
            //
            // SMBus slave A enable
            //
            SET_MASK(HOCTL2_A, BIT5);
            
            //
            // default slave A interface is located at SMCLK0/SMDAT0
            //
            CLEAR_MASK(SLVISEL, (BIT0+BIT1));
            
            //
            // slave A interface is located at SMCLK[p_local_channel] / SMDAT[p_local_channel]
            //
            SLVISEL |= p_local_channel;

            //
            // clock and data pin to alt function.
            //
            *asI2CSlaveConfig[p_local_channel].SMBusPin0 = ALT;
            *asI2CSlaveConfig[p_local_channel].SMBusPin1 = ALT;

            //
            // W/C isr[x]
            //
            ISR1 = Int_SMBUS0;

            //
            // enable ier[x]
            //
            IER1 |= Int_SMBUS0;
        }
    }

    //
    // selection for slave B
    //
    if(p_slave_module == _I2C_Slave_B)
    {
        //
        // the parameter is valided.
        //
        if(p_local_channel <= _I2C_Slave_at_Channel_B)
        {
            //
            // SMBus slave B enable
            //
            SET_MASK(HOCTL2_B, BIT5);
            
            //
            // default slave B interface is located at SMCLK0/SMDAT0
            //
            CLEAR_MASK(SLVISEL, (BIT2+BIT3));
            
            //
            // slave B interface is located at SMCLK[p_local_channel] / SMDAT[p_local_channel]
            //
            SLVISEL |= (p_local_channel<<2);

            //
            // clock and data pin to alt function.
            //
            *asI2CSlaveConfig[p_local_channel].SMBusPin0 = ALT;
            *asI2CSlaveConfig[p_local_channel].SMBusPin1 = ALT;

            //
            // W/C isr[x]
            //
            ISR1 = Int_SMBUS1;

            //
            // enable ier[x]
            //
            IER1 |= Int_SMBUS1;
        }
    }
}

//*****************************************************************************
//
//  To enable slave A module.
//
//  parameter :
//      p_slave_address_1 : 7bit I2C slave address
//      p_slave_address_2 : 7bit I2C slave address 2
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_A_Enable(BYTE p_slave_address_1, BYTE p_slave_address_2)
{
    //
    // bit5 : SMBus slave A enable.
    //
    HOCTL2_A = BIT5;

    //
    // bit0 : host notify interrupt enable.
    // bit1 : slave interrupt enable.
    // bit2 : SMCLK/SMDAT will be released if timeout.
    // bit3 : slave detect STOP condition interrupt enable.
    //
    SICR_A = (BIT0+BIT1+BIT2+BIT3);

    //
    // slave address 1
    //
    RESLADR_A = p_slave_address_1;

    //
    // slave address 2
    // bit7 : SADR2 field is valided.
    //
    if(p_slave_address_2!=0)
    {
        RESLADR_2_A = (p_slave_address_2+BIT7);
    }

    //
    // Kill the current host transaction.
    // This bit once set, has to be cleared by software to allow the SMBus
    // Host controller to function normally.
    //
    HOCTL_A = BIT1;
    HOCTL_A = 0x00;

    //
    // W/C all master status
    //
    HOSTA_A = 0xFF;

    //
    // W/C all slave status
    //
    SLSTA_A = 0xFF;
}

//*****************************************************************************
//
//  To enable slave B module.
//
//  parameter :
//      p_slave_address_1 : 7bit I2C slave address
//      p_slave_address_2 : 7bit I2C slave address 2
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_B_Enable(BYTE p_slave_address_1, BYTE p_slave_address_2)
{
    //
    // bit5 : SMBus slave B enable.
    //
    HOCTL2_B = BIT5;

    //
    // bit0 : host notify interrupt enable.
    // bit1 : slave interrupt enable.
    // bit2 : SMCLK/SMDAT will be released if timeout.
    // bit3 : slave detect STOP condition interrupt enable.
    //
    SICR_B = (BIT0+BIT1+BIT2+BIT3);

    //
    // slave address 1
    //
    RESLADR_B = p_slave_address_1;

    //
    // slave address 2
    // bit7 : SADR2 field is valided.
    //
    if(p_slave_address_2!=0)
    {
        RESLADR_2_B = (p_slave_address_2+BIT7);
    }

    //
    // Kill the current host transaction.
    // This bit once set, has to be cleared by software to allow the SMBus
    // Host controller to function normally.
    //
    HOCTL_B = BIT1;
    HOCTL_B = 0x00;

    //
    // W/C all master status
    //
    HOSTA_B = 0xFF;

    //
    // W/C all slave status
    //
    SLSTA_B = 0xFF;
}

#if I2C_SLAVE_A_SUPPORT
//*****************************************************************************
//
//  The ISR for slave A module
//
//  parameter :
//      p_match_slave_address   : _I2C_Match_Slave_Address1 || _I2C_Match_Slave_Address2
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_A_ISR_Address_x(BYTE p_match_slave_address)
{
    BYTE l_buffer;

    //
    // slave data status, slave data register is waiting for read or write.
    //
    if(IS_MASK_SET(SLSTA_A, SDS))
    {
        if(IS_MASK_SET(SLSTA_A, RCS))
        {
            //
            // Master byte read, return data to master 
            //	
			if(Slave_Start_A)
			{
				//
				// read data from buffer and reset Slave_Start_A
				//
				SLDA_A = g_i2c_slave_a_byte_buffer_pointer[Slave_Cmd_A];
				Slave_Start_A = 0;
			} 

            //
            // W/C slave data status
            //
            SLSTA_A = SDS;

            //
            // to release clock pin
            //
            SLDA_A = 0x00;
        }
        else
        {
            //
            // Master byte write , get data from master.
            //
			if(!Slave_Start_A)
			{
				//
				// command byte
				//
				Slave_Start_A = 1;
				Slave_Cmd_A = SLDA_A;
			}
			else
			{
				//
				// write data to buffer and reset Slave_Start_A 
				//
				g_i2c_slave_a_byte_buffer_pointer[Slave_Cmd_A] = SLDA_A;
				Slave_Start_A = 0;
			}

            //
            // W/C slave data status
            //
            SLSTA_A = SDS;

            //
            // to release clock pin
            //
            l_buffer = SLDA_A;
        }
    }    
    //
    // Stop condition, indicate stop condition detected.
    //
    else if(IS_MASK_SET(SLSTA_A, SPDS))
    {
		//
		// reset Slave_Start_A
		//
		Slave_Start_A = 0;

        //
        // W/C stop condition
        //
        SLSTA_A = SPDS;

        if(p_match_slave_address == _I2C_Match_Slave_Address2)
        {
            //
            // hook function for oem if address 2 match
            //
            g_i2c_slave_a_stop_condition_hook_func_addr2();
        }
        else
        {
            //
            // hook function for oem if address match
            //
            g_i2c_slave_a_stop_condition_hook_func();
        }
    }

    //
    // slave time status, timeout status occurs.
    //
    else if(IS_MASK_SET(SLSTA_A, STS))
    {
        //
        // W/C timeout status
        //
        SLSTA_A = STS;

        //
        // hook function for oem if timeout
        //
        g_i2c_slave_a_timeout_hook_func();
    }
    //
    //
    //
    else
    {
    }
}

//*****************************************************************************
//
//  The ISR for slave A module.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_A_ISR(void)
{
    //
    // W/C isr[x]
    //
    ISR1 = Int_SMBUS0;

    //
    // match slave address 2.
    //
    if(IS_MASK_SET(SLSTA_A, MSLA2))
    {
        //
        // slave address 2.
        //
        I2C_Slave_A_ISR_Address_x(_I2C_Match_Slave_Address2);
    }
    else
    {
        //
        // slave address 1.
        //
        I2C_Slave_A_ISR_Address_x(_I2C_Match_Slave_Address1);
    }
}
#endif

#if	I2C_SLAVE_B_SUPPORT
//*****************************************************************************
//
//  The ISR for slave B module
//
//  parameter :
//      p_match_slave_address   : _I2C_Match_Slave_Address1 || _I2C_Match_Slave_Address2
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_B_ISR_Address_x(BYTE p_match_slave_address)
{
    BYTE l_buffer;
    
    //
    // slave data status, slave data register is waiting for read or write.
    //
    if(IS_MASK_SET(SLSTA_B, SDS))
    {
        if(IS_MASK_SET(SLSTA_B, RCS))
        {
            //
            // Master byte read	, return data to master 
            //
            if(Slave_Start_B)
			{
				//
				// read data from buffer and reset Slave_Start_B
				//
				SLDA_B = g_i2c_slave_b_byte_buffer_pointer[Slave_Cmd_B];
				Slave_Start_B = 0;
			}

            //
            // W/C slave data status
            //
            SLSTA_B = SDS;

            //
            // to release clock pin
            //
            SLDA_B = 0x00;
        }
        else
        {
            //
            // Master byte write , get data from master.
            //
            if(!Slave_Start_B)
			{
				//
				// command byte
				//
				Slave_Start_B = 1;
				Slave_Cmd_B = SLDA_B;
			}
			else
			{
				//
				// write data to buffer and reset Slave_Start_B 
				//
				g_i2c_slave_b_byte_buffer_pointer[Slave_Cmd_B] = SLDA_B;
				Slave_Start_B = 0;
			}

            //
            // W/C slave data status
            //
            SLSTA_B = SDS;

            //
            // to release clock pin
            //
            l_buffer = SLDA_B;
        }
    }
    //
    // Stop condition, indicate stop condition detected.
    //
    else if(IS_MASK_SET(SLSTA_B, SPDS))
    {
		//
		// reset Slave_Start_B
		//
		Slave_Start_B = 0;
        //
        // W/C stop condition
        //
        SLSTA_B = SPDS;

        if(p_match_slave_address == _I2C_Match_Slave_Address2)
        {
            //
            // hook function for oem if address 2 match
            //
            g_i2c_slave_b_stop_condition_hook_func_addr2();
        }
        else
        {
            //
            // hook function for oem if address match
            //
            g_i2c_slave_b_stop_condition_hook_func();
        }
    }

    //
    // slave time status, timeout status occurs.
    //
    else if(IS_MASK_SET(SLSTA_B, STS))
    {
        //
        // W/C timeout status
        //
        SLSTA_B = STS;

        //
        // hook function for oem if timeout
        //
        g_i2c_slave_b_timeout_hook_func();
    }
    //
    //
    //
    else
    {

    }
}

//*****************************************************************************
//
//  The ISR for slave B module.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void I2C_Slave_B_ISR(void)
{
    //
    // W/C isr[x]
    //
    ISR1 = Int_SMBUS1;

    //
    // match slave address 2.
    //
    if(IS_MASK_SET(SLSTA_B, MSLA2))
    {
        //
        // slave address 2.
        //
        I2C_Slave_B_ISR_Address_x(_I2C_Match_Slave_Address2);
    }
    else
    {
        //
        // slave address 1.
        //
        I2C_Slave_B_ISR_Address_x(_I2C_Match_Slave_Address1);
    }  
}
#endif
#endif
