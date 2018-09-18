/*-----------------------------------------------------------------------------
 * Filename: CORE_PS2.C - PS/2 devices handler
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of ITE Tech. Inc.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

const sPS2Struct code asPS2Struct[] = 
{
 	{ &PSCTL1, &PSINT1, &PSSTS1,	&PSDAT1,	&IER2,	&ISR2,	Int_PS2_0	},
	{ &PSCTL2, &PSINT2, &PSSTS2,	&PSDAT2,	&IER2,	&ISR2,	Int_PS2_1	},
	{ &PSCTL3, &PSINT3, &PSSTS3,	&PSDAT3,	&IER2,	&ISR2,	Int_PS2_2	}
};

/* ----------------------------------------------------------------------------
 * FUNCTION: Service_Send_PS2
 *
 * ------------------------------------------------------------------------- */
void service_PS2_data(void)
{
    BYTE index;
	
    if(IS_MASK_SET(KBHISR,OBF)||IS_MASK_SET(KBHISR,IBF))	        // Dino 0202
    //if(IS_MASK_SET(KBHISR,OBF))
	{
        SetPS2InhibitTime(InactiveTime);
		return;
	}

	if(TPACKCounter!=0x00)
	{
		TPACKCounter--;
	}
	else
	{
        #ifdef Hook_Func_DisableTP  // For internal TB disable
        if(Ccb42_DISAB_AUX || (Hook_DisableInternalTB()==InternalTB_Disable))
        #else
		if(Ccb42_DISAB_AUX)		
        #endif
		{
            SetPS2InhibitTime(InactiveTime);
			return;
		}
	}

	SendFromAux(MousePendingBuf);

    if(MULPX_Multiplex)
    {
        PS2Deviceactive();          // Enable all ps2 interface
        SetPS2SkipScanTime(MSSkipScanAUXTime);
    }
    else
    {
        for(index=0x00;index<3;index++)     // Check any keyboard is attached?
        {
            if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_KEYBOARD))
            {
                *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
                SET_MASK(*asPS2Struct[index].ps2ier, asPS2Struct[index].ctrlbit); 
            }
        }
        for(index=0x00;index<3;index++)     // Check any keyboard is attached?
        {
            if(index == AUXPortNum)
            {
                *asPS2Struct[AUXPortNum].ps2ctrl=PS2_ReceiveMode;
		        SET_MASK(*asPS2Struct[AUXPortNum].ps2ier, asPS2Struct[AUXPortNum].ctrlbit);
            }
        }  

        SetPS2InhibitTime(InactiveTime);
    }
    ResetMSPendingData();
}

//-----------------------------------------------------------------
// Send data from aux mouse 
//-----------------------------------------------------------------
void SendFromAux(BYTE auxdata)
{
    KBHISR &= 0x0F;

	if(MULPX_Multiplex)
	{
		if(AUXPortNum==0x00)
		{
			KBHISR = 0x40;				// source bits is 01
		}
		else if(AUXPortNum==0x01)
		{
			KBHISR = 0x80;				// source bits is 10
		}
        else if(AUXPortNum==0x02)
        {
			KBHISR = 0xC0;				// source bits is 11
		}
		CLEAR_MASK(KBHISR,BIT2);	    // clear error bit 
	}

	SET_MASK(KBHISR,AOBF);			    // set AUX bit
	KBHICR &= 0xFC;
    if ( Ccb42_INTR_AUX )
    {
       	SET_MASK(KBHICR,OBFMIE);
    }

	KBHIMDOR = auxdata;

	if(PS2_MSCMD)
	{   
        #ifdef UART_Debug
            printf("MS Port_%bX ACK : 0X%bX\n",AUXPortNum, auxdata);
        #endif
	}
    
#if PS2_Pack_Debug    
    if(PS_Debug_ECToHost==0xFF)
    {
       PS_Debug_ECToHost = 0x03;
    }
    else
    {
        PS_Debug_ECToHost++;
        if(PS_Debug_ECToHost>3)
        {
            PS_Debug_ECToHost = 0x01;
        }
    }
#endif
}

//-----------------------------------------------------------------
// 
//-----------------------------------------------------------------
void SetPS2InhibitTime(BYTE time)
{
    if(AUXInactiveCounter<time)
    {
        AUXInactiveCounter = time;
    }
}

//-----------------------------------------------------------------
// 
//-----------------------------------------------------------------
void SetPS2SkipScanTime(BYTE time)
{
    if(SKIP_AUX_SCAN_CUNT<time)
    {
        SKIP_AUX_SCAN_CUNT = time;
    }
}

//-----------------------------------------------------------------
// Process mouse data from ps2 interface
//-----------------------------------------------------------------
void ProcessMouseData(BYTE channel)
{
    BYTE index;
    
#if PS2_Pack_Debug                          // Debug only
    if(PS_Debug_ECToHost==0xFF)
    {
       PS_Debug_DeviceToEC = 0x03;
    }
    else
    {
        PS_Debug_DeviceToEC++;
        if(PS_Debug_DeviceToEC>3)
        {
            PS_Debug_DeviceToEC = 0x01;
        }
    }
#endif

    if(MS_ID_CUNT!=0x00)                    // Save mouse driver type(3bytes, 4bytes, or 5bytes)
    {
        if(--MS_ID_CUNT==0x00)
        {
            if(PS2PortxData[channel]==0x00||
                PS2PortxData[channel]==0x03||
                 PS2PortxData[channel]==0x04)
            {
                MS_DRIVER_TYPE = PS2PortxData[channel];
            }
        }
    }

    #ifdef Hook_Func_DisableTP     // For internal TB disable
    if(IS_MASK_SET(KBHISR,OBF)||IS_MASK_SET(KBHISR,IBF)||(Ccb42_DISAB_AUX)||(Hook_DisableInternalTB()==InternalTB_Disable))
    #else
    if(IS_MASK_SET(KBHISR,OBF)||IS_MASK_SET(KBHISR,IBF)||(Ccb42_DISAB_AUX))
    #endif
    //if(IS_MASK_SET(KBHISR,OBF)||(Ccb42_DISAB_AUX))
    {	
        AUXPortNum = channel;
	    MousePendingBuf=PS2PortxData[channel];
	    MSPending = 0x33;
    }
    else
    {
        AUXPortNum = channel;
	    SendFromAux(PS2PortxData[channel]);
	    if(TPACKCounter!=0x00)
	    {
		    TPACKCounter--;
	    }

        if(MULPX_Multiplex)
	    {
            if(!AUXInterfaceBusy)
            {
                PS2Deviceactive();              // Enable all ps2 interface
                SetPS2SkipScanTime(MSSkipScanAUXTime);
            }
        }
        else
	    {
            if(!AUXInterfaceBusy)
            {
                for(index=0x00;index<3;index++)     // Check any keyboard is attached?
                {
                    if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_KEYBOARD))
                    {
                        *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
                        SET_MASK(*asPS2Struct[index].ps2ier, asPS2Struct[index].ctrlbit); 
                    }
                }
                for(index=0x00;index<3;index++)     // Check any keyboard is attached?
                {
                    if(index == channel)
                    {
                        *asPS2Struct[channel].ps2ctrl=PS2_ReceiveMode;
		                SET_MASK(*asPS2Struct[channel].ps2ier, asPS2Struct[channel].ctrlbit);
                    }
                }
                SetPS2InhibitTime(InactiveTime);
            }
	    }
    }
} 

//-----------------------------------------------------------------
// Process keybaord data from ps2 interface
//-----------------------------------------------------------------
void ProcessKeyboardData(BYTE channel)
{
    BYTE index;
    if(Main_KB_ACK_CUNT!=0x00)
    {
        Main_KB_ACK_CUNT--;

        KBC_DataPending(PS2PortxData[channel]);
        SetServiceSendFlag();
        #if PS2_KBCMD
            #ifdef UART_Debug
            printf("External KB ACK : 0X%bX\n",PS2PortxData[channel]);
            #endif
        #endif
    }
    else
    {
        Buffer_Key(PS2PortxData[channel]);
        SetServiceSendFlag();
    }

    if(Main_KB_ACK_CUNT==0x00)
    {   
        if(MSPending==0x33)             // PS2 data is pending
        {
            if(!AUXInterfaceBusy)       // PS2 interface isn't busy
            {
                *asPS2Struct[channel].ps2ctrl=PS2_ReceiveMode;
                SET_MASK(*asPS2Struct[channel].ps2ier, asPS2Struct[channel].ctrlbit);
                SetPS2InhibitTime(InactiveTime);
            }
        }
        else
        {
            if(!AUXInterfaceBusy)       // PS2 interface isn't busy
            {
                PS2Deviceactive();
                SetPS2SkipScanTime(KBSkipScanAUXTime);
            }
        }
    }
    else
    {
        if(!AUXInterfaceBusy)           // PS2 interface isn't busy
        {
            *asPS2Struct[channel].ps2ctrl=PS2_ReceiveMode;
            SET_MASK(*asPS2Struct[channel].ps2ier, asPS2Struct[channel].ctrlbit);
            SetPS2InhibitTime(InactiveTime);
        }
    }
}

