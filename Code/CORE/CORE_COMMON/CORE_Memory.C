/*-----------------------------------------------------------------------------
 * Filename: CORE_MEMORY.C     For Chipset: ITE.IT85XX
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
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Internal ram variables (direct)[0x30-0x7F]
//----------------------------------------------------------------------------
IBYTE 		KBHICmd 						_at_ 0x30;
IBYTE 		KBHIStep 						_at_ 0x31;
IBYTE 		KBHIData						_at_ 0x32;
IBYTE		KBHIData1						_at_ 0x33;
IBYTE 		KBHIData2						_at_ 0x34;
IBYTE   	PM1Cmd							_at_ 0x35;
IBYTE 		PM1Step							_at_ 0x36;
IBYTE		PM1Data							_at_ 0x37;
IBYTE 		PM1Data1						_at_ 0x38;
IBYTE 		PM1Data2						_at_ 0x39;
IBYTE   	PM2Cmd							_at_ 0x3A;
IBYTE 		PM2DataCount					_at_ 0x3B;
IBYTE		PM2Data							_at_ 0x3C;
IBYTE 		PM2Data1						_at_ 0x3D;
IBYTE 		PM2Data2						_at_ 0x3E;
IBYTE   	Tmp_Load						_at_ 0x3F;

TIMER		Timer_A							_at_ 0x40;
TIMER  		Timer_B							_at_ 0x41;
IBYTE   	*data Tmp_Pntr					_at_ 0x42;
IBYTE 		Timer1msCnt						_at_ 0x43;
IBYTE		Timer5msCnt						_at_ 0x44;
IBYTE		Timer100msCnt					_at_ 0x45;
IBYTE		Timer100msCntB					_at_ 0x46;
IBYTE 		Timer1SecCnt					_at_ 0x47;
IBYTE		Timer1MinCnt					_at_ 0x48;
data union  Unew_keyl new_keyl 				_at_ 0x49;
data struct Sscan scan 						_at_ 0x4A;	// 3 BYTES
data union	KEY new_keyh 					_at_ 0x4D; 	// Holds new scan key address and debounce status.
data union 	KEY typematic 					_at_ 0x4E;	// Holds new_keyh for typematic action.
data union  KEY new_extendkey 				_at_ 0x4F; 	// For extend keys
data struct Sscan extendscan 				_at_ 0x50;	// 3 BYTES
data union  Unew_keyl extendstatus 			_at_ 0x53;
data union 	KEY etkeytypematic 				_at_ 0x54;
BYTE code 	*data Tmp_code_pointer 			_at_ 0x55;
IBYTE		Timer125msCnt                   _at_ 0x57;
IBYTE       Timer250msCnt                   _at_ 0x58;

IBYTE   	PM3Cmd							_at_ 0x59;
IBYTE 		PM3DataCount					_at_ 0x5A;
IBYTE		PM3Data							_at_ 0x5B;
IBYTE 		PM3Data1						_at_ 0x5C;
IBYTE 		PM3Data2						_at_ 0x5D;
IBYTE 		MainFucnLow						_at_ 0x5E;
IBYTE 		MainFucnHigh					_at_ 0x5F;
									    //Reserved 0x60 ~ 0x64
IBYTE		ITempB01						_at_ 0x65;
IBYTE		ITempB02						_at_ 0x66;
IBYTE		ITempB03						_at_ 0x67;
IBYTE		ITempB04						_at_ 0x68;
IBYTE		ITempB05						_at_ 0x69;
IBYTE		ITempB06						_at_ 0x6A;
IWORD		ITempW01						_at_ 0x6B;
									    //Reserved 0x6C
IBYTE 		bscan_matrix[MAX_SCAN_LINES] 	_at_ 0x6D;	

//----------------------------------------------------------------------------
// Internal ram variables (Indirect)[0x80-0xCF]
//----------------------------------------------------------------------------
//PS2 Port Service
IIBYTE		AUXInactiveCounter				_at_ 0x80;
IIBYTE		CheckAUXIndex					_at_ 0x81;
IIBYTE		TPResolution					_at_ 0x82;
IIBYTE		TPSamplingRate					_at_ 0x83;
IIBYTE		PS2_IRQ_Channel					_at_ 0x84;
IIBYTE		TPACKCounter					_at_ 0x85;
IIBYTE 	    AUXCmdFFCnt					    _at_ 0x86;
IIBYTE 	    AUXPortNum					    _at_ 0x87;
IIBYTE 	    AuxFlags[3] 				    _at_ 0x88;	
IIBYTE	    MousePendingBuf					_at_ 0x8B;
IIBYTE	    ScanAUXStepIndex                _at_ 0x8C; 
IIBYTE 	    AuxFlags2[3]                    _at_ 0x8D;  

IIBYTE      MS_ID_CUNT                      _at_ 0x90; 
IIBYTE      MS_DRIVER_TYPE                  _at_ 0x91; 
IIBYTE      KB_ACK_DELAY_CUNT               _at_ 0x92;
IIBYTE      KB_CodeSet                      _at_ 0x93;
IIBYTE      PS2KB_Typematic                 _at_ 0x94;
IIBYTE      PS2IFAck                        _at_ 0x95;   
IIBYTE      Save_Typematic                  _at_ 0x96;
IIBYTE 	    PS2PortxData[3] 			    _at_ 0x97;	
IIBYTE 	    KB_Typematic                    _at_ 0x9A;
IIBYTE 	    Main_MOUSE_CHN                  _at_ 0x9B;
IIBYTE 	    Main_KB_CHN                     _at_ 0x9C;
IIBYTE 	    Main_KB_ACK_CUNT                _at_ 0x9D;
IIBYTE 	    AUX_SCAN_INDEX                  _at_ 0x9E;
IIBYTE 	    AUX_SCAN_INDEX_HS               _at_ 0x9F;

IIBYTE 	    AUX_SCAN_TIMEOUT_CUNT           _at_ 0xA0;
IIBYTE 	    SKIP_AUX_SCAN_CUNT              _at_ 0xA1;
IIBYTE 	    AuxFlags_KB_CMD[3] 			    _at_ 0xA2;	
IIBYTE 	    AuxFlags_MS_CMD[3] 			    _at_ 0xA5;	
IIBYTE 	    AuxScanWDT			            _at_ 0xA8;	
IIBYTE      SMBUS_STATUS                    _at_ 0xA9;
IIBYTE		PS2_SSIRQ_Channel			    _at_ 0xAA;
IIBYTE		PS2_KBCmd_BK			        _at_ 0xAB;
IIBYTE      KB_Command                      _at_ 0xAC;
IIBYTE      MSPending                       _at_ 0xAD;
IIBYTE      PS2_ReTryCunt                   _at_ 0xAE;
IIBYTE      SMBCRC8_A                       _at_ 0xAF;
                                        
INT_VAR 	Int_Var							_at_ 0xB0;	// 2 bytes
FLAGS 		Flag							_at_ 0xB2;	// 2 bytes
EXT_CB2   	Ext_Cb2							_at_ 0xB4;
IIBYTE		Save_Kbd_State 					_at_ 0xB5;
                                        //Reserved 0xB6
XBYTE 		*idata	Tmp_XPntr 				_at_ 0xB7;	// 2 bytes
XBYTE		*idata 	Tmp_XPntr1	 			_at_ 0xB9;	// 2 bytes
IIBYTE 		KBHIReponse 					_at_ 0xBB;
key_state	temp_scanner_state				_at_ 0xBC;

									    //Reserved 0xBD ~ 0xCF
//****************************************************************************
//Stack                             0xD0 - 0xFF         // 48 bytes
//
// Don't use Idata (0xD0 ~ 0xFF).
// Idata (0xD0 ~ 0xFF). for stack point.
//****************************************************************************
					
//----------------------------------------------------------------------------
// External ram variables (0x00 ~ 0xFF)
//----------------------------------------------------------------------------
XBYTE 	bKEY_BUFF[KBF_SIZE]					_at_ 0x00;	// Scanned keyboard buffer storage. 
XBYTE 	Pass_Buff[8]						_at_ 0x10;
XBYTE 	Pass_Buff_Idx						_at_ 0x18;
XBYTE  	Pass_On								_at_ 0x19;
XBYTE 	Pass_Off							_at_ 0x1A;
XBYTE 	Pass_Make1							_at_ 0x1B;
XBYTE  	Pass_Make2							_at_ 0x1C;
XBYTE  	PS_Debug_ECToHost                   _at_ 0x1D;
XBYTE   PS_Debug_DeviceToEC                 _at_ 0x1E;
XBYTE   DebugTest                           _at_ 0x1F;

//*******************************************************
#ifdef KB_HW_KeyScan   // Hardware scan keyboard
//*******************************************************
XBYTE   KB_HW_ExtendKeyIndex                _at_ 0x20;
XBYTE   KB_HW_ExtendKeyTypematic            _at_ 0x21;

//*******************************************************
#endif // KB_HW_KeyScan Hardware scan keyboard
//*******************************************************
                                            // 0x22
                                        
XBYTE 	bTMrepeat							_at_ 0x23;
XBYTE 	bTMdelay							_at_ 0x24;
XBYTE 	bTMcount							_at_ 0x25;
XBYTE 	diode_key							_at_ 0x26;
BYTE code *Scanner_Table_Pntr 				_at_ 0x27;
BYTE code *Extendkey_Table_Pntr 			_at_ 0x29;	
                                        //Reserved 0x2B ~ 0x40
XBYTE	PS2BufHead							_at_ 0x41;
XBYTE	PS2BufTail							_at_ 0x42;
XBYTE	PS2DataPinStatusCounter			    _at_ 0x43;
XBYTE	PS2TypeCounter						_at_ 0x44;	// Dino 1128	
XBYTE	WinFlashMark						_at_ 0x45;	
XBYTE	RamCodePort							_at_ 0x46;	
XBYTE   KBDataPending[4]                    _at_ 0x47;
XBYTE   KBPendingRXCount                    _at_ 0x4B;
XBYTE   KBPendingTXCount                    _at_ 0x4C;
XBYTE	PS2DataPinStatus			        _at_ 0x4D;
                                        //Reserved 0x4E ~ 0x4F
                                        
XBYTE 	*SMBus1BlockPtr 					_at_ 0x50;	// 2 bytes
XBYTE 	*SMBus2BlockPtr 					_at_ 0x52;	// 2 bytes
XBYTE 	*SMBus3BlockPtr 					_at_ 0x54;	// 2 bytes
XBYTE	DB_SMBusAddr						_at_ 0x56;	
XBYTE	DB_SMBusCmd							_at_ 0x57;	
XBYTE	DB_SMBusBCunt						_at_ 0x58;	
XBYTE	DB_SMBusFlag1						_at_ 0x59;	
XBYTE	DB_SMBusFlag2						_at_ 0x5A;	
XBYTE	DB_SMBusFlag3						_at_ 0x5B;	
XBYTE	DB_SMBusData[32]					_at_ 0x5C;	
XBYTE	DB_SMBusAck1						_at_ 0x7C;	
XBYTE	DB_SMBusACDID						_at_ 0x7D;			
					                    //Reserved 0x7E ~ 0x80
					                    
XBYTE	ExtendScanPin						_at_ 0x81;	
XBYTE	RSTStatus							_at_ 0x82;	
XBYTE	RamcodeCmd							_at_ 0x83;	
XBYTE	RamcodeSend							_at_ 0x84;	
BYTE code *Tmp_Code_Pntr 					_at_ 0x85;	
FUNCT_PTR_V_V Tmp_Func_Pnter				_at_ 0x87;	
XBYTE	SMBus1RecoverCunt				    _at_ 0x89;	
XBYTE	SMBus2RecoverCunt				    _at_ 0x8A;	
XBYTE	SMBus3RecoverCunt				    _at_ 0x8B;	
XBYTE	SMBus4RecoverCunt				    _at_ 0x8C;	
XBYTE   FN_Key_Break                        _at_ 0x8D;
XBYTE   FN_Key_Break_HS                     _at_ 0x8E;
XBYTE   SMBus_BusyRecover                   _at_ 0x8F;
					                    
XBYTE	SPIIDBuf[4]							_at_ 0x90;	
XBYTE	SPIIndex							_at_ 0x94;	
XBYTE	SPIAddrCycle[3]						_at_ 0x95;	
XBYTE	SPIAEraseCmd						_at_ 0x98;	
XBYTE	SPIReadStatus						_at_ 0x99;	
XBYTE	SPIWriteStatus						_at_ 0x9A;	
XBYTE	*SPIDataPointer						_at_ 0x9B;	
XBYTE	SPIID								_at_ 0x9D;	
XBYTE   SSTDeviceID  						_at_ 0x9E;
XBYTE   EC_Indirect_Selection               _at_ 0x9F;

					                    //Reserved 0xA0 ~ 0xDF 

XBYTE   FnKeyBundledFalg[16]                _at_ 0xE0;	
                                        
XBYTE  	KBCPortPending						_at_ 0xF0;	
XBYTE  	PMPortPending						_at_ 0xF1;	

					                    //Reserved 0xF2~ 0xF9
					                    
XBYTE  	KeyScanKSI							_at_ 0xFA;	
XBYTE  	KeyScanKSO							_at_ 0xFB;	
XBYTE	KeyScanACK							_at_ 0xFC;	
XBYTE  	ExtKeyScanKSI						_at_ 0xFD;	
XBYTE  	ExtKeyScanKSO						_at_ 0xFE;	
XBYTE	UtilityFlag							_at_ 0xFF;	

