/*-----------------------------------------------------------------------------
 * Filename: CORE_MEMORY.H     For Chipset: ITE.IT85XX
 *
 * Function: Memory Definition for extern all code base reference
 *
 * [Memory Map Description]
 *
 * =Chip Internal= 0x00-0xFF
 * 0x00-0xFF     For Kernel and Chip Level use
 *
 ***************************************************
 * Chip 8500       : External ram 0x000-0x7FF
 * Chip Other 85XX : External ram 0x000-0xFFF
 ***************************************************
 * Memory Map :
 * 0x000-0x0FF   For Kernel Core/Module     
 * 0x600-0x6FF   For ITE flash utility,EC SPI rom read write function.
 * 0x700-0x7FF   For Keil C Complier and Ram Code Space (for SPI programming).
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef CORE_DAT_H
#define CORE_DAT_H

//----------------------------------------------------------------------------
// The Controller Command Byte.  Accessed through Commands 20h
// and 60h.  First byte in the 0 through 1F space in an 8042.
//----------------------------------------------------------------------------
#define INTR_KEY     0x01	//bit0
#define INTR_AUX     0x02	//bit1
//#define SYS_FLAG     0x04	//bit2
#define DISAB_KEY    0x10	//bit4
#define DISAB_AUX    0x20	//bit5
#define XLATE_PC     0x40	//bit6

#define all 		byte
#define SCROLL   	bit0
#define NUM      	bit1
#define CAPS      	bit2
#define OVL     	bit3
#define LED4    	bit4
#define LED5     	bit5
#define LED6    	bit6
#define LED7    	bit7

extern	IBYTE	KBHICmd;
extern	IBYTE 	KBHIStep;
extern	IBYTE	KBHIData;
extern	IBYTE 	KBHIData1;
extern	IBYTE 	KBHIData2;
extern	IBYTE	PM1Cmd;
extern	IBYTE	PM1Step;
extern	IBYTE 	PM1Data;
extern	IBYTE	PM1Data1;
extern	IBYTE 	PM1Data2;
extern	IBYTE	PM2Cmd;
extern	IBYTE	PM2DataCount;
extern	IBYTE 	PM2Data;
extern	IBYTE	PM2Data1;
extern	IBYTE 	PM2Data2;

extern 	IBYTE 	Tmp_Load;

//----------------------------------------------------------------------------
// Timer_A, Timer_B 
// Bits 0 through 3 of TIMER are reserved for "count". 
//----------------------------------------------------------------------------
extern 	TIMER Timer_A;		// Timer A. Timer A has a time base of 1 mS. 
#define HIF2_SAFETY  count	// Secondary host interface timer.
#define TMR_SCAN     bit4   // Scanner interval enabled.
#define TMR_GENTMO   bit5   // General timeouts.
//                   bit6 	//
//                   bit7   //
extern TIMER Timer_B;		// Timer B. Timer A has a time base of 150 uS.
#define SEND_DELAY   count  // Internal device send delay count used with SEND_ENABLE.
#define SEND_ENABLE  bit4   // Internal device send request.
#define INH_CLEAR    bit5   // Delay to enable serial clock lines.
#define UNLOCK_TMO   bit6   // Delay for unlock request.
//                   bit7   //

extern 	IBYTE 	*data Tmp_Pntr;
extern	IBYTE 	Timer1msCnt;		// 0x43
extern	IBYTE	Timer5msCnt;		// 0x44
extern	IBYTE	Timer100msCnt;		// 0x45
extern 	IBYTE	Timer100msCntB;		// 0x46
extern	IBYTE 	Timer1SecCnt; 		// 0x47
extern	IBYTE	Timer1MinCnt;		// 0x48

extern 	BYTE code *data Tmp_code_pointer; 
extern  IBYTE   Timer125msCnt;      // 0x57
extern  IBYTE   Timer250msCnt;      // 0x58

extern  IBYTE   PM3Cmd;			    // 0x59
extern  IBYTE   PM3DataCount;	    // 0x5A
extern  IBYTE   PM3Data;		    // 0x5B
extern  IBYTE   PM3Data1;		    // 0x5C
extern  IBYTE   PM3Data2;		    // 0x5D

extern  IBYTE   MainFucnLow;	    // 0x5E
extern  IBYTE   MainFucnHigh;	    // 0x5F
    
extern	IBYTE	ITempB01;
extern	IBYTE	ITempB02;
extern	IBYTE	ITempB03;
extern	IBYTE	ITempB04;
extern	IBYTE	ITempB05;
extern	IBYTE	ITempB06;
extern	IWORD	ITempW01;
extern 	IBYTE 	bscan_matrix[];

/*****************************************************************************/
/* INTERNAL INDIRECT RAM AREA     (0x80 ~ 0xFF) ******************************/
/*****************************************************************************/
//----------------------------------------------------------------------------
// Internal ram variables (Indirect)[0x80-0xCF]
//----------------------------------------------------------------------------
//PS2 Port Service
extern 	IIBYTE		AUXInactiveCounter;     // 0x80
extern	IIBYTE		CheckAUXIndex;          // 0x81
extern  IIBYTE		TPResolution;           // 0x82
extern	IIBYTE		TPSamplingRate;         // 0x83
extern 	IIBYTE      PS2_IRQ_Channel;	    // 0x84
extern  IIBYTE		TPACKCounter;           // 0x85
extern  IIBYTE 	    AUXCmdFFCnt;	        // 0x86
extern  IIBYTE 	    AUXPortNum;			    // 0x87
extern  IIBYTE 	    AuxFlags[];             // 0x88 ~ 0x8A
#define DEVICE_IS_MOUSE             BIT7
#define DEVICE_IS_KEYBOARD          BIT6
#define DEVICE_IS_MAIN_MOUSE        BIT5
#define DEVICE_IS_MAIN_KB           BIT4
#define DEVICE_NEED_CONFIG          BIT3
#define DEVICE_MS_DRIVER_NO_MATCH   BIT2
#define DEVICE_NEED_INIT            BIT1
#define DEVICE_IS_ATTACHED          BIT0