void ProcessECTestAUXACK(BYTE PortNum, BYTE enablenow)
{
    ECSendtoAUXFlag = 0;
    ClearAUXScanTimeOutCunt();
    SetAUXScanIndexHS(AUXScanIndexFree);
    ScanAUXStepIndex = ScanAUXStep_CheckOK + PortNum;

    if(IS_MASK_SET(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_DISABLED))     // Command 0xF5 ACK
    {
        if(PS2PortxData[PortNum]==0xFA)
        {
            //CLEAR_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_DISABLED);
            AuxFlags2[AUX_SCAN_INDEX] = 0x00;
            SET_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_IS_DISABLED);
        }
        else
        {
            PS2_ReTryCunt++;
            if(PS2_ReTryCunt>PS2_OnOffTimeOutCUNT)
            {
                PS2_ReTryCunt = 0x00;
                //CLEAR_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_DISABLED);
                AuxFlags2[AUX_SCAN_INDEX] = 0x00;
                SET_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_DISABLE_TIME_OUT);
            }
        }
    }
    else if(IS_MASK_SET(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_ENABLED))     // Command 0xF4 ACK
    {
        if(PS2PortxData[PortNum]==0xFA)
        {
            //CLEAR_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_ENABLED);
            AuxFlags2[AUX_SCAN_INDEX] = 0x00;
            SET_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_IS_ENABLED);
        }
        else
        {
            PS2_ReTryCunt++;
            if(PS2_ReTryCunt>PS2_OnOffTimeOutCUNT)
            {
                PS2_ReTryCunt = 0x00;
                //CLEAR_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_ENABLED);
                AuxFlags2[AUX_SCAN_INDEX] = 0x00;
                SET_MASK(AuxFlags2[AUX_SCAN_INDEX],DEVICE_ENABLED_TIME_OUT);
            }
        }
    }
    else                                            // Test Command 0xF1 ACK 
    {
        if(AuxFlags[PortNum]==0x00)                 // Device first time plug-in
        {
            AuxFlags[PortNum] = DEVICE_NEED_INIT;
            SetAUXScanIndexHS(AUXScanIndexInUse);
            ScanAUXStepIndex = ScanAUXStep_CheckType + PortNum; // goto check device is keyboard or mouse
        }
        else
        {
            if(IS_MASK_SET(AuxFlags[PortNum], DEVICE_NEED_CONFIG))
            {
                SetAUXScanIndexHS(AUXScanIndexInUse);
                ScanAUXStepIndex = ScanAUXStep_Init + PortNum;  // goto config. device 
            }
            else if(AuxFlags[PortNum] == DEVICE_NEED_INIT)
            {
                SetAUXScanIndexHS(AUXScanIndexInUse);
                ScanAUXStepIndex = ScanAUXStep_CheckType + PortNum; // goto check device is keyboard or mouse
            }
            else
            {
                if(AuxFlags_KB_CMD[PortNum]!=0x00)
                {
                    SetAUXScanIndexHS(AUXScanIndexInUse);
                    ScanAUXStepIndex = ScanAUXStep_UpdateKB + PortNum;
                }
            }
        }
    }

    if(enablenow==0x01)
    {
        PS2Deviceactive();	
    }
}


//-----------------------------------------------------------------
// Bypass AUX data to host
//-----------------------------------------------------------------
void SendAUXData(BYTE PortNum)  // Dino 0907             
{
    BYTE index;

    if(SendtoAUXFlag)				        // Send command to device and transmit done.
    {
        SendtoAUXFlag = 0;		
        *asPS2Struct[PortNum].ps2ctrl=PS2_ReceiveMode;  // Enable Receive mode for ACK byte
        SET_MASK(*asPS2Struct[PortNum].ps2ier, asPS2Struct[PortNum].ctrlbit);  // Enable interrupt for ACK byte
        ClearAUXScanTimeOutCunt();
    }
    else							        // Receive done and get data
    {	
        if(ECSendtoAUXFlag)                 // If thsi byte is EC scan channel ACK, no send to host
        {
            ProcessECTestAUXACK(PortNum, 1);
        }
        else                                // receive mode transmit done.      
        {
            SetAUXScanIndexHS(AUXScanIndexFree);
            ClearAUXScanTimeOutCunt();
            if(IS_MASK_SET(AuxFlags[PortNum], DEVICE_IS_MOUSE))     // If data from mosue
	        {
                ProcessMouseData(PortNum);      // Process mosue data
	        }
            else if(IS_MASK_SET(AuxFlags[PortNum], DEVICE_IS_KEYBOARD)) // If data from keyboard
	        {	
	            ProcessKeyboardData(PortNum);   // Process keyboard data
	        }
            else
            {
                PS2Deviceactive();              // Enable all ps2 interface
            }
        }
    }
}


//-----------------------------------------------------------------
// 
//-----------------------------------------------------------------
void ClaerPS2IFPendingEvent(void)
{
    InhibitAUXDevice();
    IER2&= ~(Int_PS2_0+Int_PS2_1+Int_PS2_2);    // Disable all PS2 interrupt
    ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
    PS2StartBit = 0;            // clear ps2 interrupt start bit flag
    F_Service_PS2 = 0;	        // Clear PS2 interrupt service flag
}

//-----------------------------------------------------------------
// EC Send command to ps2 interface no ack to host
//-----------------------------------------------------------------
void ECSend2Port( BYTE PortNum, BYTE PortData)
{
    ClaerPS2IFPendingEvent();
	ECSendtoAUXFlag = 1;
    SendtoAUXFlag = 1;
	*asPS2Struct[PortNum].ps2ctrl = 0x1D;
	*asPS2Struct[PortNum].ps2data = PortData;
	*asPS2Struct[PortNum].ps2ctrl = 0x1C;
	*asPS2Struct[PortNum].ps2ctrl = 0x1E;
   
    SET_MASK(*asPS2Struct[PortNum].ps2ier, asPS2Struct[PortNum].ctrlbit);    // Enable interrupt   
}

//-----------------------------------------------------------------
// Before sending command to PS2 device to make sure no any data is done
//-----------------------------------------------------------------
void CheckNWaitReceiveDone(void)
{
    BYTE busy;
    busy=0x00;
        
    if(IS_MASK_SET(PSSTS1, SS)||IS_MASK_SET(PSSTS2, SS)||IS_MASK_SET(PSSTS3, SS)
    ||F_Service_PS2 == 1||PS2StartBit == 1)
    {
        TR1 = 0;                 	    // Disable timer1
        ET1 = 0;                  	    // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_30ms>>8;            // Set timer1 counter 30ms
        TL1 = Timer_30ms;               // Set timer1 counter 30ms
        TF1 = 0;                  	    // Clear overflow flag
        TR1 = 1;                 	    // Enable timer1

        while(!TF1)
        {
            if(F_Service_PS2)
            {
                busy=0x01;
                TR1 = 0;			            // disable timer1
                TF1 = 0;						// clear overflow flag
                break;
            }
        }

        if(TF1)
        {
            if(PS2CheckPendingISR()==0x01)
            {
                busy=0x01;
            }
        }

        if(busy==0x01)
        {
            F_Service_PS2=0;
            AUXInterfaceBusy=1;
            service_ps2();
            AUXInterfaceBusy=0;
        }
   
        TR1 = 0;			            // disable timer1
        TF1 = 0;						// clear overflow flag
        ET1 = 1;	
    }
    else
    {
        PS2DeviceInactive();
    }
}

//-----------------------------------------------------------------
// Send data to ps2 interface
//-----------------------------------------------------------------
void Send2Port( BYTE PortNum, BYTE PortData, BYTE action)
{
    BYTE tempinactvietime;

    #if !TouchPad_only
        if(ECSendtoAUXFlag)
        {
            if(WaitECSend2PortACK(AUX_SCAN_INDEX)==0x01)
            {
                AUXDevicePlugOutClearVariables();
            }
        }
        else
        {
            if(action == SendCmdToKB)
            {
                CheckNWaitReceiveDone();
            }
        }
    #endif

    ClaerPS2IFPendingEvent();
    
    if(PortData==0xFF)                              // reset command
    {
        SetPS2InhibitTime(DeviceResetCmdITTime);    // 1.2sec
    }
    else
    {
        if(TPACKCounter!=0x00)
        {
            tempinactvietime = InactiveTime*TPACKCounter;
        }
        else if(Main_KB_ACK_CUNT!=0x00)
        {
            tempinactvietime = InactiveTime*Main_KB_ACK_CUNT;
        }
        else
        {
            tempinactvietime = InactiveTime;
        }
        SetPS2InhibitTime(tempinactvietime);
    }
    
    SetAUXScanIndexHS(AUXScanIndexFree);

    ECSendtoAUXFlag = 0;
    SendtoAUXFlag = 1;
	*asPS2Struct[PortNum].ps2ctrl = 0x1D;
	*asPS2Struct[PortNum].ps2data = PortData;
	*asPS2Struct[PortNum].ps2ctrl = 0x1C;
	*asPS2Struct[PortNum].ps2ctrl = 0x1E;
  
    SET_MASK(*asPS2Struct[PortNum].ps2ier, asPS2Struct[PortNum].ctrlbit);    // Enable interrupt 

    WaitPS2DeviceACK(PortNum);
}

