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

//-------------------------------------------------------------------------------
//	0x100-0x1FF   OEM RAM 1  
//-------------------------------------------------------------------------------
#ifdef ECPowerDownModeSupport
XBYTE   g_ECPowerDownCurrentMode        _at_    (ECPowerDownCtrl+0x00);
XBYTE   g_KernelDelayPowerDownMode      _at_    (ECPowerDownCtrl+0x01);
XBYTE   g_ECPowerDownPeriodWakeUpTime   _at_    (ECPowerDownCtrl+0x02);
XWORD   g_OEMDelayPowerDownMode         _at_    (ECPowerDownCtrl+0x03);
XBYTE   g_ECPowerDownModeTest           _at_    (ECPowerDownCtrl+0x05);
#endif

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
XBYTE   POWER_FLAG3         _at_(ECRAM+0x42); 	// EC power flag 3
XBYTE   SYS_MISC1           _at_(ECRAM+0x43); 	// System Misc flag 1
XBYTE   SYS_MISC2           _at_(ECRAM+0x44); 	// System Misc flag 2
XBYTE   SYS_MISC3           _at_(ECRAM+0x45); 	// System Misc flag 3
XBYTE   EVT_STATUS1         _at_(ECRAM+0x46); 	// Event status flag 1
XBYTE   EVT_STATUS2         _at_(ECRAM+0x47); 	// Event status flag 2
XBYTE   EVT_STATUS3         _at_(ECRAM+0x48); 	// Event status flag 3
XBYTE   MISC_FLAG1          _at_(ECRAM+0x49); 	// Misc flag 1
XBYTE   MISC_FLAG2          _at_(ECRAM+0x4A); 	// Misc flag 2
XBYTE   MISC_FLAG3          _at_(ECRAM+0x4B); 	// Misc flag 3
XBYTE   MISC_FLAG4          _at_(ECRAM+0x4C); 	// Misc flag 4
XBYTE   BrgLevel            _at_(ECRAM+0x4D);   // Brightness level
XBYTE   CrisisKeyStatus     _at_(ECRAM+0x4E);   // Crisis key flag
XBYTE   PanelId             _at_(ECRAM+0x4F);   // Panel ID

XBYTE   TDIM0_temp          _at_(ECRAM+0x50);   // DRAM 0 temperature
XBYTE   TDIM1_temp          _at_(ECRAM+0x51);   // DRAM 1 temperature
XBYTE   TPkg_temp           _at_(ECRAM+0x52);   // 
XBYTE   TVGA_temp           _at_(ECRAM+0x53);   // VGA Temperature
XBYTE   TPCH_temp		    _at_(ECRAM+0x54);   // PCH Temperature
XBYTE   TSys_temp           _at_(ECRAM+0x55);   // system Temperature
XBYTE   TCPU_temp           _at_(ECRAM+0x56);   // CPU Temperature
XBYTE   PECI_CPU_temp       _at_(ECRAM+0x57);   // Use PECI interface to read CPU temperature
//Reserved ECRAM offset 0x58 ~ 0x5F