extern  IIBYTE	    MousePendingBuf;		// 0x8B
extern  IIBYTE	    ScanAUXStepIndex;       // 0x8C
extern  IIBYTE 	    AuxFlags2[];            // 0x8D ~ 0x8F
#define DEVICE_POWER_DOWN           BIT7
#define DEVICE_ENABLED_TIME_OUT     BIT6
#define DEVICE_IS_ENABLED           BIT5
#define DEVICE_NEED_ENABLED         BIT4

#define DEVICE_DISABLE_TIME_OUT     BIT2
#define DEVICE_IS_DISABLED          BIT1
#define DEVICE_NEED_DISABLED        BIT0

extern  IIBYTE      MS_ID_CUNT;             // 0x90
extern  IIBYTE      MS_DRIVER_TYPE;         // 0x91
extern  IIBYTE      KB_ACK_DELAY_CUNT;      // 0x92
extern  IIBYTE      KB_CodeSet;             // 0x93
extern  IIBYTE      PS2KB_Typematic;        // 0x94
extern  IIBYTE      PS2IFAck;               // 0x95
extern  IIBYTE      Save_Typematic;         // 0x96
extern  IIBYTE 	    PS2PortxData[3];        // 0x97
extern  IIBYTE 	    KB_Typematic;           // 0x98

extern  IIBYTE 	    Main_MOUSE_CHN;         // 0x9B
extern  IIBYTE 	    Main_KB_CHN;            // 0x9C
extern  IIBYTE 	    Main_KB_ACK_CUNT;       // 0x9D
extern  IIBYTE 	    AUX_SCAN_INDEX;         // 0x9E
extern  IIBYTE 	    AUX_SCAN_INDEX_HS;      // 0x9F
extern  IIBYTE 	    AUX_SCAN_TIMEOUT_CUNT;  // 0xA0
extern  IIBYTE 	    SKIP_AUX_SCAN_CUNT;     // 0xA1
extern  IIBYTE 	    AuxFlags_KB_CMD[]; 		// 0xA2 ~ 0xA4
#define KB_CMD_0xF5     BIT0
#define KB_CMD_0xF4     BIT1
#define KB_CMD_0xF3     BIT2
#define KB_CMD_0xED     BIT3

extern  IIBYTE 	    AuxFlags_MS_CMD[];      // 0xA5 ~ 0xA7
extern  IIBYTE 	    AuxScanWDT;             // 0xA8;

//--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -
extern  IIBYTE      SMBUS_STATUS;           // 0xA9
extern  IIBYTE		PS2_SSIRQ_Channel;      // 0xAA
extern  IIBYTE		PS2_KBCmd_BK;           // 0xAB
extern  IIBYTE      KB_Command;             // 0xAC
extern  IIBYTE      MSPending;              // 0xAD
extern  IIBYTE      PS2_ReTryCunt;          // 0xAE
extern  IIBYTE      SMBCRC8_A;              // 0xAF