//-----------------------------------------------------------------
// Send command to ps2 interface and check ack or not
//  Note : return   0 --> // Transaction done
//                  1 --> // Transaction fail
//
//                  After this function, all ps2 channel is inhibit and channel interrupt is disabled
//-----------------------------------------------------------------
BYTE Send2PortNWait( BYTE PortNum, BYTE cmd, BYTE bytecunt)
{
    BYTE result;
    BYTE index;

    PS2IFAck = 0x00;

    ClaerPS2IFPendingEvent();

    ECSendtoAUXFlag = 0;
    SendtoAUXFlag = 0;
	*asPS2Struct[PortNum].ps2ctrl = 0x1D;
	*asPS2Struct[PortNum].ps2data = cmd;
	*asPS2Struct[PortNum].ps2ctrl = 0x1C;
	*asPS2Struct[PortNum].ps2ctrl = 0x1E;

    result = bExtAUXTimeOutCheck(PortNum, PS2_Transmission_Mode);

    if(result==0x00)                // Transaction done
    {
        for(index=0x00;index<bytecunt;index++)
        {
            *asPS2Struct[PortNum].ps2ctrl=PS2_ReceiveMode;  // Get Last ACK by bytecunt
            result = bExtAUXTimeOutCheck(PortNum, PS2_Receive_Mode);
            if(result!=0x00)
            {
                break;              // Transaction fail
            }
        }
    }

    *asPS2Struct[PortNum].ps2ctrl=PS2_InhibitMode;
    ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
  
    return(result);		                        
}

//-----------------------------------------------------------------
// Process AUX command
//-----------------------------------------------------------------
void SendCmdtoMouse(BYTE PortNum)
{
    BYTE index;

    Cmd_A8();
    ResetMSPendingData();
    SetPS2CmdACKCounter(0);
    MS_ID_CUNT = 0x00;

	if(AUX2ByteCommand)
	{	
        SetPS2CmdACKCounter(1);
		if(TPResolution == 0xFF)
		{
			TPResolution = KBHIData;
		}
		else if(TPSamplingRate == 0xFF)
		{
			TPSamplingRate = KBHIData;		
		}

		Send2Port(PortNum, KBHIData, SendCmdToMS);	
		AUX2ByteCommand = 0;
		return;
	}

	switch(KBHIData)
	{
		case 0xE8:     			// Set Resolution (2 byte)
			TPResolution = 0xFF;
			AUX2ByteCommand=1;
			break;
		
		case 0xF3:     			// Set Sampling Rate (2 byte)
			TPSamplingRate = 0xFF;	
			AUX2ByteCommand=1;
			break;	
			
		case 0xF4:	
            #if PS2_Pack_Debug
            PS_Debug_ECToHost = 0xFF;
            #endif
			//EnableTP = 1;
			MouseDriverIn = 1;
			break;
			
		case 0xF5:
			MouseDriverIn = 0;
			break;	
			
		case 0xE6:
			break;
			
		case 0xE7:
			break;
			
		case 0xEA:
			break;
			
		case 0xEC:
			break;
			
		case 0xEE:
			break;
			
		case 0xF0:
			break;
			
		case 0xF6:		
			break;	
			
		case 0xE9:	
			break;
			
		case 0xF2:	
            MS_ID_CUNT = 2;
			break;
			
		case 0xEB:
		case 0xFE:	
			break;
			
		case 0xFF:
			MouseDriverIn = 0;
            MULPX_Multiplex = 0;	    // Disable Activate Multiplex mode 
			//EnableTP = 0;

            for(index=0x00; index<3; index++)
            {
                if((Main_MOUSE_CHN-1)!=index)
                {
                    if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_MOUSE))
                    {
                        AuxFlags[index] = 0x00;
                    }
                }
            }
			break;
			
		default:			            // Invalid command
			break;
	}

    if(KBHIData==0xFF)      // Reset command
    {
        SetPS2CmdACKCounter(3);
    }
    else if(KBHIData==0xF2) // Read ID command
    {
        SetPS2CmdACKCounter(2);
    }
    else if(KBHIData==0xE9) // Read status cmmand
    {
        SetPS2CmdACKCounter(4);
    }
    else                    // Other commands
    {
        SetPS2CmdACKCounter(1);
    }
    
	Send2Port(PortNum, KBHIData, SendCmdToMS);
}

//-----------------------------------------------------------------
// Process AUX MUX command
//-----------------------------------------------------------------
void SendCmdtoMUX(BYTE port)
{
    SetPS2CmdACKCounter(0);
    ResetMSPendingData();
	if(AUX2ByteCommand)
	{	
        SetPS2CmdACKCounter(1);
		Send2Port(port, KBHIData, SendCmdToMS);	
		AUX2ByteCommand = 0;
		return;
	}

	switch(KBHIData)
	{
		case 0xE8:     		// Set Resolution (2 byte)
		case 0xF3:     		// Set Sampling Rate (2 byte)
			AUX2ByteCommand=1;
			break;	
			
		case 0xF4:	
		case 0xF5:	
		case 0xE6:
		case 0xE7:
		case 0xEA:
		case 0xEC:
		case 0xEE:
		case 0xF0:	
		case 0xF6:	
		case 0xE9:
		case 0xEB:
		case 0xF2:				
		case 0xFE:	
		case 0xE1:		    // For older Synaptics TouchPads		
		case 0xFF:
			break;
			
		default:		    // Invalid command
			break;
	}

    if(KBHIData==0xFF)      // Reset command
    {
        SetPS2CmdACKCounter(3);
    }
    else if(KBHIData==0xF2) // Read ID command
    {
        SetPS2CmdACKCounter(2);
    }
    else if(KBHIData==0xE9) // Read status cmmand
    {
        SetPS2CmdACKCounter(4);
    }
    else                    // Other commands
    {
        SetPS2CmdACKCounter(1);
    }

    Send2Port(port, KBHIData, SendCmdToMS); 
}

//-----------------------------------------------------------------
// FUNCTION: Ps2_Init - Init PS2 registers and variables.  
// Put in receive mode.
//-----------------------------------------------------------------
void Ps2_Init(void)
{

}

