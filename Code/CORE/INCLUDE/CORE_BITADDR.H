/*-----------------------------------------------------------------------------
 * TITLE: CORE_BITADDR.H
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/

#ifndef CORE_BITADDR
#define CORE_BITADDR

extern BBYTE Ccb42;
extern bit Ccb42_INTR_KEY;
extern bit Ccb42_INTR_AUX;
extern bit Ccb42_SYS_FLAG;
extern bit Ccb42_RV1;
extern bit Ccb42_DISAB_KEY;
extern bit Ccb42_DISAB_AUX;
extern bit Ccb42_XLATE_PC;
extern bit Ccb42_RV2;

//----------------------------------------------------------------------------
// MULPX - Active PS/2 Mulplexing control byte
//----------------------------------------------------------------------------
extern BBYTE MULPX;
extern bit EnableTP;
extern bit MULPX_Mx_state2;
extern bit MULPX_Mx_state3;
extern bit MULPX_Multiplex;
extern bit MULPX_RV1;
extern bit MULPX_RV2;
extern bit MULPX_RV3;
extern bit MULPX_RV4;

//----------------------------------------------------------------------------
// PS2 interface control flag
//----------------------------------------------------------------------------
extern BBYTE AuxTestFlagS;
extern bit PS2StartBit;
extern bit MouseDriverIn;
extern bit KeyboardDriverIn;
extern bit AUX2ByteCommand;
extern bit AuxTestFlagS_RV1;
extern bit AuxTestFlagS_RV2;
extern bit AuxTestFlagS_RV3;
extern bit AuxTestFlagS_RV4;

//----------------------------------------------------------------------------
// Led_Ctrl, Led_Data, Save_Kbd_State
// Accessed through Commands 9Eh and 9Fh.
//----------------------------------------------------------------------------
extern BBYTE Led_Ctrl; 		// Extended LED Control Byte. 
extern bit Led_Ctrl_SCROLL;
extern bit Led_Ctrl_NUM;
extern bit Led_Ctrl_CAPS;
extern bit Led_Ctrl_OVL;
extern bit Led_Ctrl_LED4;
extern bit Led_Ctrl_LED5;
extern bit Led_Ctrl_LED6;
extern bit Led_Ctrl_LED7;

//----------------------------------------------------------------------------
// Events that require service in main. 
//----------------------------------------------------------------------------
extern BBYTE Service;
extern bit F_Service_PCI;
extern bit F_Service_UNLOCK;
extern bit F_Service_SEND;
extern bit F_Service_Send_PS2;
extern bit F_Service_PS2;
extern bit F_Service_MS_1;
extern bit F_Service_PCI2;
extern bit F_Service_KEY;

extern BBYTE Service1;
extern bit F_Service_Low_LV;
extern bit F_Service_PCI3;
extern bit F_Service_CIR;
extern bit F_Service_PCI4;
extern bit F_Service_OEM_1;
extern bit F_Service_OEM_2;
extern bit F_Service_OEM_3;
extern bit F_Service_OEM_4;

//----------------------------------------------------------------------------
// tate of local keyboard LEDs. 
//----------------------------------------------------------------------------
extern BBYTE Led_Data; 
extern bit Led_Data_SCROLL;
extern bit Led_Data_NUM;
extern bit Led_Data_CAPS;
extern bit Led_Data_OVL;
extern bit Led_Data_LED4;
extern bit Led_Data_LED5;
extern bit Led_Data_LED6;
extern bit Led_Data_LED7;

//----------------------------------------------------------------------------
// Scanner_State 
//----------------------------------------------------------------------------
extern BBYTE Scanner_State;
extern bit Scanner_State_NUM_LOCK;
extern bit Scanner_State_LEFT;
extern bit Scanner_State_RIGHT;
extern bit Scanner_State_ALT;
extern bit Scanner_State_CONTROL;
extern bit Scanner_State_OVERLAY;
extern bit Scanner_State_FN;
extern bit Scanner_State_FN_SILENT;

//----------------------------------------------------------------------------
// Gen_Info
//----------------------------------------------------------------------------
extern BBYTE Gen_Info;
extern bit Gen_Info_LED_CHANGE;
extern bit Gen_Info_TYPM_CHANGE;
extern bit Gen_Info_CODE_CHANGE;
extern bit Gen_Info_SCAN_LOCKED;
extern bit Gen_Info_PASS_ENABLE;
extern bit Gen_Info_BREAK_AUXD;
extern bit Gen_Info_BREAK_AUXK;
extern bit Gen_Info_BREAK_SCAN;

//----------------------------------------------------------------------------
// Kbd_Response
// Response code from keyboard.  0 = no response.
//----------------------------------------------------------------------------
extern BBYTE Kbd_Response;
extern bit Kbd_Response_SECOND_ACK;
extern bit Kbd_Response_CMD_RESPONSE;

//----------------------------------------------------------------------------
//  
//----------------------------------------------------------------------------
extern BBYTE AuxScanFlagS;
extern bit SendtoAUXFlag;	
extern bit ECSendtoAUXFlag;
extern bit StartScanAUXDevice;
extern bit StartENAUXDevice;
extern bit AUXInterfaceBusy;
extern bit AuxScanFlagS_RV3;
extern bit AuxScanFlagS_RV1;
extern bit AuxScanFlagS_RV2;

//----------------------------------------------------------------------------
//  
//----------------------------------------------------------------------------
extern BBYTE CustomFlag;
extern bit KbdNeedResponseFlag;
extern bit ExtendMatrix;	
extern bit Isr_Int1_Occur;
extern bit FastA20;
extern bit ChkAUXRespFlag2;
extern bit ECCheckBurstMode;
extern bit OEM_Isr_Int1_Request;
extern bit FnStickKey;

//----------------------------------------------------------------------------
//  
//----------------------------------------------------------------------------
extern BBYTE SMBusFlagS;
extern bit SMBusFlagS_RV0;
extern bit SMBusFlagS_RV1;
extern bit SMBusFlagS_RV2;
extern bit SMBusFlagS_RV3;
extern bit SMBusFlagS_RV4;
extern bit SMBusFlagS_RV5;
extern bit SMBusFlagS_RV6;
extern bit SMBusFlagS_RV7;
#endif
