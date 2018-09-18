/*-----------------------------------------------------------------------------
 * TITLE: CORE_BITADDR.C
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/

//----------------------------------------------------------------------------
// Bit addressing variables [0x20-0x2F]
//----------------------------------------------------------------------------
volatile unsigned char bdata Ccb42 _at_ 0x20;
sbit Ccb42_INTR_KEY  = Ccb42^0;
sbit Ccb42_INTR_AUX  = Ccb42^1;
sbit Ccb42_SYS_FLAG  = Ccb42^2;
sbit Ccb42_RV1       = Ccb42^3;
sbit Ccb42_DISAB_KEY = Ccb42^4;
sbit Ccb42_DISAB_AUX = Ccb42^5;
sbit Ccb42_XLATE_PC  = Ccb42^6;
sbit Ccb42_RV2       = Ccb42^7;
                                    //Reserved 0x21

volatile unsigned char bdata MULPX _at_ 0x22;
sbit EnableTP      		= MULPX^0;
sbit MULPX_Mx_state2    = MULPX^1;
sbit MULPX_Mx_state3    = MULPX^2;
sbit MULPX_Multiplex    = MULPX^3;
sbit MULPX_RV1          = MULPX^4;
sbit MULPX_RV2          = MULPX^5;
sbit MULPX_RV3          = MULPX^6;
sbit MULPX_RV4          = MULPX^7;

volatile unsigned char bdata AuxTestFlagS _at_ 0x23;
sbit PS2StartBit            = AuxTestFlagS^0;
sbit MouseDriverIn          = AuxTestFlagS^1;
sbit KeyboardDriverIn       = AuxTestFlagS^2;
sbit AUX2ByteCommand        = AuxTestFlagS^3;
sbit AuxTestFlagS_RV1       = AuxTestFlagS^4;
sbit AuxTestFlagS_RV2       = AuxTestFlagS^5;
sbit AuxTestFlagS_RV3       = AuxTestFlagS^6;
sbit AuxTestFlagS_RV4       = AuxTestFlagS^7;

volatile unsigned char bdata SMBusFlagS _at_ 0x24;
sbit SMBusFlagS_RV0			= SMBusFlagS^0;	
sbit SMBusFlagS_RV1			= SMBusFlagS^1;	
sbit SMBusFlagS_RV2		    = SMBusFlagS^2;
sbit SMBusFlagS_RV3     	= SMBusFlagS^3;	
sbit SMBusFlagS_RV4		    = SMBusFlagS^4;	
sbit SMBusFlagS_RV5		    = SMBusFlagS^5;
sbit SMBusFlagS_RV6         = SMBusFlagS^6;
sbit SMBusFlagS_RV7         = SMBusFlagS^7;

volatile unsigned char bdata Led_Ctrl _at_ 0x25;
sbit Led_Ctrl_SCROLL = Led_Ctrl^0;
sbit Led_Ctrl_NUM    = Led_Ctrl^1;
sbit Led_Ctrl_CAPS   = Led_Ctrl^2;
sbit Led_Ctrl_OVL    = Led_Ctrl^3;
sbit Led_Ctrl_LED4   = Led_Ctrl^4;
sbit Led_Ctrl_LED5   = Led_Ctrl^5;
sbit Led_Ctrl_LED6   = Led_Ctrl^6;
sbit Led_Ctrl_LED7   = Led_Ctrl^7;

volatile unsigned char bdata Service	_at_ 0x26;
sbit F_Service_PCI  	= Service^0;
sbit F_Service_UNLOCK 	= Service^1;
sbit F_Service_SEND 	= Service^2;
sbit F_Service_Send_PS2 = Service^3;
sbit F_Service_PS2 		= Service^4;
sbit F_Service_MS_1  	= Service^5;
sbit F_Service_PCI2  	= Service^6;
sbit F_Service_KEY  	= Service^7;

volatile unsigned char bdata Service1 _at_ 0x27;	
sbit F_Service_Low_LV  		= Service1^0; 
sbit F_Service_PCI3 		= Service1^1;
sbit F_Service_CIR  	  	= Service1^2;
sbit F_Service_PCI4         = Service1^3;
sbit F_Service_OEM_1      	= Service1^4;
sbit F_Service_OEM_2      	= Service1^5;
sbit F_Service_OEM_3  		= Service1^6;
sbit F_Service_OEM_4 	    = Service1^7;

volatile unsigned char bdata Led_Data _at_ 0x28;
sbit Led_Data_SCROLL = Led_Data^0;
sbit Led_Data_NUM    = Led_Data^1;
sbit Led_Data_CAPS   = Led_Data^2;
sbit Led_Data_OVL    = Led_Data^3;
sbit Led_Data_LED4   = Led_Data^4;
sbit Led_Data_LED5   = Led_Data^5;
sbit Led_Data_LED6   = Led_Data^6;
sbit Led_Data_LED7   = Led_Data^7;

volatile unsigned char bdata Scanner_State _at_ 0x29;
sbit Scanner_State_NUM_LOCK  = Scanner_State^0;
sbit Scanner_State_LEFT      = Scanner_State^1;
sbit Scanner_State_RIGHT     = Scanner_State^2;
sbit Scanner_State_ALT       = Scanner_State^3;
sbit Scanner_State_CONTROL   = Scanner_State^4;
sbit Scanner_State_OVERLAY   = Scanner_State^5;
sbit Scanner_State_FN        = Scanner_State^6;
sbit Scanner_State_FN_SILENT = Scanner_State^7;

volatile unsigned char bdata Gen_Info _at_ 0x2A;
sbit Gen_Info_LED_CHANGE  = Gen_Info^0;
sbit Gen_Info_TYPM_CHANGE = Gen_Info^1;
sbit Gen_Info_CODE_CHANGE = Gen_Info^2;
sbit Gen_Info_SCAN_LOCKED = Gen_Info^3;
sbit Gen_Info_PASS_ENABLE = Gen_Info^4;
sbit Gen_Info_BREAK_AUXD  = Gen_Info^5;
sbit Gen_Info_BREAK_AUXK  = Gen_Info^6;
sbit Gen_Info_BREAK_SCAN  = Gen_Info^7;

volatile unsigned char bdata Kbd_Response _at_ 0x2B;
// Don't use bit0 ~ bit5
sbit Kbd_Response_SECOND_ACK   = Kbd_Response^6;
sbit Kbd_Response_CMD_RESPONSE = Kbd_Response^7;

volatile unsigned char bdata AuxScanFlagS _at_ 0x2C;
sbit SendtoAUXFlag			= AuxScanFlagS^0;	
sbit ECSendtoAUXFlag        = AuxScanFlagS^1;
sbit StartScanAUXDevice     = AuxScanFlagS^2;
sbit StartENAUXDevice       = AuxScanFlagS^3;
sbit AUXInterfaceBusy       = AuxScanFlagS^4;
sbit AuxScanFlagS_RV3       = AuxScanFlagS^5;
sbit AuxScanFlagS_RV1       = AuxScanFlagS^6;
sbit AuxScanFlagS_RV2       = AuxScanFlagS^7;

volatile unsigned char bdata CustomFlag _at_ 0x2D;
sbit KbdNeedResponseFlag	= CustomFlag^0;
sbit ExtendMatrix			= CustomFlag^1;
sbit Isr_Int1_Occur         = CustomFlag^2;
sbit FastA20		        = CustomFlag^3;
sbit ChkAUXRespFlag2		= CustomFlag^4;
sbit ECCheckBurstMode		= CustomFlag^5;
sbit OEM_Isr_Int1_Request   = CustomFlag^6;
sbit FnStickKey             = CustomFlag^7;

/*****************************************************************************/
//      NOTE : 
/*****************************************************************************/
// Don't use bit addressble 0x2E and 0x2F.
/*****************************************************************************/