//-----------------------------------------------------------------
// The function of PS2 interface interrupt service routine
//-----------------------------------------------------------------
void service_ps2(void)
{	
    BYTE channel;

    channel = PS2_IRQ_Channel;
    if(channel!=0xFF)
    {
        Hook_service_ps2(channel, PS2PortxData[channel]);
        PS2_IRQ_Channel = 0xFF;
        SendAUXData(channel);
    }
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// The function of stopping ps2 devices send data to KBC
//----------------------------------------------------------------------------
void PS2DeviceInactive(void)
{
	PSCTL1 = PS2_InhibitMode;
	PSCTL2 = PS2_InhibitMode;
	PSCTL3 = PS2_InhibitMode;
}

//----------------------------------------------------------------------------
// The function of starting ps2 devices send data to KBC
//----------------------------------------------------------------------------
void PS2Deviceactive(void)
{	 
    BYTE index;
    for(index=0x00;index<3;index++)
    {
        if(IS_MASK_SET(AuxFlags[index],DEVICE_IS_KEYBOARD))
        {
            *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
            SET_MASK(*asPS2Struct[index].ps2ier, asPS2Struct[index].ctrlbit); 
        }
    }
    for(index=0x00;index<3;index++)
    {
        if(IS_MASK_SET(AuxFlags[index],DEVICE_IS_MOUSE))
        {
            *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
            SET_MASK(*asPS2Struct[index].ps2ier, asPS2Struct[index].ctrlbit); 
        }
    }     
}

//----------------------------------------------------------------------------
// The function of inhibit AUX device
//----------------------------------------------------------------------------
void InhibitAUXDevice(void)
{ 
	PS2DeviceInactive();

    TR1 = 0;        // Disable timer1
	ET1 = 0;		// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_150u>>8;    // set timer1 counter 150 us	
    TL1 = Timer_150u;       // set timer1 counter 150 us
    TF1 = 0;		// clear overflow flag
	TR1 = 1;		// enable timer1
	while(!TF1);	// waitting overflow flag
    TR1 = 0;        // Disable timer1
	TF1 = 0;		// clear overflow flag
	ET1 = 1;		// Enable timer1 interrupt
}

//----------------------------------------------------------------------------
// The function of scaning AUX device
// Parameter 1 : 
//           0 : scan all channel
//           1 : scan mouse channel
//           2 : scan keyboard channel
//----------------------------------------------------------------------------
void ScanAUXDevice(BYTE scan_selection)
{
	BYTE index;
    BYTE timeout;
    
    if(scan_selection==ScanMouseChannel)    // Scan mouse channel
    {
        if(Main_MOUSE_CHN!=0x00)    // Main mouse is presetn
        {
            return;
        }
    }
    else if(scan_selection==ScanKeyboardChannel)   // Scan keyboard channel
    {
        if(Main_KB_CHN!=0x00)       // Main keyboard is present
        {
            return;
        }
    }
   
	for(index=0x00;index<3;index++)
	{
        if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_MOUSE)||IS_MASK_SET(AuxFlags[index], DEVICE_IS_KEYBOARD))
        {
            continue;
        }
		AuxFlags[index] = 0x00;                 

		if(index==0x00)
		{
			if((PS2_Port0_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port0_Data_CtrlReg&0xFB)!=0x00)
				continue;                   // If this channel isn't PS2 ALT function, scan next.             
		}
		else if(index==0x01)
		{
			if((PS2_Port1_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port1_Data_CtrlReg&0xFB)!=0x00)
				continue;                   // If this channel isn't PS2 ALT function, scan next.    
		}
		else if(index==0x02)
		{
			if((PS2_Port2_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port2_Data_CtrlReg&0xFB)!=0x00)
				continue;                   // If this channel isn't PS2 ALT function, scan next.    
		}
        
        if(Send2PortNWait(index,0xFF,1)==0x00 && (PS2IFAck==0xFA))
        {
            SET_MASK(AuxFlags[index], DEVICE_IS_ATTACHED);

            *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
            for(timeout=0x00;timeout<=ResetCmdTOTime;timeout++) // 510 ms time-out
            {
                if(!bExtAUXTimeOutCheck(index, PS2_Receive_Mode))
                {
                    break;
                }
            }
                
            if(timeout>ResetCmdTOTime)                          // wait aa time-out
            {
                CLEAR_MASK(AuxFlags[index], DEVICE_IS_ATTACHED);
            }
            else
            {
                *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
                for(timeout=0x00;timeout<=ResetCmdTOTime;timeout++) // 510 ms time-out
                {
                    if(!bExtAUXTimeOutCheck(index, PS2_Receive_Mode))
                    {
                        break;
                    }
                }
                    
                if(timeout>ResetCmdTOTime)                  // wait 00 time-out
                {
                    SET_MASK(AuxFlags[index], DEVICE_IS_KEYBOARD);
                    CheckNSetMainKBCHN(index);
                    if(scan_selection==ScanKeyboardChannel) // Scan keyboard channel
                    {
                        break;
                    }
                }
                else
                {
                    if(PS2IFAck==0x00)      // Mouse
                    {
                        SET_MASK(AuxFlags[index], DEVICE_IS_MOUSE);
                        CheckNSetMainMSCHN(index);
                        if(scan_selection==ScanMouseChannel)    // Scan mouse channel
                        {
                            break;
                        }
                    }
                    else                    // Keyboard
                    {
                        SET_MASK(AuxFlags[index], DEVICE_IS_KEYBOARD);
                        CheckNSetMainKBCHN(index);
                        if(scan_selection==ScanKeyboardChannel) // Scan keyboard channel
                        {
                            break;
                        }
                    }
                }
            }

            *asPS2Struct[index].ps2ctrl=PS2_InhibitMode;
            ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
        }
        else
        {
            *asPS2Struct[index].ps2ctrl=PS2_InhibitMode;
            ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
			continue;           // Device non-ack
        }       
	}

    if((Main_MOUSE_CHN==0x00)&&(Main_KB_CHN==0x00)) // No any device
    {
        ClearAUXScanTimeOutCunt();
        SetAUXScanIndexHS(AUXScanIndexFree);
    }
}

//----------------------------------------------------------------------------
// The function of checking AUX device is keyborad or mouse
//----------------------------------------------------------------------------
void CheckAUXDeviceType(void)
{
    BYTE timeout;
    
    if(AuxFlags[AUX_SCAN_INDEX] == DEVICE_NEED_INIT)
    {
        AuxFlags[AUX_SCAN_INDEX]=0x00;
        PS2IFAck = 0x00;

        if(Send2PortNWait(AUX_SCAN_INDEX,0xFF,1)==0x00 && (PS2IFAck==0xFA))
        {
            SET_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_ATTACHED);

            *asPS2Struct[AUX_SCAN_INDEX].ps2ctrl=PS2_ReceiveMode;
            for(timeout=0x00;timeout<=ResetCmdTOTime;timeout++) // 510 ms time-out
            {
                if(!bExtAUXTimeOutCheck(AUX_SCAN_INDEX, PS2_Receive_Mode))
                {
                    break;
                }
            }
                
            if(timeout>ResetCmdTOTime)  // wait aa time-out
            {
                CLEAR_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_ATTACHED);
            }
            else
            {
                *asPS2Struct[AUX_SCAN_INDEX].ps2ctrl=PS2_ReceiveMode;
                for(timeout=0x00;timeout<=ResetCmdTOTime;timeout++) // 510 ms time-out
                {
                    if(!bExtAUXTimeOutCheck(AUX_SCAN_INDEX, PS2_Receive_Mode))
                    {
                         break;
                    }
                }
                    
                if(timeout>ResetCmdTOTime)  // wait 00 time-out
                {
                    SET_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_KEYBOARD);
                    CheckNSetMainKBCHN(AUX_SCAN_INDEX);      
                }
                else
                {
                    if(PS2IFAck==0x00)      // Mouse
                    {
                        SET_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_MOUSE);      // Device is mouse
                        CheckNSetMainMSCHN(AUX_SCAN_INDEX);
                    }
                    else                    // Keyboard
                    {
                        SET_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_KEYBOARD);
                        CheckNSetMainKBCHN(AUX_SCAN_INDEX);
                    }
                }
            }
            
            *asPS2Struct[AUX_SCAN_INDEX].ps2ctrl=PS2_InhibitMode;
            ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt

            if(IS_MASK_SET(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_ATTACHED))
            {
                SET_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_NEED_CONFIG);
                ScanAUXStepIndex = ScanAUXStep_Init + AUX_SCAN_INDEX;
            }
            else
            {
                SetAUXScanIndexHS(AUXScanIndexFree);
                ScanAUXStepIndex = ScanAUXStep_CheckTypeFail + AUX_SCAN_INDEX;
            }
        }
        else
        {
            *asPS2Struct[AUX_SCAN_INDEX].ps2ctrl=PS2_InhibitMode;
            ISR2=(Int_PS2_0+Int_PS2_1+Int_PS2_2);       // Write to clear all PS2 pending interrupt
             
            SetAUXScanIndexHS(AUXScanIndexFree);
            ScanAUXStepIndex = ScanAUXStep_InitFail + AUX_SCAN_INDEX;
        }
        PS2Deviceactive();
    } 
}

