/*-----------------------------------------------------------------------------
* TITLE: API_OW.C
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
#if API_OW_SUPPORT
//*****************************************************************************
ECReg   OW_DATA          _at_ 0x2A00;		// One Wire Data Register
ECReg   OW_CTRL          _at_ 0x2A01;		// One Wire Control Register
ECReg   OW_MOD           _at_ 0x2A02;		// One Wire Mode Register
ECReg   OW_STS           _at_ 0x2A03;		// One Wire Status Register
ECReg   OW_INTEN         _at_ 0x2A04;		// One Wire Interrupt Enable Register
ECReg   OW_RSTL_RSTH_H   _at_ 0x2A05;		// One Wire High bit of Reset Low and Reset High Register
ECReg   OW_RST_LOW       _at_ 0x2A06;		// One Wire Reset Low Register
ECReg   OW_MSP           _at_ 0x2A07;		// One Wire Master Sample Present Register
ECReg   OW_RSTH          _at_ 0x2A08;		// One Wire Reset High Register
ECReg   OW_SLOT          _at_ 0x2A09; 		// One Wire Time Slot Register
ECReg   OW_W1L           _at_ 0x2A0A; 		// One Wire Write 1 Low Register
ECReg   OW_W0L           _at_ 0x2A0B; 		// One Wire Write 0 Low Register
ECReg   OW_MSR           _at_ 0x2A0C; 		// One Wire Master Sample Read Bit Register

//*****************************************************************************
// Software OW
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//
// Reset OW device function
//
//  parameter :
//      none
//
//  return :
//      FFh : Reset device OK.
//      00h : Reset device fail.
//
//*****************************************************************************
//__attribute__((optimize("O0")))
BYTE SW_OW_Device_Reset(void)
{	
    BYTE report;
    BYTE delay;

    DisableAllInterrupt();
    report = 0xFF;          // Pre-set 0xFF, OK
    
    //-------------------------------------------------
    // Low 500 us, tRSTL
    //-------------------------------------------------
    OneWireOutput;
    OneWireLow;             // Output low

    for(delay=0x00; delay<=34; delay++) 
    {                       // Delay > 480 us
        WNCKR = 0x00;       // Delay 15.26 us
    }

    OneWireInput;
    //-------------------------------------------------
    // To wait pin high (120us time out)
    //-------------------------------------------------    
    for(delay=0x00; delay<8; delay++) // (120us time out)
    {
        WNCKR = 0x00;       // Delay 15.26 us
        
        if(OneWireStatusHigh)
        {
            report = 0xFF;  // 0xFF, OK
            break;
        }
        else
        {
            report = 0x00;  // 0x00, Fail
        }
    }

    if(report == 0xFF)
    {
        //-------------------------------------------------
        // To wait pin high (240us time out)
        //-------------------------------------------------   
        for(delay=0x00; delay<=16; delay++) // (240us time out)
        {
            WNCKR = 0x00;       // Delay 15.26 us
            
            if(OneWireStatusLow)
            {
                report = 0xFF;  // 0xFF, OK
                break;
            }
            else
            {
                report = 0x00;  // 0x00, Fail
            }
        }
    }
        
    if(report == 0xFF)
    {
        //-------------------------------------------------
        // To wait pin high (1ms time out)
        //-------------------------------------------------    
        for(delay=0x00; delay<=66; delay++) // (1ms time out)
        {
            if(OneWireStatusHigh)
            {
                report = 0xFF;  // 0xFF, OK
                break;
            }
            else
            {
                report = 0x00;  // 0x00, Fail
            }
        }
    }
    
    EnableAllInterrupt();
    return(report);
}

//*****************************************************************************
//
// Write one bit function
//
//  parameter :
//      0 or 1
//
//  return :
//      none
//
//*****************************************************************************
//__attribute__((optimize("O0")))
void SW_OW_Device_WriteBit(BYTE Psidbit)
{
    BYTE delay;
    
    OneWireOutput;
    OneWireLow;

    if(Psidbit)
    {
        OneWireHigh;
    }
    else
    {
        OneWireLow;
    }

    //-------------------------------------------------
    // Delay 60us
    //-------------------------------------------------
    for(delay=0x00; delay<4; delay++) 
    {                       // Delay 60 us
        WNCKR = 0x00;       // Delay 15.26 us
    }

    OneWireInput;
    WNCKR = 0x00;           // Delay 15.26 us
}

//*****************************************************************************
//
// Write one byte to OW device.
//
//  parameter :
//      00h ~ FFh
//
//  return :
//      none
//
//*****************************************************************************
//__attribute__((optimize("O0")))
void SW_OW_Device_WriteByte(BYTE PsidByte)
{
    BYTE index;

    DisableAllInterrupt();
	for(index=0x00;index<8;index++)
	{
		if((PsidByte>>index)&0x01)
		{
		    SW_OW_Device_WriteBit(1);
		}
		else
		{
		    SW_OW_Device_WriteBit(0);
		}
	}
    EnableAllInterrupt();
}

//*****************************************************************************
//
// Read one bit function
//
//  parameter :
//      none
//
//  return :
//      0 or 1
//
//*****************************************************************************
//__attribute__((optimize("O0")))
BYTE SW_OW_Device_ReadBit(void)
{
	BYTE tempdata;
    BYTE delay;
    
    OneWireOutput;
    OneWireLow;
    _nop_();
    
    OneWireInput;
    WNCKR = 0x00;       // Delay 15.26 us

    if(OneWireStatusHigh)
    {
        tempdata = 1;
    }
    else
    {
        tempdata = 0;
    }

    //-------------------------------------------------
    // Delay 60us
    //-------------------------------------------------
    for(delay=0x00; delay<4; delay++) 
    {                       // Delay 60 us
        WNCKR = 0x00;       // Delay 15.26 us
    }

    return(tempdata);
}

//*****************************************************************************
//
// Read one byte from OW device.
//
//  parameter :
//      none
//
//  return :
//      00h ~ FFh
//
//*****************************************************************************
//__attribute__((optimize("O0")))
BYTE SW_OW_Device_ReadByte(void)
{
    BYTE index;
    BYTE readbit;
    BYTE result;

    DisableAllInterrupt();
	result=0x00;
	for(index=0x00;index<8;index++)
	{
		readbit = SW_OW_Device_ReadBit();
		result|=(readbit<<index);
	}
	EnableAllInterrupt();
    
	return(result);
}

//*****************************************************************************
//*****************************************************************************
// Hardware OW
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
// OW register setting
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void OW_Init_Registers(void)
{   
    GPCRB2 = ALT+PULL_UP;           // GPIO B2 alt function
    //CGCTRL3R = 0x01;	            // 0x1E05 , Bit0 = 1
    GCR6 |= BIT4;			        // 0x16F5 , Bit4 = 1
}

//*****************************************************************************
//
// Init timer1 for interface time-out
//
//  parameter :
//      Tomeout : 1, 2, 5, 20, 30, 40 ms ; Default : 5 ms
//
//  return :
//      none
//
//*****************************************************************************
void Enable_ETimer_T(BYTE Tomeout)
{
	WORD _Timeout;

	switch(Tomeout)
	{
		case 1:
  			_Timeout = Timer_1ms;	  	// Set timer1 counter 5ms
			break;

		case 2:
  			_Timeout = Timer_2ms;	  	// Set timer1 counter 5ms
			break;

		case 5:
  			_Timeout = Timer_5ms;	  	// Set timer1 counter 5ms
			break;

		case 20:
			_Timeout = Timer_20ms;
			break;

		case 30:
  			_Timeout = Timer_30ms;
			break;

		case 40:
			_Timeout = Timer_40ms;
			break;

		default:
			_Timeout = Timer_5ms; 		// Set timer1 counter 5ms
			break;

	}
	TR1 = 0;                 	// Disable timer1
    ET1 = 0;                  	// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
	TH1 = _Timeout>>8;        	
    TL1 = _Timeout;           	// Set timer1 counter 5ms
	TF1 = 0;                  	// Clear overflow flag
    TR1 = 1;                 	// Enable timer1
}

//*****************************************************************************
//
// Stop Time Out Function 
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Stop_ETimer(void)
{
	TR1=0;
	TF1=0;
    ET1=1;
}

//*****************************************************************************
//
// Reset OW device function
//
//  parameter :
//      none
//
//  return :
//      01h : Reset device OK.
//      00h : Reset device fail.
//
//*****************************************************************************
BYTE HW_OW_Device_Reset(void)
{
    BYTE result;
    result = FALSE;                 // Pr-set result is fail

    SET_MASK(OW_CTRL, OW_RST);      // start reset

    Enable_ETimer_T(5);             // To enable 5ms time-out timer

    while(!TF1)     				// No overflow, no time out
    {    
        if(IS_MASK_SET(OW_STS, OW_DONE))    // One-Wire Done 
        {
            SET_MASK(OW_STS, OW_DONE);      // Write clear
            result = TRUE;          		// return true
            break;
        }
        else if(IS_MASK_SET(OW_STS, OWLOW_ERR))
        {
            SET_MASK(OW_STS, OWLOW_ERR);    // Write clear
            break;
        }
        else if(IS_MASK_SET(OW_STS, OWHIGH_ERR))
        {
            SET_MASK(OW_STS, OWHIGH_ERR);   // Write clear
            break;
        }
    }

    Stop_ETimer();
    return(result);                 // return result
}

//*****************************************************************************
// 
// Write one byte to device.
//
//  parameter :
//      00h ~ FFh
//
//  return :
//      none
//
//*****************************************************************************
BYTE HW_OW_Device_WriteByte(BYTE writedata)
{
    BYTE result;
    result = FALSE;

    CLEAR_MASK(OW_MOD, OBMOD);
    OW_DATA = writedata;
    SET_MASK(OW_CTRL, OW_WR);

    Enable_ETimer_T(5);             		// To enable 5ms time-out timer

    while(!TF1)     						// No overflow, no time out
    {    
        if(IS_MASK_SET(OW_STS, OW_DONE))    // One-Wire Done 
        {
            SET_MASK(OW_STS, OW_DONE);      // Write clear
            result = TRUE;          		// return true
            break;
        }
        else if(IS_MASK_SET(OW_STS, OWLOW_ERR))
        {
            SET_MASK(OW_STS, OWLOW_ERR);    // Write clear
            break;
        }
        else if(IS_MASK_SET(OW_STS, OWHIGH_ERR))
        {
            SET_MASK(OW_STS, OWHIGH_ERR);   // Write clear
            break;
        }
    }

    Stop_ETimer();
    return(result);
}

//*****************************************************************************
// 
// Read one byte from device.
//
//  parameter :
//      none
//
//  return :
//      00h ~ FFh
//
//*****************************************************************************
BYTE HW_OW_Device_ReadByte(void)
{
    BYTE result;
    result = 0xFF;

    CLEAR_MASK(OW_MOD, OBMOD);
    SET_MASK(OW_CTRL, OW_RD);

    Enable_ETimer_T(5);             		// To enable 5ms time-out timer

    while(!TF1)     						// No overflow, no time out
    {    
        if(IS_MASK_SET(OW_STS, OW_DONE))    // One-Wire Done 
        {
            SET_MASK(OW_STS, OW_DONE);      // Write clear
            result = OW_DATA;               // return true
            break;
        }
        else if(IS_MASK_SET(OW_STS, OWLOW_ERR))
        {
            SET_MASK(OW_STS, OWLOW_ERR);    // Write clear
            break;
        }
        else if(IS_MASK_SET(OW_STS, OWHIGH_ERR))
        {
            SET_MASK(OW_STS, OWHIGH_ERR);   // Write clear
            break;
        }
    }

    Stop_ETimer();
    return(result);
}
#endif