XBYTE   BT1_STATUS1         _at_(ECRAM+0x60);   // Battery 1 status1 flag
XBYTE   BT1_STATUS2         _at_(ECRAM+0x61);   // Battery 1 status2 flag
XBYTE   BAT1_temp_L         _at_(ECRAM+0x62);   // Battery 1 
XBYTE   BAT1_temp_H         _at_(ECRAM+0x63);   // Battery 1 
XBYTE   BAT1_volt_L         _at_(ECRAM+0x64);   // Battery 1
XBYTE   BAT1_volt_H         _at_(ECRAM+0x65);   // Battery 1
XBYTE   BAT1_current_L      _at_(ECRAM+0x66);   // Battery 1
XBYTE   BAT1_current_H      _at_(ECRAM+0x67);   // Battery 1
XBYTE   BAT1_RSOC           _at_(ECRAM+0x68);   // Battery 1
// Never use offset 0x69 of ECRAM
XBYTE   BAT1_RMcap_L        _at_(ECRAM+0x6A);   // Battery 1
XBYTE   BAT1_RMcap_H        _at_(ECRAM+0x6B);   // Battery 1
XBYTE   BAT1_FCcap_L        _at_(ECRAM+0x6C);   // Battery 1
XBYTE   BAT1_FCcap_H        _at_(ECRAM+0x6D);   // Battery 1
XBYTE   BAT1_CC_L    	    _at_(ECRAM+0x6E);   // Battery 1	
XBYTE   BAT1_CC_H    	    _at_(ECRAM+0x6F);   // Battery 1	
XBYTE   BAT1_CV_L    	    _at_(ECRAM+0x70);   // Battery 1
XBYTE   BAT1_CV_H    	    _at_(ECRAM+0x71);   // Battery 1
XBYTE   BAT1_ALARM1         _at_(ECRAM+0x72);   // Battery 1
XBYTE   BAT1_ALARM2         _at_(ECRAM+0x73);   // Battery 1
XBYTE   BT1_STATUS3         _at_(ECRAM+0x74);   // Battery 1

//-------------------------------------------------------------------------------
//	0x200-0x2FF   OEM RAM 2  
//-------------------------------------------------------------------------------
XBYTE   SPIBuffer[256]      _at_(SPIBufferRAM+0x00);    // 256 bytes SPI read/write buffer

//-------------------------------------------------------------------------------
//	0x300-0x3FF   OEM RAM 3  
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//	0x400-0x4FF   OEM RAM 4  
//-------------------------------------------------------------------------------
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

//===============================================================================
// OEMRAM4 Offset 0x10 ~ 0x1F   Thermal variables
XBYTE   VeryHotCnt    		_at_(ThermalRAM+0x00);  //(byte)	
XBYTE   SysVeryHotCnt		_at_(ThermalRAM+0x01);  //(byte)	
//Reserved offset 0x02 ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x20 ~ 0x27   LED variables
XWORD   LED_FLASH_CNT  		_at_(LEDRAM+0x00);  //(word) LED index
//Reserved offset 0x02 ~ 0x07
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x28 ~ 0x2F   LCD variables
XBYTE   bBrightness         _at_(LCDRAM+0x00);  //(byte)
//Reserved offset 0x01 ~ 0x07
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x30 ~ 0x4F   ADC variables
XWORD	ADCAvg0				_at_(ADCRAM+0x00);
XWORD	ADCAvg1				_at_(ADCRAM+0x02);
XWORD	ADCAvg2				_at_(ADCRAM+0x04);
XWORD	ADCAvg3				_at_(ADCRAM+0x06);
XWORD	ADCAvg4				_at_(ADCRAM+0x08);
XWORD	ADCAvg5				_at_(ADCRAM+0x0A);
XWORD	Fix_ADCAvg0			_at_(ADCRAM+0x0C);
XWORD	Fix_ADCAvg1			_at_(ADCRAM+0x0E);

