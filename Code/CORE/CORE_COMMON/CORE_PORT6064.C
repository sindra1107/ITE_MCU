/*-----------------------------------------------------------------------------
 * TITLE: CORE_PORT6064.C - Standard 8042 Keyboard Controller Commands
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------
// Process Command/Data received from System via the KBC interface
//-----------------------------------------------------------------------
void service_pci1(void)
{
    if ( IS_MASK_CLEAR(KBHISR,IBF) )  
	{	
		return;
    }

    if ( KBHISR & C_D )   			// command
	{
        KBHIStep = 0;   			// command start
       	KbdNeedResponseFlag = 0;
 		KBHICmd  = KBHIDIR;
        
        Core_64Port(KBHICmd);
        Hook_64Port(KBHICmd);
 	    if ( KbdNeedResponseFlag ) 
	    {
		    KbdNeedResponseFlag = 0;
		    KBC_DataToHost(KBHIReponse);
        }
	}
    else        					// data
    {
        KBHIData  = KBHIDIR;
	    
	    if(FastA20)
	    {
		    if((KBHIData&0x02)!= 0x00)
		    {
  			    Hook_A20ON();
		    }
		    else
		    {
    		    Hook_A20OFF();
		    }
		    FastA20=0;
		    KBHIStep = 0;
	    }
        else
        {
       	    if (KBHIStep!=0x00 )     	// if need data
    	    {
        	    Core_60Port(KBHICmd);
                Hook_60Port(KBHICmd);
			    KBHIStep --;
        	    if (KbdNeedResponseFlag) 
			    {
				    KbdNeedResponseFlag = 0;
				    KBC_DataToHost(KBHIReponse);
        	    }
     	    }
  		    else
    	    {
    		    Cmd_AE();   				// Enable auxiliary keyboard.
    		
    	        #if PS2_KBCMD
                    #ifdef UART_Debug
                        printf("\nKB CMD : 0X%bX\n",KBHIData);
                    #endif    
                #endif
            
     		    KeyboardCmd(KBHIData);		// Keyboard command
     	    }
	    }
    }

    EnableKBCIBFInt();          // enable interrupt again
}

//-----------------------------------------------------------------------
// Handle 64 port command 2x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command 20 - Read command byte
//-----------------------------------------------------------------------
void Cmd_20(void)	
{
	ResponseKBData(Ccb42);
}

//-----------------------------------------------------------------------
// Handle 64 port command 3x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command 33 - Send Security Code On byte to host
//-----------------------------------------------------------------------
void Cmd_33(void)	
{
	ResponseKBData(Pass_On);
}

//-----------------------------------------------------------------------
// Handle command 34 - Send Security Code Off byte to host
//-----------------------------------------------------------------------
void Cmd_34(void)	
{
	ResponseKBData(Pass_Off);
}

//-----------------------------------------------------------------------
// Handle command 36 - Send Reject make code 1 to host
//----------------------------------------------------------------------- 
void Cmd_36(void)
{
	ResponseKBData(Pass_Make1);
}

//-----------------------------------------------------------------------
// Handle command 37 - Send Reject make code 2 to host
//----------------------------------------------------------------------- 
void Cmd_37(void)
{
	ResponseKBData(Pass_Make2);
}

//-----------------------------------------------------------------------
// Handle 64 port command 6x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command 60 - Write command byte to KBC
//-----------------------------------------------------------------------
void Cmd_60(void)	
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle 64 port command 7x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command 73 - Write security Code On byte. 
//-----------------------------------------------------------------------
void Cmd_73(void)	
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command 74 - Write security Code Off byte. 
//-----------------------------------------------------------------------
void Cmd_74(void)	
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command 76 - Write Password Code Discard 1
//-----------------------------------------------------------------------
void Cmd_76(void)
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command 77 - Write Password Code Discard 2
//-----------------------------------------------------------------------
void Cmd_77(void)
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle 64 port command 9x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command 90 - 
//-----------------------------------------------------------------------
void Cmd_90(void)	
{
	SetHandleCmdData(1);
}	

//-----------------------------------------------------------------------
// Handle command 91 - 
//-----------------------------------------------------------------------
void Cmd_91(void)	
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command 92 - 
//-----------------------------------------------------------------------
void Cmd_92(void)	
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command 93 - 
//-----------------------------------------------------------------------
void Cmd_93(void)	
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle 64 port command Ax.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command A4 - Test Password Installed
// Return: data to send to HOST (FA or F1)
//-----------------------------------------------------------------------
void Cmd_A4(void)	
{
    if (Flag.PASS_READY) 
	{
       	ResponseKBData(0xFA);	// Return FA if password is loaded 
    }
    else 
	{
       	ResponseKBData(0xF1);	// Return F1 if password not loaded 
    }
}

//-----------------------------------------------------------------------
// Handle command A5 - Load Password
//----------------------------------------------------------------------- 
void Cmd_A5(void)
{
	Tmp_Load = 0x00;
	SetHandleCmdData(8);
}

//-----------------------------------------------------------------------
// Handle command A6 - Enable Password
//-----------------------------------------------------------------------
void Cmd_A6(void)
{
    if (Flag.PASS_READY)			// At this point, a password is loaded.
    {   							// Enable inhibit switch      
        Gen_Info_PASS_ENABLE = 1; 	// Enable password 
        Pass_Buff_Idx = 0;        	// Clear password buffer index 
        Flag.SCAN_INH = 0;     		// Clear internal keyboard inhibit 
		ResponseKBData(Pass_On);	
    }
    else
    {   							// At this point, a password is not loaded.
    	ResponseKBData(0x00);	
    } 
}

//-----------------------------------------------------------------------
// Handle command A7 - Disable Aux Device Interface
//-----------------------------------------------------------------------
void Cmd_A7(void)
{
	Ccb42_DISAB_AUX = 1;   // Disable auxiliary device (mouse)	
}

//-----------------------------------------------------------------------
// Handle command A8 - Enable Auxiliary Device Interface
//-----------------------------------------------------------------------
void Cmd_A8(void)
{
	Ccb42_DISAB_AUX = 0; 	// Enable aux device (mouse) 
}

//-----------------------------------------------------------------------
// Handle command A9 - Test Aux Device Interface
// Returns: test error code:
//             0 = no error
//             1 = Clock line stuck low
//             2 = Clock line stuck high
//             3 = Data line stuck low
//             4 = Data line stuck high
//-----------------------------------------------------------------------
void Cmd_A9(void)
{
    MULPX_Multiplex = 0;
	ResponseKBData(0x00);
}

//-----------------------------------------------------------------------
// Handle command AA - Self Test
// Returns: 0x55 to signify that the test passed
//-----------------------------------------------------------------------
void Cmd_AA(void)
{
    #if TouchPad_only
        #ifdef ITE_EVBoard
        ScanAUXDevice(ScanAllPS2Channel);   // Scan all PS2 channels
        #else
        ScanAUXDevice(ScanMouseChannel);    // Scan Mouse channel
        #endif
    #else
    ScanAUXDevice(ScanAllPS2Channel);   // Scan all PS2 channels
    #endif
    
    MULPX_Multiplex = 0;		// Dino MUX ps2

    Data_To_Host(0x55 );
    //KBC_DataToHost(0x55);
}

//-----------------------------------------------------------------------
// Handle command AB - Test Keyboard Interface
// Returns: test error code:
//             0 = no error
//             1 = Clock line stuck low
//             2 = Clock line stuck high
//             3 = Data line stuck low
//             4 = Data line stuck high
//-----------------------------------------------------------------------
void Cmd_AB(void)
{
	ResponseKBData(0x00);
}

//-----------------------------------------------------------------------
// Handle command AC - Diagnostic Dump
//-----------------------------------------------------------------------
void Cmd_AC(void)	
{
   	//Kbd_Response = respCMD_AC;// Send multibyte sequence.
   	//Tmp_Byte[0] = 0;			// Tmp_Byte[0] will be used as the index for data.
}

//-----------------------------------------------------------------------
// Handle command AD - Disable Keyboard Interface
//-----------------------------------------------------------------------
void Cmd_AD(void)
{
    Ccb42_DISAB_KEY = 1;   		// Disable auxiliary keyboard.
    Flag.SCAN_INH = 1;         	// Inhibit scanner (internal keyboard).
    Lock_Scan();              	// Lock scanner. 
    //Load_Timer_B();			// Start inhibit delay timer. 
}

//-----------------------------------------------------------------------
// Handle command AE - Enable Keyboard Interface
//-----------------------------------------------------------------------
void Cmd_AE(void)
{
   	Ccb42_DISAB_KEY = 0;   		// Enable auxiliary keyboard.
   	Flag.SCAN_INH = 0;  		// Enable scanner (internal keyboard).
}

//-----------------------------------------------------------------------
// Handle command AF - 
//-----------------------------------------------------------------------
void Cmd_AF(void)
{

}

//-----------------------------------------------------------------------
// Handle 64 port command Cx.
// Return: Byte from input port.
//     Bit 7 = Keyboard not inhibited via switch.
//     Bit 6 = Monochrome adapter (0 = Color/Graphics adapter).
//     Bit 5 = Manufacturing jumper not installed.
//     Bit 4 = Enable 2nd 256K of system board RAM.
//     Bit 3 =
//     Bit 2 =
//     Bit 1 = Auxiliary data in line (PS/2 only).
//     Bit 0 = Keyboard data in line (PS/2 only).
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command C0 - Emulate reading the 8042 Input port and send data 
//					 	to the system
//-----------------------------------------------------------------------
void Cmd_C0(void)	
{ 
	ResponseKBData(0xBF);	//  Just return the compatibility value for now. //return (PCIN | 0x1F);
}

//-----------------------------------------------------------------------
// Handle 64 port command Dx.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command D0 - Send 8042 Output port value to the system 
//						(emulates data since there¡¦s no real Output port)
//-----------------------------------------------------------------------
void Cmd_D0(void)	
{
	ResponseKBData(Read_Output_Port_2());
}

//-----------------------------------------------------------------------
// Handle command D1 - Only set/reset GateA20 line based on the System Data bit1.
//-----------------------------------------------------------------------
void Cmd_D1(void)	
{	
	FastA20=1;
	//SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command D2 - Send data to the system as if it came from the keyboard.
//-----------------------------------------------------------------------
void Cmd_D2(void)	
{
    TR1 = 0;                 	// Disable timer1
    ET1 = 0;                  	// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_20ms>>8;        // Set timer1 counter 20ms
    TL1 = Timer_20ms;           // Set timer1 counter 20ms
    TF1 = 0;                  	// Clear overflow flag
    TR1 = 1;                 	// Enable timer1

	while (!TF1)
	{
  	    if(IS_MASK_SET(KBHISR,IBF))
  		{
            if(IS_MASK_CLEAR(KBHISR,C_D))   // Data Port
            {
                KBHIData = KBHIDIR;
                Data_To_Host(KBHIData);
            }
            TR1 = 0;            // Disable timer 1
            TF1 = 0;		    // clear overflow flag
            ET1 = 1;		    // Enable timer1 interrupt
            return;
  		}
    }

    TR1 = 0;                    // Disable timer 1
    TF1 = 0;			        // clear overflow flag
    ET1 = 1;			        // Enable timer1 interrupt
    SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command D3 - Send data to the system as if it came from the auxiliary device.
//-----------------------------------------------------------------------
void Cmd_D3(void)	
{
    TR1 = 0;                 	// Disable timer1
    ET1 = 0;                  	// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_20ms>>8;        // Set timer1 counter 20ms
    TL1 = Timer_20ms;           // Set timer1 counter 20ms
    TF1 = 0;                  	// Clear overflow flag
    TR1 = 1;                 	// Enable timer1

	while (!TF1)
	{
  	    if(IS_MASK_SET(KBHISR,IBF))
  		{
            if(IS_MASK_CLEAR(KBHISR,C_D))   // Data Port
            {
                KBHIData = KBHIDIR;
                #if MultiplexedModes
	                Aux_Data_To_Host(CheckAuxMux());
                #else
                    Aux_Data_To_Host(KBHIData);
                #endif
            }
            TR1 = 0;            // Disable timer 1
            TF1 = 0;		    // clear overflow flag
            ET1 = 1;		    // Enable timer1 interrupt
            return;
  		}
    }

    TR1 = 0;                    // Disable timer 1
    TF1 = 0;			        // clear overflow flag
    ET1 = 1;			        // Enable timer1 interrupt
    SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command D4 - Output next received byte of data from system to auxiliary device.
//-----------------------------------------------------------------------
void Cmd_D4(void)	
{
	SetHandleCmdData(1);
	MULPX_Multiplex = 0;		// Dino MUX ps2
}

//-----------------------------------------------------------------------
// Handle 64 port command Ex.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Handle command E0 - Reports the state of the test inputs
//-----------------------------------------------------------------------
void Cmd_E0(void)				
{
	ResponseKBData(0x00);
}

//-----------------------------------------------------------------------
// Handle 64 port command Fx.
//-----------------------------------------------------------------------
void Cmd_FX(void)
{
	if ((KBHICmd % 2)==0x00)    // Even command
    {
        //CLEAR_MASK(KBHISR,SYSF);	
		Hook_A20ON();
		Hook_KBRSTON();
		//Microsecond_Delay(64);  // Delay. 
	    WNCKR = 0x00;           // Delay 15.26 us
        WNCKR = 0x00;           // Delay 15.26 us
        WNCKR = 0x00;           // Delay 15.26 us
        WNCKR = 0x00;           // Delay 15.26 us
        WNCKR = 0x00;           // Delay 15.26 us
		Hook_KBRSTOFF();
    }							// Odd command do no thing	
}

//-----------------------------------------------------------------------
// Handle 60 port data 6x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Process command data 60 - Write command byte
//-----------------------------------------------------------------------
void Cmd_60Data(void)
{
	Ccb42 = KBHIData;   // Write the data.
	//if (Ext_Cb0_PS2_AT)	// Reconfigure variables/registers that are dependent on Command Byte value.
  	//{   
   	//	if (Ccb42_DISAB_AUX)	// For PS/2 style 8042 interface. 	
	//	{
    //      	Cmd_A7();	// Disable aux device interface.
    // 	}
   //  	else 
	//	{
    //   		Cmd_A8();	// Enable Auxiliary Device Interface.
    // 	}
 	//}

	if (Ccb42_DISAB_KEY) 
	{
    	Cmd_AD();		// Disable keyboard interface. 
	}
	else 
	{
     	Cmd_AE(); 		// Enable keyboard interface. 
 	}

            
	if (Ccb42_SYS_FLAG)	// Put system flag bit in Status Reg.
  		SET_MASK(KBHISR,SYSF);
  	else
		CLEAR_MASK(KBHISR,SYSF);
}

//-----------------------------------------------------------------------
// Handle 60 port data 7x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Process command data 71 - Write Security Code On byte
//-----------------------------------------------------------------------
void Cmd_73Data(void)
{
 	Pass_On = KBHIData;   	// Write the data.
}

//-----------------------------------------------------------------------
// Process command data 74 - Write Security Code Off byte
//-----------------------------------------------------------------------
void Cmd_74Data(void)
{
 	Pass_Off = KBHIData;   	// Write the data.
}

//-----------------------------------------------------------------------
// Process command data 76 - Reject make code 1
//-----------------------------------------------------------------------
void Cmd_76Data(void)
{
 	Pass_Make1 = KBHIData;	// Write the data.
}

//-----------------------------------------------------------------------
// Process command data 77 - Reject make code 2
//-----------------------------------------------------------------------
void Cmd_77Data(void)
{
 	Pass_Make2 = KBHIData;	// Write the data.
}

// Dino MUX ps2 -->
//-----------------------------------------------------------------------
// Handle 60 port data 9x.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Process command data 90 - MUX AUX port #0
//-----------------------------------------------------------------------
void Cmd_90Data(void)			// always send timeout error to system 
{
    if(PS2_MSCMD)
    {
        #ifdef UART_Debug
            printf("\nMS 90Port CMD : 0X%bX\n",KBHIData);
        #endif
    }
    
    #if !TouchPad_only
        if(ECSendtoAUXFlag)
        {
            if(WaitECSend2PortACK(AUX_SCAN_INDEX)==0x01)
            {
                AUXDevicePlugOutClearVariables();
            }
        }

        SetPS2SkipScanTime(100);    // 1Sec
    #endif
    
    if(KBHIData==0xFF)
    {
        ScanAUXDevice(ScanAllPS2Channel);
    }
        
    KBHISR = 0x24;				    // set error bit and AUX bit, source bits is 00
    KBHICR &= 0xFC;
    if ( Ccb42_INTR_AUX )		    // If AUX IRQ bit of command is present	
    {
        SET_MASK(KBHICR,OBFMIE);    // Enable IRQ
    }

    DelayXms(5);				    // Emulate transmission delay times 
    KBHIMDOR = 0xFC;			    // timeout error  

    Hook_Mouse_90Cmd(KBHIData);
}

//-----------------------------------------------------------------------
// Process command data 91 - MUX AUX port #1 internal mouse
//-----------------------------------------------------------------------
void Cmd_91Data(void)
{
    if(PS2_MSCMD)
    {
        #ifdef UART_Debug
            printf("\nMS 91Port CMD : 0X%bX\n",KBHIData);
        #endif
    }
    
    if(IS_MASK_SET(AuxFlags[0], DEVICE_IS_MOUSE))
    {
        SendCmdtoMUX(0);		    // Send command to channel 0 mouse
    }
    else
    {
	    KBHISR = 0x40;	
	    DelayXms(5);				// Emulate transmission delay times 
	    KBHIMDOR = 0xFC;			// timeout error
    }

    Hook_Mouse_91Cmd(KBHIData);
}

//-----------------------------------------------------------------------
// Process command data 92 - MUX AUX port #2
//-----------------------------------------------------------------------
void Cmd_92Data(void)
{
    if(PS2_MSCMD)
    {
        #ifdef UART_Debug
            printf("\nMS 92Port CMD : 0X%bX\n",KBHIData);
        #endif
    }
    
    if(IS_MASK_SET(AuxFlags[1], DEVICE_IS_MOUSE))
    {
	    SendCmdtoMUX(1);		    // Send command to channel 0 mouse
    }
    else
    {
        KBHISR = 0x80;	
	    DelayXms(5);				// Emulate transmission delay times 
        KBHIMDOR = 0xFC;			// timeout error
    }

    Hook_Mouse_92Cmd(KBHIData);
}

//-----------------------------------------------------------------------
// Process command data 93 - MUX AUX port #3 external mouse
//-----------------------------------------------------------------------
void Cmd_93Data(void)
{
    if(PS2_MSCMD)
    {
        #ifdef UART_Debug
            printf("\nMS 93Port CMD : 0X%bX\n",KBHIData);
        #endif
    }
    
    if(IS_MASK_SET(AuxFlags[2], DEVICE_IS_MOUSE))
    {
	    SendCmdtoMUX(2);	        // Send command to channel 2 mouse
    }
    else
    {
	    KBHISR = 0xC0;				// source bits is 11
	    DelayXms(5);				// Emulate transmission delay times 
	    KBHIMDOR = 0xFC;
    }

    Hook_Mouse_93Cmd(KBHIData);
}
// Dino MUX ps2 <--

//-----------------------------------------------------------------------
// Handle 60 port data Ax.
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Process command data A5 - Load Password
//-----------------------------------------------------------------------
void Cmd_A5Data(void)
{
	if ((Tmp_Load == 0) && (KBHIData == 0))	// The first byte is NULL 
	{  	 		
 		Flag.PASS_READY = 0; 	// clear password ready flag and exit 
              					// Cmd_Byte has already been set to 0.  So the code will
              					// NOT wait for next byte 
	}
	else
	{
     	if (Tmp_Load < 8)		// PASS_SIZE = 8
     	{   					// If there is room in the buffer
      		Pass_Buff[Tmp_Load] = KBHIData;   // Store scan code
          	Tmp_Load++; 		// Increment password buffer index
      	}
     	//Cmd_Byte = 0xA5;  	// Set to keep waiting for next byte
   		if (KBHIData == 0)		// The last byte (null terminated string) has been stored
      	{   
        	//Cmd_Byte = 0;     // Clear out the command byte.
         	Flag.PASS_READY = 1; // Set password ready bit.
    	}
	} 
}

//-----------------------------------------------------------------------
// Handle 60 port data Dx.
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Process command data D1 - set/reset GateA20 line based on the System Data bit1.
//-----------------------------------------------------------------------
void Cmd_D1Data(void)	
{
	if ( (KBHIData & 0x02) != 0x00)
	{
    	Hook_A20ON();
	}
	else
	{
     	Hook_A20OFF();
	}
}

//-----------------------------------------------------------------------
// Process command data D2 - Send data back to the system as if it came from the keyboard.
//-----------------------------------------------------------------------
void Cmd_D2Data(void)
{
    Data_To_Host(KBHIData);
}

//-----------------------------------------------------------------------
// Process command data D3 - Send data back to the system as if it came from the auxiliary device.
//-----------------------------------------------------------------------
void Cmd_D3Data(void)				// Dino MUX ps2
{
    #if MultiplexedModes
	    Aux_Data_To_Host(CheckAuxMux());
    #else
        Aux_Data_To_Host(KBHIData);
    #endif
}

//-----------------------------------------------------------------------
// Process command data D4 - Output next received byte of data from system to auxiliary device.
//-----------------------------------------------------------------------
void Cmd_D4Data(void)
{
    if(PS2_MSCMD)
    {
        #ifdef UART_Debug
            printf("\nMS CMD : 0X%bX\n",KBHIData);
        #endif
    }
    if(KBHIData==0xFF)                      // if is reset command
    {
        ScanAUXDevice(ScanMouseChannel);    // Scan mouse channel
    }
              
    if(Main_MOUSE_CHN!=0x00)                // mouse device is attached 
    {
        CLEAR_MASK(AuxFlags[(Main_MOUSE_CHN-1)], DEVICE_NEED_INIT);
        CLEAR_MASK(AuxFlags[(Main_MOUSE_CHN-1)], DEVICE_NEED_CONFIG);
	    SendCmdtoMouse((Main_MOUSE_CHN-1));
    }    
    else
    {
	    DelayXms(20);				    // Emulate transmission delay times 
	    #ifdef Hook_ECACKMouseDriver
        Hook_ECRespondtoMouseDriver(KBHIData);
        #else
	    SendFromAux(0xFC);
        #endif
    }

    Hook_Mouse_D4Cmd(KBHIData);
}

//-----------------------------------------------------------------------
// Handle 60 port data Fx.
//-----------------------------------------------------------------------
void ResponseKBData(BYTE RData)
{
	KBHIReponse = RData;
	KbdNeedResponseFlag = 1;
}

//-----------------------------------------------------------------------
// Handle 60 port data Fx.
//-----------------------------------------------------------------------
void SetHandleCmdData(BYTE step)
{
    KBHIStep = step;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: vKeyboardCmd
 *
 * Passes data sent from the Host (port 60 write) to the keyboard.
 *
 * Input: data = data byte to send
 * ------------------------------------------------------------------------- */