//----------------------------------------------------------------------------
// Clear variables for device plug-out
//----------------------------------------------------------------------------
void AUXDevicePlugOutClearVariables(void)
{
    BYTE index;
  
    ClearAUXScanTimeOutCunt();
    SetAUXScanIndexHS(AUXScanIndexFree);
    AuxFlags[AUX_SCAN_INDEX] = 0x00;
    AuxFlags2[AUX_SCAN_INDEX] = 0x00;
    PS2_ReTryCunt = 0x00;
    SendtoAUXFlag = 0;	
    ECSendtoAUXFlag = 0;

    if(Main_MOUSE_CHN == (AUX_SCAN_INDEX+1))
    {
        Main_MOUSE_CHN = 0x00;
        for(index=0x00;index<3;index++)
        {
            if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_MOUSE))
            {
                SET_MASK(AuxFlags[index], DEVICE_IS_MAIN_MOUSE);
                Main_MOUSE_CHN = index + 1;
                break;
            }
        }   
    }
                    
    if(Main_KB_CHN == (AUX_SCAN_INDEX+1))
    {
        Main_KB_CHN = 0x00;
        for(index=0x00;index<3;index++)
        {
            if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_KEYBOARD))
            {
                SET_MASK(AuxFlags[index], DEVICE_IS_MAIN_KB);
                Main_KB_CHN = index + 1;
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------
// The polling aux device center
//----------------------------------------------------------------------------
void PollingAUXDeviceCenter(void)
{
    if(AUX_SCAN_INDEX_HS!=AUXScanIndexInUse)
    {
        SetAUXScanIndexHS(AUXScanIndexInUse);
        AUX_SCAN_INDEX++;
        if(AUX_SCAN_INDEX>2)
        {
            AUX_SCAN_INDEX=0x00;
        }
        ScanAUXStepIndex = ScanAUXStep_ScanPort+AUX_SCAN_INDEX;
    }
    else
    {
        if(ECSendtoAUXFlag)
        {
            AUX_SCAN_TIMEOUT_CUNT++;
            if(AUX_SCAN_TIMEOUT_CUNT>=CheckDeviceTimeOut)
            {
                AUXDevicePlugOutClearVariables();
                PS2Deviceactive();	
            }
        }
    }
}

//----------------------------------------------------------------------------
// The function of update external keyboard device
//----------------------------------------------------------------------------
const BYTE code UpdateConfigAUXKB[] = {0xF5, 0xF4, 0xF3, 0xED};	// Command table

void UpdateExtKeyboard(BYTE portnum)
{   
	BYTE index;
    
    for(index=0x00; index<sizeof(UpdateConfigAUXKB); index++)	
    {
        //if(IS_BIT_SET(AuxFlags_KB_CMD[AUX_SCAN_INDEX], bit(index)))
        if(IS_MASK_SET(AuxFlags_KB_CMD[AUX_SCAN_INDEX], BIT(index)))
        {
            if(!Send2PortNWait(portnum,UpdateConfigAUXKB[index],1))
            {
                if(UpdateConfigAUXKB[index]==0xF3)
                {
                    Send2PortNWait(portnum,Save_Typematic,1);
                }
                else if(UpdateConfigAUXKB[index]==0xED)
                {
                    Send2PortNWait(portnum,(Led_Data&0x07),1);
                }
                CLEAR_MASK(AuxFlags_KB_CMD[AUX_SCAN_INDEX], BIT(index));
            }
        }
    }
}

//----------------------------------------------------------------------------
// The function of update aux keyboard device
//----------------------------------------------------------------------------
void UpdateAUXKBDevice(void)
{
    UpdateExtKeyboard(AUX_SCAN_INDEX);
    SetAUXScanIndexHS(AUXScanIndexFree);
}


//----------------------------------------------------------------------------
// The function of init, AUX device
//----------------------------------------------------------------------------
void InitAUXDevice(void)
{
    if(IS_MASK_SET(AuxFlags[AUX_SCAN_INDEX], DEVICE_IS_KEYBOARD))   // device is keyboard
    {
        if(KeyboardDriverIn)
        {
            if(AuxFlags_KB_CMD[AUX_SCAN_INDEX]==0x00)
            {
                ConfigExtKeyboard(AUX_SCAN_INDEX);
            }
            else
            {
                UpdateExtKeyboard(AUX_SCAN_INDEX);
            }
            CLEAR_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_NEED_CONFIG);
        }
        else
        {
            
        }
    }
    else                                                // device is mouse
    {
        if(MouseDriverIn)
        {
	        if(MULPX_Multiplex)
	        {
                AUXData_To_Host_nWait(0xAA,AUX_SCAN_INDEX);
                AUXData_To_Host_nWait(0x00,AUX_SCAN_INDEX);
                CLEAR_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_NEED_CONFIG);
                SetPS2SkipScanTime(10);
	        }
            else
            {
                if(SetIntellimouse(MS_DRIVER_TYPE,AUX_SCAN_INDEX))
                {
                    if(ReadMouseID(AUX_SCAN_INDEX)==MS_DRIVER_TYPE)
                    {
                        if(ConfigExtMouse(AUX_SCAN_INDEX))
                        {
                            CLEAR_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_NEED_CONFIG);
                        }
                        else
                        {
                            AuxFlags[AUX_SCAN_INDEX] = 0x00;        // device error
                        }
                    }
                    else
                    {
                        SET_MASK(AuxFlags[AUX_SCAN_INDEX],DEVICE_MS_DRIVER_NO_MATCH);
                        CLEAR_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_NEED_CONFIG);
                    }
                }
                else
                {
                    AuxFlags[AUX_SCAN_INDEX] = 0x00;                // device error
                }
            }
        }
        else
        {
	        if(MULPX_Multiplex)
	        {
                AUXData_To_Host_nWait(0xAA,AUX_SCAN_INDEX);
                AUXData_To_Host_nWait(0x00,AUX_SCAN_INDEX);
                CLEAR_MASK(AuxFlags[AUX_SCAN_INDEX], DEVICE_NEED_CONFIG);
	        }
        }
    }
    PS2Deviceactive();
    SetAUXScanIndexHS(AUXScanIndexFree);
}

//----------------------------------------------------------------------------
// The function of enabling/disabling TP by EC self.
//
//      Note : If want to enable mouse device. Please ensrue "MouseDriverIn" is set.
//----------------------------------------------------------------------------
void TPOnlyLowLevelFunc(void)
{
    BYTE index;

    if(StartENAUXDevice)        // 10ms time base
    {
        StartENAUXDevice = 0;

        if(MSPending==0x33)     // PS2 data is pending
        {
            return;             // Exit
        }

        if(TPACKCounter!=0x00)
        {
            return;
        }

        Hook_TPOnlyLowLevelFunc();

        if(AUXInactiveCounter!=0x00)
	    {
		    AUXInactiveCounter--;
            return;
	    }
        else
        {
            if(IS_MASK_SET(PSSTS1, SS)||IS_MASK_SET(PSSTS2, SS)||IS_MASK_SET(PSSTS3, SS)||F_Service_PS2)
            {
                return;
            }
        }

        if(AUXInactiveCounter==0x00)
        {
	        for(index=0x00;index<3;index++)
	        {
		        if(IS_MASK_SET(AuxFlags2[index], DEVICE_NEED_DISABLED))
		        {
    		        if(!Send2PortNWait(index,0xF5,1))
    		        {
        		        CLEAR_MASK(AuxFlags2[index], DEVICE_NEED_DISABLED);
            	        SET_MASK(AuxFlags2[index],DEVICE_IS_DISABLED);
    		        }
		        }
		        else if(IS_MASK_SET(AuxFlags2[index], DEVICE_NEED_ENABLED))
		        {
    		        if(!Send2PortNWait(index,0xF4,1))
    		        {
        		        CLEAR_MASK(AuxFlags2[index], DEVICE_NEED_ENABLED);
            	        SET_MASK(AuxFlags2[index],DEVICE_IS_ENABLED);
				        *asPS2Struct[index].ps2ctrl=PS2_ReceiveMode;
                        SET_MASK(*asPS2Struct[index].ps2ier, asPS2Struct[index].ctrlbit); 
    		        }
		        }
	        }
        }
    }
}

//----------------------------------------------------------------------------
// The function of scaning external AUX device
//----------------------------------------------------------------------------
void ExternalAUXLowLevelFunc(void)
{
    BYTE ISR2Temp;

    if(StartENAUXDevice)                // 10ms time base
    {        
        StartENAUXDevice = 0;

        if(MSPending==0x33)             // PS2 data is pending
        {
            return;                     // Exit
        }
        
        EnableAUXDevice();

        if(AUXInactiveCounter!=0x00)    // PS2 channel in inhibit.
        {
            return;                     // Exit
        }

        if(SKIP_AUX_SCAN_CUNT!=0x00)    // EC skip to scan PS2 interface
        {
            return; 
        }   

        #if !PS2IFHotPlugHotSwap
            return;
        #endif

        if(IS_MASK_SET(PSSTS1, SS)||IS_MASK_SET(PSSTS2, SS)||IS_MASK_SET(PSSTS3, SS)||PS2StartBit==1)
        {
            AuxScanWDT++;
            
            if(AuxScanWDT>100)          // Interface watch dog for hot-plug  (1sec). 
            {
                AuxScanWDT = 0x00;
                PS2StartBit = 0;

                AUXDevicePlugOutClearVariables();
                PS2Deviceactive();
                
                if(IS_MASK_SET(PSSTS1, SS)||PS2_SSIRQ_Channel == 0)
                {
	                PSCTL1 = PS2_InhibitMode;
                }
                else if(IS_MASK_SET(PSSTS2, SS)||PS2_SSIRQ_Channel == 1)
                {
                    PSCTL2 = PS2_InhibitMode;
                }
                else if(IS_MASK_SET(PSSTS3, SS)||PS2_SSIRQ_Channel == 2)
                {
                    PSCTL3 = PS2_InhibitMode;
                }
            }
            return;
        }
        else
        {
            AuxScanWDT = 0x00;

            ISR2Temp = ISR2;
            ISR2Temp &= (Int_PS2_0+Int_PS2_1+Int_PS2_2);
            if(ISR2Temp !=0x00)
            {
                return;
            }
            else
            {
                //if(PS2StartBit==1 || F_Service_PS2==1)  // Any ps2 channel has getten data.
                if(F_Service_PS2)       // Any ps2 channel has getten data.
                {
                    return;             // Exit
                }
                else
                {
                    PS2DeviceInactive();
                }
            }
        }

        PollingAUXDeviceCenter();

        switch(ScanAUXStepIndex)
        {
            case ScanAUXStep_ScanPort0:   
            case ScanAUXStep_ScanPort1:
            case ScanAUXStep_ScanPort2:
                ScanAUXPortX();
                break;      
            
            case ScanAUXStep_CheckType0:
            case ScanAUXStep_CheckType1:
            case ScanAUXStep_CheckType2:
                CheckAUXDeviceType();
                break;
            
            case ScanAUXStep_Init0:
            case ScanAUXStep_Init1:
            case ScanAUXStep_Init2:
                InitAUXDevice();
                break;

            case ScanAUXStep_UpdateKB0:
            case ScanAUXStep_UpdateKB1:
            case ScanAUXStep_UpdateKB2:
                UpdateAUXKBDevice();
                break;

            case ScanAUXStep_CheckOK1:
            case ScanAUXStep_CheckOK2:
            case ScanAUXStep_CheckOK3:
            
            case ScanAUXStep_InitFail0:
            case ScanAUXStep_InitFail1:
            case ScanAUXStep_InitFail2:    

            case ScanAUXStep_CheckTypeFail0:
            case ScanAUXStep_CheckTypeFail1:
            case ScanAUXStep_CheckTypeFail2:
       
            case ScanAUXStep_Skip0:
            case ScanAUXStep_Skip1:
            case ScanAUXStep_Skip2:
            
            case ScanAUXStep_WaitPort0:
            case ScanAUXStep_WaitPort1:
            case ScanAUXStep_WaitPort2:
            
            default:
                break;
        } 
        
    }
}