XBYTE	ADCDyTable1Index    _at_(ADCRAM+0x10);
XBYTE	ADCDyTable2Index    _at_(ADCRAM+0x11);
//Reserved offset 0x12 ~ 0x1F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x50 ~ 0x6F   SMBus center variables
XBYTE	SMBus1Flag1			_at_(SMBusCenterRAM+0x00);
XBYTE	SMBus1Flag2			_at_(SMBusCenterRAM+0x01);
XBYTE	SMBus1Flag3			_at_(SMBusCenterRAM+0x02);
XBYTE	SMBus1Flag4			_at_(SMBusCenterRAM+0x03);
XBYTE	SMBus1Flag5			_at_(SMBusCenterRAM+0x04);
XBYTE	SMBus2Flag1			_at_(SMBusCenterRAM+0x05);
XBYTE	SMBus2Flag2			_at_(SMBusCenterRAM+0x06);
XBYTE	SMBus2Flag3			_at_(SMBusCenterRAM+0x07);
XBYTE	SMBus2Flag4			_at_(SMBusCenterRAM+0x08);
XBYTE	SMBus2Flag5			_at_(SMBusCenterRAM+0x09);
XBYTE	SMBus3Flag1			_at_(SMBusCenterRAM+0x0A);
XBYTE	SMBusSelection	    _at_(SMBusCenterRAM+0x0B);
XBYTE	F_Service_SMBus1    _at_(SMBusCenterRAM+0x0C);
XBYTE	F_Service_SMBus2    _at_(SMBusCenterRAM+0x0D);
XBYTE	F_Service_SMBus3    _at_(SMBusCenterRAM+0x0E);
XBYTE	F_Service_SMBus4     _at_(SMBusCenterRAM+0x0F);
XBYTE	SMBus1ByteCunt	    _at_(SMBusCenterRAM+0x10);
XBYTE	SMBus2ByteCunt		_at_(SMBusCenterRAM+0x11);
XBYTE	SMBus3ByteCunt		_at_(SMBusCenterRAM+0x12);
XBYTE	SMBus1counter		_at_(SMBusCenterRAM+0x13);
XBYTE	SMBus2counter		_at_(SMBusCenterRAM+0x14);
XBYTE	SMBus3counter		_at_(SMBusCenterRAM+0x15);
XBYTE	SMBus1index			_at_(SMBusCenterRAM+0x16);
XBYTE	SMBus2index			_at_(SMBusCenterRAM+0x17);
XBYTE	SMBus3index			_at_(SMBusCenterRAM+0x18);
XBYTE   SMBus1InUsing       _at_(SMBusCenterRAM+0x19);
XBYTE   SMBus2InUsing       _at_(SMBusCenterRAM+0x1A);
XBYTE   SMBus3InUsing       _at_(SMBusCenterRAM+0x1B);
XBYTE   SMBus1TableSize     _at_(SMBusCenterRAM+0x1C);
XBYTE   SMBus2TableSize     _at_(SMBusCenterRAM+0x1D);
XBYTE   SMBus3TableSize     _at_(SMBusCenterRAM+0x1E);
XBYTE   SMBusXStatus        _at_(SMBusCenterRAM+0x1F);
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x70 ~ 0x9F   Battery 1 control variables
XBYTE   BAT1_CtrlStep       _at_(BAT1CtrlRAM+0x00);
XBYTE   BAT1_ID_Step        _at_(BAT1CtrlRAM+0x01);
XBYTE   BAT1_1SecTimer      _at_(BAT1CtrlRAM+0x02);
XBYTE   BAT1_S_Number       _at_(BAT1CtrlRAM+0x03);
XBYTE   ByteTemp01          _at_(BAT1CtrlRAM+0x04);
XBYTE   ByteTemp02          _at_(BAT1CtrlRAM+0x05);
XBYTE   BAT1_ID_TimeOut_CNT _at_(BAT1CtrlRAM+0x06);
XBYTE   BAT1_Number         _at_(BAT1CtrlRAM+0x07);
XBYTE   BAT1_FailCause      _at_(BAT1CtrlRAM+0x08);
XBYTE   BAT1_FirstDataIndex _at_(BAT1CtrlRAM+0x09);
XBYTE	INPUT_CURRENT_LO    _at_(BAT1CtrlRAM+0x0A);
XBYTE	INPUT_CURRENT_HI    _at_(BAT1CtrlRAM+0x0B);
XBYTE	CHARGE_CURRENT_LO   _at_(BAT1CtrlRAM+0x0C);
XBYTE	CHARGE_CURRENT_HI   _at_(BAT1CtrlRAM+0x0D);
XBYTE	CHARGE_VOLTAGE_LO   _at_(BAT1CtrlRAM+0x0E);    
XBYTE	CHARGE_VOLTAGE_HI   _at_(BAT1CtrlRAM+0x0F);
XBYTE	Charger_TimeOut     _at_(BAT1CtrlRAM+0x10);
XBYTE   WakeUpChrCunt_Min   _at_(BAT1CtrlRAM+0x11); 
XWORD   PreChrCunt_Min      _at_(BAT1CtrlRAM+0x12); 
XWORD   NormalChrCunt_Min   _at_(BAT1CtrlRAM+0x14); 
XWORD   WakeUpChrCunt       _at_(BAT1CtrlRAM+0x16);  
XWORD   PreChrCunt          _at_(BAT1CtrlRAM+0x18);  
XWORD   NormalChrCunt       _at_(BAT1CtrlRAM+0x1A);  
XBYTE   BAT1_OTCunt         _at_(BAT1CtrlRAM+0x1C);
XBYTE   BAT1_OVCunt         _at_(BAT1CtrlRAM+0x1D);
XWORD   CHARGE_CURRENT_BK   _at_(BAT1CtrlRAM+0x1E);	
XWORD   CHARGE_VOLTAGE_BK   _at_(BAT1CtrlRAM+0x20);	

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
//===============================================================================