static void KeyboardCmd(BYTE nKB60DAT)
{
    BYTE ack,ack1,ack2,index,cmdbk;

    KBCmdAckByteCunt(0x00);         // New keyboard command, clear ack counter
    ack = 0x00;
    ack1 = 0x00;
    ack2 = 0x00;
    
    //-------------------------------------------------------------------------
    //Keyboard Command Received Data Process
    //-------------------------------------------------------------------------
    if ( KB_Command )
    {
        cmdbk = KB_Command;
        
        switch(KB_Command)
        {
            case 0xED:  /* Update LEDs command. */
                        Led_Data = nKB60DAT;
                        ack = 0xFA;
                        KB_Command = 0x00;
                        OEM_Write_Leds(Led_Data);   //Hook Oem On-board LED control

                        /* Update scanner numlock state. */
                        Scanner_State_NUM_LOCK = Led_Data_NUM;
                        break;
            case 0xF0:  /* Set alternate scan codes. */
                        KB_CodeSet = nKB60DAT;
                        ack = 0xFA;
                        KB_Command = 0x00;
                        break;
            case 0xF3:  /* Set typematic rate/delay. */
                        PS2KB_Typematic = nKB60DAT;
                        Set_Typematic(PS2KB_Typematic);
                        ack = 0xFA;
                        KB_Command = 0x00;
                        break;
            default:    //Unknown command request system resend   
                        ack = 0xFE;         //Resend         
                        //KBCUnProcessCnt++;
                        break;
        }

        if((cmdbk==0xF3)||(cmdbk==0xED))
        {
            KeyboardDriverIn = 1;
        } 
        
        if( Main_KB_CHN ==0x00)             // no any external keyboard
        {
            if(ack != 0x00)                 // if need send ack to host
            {
                KBC_DataToHost(ack);        // send to host
                #if PS2_KBCMD
                    #ifdef UART_Debug
                    printf("EC KB ACK : 0X%bX\n",ack); 
                    #endif
                #endif
            }
        }
        else                                // Send command to external keyboard
        {

            CLEAR_MASK(AuxFlags[(Main_KB_CHN-1)], DEVICE_NEED_INIT);
            CLEAR_MASK(AuxFlags[(Main_KB_CHN-1)], DEVICE_NEED_CONFIG);
            
            KBCmdAckByteCunt(0x01);         // set ec need send one byte to host
            
            if(cmdbk==0xED)
            {
	            Send2Port((Main_KB_CHN-1), (nKB60DAT&0x07), SendCmdToKB);
            }
            else
            {
	            Send2Port((Main_KB_CHN-1), nKB60DAT, SendCmdToKB);
            }

            if((cmdbk==0xF3)||(cmdbk==0xED))
            {
                SetOtherKBNeedUpdataFlag(cmdbk);   
            } 
        }

        Hook_Keyboard_Cmd_Parameter(nKB60DAT);
        return;
    }
    
    //-------------------------------------------------------------------------
    //Keyboard Command Process
    //-------------------------------------------------------------------------
    switch(nKB60DAT)
    {
        KB_Command = 0x00;
        case 0xED:  /* Update LEDs command. */
                    ack = 0xFA;
                    KB_Command = 0xED;
                    break;
        case 0xEC:
                    ack = 0xFA;
                    break;

        case 0xEE:  /* ECHO command. */
                    ack = 0xEE;
                    break;

        case 0xF0:  /* Set alternate scan codes. */
                    ack = 0xFA;
                    KB_Command = 0xF0;
                    break;

        case 0xF2:  /* Read manufacturers ID */
                    ack = 0xFA;
                    ack1 = 0xAB;
                    if( Ccb42_XLATE_PC )
                    {
                        ack2 = 0x83;
                    }
                    else
                    {
                        ack2 = 0x41;
                    }
                    break;

        case 0xF3:  /* Set typematic rate/delay. */
                    ack = 0xFA;
                    KB_Command = 0xF3;
                    break;

        case 0xF4:  /* Enable scanning. */
                    KeyboardDriverIn = 1;
                    Clear_Key();
                    ack = 0xFA;
                    break;

        case 0xF5:  /* Default disable. */
                    KeyboardDriverIn = 0;
                    Clear_Key();
                    Clear_Typematic();
                    ack = 0xFA;
                    break;

        case 0xF6:  /* Set defaults. */
                    Clear_Key();
                    Clear_Typematic();
                    ack = 0xFA;
                    break;
        case 0xF7:
        case 0xF8:
        case 0xF9:
        case 0xFA:
        case 0xFB:
                    ack = 0xFA;
                    break;

        case 0xFF:  /* Reset keyboard. */
                    KeyboardDriverIn = 0;
                    ScanAUXDevice(ScanKeyboardChannel); // Scan keyboard channel    
                    Clear_Key();
                    Clear_Typematic();
                    Scanner_State = 0;
                    Clear_Fn_Keys();
                    ack = 0xFA;
                    ack1 = 0xAA;
                    
                    for(index=0x00; index<3; index++)
                    {
                        if((Main_KB_CHN-1)!=index)
                        {
                            if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_KEYBOARD))
                            {
                                AuxFlags[index] = 0x00;
                            }
                        }
                    }
                    
                    #if KB_FnStickKey
                    FnStickKey = 0;
                    #endif
                    
                    break;

        default:    //Unknown command request system resend
                    ack = 0xFE;
                    //KBCUnProcessCnt++;
                    //KBCUnProcessRec = nKB60DAT;
                    break;

    }

    if( Main_KB_CHN ==0x00)             // no any external keyboard
    {
        KBCmdAckByteCunt(0x00);
        
        if(ack != 0x00)
        {
            KBC_DataToHost(ack);
            
            #if PS2_KBCMD
                #ifdef UART_Debug
                printf("EC KB ACK : 0X%bX\n",ack);  
                #endif
            #endif
            
            if(ack1 != 0x00)
            {
                KBC_DataPending(ack1);
                
                #if PS2_KBCMD
                    #ifdef UART_Debug
                    printf("EC KB ACK : 0X%bX\n",ack1);
                    #endif
                #endif
                
                if(ack2 != 0x00)
                {
                    KBC_DataPending(ack2);
                    
                    #if PS2_KBCMD
                        #ifdef UART_Debug
                        printf("EC KB ACK : 0X%bX\n",ack2);   
                        #endif
                    #endif 
                }
            }
        }
    }
    else                                    // Send command to external keyboard
    {
        CLEAR_MASK(AuxFlags[(Main_KB_CHN-1)], DEVICE_NEED_INIT);
        CLEAR_MASK(AuxFlags[(Main_KB_CHN-1)], DEVICE_NEED_CONFIG);
        
        if(nKB60DAT==0xFF)                  // reset command
        {
            KBCmdAckByteCunt(0x02);
        }
        else                             
        {
            if(nKB60DAT==0xF2)              // read keyboard ID command
            {
                KBCmdAckByteCunt(0x03);
            }
            else if((nKB60DAT==0xF3)||(nKB60DAT==0xED))
            {
                KBCmdAckByteCunt(0x02);
            }
            else                            // other
            {
                KBCmdAckByteCunt(0x01);
            }
        }

	    Send2Port((Main_KB_CHN-1), nKB60DAT, SendCmdToKB);

        if((nKB60DAT==0xF4)||(nKB60DAT==0xF5))
        {
            SetOtherKBNeedUpdataFlag(nKB60DAT);   
        }  
    }

    Hook_Keyboard_Cmd(nKB60DAT);
}