//----------------------------------------------------------------------------
// The function of scaning AUX device step
//----------------------------------------------------------------------------
void ScanAUXDeviceStep(void)
{ 
    #if TouchPad_only
    TPOnlyLowLevelFunc();
    #else
    ExternalAUXLowLevelFunc();
    #endif    
}

//----------------------------------------------------------------------------
// The function of checking AUX device
//----------------------------------------------------------------------------
void ScanAUXPortX(void)
{
    if(AUX_SCAN_INDEX_HS==AUXScanIndexInUse)
    {
        if(AUX_SCAN_INDEX==0x00)
        {
            if((PS2_Port0_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port0_Data_CtrlReg&0xFB)!=0x00)
            {
                 SetAUXScanIndexHS(AUXScanIndexFree);
            }
        }
        else if(AUX_SCAN_INDEX==0x01)
        {
            if((PS2_Port1_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port1_Data_CtrlReg&0xFB)!=0x00)
            {
                SetAUXScanIndexHS(AUXScanIndexFree);
            }
        }
        else if(AUX_SCAN_INDEX==0x02)
        {
            if((PS2_Port2_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port2_Data_CtrlReg&0xFB)!=0x00)
            {
                 SetAUXScanIndexHS(AUXScanIndexFree);
            }
        }
            
        if(AUX_SCAN_INDEX_HS == AUXScanIndexFree)
        {
            ScanAUXStepIndex = ScanAUXStep_Skip + AUX_SCAN_INDEX;
        }
        else
        {
            ClearAUXScanTimeOutCunt();
            if(IS_MASK_SET(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_DISABLED))
            {
                ECSend2Port(AUX_SCAN_INDEX, 0xF5);
            }
            else if(IS_MASK_SET(AuxFlags2[AUX_SCAN_INDEX],DEVICE_NEED_ENABLED))
            {
                ECSend2Port(AUX_SCAN_INDEX, 0xF4);
            }
            else
            {
                ECSend2Port(AUX_SCAN_INDEX, 0xF1);
            }
            ScanAUXStepIndex = ScanAUXStep_WaitPort + AUX_SCAN_INDEX;
        }
    }
}

//----------------------------------------------------------------------------
// The function of enabling all PS2 interface
//----------------------------------------------------------------------------
void EnableAUXDevice(void)
{
	if(AUXInactiveCounter!=0x00)
	{
		if(--AUXInactiveCounter==0x00)
		{
			PS2Deviceactive();
		}
	}

    if(SKIP_AUX_SCAN_CUNT!=0x00)
    {
        SKIP_AUX_SCAN_CUNT--;
    }
}

//----------------------------------------------------------------------------
// The function of starting to check AUX device
//----------------------------------------------------------------------------
BYTE bExtAUXTimeOutCheck(BYTE channel, BYTE p_mode)
{
    BYTE result;
    result = 0x01;      // pre-set resutl is fail
    
    TR1 = 0;            // Disable timer 1
	ET1 = 0;			// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_30ms>>8;    // Set timer1 counter 30ms
    TL1 = Timer_30ms;       // Set timer1 counter 30ms
    TF1 = 0;			// clear overflow flag
	TR1 = 1;			// enable timer1

	do
	{
        //
        // Wait PS2 transaction Done
        //
        #if TouchPad_only
        if(IS_MASK_SET(*asPS2Struct[channel].ps2isr, asPS2Struct[channel].ctrlbit))
        #else
        if(IS_MASK_SET(*asPS2Struct[channel].ps2status, TDS))
        #endif
        {
            if(p_mode == PS2_Transmission_Mode)
            {
                for(PS2DataPinStatus=0x00;PS2DataPinStatus<5;PS2DataPinStatus++)
                {
                    //if(IS_MASK_SET(*asPS2Struct[channel].ps2status, DLS))   // DATA Line Status is high
                    //{
                    //    break;
                    //}
                    //else
                    //{
                    //    WNCKR = 0x00;       // Delay 15.26 us
                    //}
                    if(channel==2)
                    {
                        //
                        // DATA Line Status is high of ps2 port 1
                        //
                        if(IS_MASK_SET(GPDRF, BIT5))   // DATA Line Status is high
                        {
                            break;
                        }
                    }
                    else if(channel==1)
                    {
                        //
                        // DATA Line Status is high of ps2 port 1
                        //
                        if(IS_MASK_SET(GPDRF, BIT3))
                        {
                            break;
                        }
                    }
                    else if(channel==0)
                    {
                        //
                        // DATA Line Status is high of ps2 port 0
                        //
                        if(IS_MASK_SET(GPDRF, BIT1))
                        {
                            break;
                        }
                    }
                    else
                    {
                        //WNCKR = 0x00;       // Delay 15.26 us
                    }

                    //
                    // Delay 15.26 us
                    //
                    WNCKR = 0x00;
                }
            }
            //WNCKR = 0x00;               // Delay 15.26 us
            //WNCKR = 0x00;               // Delay 15.26 us
            //WNCKR = 0x00;               // Delay 15.26 us
            //WNCKR = 0x00;               // Delay 15.26 us
            //WNCKR = 0x00;               // Delay 15.26 us
            //WNCKR = 0x00;               // Delay 15.26 us
            //WNCKR = 0x00;               // Delay 15.26 us
            *asPS2Struct[channel].ps2ctrl=PS2_InhibitMode;
            PS2IFAck=*asPS2Struct[channel].ps2data;
            result = 0x00;

            //
			// Clear ISR
			//
            *asPS2Struct[channel].ps2isr = asPS2Struct[channel].ctrlbit;
            break;
        }
	}while(!TF1);					// waitting for overflow flag
 
    TR1 = 0;			            // disable timer1
    TF1 = 0;						// clear overflow flag
    ET1 = 1;	
	return(result);
}

//----------------------------------------------------------------------------
// The function of setting external keyboard device
//----------------------------------------------------------------------------
const BYTE code ConfigAUXKB[] = {0xF3, 0xED, 0xF4 };	// Command table

void ConfigExtKeyboard(BYTE portnum)
{   
	BYTE index;

    for(index=0x00; index<sizeof(ConfigAUXKB); index++)	
    {
        if(!Send2PortNWait(portnum,ConfigAUXKB[index],1))
        {
            if(ConfigAUXKB[index]==0xF3)
            {
                Send2PortNWait(portnum,Save_Typematic,1);
            }
            else if(ConfigAUXKB[index]==0xED)
            {
                Send2PortNWait(portnum,(Led_Data&0x07),1);
            }
        }
    }
}

//----------------------------------------------------------------------------
// The function of setting Resolution
//  return : 1 OK, 0 fail
//----------------------------------------------------------------------------
BYTE EnableMouse(BYTE port)
{
    BYTE resault;
    if(!Send2PortNWait(port,0xF4,1))
    {
        resault = 1;
    }
    else
    {
        resault = 0;
    }
    return(resault);
}

//----------------------------------------------------------------------------
// The function of setting Resolution
//  return : 1 OK, 0 fail
//----------------------------------------------------------------------------
BYTE SetResolution(BYTE port, BYTE resolution)
{
    BYTE resault;
    if(!Send2PortNWait(port,0xE8,1))
    {
        if(!Send2PortNWait(port,resolution,1))
        {
            resault = 1;
        }
        else
        {
            resault = 0;
        }
    }
    else
    {
        resault = 0;
    }
    return(resault);
}

//----------------------------------------------------------------------------
// The function of setting samplerate
//  return : 1 OK, 0 fail
//----------------------------------------------------------------------------
BYTE Setsamplerate(BYTE port, BYTE samplerate)
{
    BYTE resault;
    if(!Send2PortNWait(port,0xF3,1))
    {
        if(!Send2PortNWait(port,samplerate,1))
        {
            resault = 1;
        }
        else
        {
            resault = 0;
        }
    }
    else
    {
        resault = 0;
    }
    return(resault);
}

//----------------------------------------------------------------------------
// The Microsoft Intellimouse
//----------------------------------------------------------------------------
const BYTE code Intellimouse_5Byte[3] = 
{	
    200,    200,    80
};	

const BYTE code Intellimouse_4Byte[3] = 
{	
    200,    100,    80
};