//-------------------------------------------------------------------------------
//	0x500-0x5FF   OEM RAM 5  
//-------------------------------------------------------------------------------
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
XBYTE	DummyStep			_at_(FanCtrlRAM+0x3C);
XBYTE	FanFullOnCont		_at_(FanCtrlRAM+0x3D);
XBYTE	RPMTimeShift		_at_(FanCtrlRAM+0x3E);
XBYTE	DebugFan1RPMT		_at_(FanCtrlRAM+0x3F);	
//===============================================================================

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

//===============================================================================
// OEMRAM5 Offset 0xC0 ~ 0xCF   For OEM SPI function 

XBYTE   SPI_Mouse_Buf[3]        _at_( SPI_Mouse + 0x00);
XBYTE   SPI_Mouse_DeltaX        _at_( SPI_Mouse + 0x03);
XBYTE   SPI_Mouse_DeltaY        _at_( SPI_Mouse + 0x04);
XBYTE   SPI_Mouse_BYTE1         _at_( SPI_Mouse + 0x05);
XBYTE   SPI_Mouse_XMovement     _at_( SPI_Mouse + 0x06);
XBYTE   SPI_Mouse_YMovement     _at_( SPI_Mouse + 0x07);
XBYTE   SPI_Mouse_Buf_Index     _at_( SPI_Mouse + 0x08);
XBYTE   SPI_Mouse_Misc          _at_( SPI_Mouse + 0x09);
XBYTE   SPI_Mouse_ID            _at_( SPI_Mouse + 0x0A);

//Reserved offset 0x0B ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xD0 ~ 0xEF   For OEM SCI qevent function
XBYTE 	SCI_Event_In_Index 					_at_( SCI_Qevent_Ctrl + 0x00);
XBYTE 	SCI_Event_Out_Index 				_at_( SCI_Qevent_Ctrl + 0x01);
XBYTE 	SCI_Event_Buffer[EVENT_BUFFER_SIZE] _at_( SCI_Qevent_Ctrl + 0x02); // EVENT_BUFFER_SIZE bytes

XBYTE 	PD_SCI_Event_In_Index 			    _at_( SCI_Qevent_Ctrl + 0x10);
XBYTE 	PD_SCI_Event_Out_Index 				_at_( SCI_Qevent_Ctrl + 0x11);
XBYTE 	PD_SCI_Event_Buffer[PENDING_BUFFER] _at_( SCI_Qevent_Ctrl + 0x12); // PENDING_BUFFER bytes

//===============================================================================
// OEMRAM5 Offset 0xF0 ~ 0xFF   For OEM HSPI function
XBYTE   HSPI_SelfRamCode_Index              _at_( HSPI_Ctrl + 0x00);
XBYTE   HSPI_tempcmd                        _at_( HSPI_Ctrl + 0x01);
XBYTE   HSPI_FPT_timeout                    _at_( HSPI_Ctrl + 0x02);
XBYTE   HSPI_Misc1                          _at_( HSPI_Ctrl + 0x03);

//===============================================================================

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
