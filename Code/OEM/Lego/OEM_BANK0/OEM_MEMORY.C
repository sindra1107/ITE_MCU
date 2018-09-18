 /*-----------------------------------------------------------------------------
 * Filename:OEM_MEMORY.C     For Chipset: ITE.IT85XX
 *
 * Function: Memory Definition for extern all code base reference
 *
 * [Memory Map Description]
 *
 * Chip Internal Ram : 0x00-0xFF For Kernel and Chip Level use
 *
 ***************************************************
 * Chip 8500       : External ram 0x000-0x7FF
 * Chip Other 85XX : External ram 0x000-0xFFF
 ***************************************************
 *
 * [OEM Memory Rang]
 * [External Ram]
 * 0x100-0x1FF   OEM RAM 
 * 0x200-0x2FF   OEM RAM SPI buffer array
 * 0x300-0x3FF   OEM RAM EC Space   
 * 0x400-0x4FF   OEM RAM
 * 0x500-0x5FF   OEM RAM      

 * 0x800-0x8FF   OEM RAM Ramdebug function.
 * 0x800-0x9FF   OEM RAM 
 * 0xA00-0xAFF   OEM RAM 
 * 0xB00-0xBFF   OEM RAM  
 * 0xC00-0xCFF   OEM RAM 
 * 0xD00-0xDFF   OEM RAM 
 * 0xE00-0xEFF   OEM RAM 
 * 0xF00-0xFFF   OEM RAM For HSPI ram code function 
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x100-0x1FF   OEM RAM 1  
//-------------------------------------------------------------------------------
//*******************************************************************************
#ifdef ECPowerDownModeSupport
XBYTE   g_ECPowerDownCurrentMode        _at_    (ECPowerDownCtrl+0x00);
XBYTE   g_KernelDelayPowerDownMode      _at_    (ECPowerDownCtrl+0x01);
XBYTE   g_ECPowerDownPeriodWakeUpTime   _at_    (ECPowerDownCtrl+0x02);
XWORD   g_OEMDelayPowerDownMode         _at_    (ECPowerDownCtrl+0x03);
XBYTE   g_ECPowerDownModeTest           _at_    (ECPowerDownCtrl+0x05);
#endif

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x200-0x2FF   OEM RAM 2  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x300-0x3FF   OEM RAM 3  
//-------------------------------------------------------------------------------
//*******************************************************************************
XBYTE	SMB_PRTC            _at_(ECRAM+0x18);   // EC SMB1 Protocol register
XBYTE	SMB_STS				_at_(ECRAM+0x19); 	// EC SMB1 Status register
XBYTE	SMB_ADDR      		_at_(ECRAM+0x1A); 	// EC SMB1 Address register
XBYTE	SMB_CMD   			_at_(ECRAM+0x1B); 	// EC SMB1 Command register
XBYTE	SMB_DATA     		_at_(ECRAM+0x1C); 	// EC SMB1 Data register array (32 bytes)
XBYTE	SMB_DATA1[31]       _at_(ECRAM+0x1D);
XBYTE	SMB_BCNT  			_at_(ECRAM+0x3C); 	// EC SMB1 Block Count register
XBYTE	SMB_ALRA    		_at_(ECRAM+0x3D); 	// EC SMB1 Alarm Address register
XBYTE	SMB_ALRD0   		_at_(ECRAM+0x3E); 	// EC SMB1 Alarm Data register 0
XBYTE	SMB_ALRD1   		_at_(ECRAM+0x3F); 	// EC SMB1 Alarm Data register 1

XBYTE   POWER_FLAG1         _at_(ECRAM+0x40); 	// EC power flag 1
XBYTE   POWER_FLAG2         _at_(ECRAM+0x41); 	// EC power flag 2
//XBYTE   POWER_FLAG3         _at_(ECRAM+0x42); 	// EC power flag 3
XBYTE   SYS_MISC1           _at_(ECRAM+0x43); 	// System Misc flag 1
//XBYTE   SYS_MISC2           _at_(ECRAM+0x44); 	// System Misc flag 2
//XBYTE   SYS_MISC3           _at_(ECRAM+0x45); 	// System Misc flag 3
XBYTE   EVT_STATUS1         _at_(ECRAM+0x46); 	// Event status flag 1
//XBYTE   EVT_STATUS2         _at_(ECRAM+0x47); 	// Event status flag 2
//XBYTE   EVT_STATUS3         _at_(ECRAM+0x48); 	// Event status flag 3
XBYTE   MISC_FLAG1          _at_(ECRAM+0x49); 	// Misc flag 1
//XBYTE   MISC_FLAG2          _at_(ECRAM+0x4A); 	// Misc flag 2
//XBYTE   MISC_FLAG3          _at_(ECRAM+0x4B); 	// Misc flag 3
//XBYTE   MISC_FLAG4          _at_(ECRAM+0x4C); 	// Misc flag 4
//XBYTE   BrgLevel            _at_(ECRAM+0x4D);   // Brightness level
//XBYTE   CrisisKeyStatus     _at_(ECRAM+0x4E);   // Crisis key flag
//XBYTE   PanelId             _at_(ECRAM+0x4F);   // Panel ID

XBYTE   TDIM0_temp          _at_(ECRAM+0x50);   // DRAM 0 temperature
XBYTE   TDIM1_temp          _at_(ECRAM+0x51);   // DRAM 1 temperature
XBYTE   TPkg_temp           _at_(ECRAM+0x52);   // 
XBYTE   TVGA_temp           _at_(ECRAM+0x53);   // VGA Temperature
XBYTE   TPCH_temp		    _at_(ECRAM+0x54);   // PCH Temperature
XBYTE   TSys_temp           _at_(ECRAM+0x55);   // system Temperature
XBYTE   TCPU_temp           _at_(ECRAM+0x56);   // CPU Temperature
XBYTE   PECI_CPU_temp       _at_(ECRAM+0x57);   // Use PECI interface to read CPU temperature
XBYTE	ATIDGPUTemp         _at_(ECRAM+0x58); //(58~5B)
//Reserved ECRAM offset 0x5C ~ 0x5F

XBYTE	SmBusI2CAddress	_at_(ECRAM+0x60);
XBYTE	NowScanCmd		_at_(ECRAM+0x61);
XBYTE	GPU_Therm_Method		_at_(ECRAM+0x62);

XBYTE   Cark_Test01         _at_(ECRAM+0xA0);



//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x400-0x4FF   OEM RAM 4  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM4 Offset 0x00 ~ 0x0F   Power sequnce control 
XBYTE	SysPowState			_at_(PowerSequnceRAM+0x00); //(byte)
XBYTE	PWSeqStep			_at_(PowerSequnceRAM+0x01); //(byte)
XBYTE	DeepSleepCunt		_at_(PowerSequnceRAM+0x02); //(byte)
XWORD   DelayDoPowerSeq		_at_(PowerSequnceRAM+0x03); //(word)
XWORD   PowSeqDelay			_at_(PowerSequnceRAM+0x05); //(word)
XBYTE	ECAutoPowerOn		_at_(PowerSequnceRAM+0x07); //(byte)
XBYTE	ECWDTRSTNow			_at_(PowerSequnceRAM+0x08); //(byte)
XBYTE	CheckPowerStateIndex _at_(PowerSequnceRAM+0x09);    //(byte)
XBYTE	SBSWReleaseCunt		_at_(PowerSequnceRAM+0x0A); //(byte)
XWORD	PSW_COUNTER         _at_(PowerSequnceRAM+0x0B); //(word)
XWORD	HWPG_TIMER          _at_(PowerSequnceRAM+0x0D); //(word)
XBYTE	ShutDnCause     	_at_(PowerSequnceRAM+0x0F); //(byte)


//===============================================================================
// OEMRAM4 Offset 0x20 ~ 0x27   LED variables
XWORD   LED_FLASH_CNT  		_at_(LEDRAM+0x00);  //(word) LED index
//Reserved offset 0x02 ~ 0x07


//===============================================================================
// OEMRAM4 Offset 0xA0 ~ 0xAF   Power sequnce control 
XBYTE   PowerStatusBK       _at_(PowerSequnce2RAM+0x00);	
XWORD   PowerOnWDT          _at_(PowerSequnce2RAM+0x01);


//===============================================================================
// OEMRAM4 Offset 0xF0 ~ 0xFF   Event debounce counter 
XBYTE	DEBOUNCE_CONT1		_at_(DebounceRAM+0x00); //(byte)
XBYTE	DEBOUNCE_CONT2		_at_(DebounceRAM+0x01); //(byte)
XBYTE	DEBOUNCE_CONT3		_at_(DebounceRAM+0x02); //(byte)
XBYTE	DEBOUNCE_CONT4		_at_(DebounceRAM+0x03); //(byte) 
XBYTE	DEBOUNCE_CONT5		_at_(DebounceRAM+0x04); //(byte)
XBYTE	DEBOUNCE_CONT6		_at_(DebounceRAM+0x05); //(byte)
XBYTE	DEBOUNCE_CONT7		_at_(DebounceRAM+0x06); //(byte)
XBYTE	DEBOUNCE_CONT8		_at_(DebounceRAM+0x07); //(byte)
XBYTE	DEBOUNCE_CONT9		_at_(DebounceRAM+0x08); //(byte) 
XBYTE	DEBOUNCE_CONT10		_at_(DebounceRAM+0x09); //(byte)
XBYTE	DEBOUNCE_CONT11		_at_(DebounceRAM+0x0A); //(byte) 
XBYTE	DEBOUNCE_CONT12		_at_(DebounceRAM+0x0B); //(byte)
XBYTE	DEBOUNCE_CONT13		_at_(DebounceRAM+0x0C); //(byte)
XBYTE	DEBOUNCE_CONT14		_at_(DebounceRAM+0x0D); //(byte)
XBYTE	DEBOUNCE_CONT15		_at_(DebounceRAM+0x0E); //(byte)
XBYTE	DEBOUNCE_CONT16		_at_(DebounceRAM+0x0F); //(byte) 

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x500-0x5FF   OEM RAM 5  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM5 Offset 0x00 ~ 0x3F   For fan control 
XBYTE	Fan1On_Step1   		_at_(FanCtrlRAM+0x00);
XBYTE	Fan1On_Step2   		_at_(FanCtrlRAM+0x01);
XBYTE	Fan1On_Step3   		_at_(FanCtrlRAM+0x02);
XBYTE	Fan1On_Step4   		_at_(FanCtrlRAM+0x03);
XBYTE	Fan1On_Step5   		_at_(FanCtrlRAM+0x04);
XBYTE	Fan1On_Step6   		_at_(FanCtrlRAM+0x05);
XBYTE	Fan1On_Step7   		_at_(FanCtrlRAM+0x06);
XBYTE	Fan1On_Step8   		_at_(FanCtrlRAM+0x07);
XBYTE	Fan2On_Step1 		_at_(FanCtrlRAM+0x08);
XBYTE	Fan2On_Step2 		_at_(FanCtrlRAM+0x09);
XBYTE	Fan2On_Step3 		_at_(FanCtrlRAM+0x0A);
XBYTE	Fan2On_Step4 		_at_(FanCtrlRAM+0x0B);
XBYTE	Fan2On_Step5 		_at_(FanCtrlRAM+0x0C);
XBYTE	Fan2On_Step6 		_at_(FanCtrlRAM+0x0D);
XBYTE	Fan2On_Step7 		_at_(FanCtrlRAM+0x0E);
XBYTE	Fan2On_Step8 		_at_(FanCtrlRAM+0x0F);

XBYTE	Fan1Off_Step1  		_at_(FanCtrlRAM+0x10);
XBYTE	Fan1Off_Step2  		_at_(FanCtrlRAM+0x11);
XBYTE	Fan1Off_Step3  		_at_(FanCtrlRAM+0x12);
XBYTE	Fan1Off_Step4  		_at_(FanCtrlRAM+0x13);
XBYTE	Fan1Off_Step5  		_at_(FanCtrlRAM+0x14);
XBYTE	Fan1Off_Step6  		_at_(FanCtrlRAM+0x15);
XBYTE	Fan1Off_Step7  		_at_(FanCtrlRAM+0x16);
XBYTE	Fan1Off_Step8  		_at_(FanCtrlRAM+0x17);
XBYTE	Fan2Off_Step1 		_at_(FanCtrlRAM+0x18);
XBYTE	Fan2Off_Step2 		_at_(FanCtrlRAM+0x19);
XBYTE	Fan2Off_Step3 		_at_(FanCtrlRAM+0x1A);
XBYTE	Fan2Off_Step4 		_at_(FanCtrlRAM+0x1B);
XBYTE	Fan2Off_Step5 		_at_(FanCtrlRAM+0x1C);
XBYTE	Fan2Off_Step6 		_at_(FanCtrlRAM+0x1D);
XBYTE	Fan2Off_Step7 		_at_(FanCtrlRAM+0x1E);
XBYTE	Fan2Off_Step8 		_at_(FanCtrlRAM+0x1F);

XBYTE	Fan1RPM_Step1 		_at_(FanCtrlRAM+0x20);
XBYTE	Fan1RPM_Step2 		_at_(FanCtrlRAM+0x21);
XBYTE	Fan1RPM_Step3 		_at_(FanCtrlRAM+0x22);
XBYTE	Fan1RPM_Step4 		_at_(FanCtrlRAM+0x23);
XBYTE	Fan1RPM_Step5 		_at_(FanCtrlRAM+0x24);
XBYTE	Fan1RPM_Step6 		_at_(FanCtrlRAM+0x25);
XBYTE	Fan1RPM_Step7 		_at_(FanCtrlRAM+0x26);
XBYTE	Fan1RPM_Step8 		_at_(FanCtrlRAM+0x27);
XBYTE	Fan2RPM_Step1 		_at_(FanCtrlRAM+0x28);
XBYTE	Fan2RPM_Step2 		_at_(FanCtrlRAM+0x29);
XBYTE	Fan2RPM_Step3 		_at_(FanCtrlRAM+0x2A);
XBYTE	Fan2RPM_Step4 		_at_(FanCtrlRAM+0x2B);
XBYTE	Fan2RPM_Step5 		_at_(FanCtrlRAM+0x2C);
XBYTE	Fan2RPM_Step6 		_at_(FanCtrlRAM+0x2D);
XBYTE	Fan2RPM_Step7 		_at_(FanCtrlRAM+0x2E);
XBYTE	Fan2RPM_Step8 		_at_(FanCtrlRAM+0x2F);

XWORD	RPM1				_at_(FanCtrlRAM+0x30);
XWORD	RPM2				_at_(FanCtrlRAM+0x32);
XBYTE	Fan1RPM 			_at_(FanCtrlRAM+0x34);
XBYTE	Fan2RPM				_at_(FanCtrlRAM+0x35);
XBYTE	FanLevel			_at_(FanCtrlRAM+0x36);
XBYTE	FanLeve2			_at_(FanCtrlRAM+0x37);
XBYTE	temperature1		_at_(FanCtrlRAM+0x38);	
XBYTE	temperature2		_at_(FanCtrlRAM+0x39);
XBYTE	Debugtemperature1	_at_(FanCtrlRAM+0x3A);			
XBYTE	Debugtemperature2	_at_(FanCtrlRAM+0x3B);	
XBYTE	DebugforceFan1RPM  _at_(FanCtrlRAM+0x3C);
XBYTE	FanFullOnCont		_at_(FanCtrlRAM+0x3D);
XBYTE	DebugforceFan2RPM  _at_(FanCtrlRAM+0x3E);
XBYTE	DebugFan1RPMT		_at_(FanCtrlRAM+0x3F);	

//===============================================================================
// OEMRAM5 Offset 0x40 ~ 0xAF   For PECI function 
XBYTE   PECIReadBuffer[16]  _at_( PECICtrlRAM + 0x000);
XBYTE   PECIWriteBuffer[16] _at_( PECICtrlRAM + 0x010);
XBYTE   PECI_CRC8           _at_( PECICtrlRAM + 0x020);
XBYTE   PECI_CompletionCode _at_( PECICtrlRAM + 0x021);
XBYTE   PECI_PCIConfigAddr[4] _at_( PECICtrlRAM + 0x022);

XBYTE   PECI_PowerCtrlStep  _at_( PECICtrlRAM + 0x030);
XBYTE   PECI_PowerUnit      _at_( PECICtrlRAM + 0x031);
XBYTE   PECI_EnergyUnit     _at_( PECICtrlRAM + 0x032);
XBYTE   PECI_TimeUnit       _at_( PECICtrlRAM + 0x033);
XBYTE   PECI_PL2Watts       _at_( PECICtrlRAM + 0x034);
XBYTE   PECI_MAXPL2         _at_( PECICtrlRAM + 0x035);
XBYTE   PECI_PL1TDP         _at_( PECICtrlRAM + 0x036);
XBYTE   PECI_PL1Time        _at_( PECICtrlRAM + 0x037);
XBYTE   PECI_Ctrl           _at_( PECICtrlRAM + 0x038);
XBYTE   PECI_AdaptorWatts   _at_( PECICtrlRAM + 0x039);
XBYTE   PECI_SystemWatts    _at_( PECICtrlRAM + 0x03A);
XBYTE   PECI_Algorithm_Delay     _at_( PECICtrlRAM + 0x03B);
LWORD   PECI_ErrorCount         _at_( PECICtrlRAM + 0x03C);
XBYTE   PECI_StressToolBuf[32]  _at_( PECICtrlRAM + 0x040);
XBYTE   PSTB_Timer              _at_( PECICtrlRAM + 0x060);
XBYTE   PSTB_CmdStatus          _at_( PECICtrlRAM + 0x061);
XBYTE   PSTB_RepeatIntervalCount    _at_( PECICtrlRAM + 0x062);  
LWORD   PSTB_RepeatCycle        _at_( PECICtrlRAM + 0x063);
XBYTE	CPUTjmax			    _at_( PECICtrlRAM + 0x067);
XBYTE	ReadCPUTjmaxCUNT        _at_( PECICtrlRAM + 0x068);
XBYTE   StressToolReadBufIndex  _at_( PECICtrlRAM + 0x069);
//Reserved offset 0xAA ~ 0xAF
//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x800-0x8FF   OEM RAM 8  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x900-0x9FF   OEM RAM 9  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xA00-0xAFF   OEM RAM A  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xB00-0xBFF   OEM RAM B  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xC00-0xCFF   OEM RAM C  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xD00-0xDFF   OEM RAM D  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xE00-0xEFF   OEM RAM E  
//-------------------------------------------------------------------------------
//*******************************************************************************

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0xF00-0xFFF   OEM RAM F  
//-------------------------------------------------------------------------------
//*******************************************************************************