BYTE SetIntellimouse(BYTE DriverType, BYTE port)
{
    BYTE index;
    BYTE result;
    result = 0x01;   // pr-set OK
    
    if(DriverType==3)
    {
        for(index=0x00;index<sizeof(Intellimouse_4Byte);index++)
        {
            if(Setsamplerate(port, Intellimouse_4Byte[index])==0x00)
            {
                result = 0x00;
                break;
            }
        }
    }
    else if(DriverType==4)
    {
        for(index=0x00;index<sizeof(Intellimouse_5Byte);index++)
        {
            if(Setsamplerate(port, Intellimouse_5Byte[index])==0x00)
            {
                result = 0x00;
                break;
            }
        }
    }
    return(result);
}

BYTE ReadMouseID(BYTE port)
{
    if(Send2PortNWait(port,0xF2,2)==0x00)
    {
        return(PS2IFAck);
    }
    return(0xFF);
}

//----------------------------------------------------------------------------
// The function of setting external mouse device
//----------------------------------------------------------------------------
BYTE ConfigExtMouse(BYTE portnum)
{  
    BYTE result;
    result = 0x00;
    
    if(SetResolution(portnum,TPResolution))
    {
        if(EnableMouse(portnum))
        {
            result = 0x01;
        }
    }
    return(result);
}

//----------------------------------------------------------------------------
// The function of checking AUX Multiplexed modes
//----------------------------------------------------------------------------
BYTE CheckAuxMux(void)
{
	BYTE current,data_byte,index;
 	current = 1;
	if (KBHIData == 0xF0)		 	// Data from Host is F0h 
 	{  
       	MULPX_Mx_state2 = 1;
      	MULPX_Mx_state3 = 0;
      	current = 0;    			// Do NOT clear State2 and State3 
      	data_byte = 0xF0;
	}
  	else if (KBHIData == 0x56)		// Data from Host is 56h
	{ 
     	if (MULPX_Mx_state2) 		// Current is State2
		{ 
         	MULPX_Mx_state2 = 0;
         	MULPX_Mx_state3 = 1;
        	current = 0;
			data_byte = 0x56;
     	}
	}
	else if (KBHIData == 0xA4)		// Data from Host is A4h 
  	{  
   		if (MULPX_Mx_state3) 		// Current is State3 
		{  
       		MULPX_Multiplex = 1;	// Enable Activate Multiplex mode 
          	data_byte = 0x11; 		// Return Version number 
     	}
	}
 	else if (KBHIData == 0xA5)		// Data from Host is A5h. 
	{   
   		if (MULPX_Mx_state3) 		// Current is State3
		{  
          	MULPX_Multiplex = 0;	// Reveret to Legacy Mode 
           	data_byte = 0x11;       // Return version number 
      	}
  	} 
    else
    {
        data_byte = KBHIData;
    }

 	if (current) 
	{
      	MULPX_Mx_state2 = 0;		// Clear State2 and State3 
		MULPX_Mx_state3 = 0;
   	}
	return(data_byte);
}