extern 	INT_VAR Int_Var;
//----------------------------------------------------------------------------
// Flag
//----------------------------------------------------------------------------
extern 	FLAGS	Flag;
#define SCAN_INH		 bit0 // 1 = Scanner transmission inhibited. 
#define SENDING_SCAN_RC  bit1 // For diagnostic mode. 
#define PASS_READY       bit2 // Password loaded. 
#define NEW_PRI_K        bit3 // Switch to new primary keyboard. 
#define NEW_PRI_M        bit4 // Switch to new primary mouse. 
#define VALID_SCAN       bit5
#define LED_ON           bit6
#define ENTER_LOW_POWER  bit7 // Go into low power mode. 
#define ACPI_IN_PROGRESS bit8
#define ACPI_SMB_ALARM   bit9
#define LEGACY_SMB_ALARM bit10
#define ALT_PRESSED      bit11// External keyboard ALT key state. 
#define CTRL_PRESSED     bit12// External keyboard CTRL key state. 
#define DETECT_EC_B0     bit13// Used to allow Insyde Software's 
#define DETECT_EC_B1     bit14// embedded controller to be detected.
#define Aux_Not_RESP     bit15

extern	EXT_CB2		Ext_Cb2;
extern IIBYTE Save_Kbd_State;

/* maskLEDS is used by Keyboard Command EDh to qualify the data.
   If any bits outside of the mask are attempted to be modifed
   by Keyboard Command EDh, the command is rejected. */
#define maskLEDS     0x07

/* shiftCODESET is used to shift the bits for the saved Scan Code
   Set number to the lower part of the byte.  maskCODESET is then
   used to isolate those bits. */
#define shiftCODESET 3
#define maskCODESET  0x03

/* The enabled state of the external keyboard
   modified by Keyboard Command F4h/F5h. */
#define maskAUXENAB  (1 << 5)

/* Bit 0 through 5 used for code. */
#define maskKBD_RESPONSE_CODE 0x03F

/* Multibyte response codes. */
#define respCMD_AC   0x80  // Diagnostic dump.  Sends version string. 
#define respCMD_CFG  0x81  // Configuration Table. 
#define respARRAY    0x82  // Sends bytes in an array. 
// Codes 83h through 8Fh are reserved for the core code. 
//extern 	IIBYTE		Save_Typematic;
extern 	XBYTE 	*idata	Tmp_XPntr;
extern	XBYTE	*idata	Tmp_XPntr1;
extern  IIBYTE 		KBHIReponse ;
extern  key_state	temp_scanner_state;

extern 	XBYTE	bKEY_BUFF[];
//----------------------------------------------------------------------------
//Pass_xxx
//----------------------------------------------------------------------------
extern 	XBYTE 	Pass_Buff[];  	// Password buffer. 
extern 	XBYTE 	Pass_Buff_Idx;  // Password buffer index
                                // (0 to PASS_SIZE-1). 
extern 	XBYTE 	Pass_On;        // Security Code On byte. 
extern 	XBYTE 	Pass_Off;       // Security Code Off byte. 
extern 	XBYTE 	Pass_Make1;     // Reject make code 1. 
extern 	XBYTE 	Pass_Make2;     // Reject make code 2. 
extern  XBYTE  	PS_Debug_ECToHost;  //_at_ 0x1D
extern  XBYTE   PS_Debug_DeviceToEC;//_at_ 0x1E
extern  XBYTE   DebugTest;      //_at_ 0x1F

//*******************************************************
//#ifdef KB_HW_KeyScan   // Hardware scan keyboard
//*******************************************************
extern  XBYTE   KB_HW_ExtendKeyIndex;       // 0x20
extern  XBYTE   KB_HW_ExtendKeyTypematic;   // 0x21

//*******************************************************
//#endif // KB_HW_KeyScan Hardware scan keyboard
//*******************************************************

extern 	XBYTE 	bTMrepeat;
extern 	XBYTE 	bTMdelay;
extern 	XBYTE 	bTMcount;
extern 	XBYTE 	diode_key;
extern 	BYTE code *Scanner_Table_Pntr;
extern 	BYTE code *Extendkey_Table_Pntr;

extern 	XBYTE	PS2BufHead;
extern 	XBYTE	PS2BufTail;
extern	XBYTE	PS2DataPinStatusCounter;
extern 	XBYTE	PS2TypeCounter;	// Dino 1128
extern 	XBYTE	WinFlashMark;
extern 	XBYTE	RamCodePort;	