/* ----------------------------------------------------------------------------
 * FUNCTION: Set_Overlay_Mask
 *
 * Set the overlay state in the scanner_state variable and
 * set the led numlock and/or overlay bits for the LED data.
 *
 * Input: data = current LED data
 *        bit_state = 1 to set overlay/numlock bits
 *                  = 0 to clear overlay/numlock bits
 *
 * Return: updated LED data (num lock and overlay state updated)
 * ------------------------------------------------------------------------- */
BBYTE Set_Overlay_Mask(BBYTE data_byte, FLAG bit_state)
{
    BITS_8 temp;
    temp.byte = data_byte;

    if (Led_Ctrl_NUM) {
        temp.fbit.NUM = bit_state;
    }

    if (Led_Ctrl_OVL) {
        temp.fbit.OVL = bit_state;
    }

    data_byte = temp.byte;
    Scanner_State_NUM_LOCK = bit_state;
    //Ext_Cb3_OVL_STATE = bit_state;

    return(data_byte);
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Read_Input_Port_1
 *
 * Read 8042 Input Port 1 and return its contents.
 *
 * Return: Byte from input port.
 *     Bit 7 = Keyboard not inhibited via switch.
 *     Bit 6 = Monochrome adapter (0 = Color/Graphics adapter).
 *     Bit 5 = Manufacturing jumper not installed.
 *     Bit 4 = Enable 2nd 256K of system board RAM.
 *     Bit 3 =
 *     Bit 2 =
 *     Bit 1 = Auxiliary data in line (PS/2 only).
 *     Bit 0 = Keyboard data in line (PS/2 only).
 * ------------------------------------------------------------------------- */
//BYTE Read_Input_Port_1(void)
//{
//   return(0xBF);   //  Just return the compatibility value for now. //return (PCIN | 0x1F);
//}


/* ----------------------------------------------------------------------------
 * FUNCTION: Read_Output_Port_2
 *
 * Read 8042 output port 2.
 *
 * Return: Byte from output port.
 *     Bit 7 = Keyboard data output line (inverted on PS/2).
 *     Bit 6 = Keyboard clock output line.
 *     Bit 5 = Input buffer empty (auxiliary interrupt IRQ12 on PS/2).
 *     Bit 4 = Output buffer full (Generates IRQ1).
 *     Bit 3 = Reserved (inverted auxiliary clock output line on PS/2).
 *     Bit 2 = Reserved (inverted auxiliary data output line on PS/2).
 *     Bit 1 = Gate A20.
 *     Bit 0 = System reset.
 * ------------------------------------------------------------------------- */
BYTE Read_Output_Port_2(void)
{
#if 1
    BYTE p2byte;

    /* "data" will hold bits read from different inputs.
        Start with bit 0 set and set bits 2 and 3 for AT mode.
        If PS2 mode is being used, bits 2 and 3 will be changed. */
    p2byte = (1 << 3) | (1 << 2) | (1 << 0);

    //if (Ext_Cb0_PS2_AT)
    //{   /* If PS2 mode is enabled */
        /* Invert auxiliary keyboard data line (bit 7) and clear bits 2 and 3.
           (Since bits 2 and 3 were set before, they can be cleared by inverting.) */
    //    p2byte^= 0x8C;
    //}

    return (p2byte);
#else

    BYTE data_byte;

    /* "data" will hold bits read from different inputs.
       Start with bit 0 set and set bits 2 and 3 for AT mode.
       If PS2 mode is being used, bits 2 and 3 will be changed. */
    data_byte = (1 << 3) | (1 << 2) | (1 << 0);

    /* Put Gate A20 bit value into bit 1. */

    if (Ext_Cb0_PS2_AT)
    {   /* PS/2 mode is enabled 8/
        /* Invert aux keyboard data line (bit 7) and clear bit[3:2]. (Since
           bits 2 and 3 were set before, they can be cleared by inverting.) */
        data_byte ^= 0x8C;

        /* Put inverted auxiliary device (mouse) clock line in bit 3. */

        /* Put inverted auxiliary device (mouse) data line in bit 2. */
    } /* if (Ext_Cb0_PS2_AT) */

    return (data_byte);
#endif
}

//----------------------------------------------------------------------------
// The function of processing 60 port
//----------------------------------------------------------------------------
void Core_60Port(BYTE KBHIData)
{
    switch(KBHIData)
    {
        case 0x60:
        Cmd_60Data();
        break;

        case 0x73:
        Cmd_73Data();
        break;

        case 0x74:
        Cmd_74Data();
        break;

        case 0x76:
        Cmd_76Data();
        break;

        case 0x77:
        Cmd_77Data();
        break;

        case 0x90:
        Cmd_90Data();
        break;

        case 0x91:
        Cmd_91Data();
        break;

        case 0x92:
        Cmd_92Data();
        break;

        case 0x93:
        Cmd_93Data();
        break;

        case 0xA5:
        Cmd_A5Data();
        break;

        case 0xD1:
        Cmd_D1Data();
        break;

        case 0xD2:
        Cmd_D2Data();
        break;

        case 0xD3:
        Cmd_D3Data();
        break;

        case 0xD4:
        Cmd_D4Data();
        break;

        default:
        break;
    }
}

//----------------------------------------------------------------------------
// The function of processing 64 port
//----------------------------------------------------------------------------
void Core_64Port(BYTE KBHICmd)
{
    switch(KBHICmd)
    {
        case 0x20:
        Cmd_20();
        break;

        case 0x33:
        Cmd_33();
        break;

        case 0x34:
        Cmd_34();
        break;

        case 0x36:
        Cmd_36();
        break;

        case 0x37:
        Cmd_37();
        break;

        case 0x60:
        Cmd_60();
        break;

        case 0x73:
        Cmd_73();
        break;

        case 0x74:
        Cmd_74();
        break;

        case 0x76:
        Cmd_76();
        break;

        case 0x77:
        Cmd_77();
        break;

        case 0x90:
        Cmd_90();
        break;

        case 0x91:
        Cmd_91();
        break;

        case 0x92:
        Cmd_92();
        break;

        case 0x93:
        Cmd_93();
        break;

        case 0xA4:
        Cmd_A4();
        break;

        case 0xA5:
        Cmd_A5();
        break;

        case 0xA6:
        Cmd_A6();
        break;

        case 0xA7:
        Cmd_A7();
        break;

        case 0xA8:
        Cmd_A8();
        break;

        case 0xA9:
        Cmd_A9();
        break;

        case 0xAA:
        Cmd_AA();
        break;

        case 0xAB:
        Cmd_AB();
        break;

        case 0xAC:
        Cmd_AC();
        break;

        case 0xAD:
        Cmd_AD();
        break;

        case 0xAE:
        Cmd_AE();
        break;

        case 0xAF:
        Cmd_AF();
        break;

        case 0xC0:
        Cmd_C0();
        break;

        case 0xD0:
        Cmd_D0();
        break;

        case 0xD1:
        Cmd_D1();
        break;

        case 0xD2:
        Cmd_D2();
        break;

        case 0xD3:
        Cmd_D3();
        break;

        case 0xD4:
        Cmd_D4();
        break;

        case 0xE0:
        Cmd_E0();
        break;

        case 0xF0:
        case 0xF1:
        case 0xF2:
        case 0xF3:
        case 0xF4:
        case 0xF5:
        case 0xF6:
        case 0xF7:
        case 0xF8:
        case 0xF9:
        case 0xFA:
        case 0xFB:
        case 0xFC:
        case 0xFD:
        case 0xFE:
        case 0xFF:
        Cmd_FX();
        break;
        
        default:
        break;
    }
}