// ----------------------------------------------------------------------------
// The function of disable ps2 channel x
// Input :  portnum --> ps2 channel
//          active  --> 1 : On, 0 : Off
//
//  Note : If want to enable mouse device. Please ensrue "MouseDriverIn" is set.
// ----------------------------------------------------------------------------
void OnOffPS2Channel_X(BYTE portnum, BYTE active)
{
    if(portnum==0x00)
    {
        if((PS2_Port0_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port0_Data_CtrlReg&0xFB)!=0x00)
        {
            return;// If this channel isn't PS2 ALT function. return;  
        }                  
    }
    else if(portnum==0x01)
    {
	    if((PS2_Port1_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port1_Data_CtrlReg&0xFB)!=0x00)
        {
            return;// If this channel isn't PS2 ALT function. return;  
        }    
    }
    else if(portnum==0x02)
    {
	    if((PS2_Port2_CLK_CtrlReg&0xFB)!=0x00 || (PS2_Port2_Data_CtrlReg&0xFB)!=0x00)
        {
            return;// If this channel isn't PS2 ALT function. return;  
        }     
    }

    if(IS_MASK_SET(AuxFlags[portnum], DEVICE_IS_MOUSE))
    {
        if(MouseDriverIn)
        {
            if(active == 0x00)
            {
                SET_MASK(AuxFlags2[portnum], DEVICE_NEED_DISABLED);
            }
            else if(active == 0x01)
            {
                SET_MASK(AuxFlags2[portnum], DEVICE_NEED_ENABLED);
            }
            PS2_ReTryCunt = 0x00;
        }
    }
    else
    {
        if(KeyboardDriverIn)
        {
            if(active == 0x00)
            {
                SET_MASK(AuxFlags2[portnum], DEVICE_NEED_DISABLED);
            }
            else if(active == 0x01)
            {
                SET_MASK(AuxFlags2[portnum], DEVICE_NEED_ENABLED);
            }
            PS2_ReTryCunt = 0x00;
        }
    }
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void KBCmdAckByteCunt(BYTE ackcunt)
{
    Main_KB_ACK_CUNT = ackcunt;
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void SetOtherKBNeedUpdataFlag(BYTE KBCmd)
{
    BYTE index;
    
    for(index=0x00;index<3;index++)
    {
        if(IS_MASK_SET(AuxFlags[index], DEVICE_IS_KEYBOARD))
        {
            if(Main_KB_CHN != (index+1))
            {
                if(IS_MASK_CLEAR(AuxFlags[index], DEVICE_NEED_CONFIG))
                {
                    if(KBCmd==0xED)
                    {
                        AuxFlags_KB_CMD[index] |= KB_CMD_0xED;
                    }
                    else if(KBCmd==0xF3)
                    {
                        AuxFlags_KB_CMD[index] |= KB_CMD_0xF3;
                    }
                    else if(KBCmd==0xF4)
                    {
                        AuxFlags_KB_CMD[index] |= KB_CMD_0xF4;
                    }
                    else if(KBCmd==0xF5)
                    {
                        AuxFlags_KB_CMD[index] |= KB_CMD_0xF5;
                    }      
                }
            }
        }
    } 
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void SetStartScanAUXFlag(void)
{
    StartENAUXDevice = 1;
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void AUXData_To_Host_nWait(BYTE data_byte, BYTE portnum)
{
    if(portnum!=0xFF)
    {
        AUXPortNum = portnum;
    }
    SendFromAux(data_byte);

    TR1 = 0;                 	// Disable timer1
    ET1 = 0;                  	// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_26ms>>8;        // Set timer1 counter 26ms
    TL1 = Timer_26ms;           // Set timer1 counter 26ms
    TF1 = 0;                  	// Clear overflow flag
    TR1 = 1;                 	// Enable timer1

	while (!TF1)
	{ 
	    if(IS_MASK_CLEAR(KBHISR, OBF))
        {
            break;
        }   
        if(IS_MASK_SET(KBHISR, IBF))
        {
            break;
        }  
	}

    TR1 = 0;                    // Disable timer 1
    TF1 = 0;			        // clear overflow flag
    ET1 = 1;			        // Enable timer1 interrupt
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void ReSendPS2PendingData(void)
{
    if(MSPending==0x33)
    {
        F_Service_Send_PS2 = 1;
    }
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void CheckNSetMainKBCHN(BYTE PortNum)
{
    if(Main_KB_CHN == 0x00)
    {
        SET_MASK(AuxFlags[PortNum], DEVICE_IS_MAIN_KB);
        Main_KB_CHN = PortNum+1;
    }
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void CheckNSetMainMSCHN(BYTE PortNum)
{
    if(Main_MOUSE_CHN == 0x00)
    {
        SET_MASK(AuxFlags[PortNum], DEVICE_IS_MAIN_MOUSE);
        Main_MOUSE_CHN = PortNum+1;
    }
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void ResetMSPendingData(void)
{
    MSPending = 0x88;
    F_Service_Send_PS2 = 0;
}

//----------------------------------------------------------------------------
// PS2 interface enable/disable OEM function call
//----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Disable port 0 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void DisablePS2Port_0(void)
{
    OnOffPS2Channel_X(0,0);
}

// ----------------------------------------------------------------------------
// Disable port 1 ( send 0xF5 command to device)
// ----------------------------------------------------------------------------
void DisablePS2Port_1(void)
{
    OnOffPS2Channel_X(1,0);
}

// ----------------------------------------------------------------------------
// Disable port 2 ( send 0xF5 command to device) 
// ----------------------------------------------------------------------------
void DisablePS2Port_2(void)
{
    OnOffPS2Channel_X(2,0);
}

// ----------------------------------------------------------------------------
// Enable port 0 ( send 0xF4 command to device) 
// ----------------------------------------------------------------------------
void EnablePS2Port_0(void)
{
    OnOffPS2Channel_X(0,1);
}

// ----------------------------------------------------------------------------
// Enable port 1 ( send 0xF4 command to device)  
// ----------------------------------------------------------------------------
void EnablePS2Port_1(void)
{
    OnOffPS2Channel_X(1,1);
}

// ----------------------------------------------------------------------------
// Enable port 2 ( send 0xF4 command to device)  
// ----------------------------------------------------------------------------
void EnablePS2Port_2(void)
{
    OnOffPS2Channel_X(2,1);
}

// ----------------------------------------------------------------------------
// Power off clock and data pins of all supported channel
// ----------------------------------------------------------------------------
void PS2_PowerOff(void)
{
    BYTE index;
    ResetMSPendingData();
    ClaerPS2IFPendingEvent();

    ClearAUXScanTimeOutCunt();
    SetAUXScanIndexHS(AUXScanIndexFree);
    PS2_ReTryCunt = 0x00;
    SendtoAUXFlag = 0;	
    ECSendtoAUXFlag = 0;
    AUXInactiveCounter = 0;
    StartENAUXDevice = 0;

    for(index=0x00;index<3;index++)
    {
        AuxFlags[index] = 0x00;
        AuxFlags2[index] = 0x00;
    }
    
    if((PS2_Port0_CLK_CtrlReg&0xFB)==0x00 && (PS2_Port0_Data_CtrlReg&0xFB)==0x00)
    {
        PS2_Port0_CLK_CtrlReg = OUTPUT+PULL_DW;
        PS2_Port0_Data_CtrlReg = OUTPUT+PULL_DW;
        SET_MASK(AuxFlags2[0], DEVICE_POWER_DOWN);
    }
           
    if((PS2_Port1_CLK_CtrlReg&0xFB)==0x00 && (PS2_Port1_Data_CtrlReg&0xFB)==0x00)
    {
        PS2_Port1_CLK_CtrlReg = OUTPUT+PULL_DW;
        PS2_Port1_Data_CtrlReg = OUTPUT+PULL_DW;
        SET_MASK(AuxFlags2[1], DEVICE_POWER_DOWN);
    }
    
    if((PS2_Port2_CLK_CtrlReg&0xFB)==0x00 && (PS2_Port2_Data_CtrlReg&0xFB)==0x00)
    {
        PS2_Port2_CLK_CtrlReg = OUTPUT+PULL_DW;
        PS2_Port2_Data_CtrlReg = OUTPUT+PULL_DW;
        SET_MASK(AuxFlags2[2], DEVICE_POWER_DOWN);
    }
}

// ----------------------------------------------------------------------------
// Power on clock and data pins of all supported channel
// ----------------------------------------------------------------------------
void PS2_PowerOn(void)
{
    PS2DeviceInactive();
    if(IS_MASK_SET(AuxFlags2[0], DEVICE_POWER_DOWN))
    {
        CLEAR_MASK(AuxFlags2[0], DEVICE_POWER_DOWN);
        PS2_Port0_CLK_CtrlReg = ALT;
        PS2_Port0_Data_CtrlReg = ALT;
    }
    
    if(IS_MASK_SET(AuxFlags2[1], DEVICE_POWER_DOWN))
    {
        CLEAR_MASK(AuxFlags2[1], DEVICE_POWER_DOWN);
        PS2_Port1_CLK_CtrlReg = ALT;
        PS2_Port1_Data_CtrlReg = ALT;
    }

    if(IS_MASK_SET(AuxFlags2[2], DEVICE_POWER_DOWN))
    {
        CLEAR_MASK(AuxFlags2[2], DEVICE_POWER_DOWN);
        PS2_Port2_CLK_CtrlReg = ALT;
        PS2_Port2_Data_CtrlReg = ALT;
    }    
}

// ----------------------------------------------------------------------------
// Power on clock and data pins of all supported channel
// ----------------------------------------------------------------------------
void PowerOffClearTPPendingData(void)
{
    ResetMSPendingData();
    ClaerPS2IFPendingEvent();
}

void SetPS2CmdACKCounter(BYTE ackcunt)
{
    TPACKCounter = ackcunt;
}

// ----------------------------------------------------------------------------
// Wait ECSend2Port transaction done  
// ----------------------------------------------------------------------------
BYTE WaitECSend2PortACK(BYTE PortNum)
{
    BYTE timeout;
    BYTE channel;

    timeout = 0x00;
    if(AuxFlags[PortNum] == 0x00)
    {
        return(timeout);
    }
    
    TR1 = 0;                    // Disable timer 1
    ET1 = 0;			        // Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_85ms>>8;        // set timer1 counter 85 ms 
    TL1 = Timer_85ms;	        // set timer1 counter 85 ms
    TF1 = 0;			        // clear overflow flag
    TR1 = 1;			        // enable timer1

    while(!TF1)                 // waitting for overflow flag
    {                           // Wait PS2 transaction Done Status
	    if(F_Service_PS2)
	    {
		    if(SendtoAUXFlag)   // Send command to device and transmit done.
		    {
			    F_Service_PS2 = 0;  // Clear main service flag
			    SendtoAUXFlag = 0;	
                PS2_IRQ_Channel = 0xFF; // Clear PS2 2 service flag
			    *asPS2Struct[PortNum].ps2ctrl=PS2_ReceiveMode;  // Enable Receive mode for ACK byte
			    SET_MASK(*asPS2Struct[PortNum].ps2ier, asPS2Struct[PortNum].ctrlbit);  // Enable interrupt for ACK byte
			    ClearAUXScanTimeOutCunt();
		    }
		    else
		    {
                channel = PS2_IRQ_Channel;
                F_Service_PS2 = 0;      // Clear main service flag
                ECSendtoAUXFlag = 0;
                PS2_IRQ_Channel = 0xFF; // Clear PS2 2 service flag
                ProcessECTestAUXACK(channel, 0);
                TR1 = 0;                    // Disable timer 1
                TF1 = 0;			        // clear overflow flag
                break;
		    }
	    }
    }

    if(TF1)
    {
        timeout = 0x01;
    }
    
    TR1 = 0;                    // Disable timer 1
    TF1 = 0;			        // clear overflow flag
    ET1 = 1;			        // Enable timer1 interrupt
    return(timeout);
}


// ----------------------------------------------------------------------------
// Wait Send2Port transaction done  
// ----------------------------------------------------------------------------
void WaitPS2DeviceACK(BYTE PortNum)
{
    TR1 = 0;                    // Disable timer 1
    ET1 = 0;			        // Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_40ms>>8;        // set timer1 counter 40 ms 
    TL1 = Timer_40ms;	        // set timer1 counter 40 ms
    TF1 = 0;			        // clear overflow flag
    TR1 = 1;			        // enable timer1

    while(!TF1)                 // waitting for overflow flag
    {                           // Wait PS2 transaction Done Status
	    if(F_Service_PS2)
	    {
		    if(SendtoAUXFlag)   // Send command to device and transmit done.
		    {
			    F_Service_PS2 = 0;  // Clear main service flag
			    SendtoAUXFlag = 0;	
                PS2_IRQ_Channel = 0xFF; // Clear PS2 2 service flag
			    *asPS2Struct[PortNum].ps2ctrl=PS2_ReceiveMode;  // Enable Receive mode for ACK byte
			    SET_MASK(*asPS2Struct[PortNum].ps2ier, asPS2Struct[PortNum].ctrlbit);  // Enable interrupt for ACK byte
			    ClearAUXScanTimeOutCunt();
		    }
		    else
		    {
                break;          // Receive transmit done.
		    }
	    }
    }
  
    TR1 = 0;                    // Disable timer 1
    TF1 = 0;			        // clear overflow flag
    ET1 = 1;			        // Enable timer1 interrupt
}

// ----------------------------------------------------------------------------
//  Return : 
//          1 : PS2 TDS pending
//          0 : No PS2 TDS pending
// ----------------------------------------------------------------------------
BYTE PS2CheckPendingISR(void)
{
    BYTE pending;
    pending = 0x00;         // Pre-clear pending flag.

    if(IS_MASK_SET(PSSTS3, TDS))
    {
        if(IS_MASK_SET(IER2,Int_PS2_2)&&IS_MASK_CLEAR(ISR2,Int_PS2_2)&&(PSCTL3==PS2_ReceiveMode))
        {
            IRQ_INT18_PS2Interrupt2();
            pending=0x01;
        }
    }
    else if(IS_MASK_SET(PSSTS2, TDS))
    {
        if(IS_MASK_SET(IER2,Int_PS2_1)&&IS_MASK_CLEAR(ISR2,Int_PS2_1)&&(PSCTL2==PS2_ReceiveMode))
        {
            IRQ_INT19_PS2Interrupt1();
            pending=0x01;
        }
    }
    else if(IS_MASK_SET(PSSTS1, TDS))
    {
        if(IS_MASK_SET(IER2,Int_PS2_0)&&IS_MASK_CLEAR(ISR2,Int_PS2_0)&&(PSCTL1==PS2_ReceiveMode))
        {
            IRQ_INT20_PS2Interrupt0();
            pending=0x01;
        }
    }

    return(pending);
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void SetAUXScanIndexHS(BYTE status)
{
    AUX_SCAN_INDEX_HS = status;
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void ClearAUXScanTimeOutCunt(void)
{
    AUX_SCAN_TIMEOUT_CUNT = 0x00;
}

/*-----------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------*/