extern  XBYTE   KBDataPending[];            //_at_ 0x47;
extern  XBYTE   KBPendingRXCount;           //_at_ 0x4B;
extern  XBYTE   KBPendingTXCount;           //_at_ 0x4C;
extern  XBYTE	PS2DataPinStatus;		    //_at_ 0x4D;

extern  XBYTE 	*SMBus1BlockPtr; 			// 0x50;	// 2 bytes
extern  XBYTE 	*SMBus2BlockPtr; 			// 0x52;	// 2 bytes
extern  XBYTE 	*SMBus3BlockPtr; 			// 0x54;	// 2 bytes

extern  XBYTE	DB_SMBusAddr;				// 0x56
extern  XBYTE	DB_SMBusCmd;				// 0x57
extern  XBYTE	DB_SMBusBCunt;				// 0x58
extern  XBYTE	DB_SMBusFlag1;				// 0x59	
extern  XBYTE	DB_SMBusFlag2;				// 0x5A	
extern  XBYTE	DB_SMBusFlag3;				// 0x5B	
#define DB_S	BIT0
#define DB_R	BIT1
#define DB_RB	BIT2
#define DB_WB	BIT3
#define DB_RW	BIT4
#define DB_WW	BIT5
#define DB_RBB	BIT6
#define DB_WBB	BIT7

extern  XBYTE	DB_SMBusData[];				// 0x5C 20 bytes

extern  XBYTE	DB_SMBusAck1;				// 0x7c
extern  XBYTE	DB_SMBusACDID;				// 0x7D

extern	XBYTE	ExtendScanPin;
extern	XBYTE	RSTStatus;
extern 	XBYTE	RamcodeCmd;
extern 	XBYTE	RamcodeSend;
extern 	BYTE code *Tmp_Code_Pntr; 
extern 	FUNCT_PTR_V_V Tmp_Func_Pnter;
extern 	XBYTE	SMBus1RecoverCunt;			// 0x89;	
extern 	XBYTE	SMBus2RecoverCunt;			// 0x8A;	
extern 	XBYTE	SMBus3RecoverCunt;			// 0x8B;	
extern  XBYTE	SMBus4RecoverCunt;		    // 0x8C;	
extern 	XBYTE   FN_Key_Break;               // 0x8D;
extern 	XBYTE   FN_Key_Break_HS;            // 0x8E;
extern  XBYTE   SMBus_BusyRecover;          // 0x8F;

extern 	XBYTE	SPIIDBuf[];				// 	_at_ 0x90
extern 	XBYTE	SPIIndex;				// 	_at_ 0x94	
extern	XBYTE	SPIAddrCycle[];			//	_at_ 0x95
extern	XBYTE	SPIAEraseCmd;			//	_at_ 0x98
extern	XBYTE	SPIReadStatus;			//	_at_ 0x99	
extern	XBYTE	SPIWriteStatus;			//	_at_ 0x9A	
extern	XBYTE	*SPIDataPointer;		//	_at_ 0x9B
#define SPIDataPointerLowByte (*(XBYTE*)( 0x09C))	//	_at_ 0x9C	overlay SPIDataPointer low byte
extern 	XBYTE	SPIID;					// 	_at_ 0x9D
extern	XBYTE   SSTDeviceID;			//	_at_ 0x9E
extern  XBYTE   EC_Indirect_Selection;  //  _at_ 0x9F

extern  XBYTE   FnKeyBundledFalg[];     //  _at_ 0xE0 ~ 0xEF, 16 bytes

extern 	XBYTE  	KeyScanKSI;	
extern 	XBYTE  	KeyScanKSO;	
extern 	XBYTE	KeyScanACK;
extern 	XBYTE  	ExtKeyScanKSI;	
extern 	XBYTE  	ExtKeyScanKSO;	
extern 	XBYTE	UtilityFlag;

#define KBDebug   		BIT6    // 1: for keyboard matrix utility
#define SMBusDebug		BIT7    // 1: for smbus utility

extern 	XBYTE  	KBCPortPending;	// 0xF0		
extern 	XBYTE  	PMPortPending;	// 0xF1	
//extern  XBYTE	PS2Buf[];

/* Bits 7 and 6 are used to select the scanner table.

   Bit
   7 6  Selection
   --- -----------
   0 0 RAM Table
   0 1 ROM Table 1
   1 0 ROM Table 2
   1 1 ROM Table 3

   shiftSCAN_SELECT is used to shift the bits for the scanner
   selection designation to the lower part of the byte.
   maskSCAN_SELECT is then used to isolate those bits. */
#define shiftSCAN_SELECT 6
#define maskSCAN_SELECT  0x03

#endif  
