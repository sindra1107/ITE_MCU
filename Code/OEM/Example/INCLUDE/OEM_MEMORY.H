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
 
#ifndef OEM_MEMORY_H
#define OEM_MEMORY_H

#define EC_RAMBase 		    0x0000

#define OEMRAM1 		    EC_RAMBase+0x0100   // EC_RAMBase+0x0100 
#define OEMRAM2 		    EC_RAMBase+0x0200   // EC_RAMBase+0x0200 
#define OEMRAM3 		    EC_RAMBase+0x0300   // EC_RAMBase+0x0300 
#define OEMRAM4 		    EC_RAMBase+0x0400   // EC_RAMBase+0x0400 
#define OEMRAM5 		    EC_RAMBase+0x0500   // EC_RAMBase+0x0500 

#define OEMRAM8 		    EC_RAMBase+0x0800   // EC_RAMBase+0x0800 
#define OEMRAM9 		    EC_RAMBase+0x0900   // EC_RAMBase+0x0900 
#define OEMRAMA 		    EC_RAMBase+0x0A00   // EC_RAMBase+0x0A00 
#define OEMRAMB 		    EC_RAMBase+0x0B00   // EC_RAMBase+0x0B00 
#define OEMRAMC 		    EC_RAMBase+0x0C00   // EC_RAMBase+0x0C00 
#define OEMRAMD 		    EC_RAMBase+0x0D00   // EC_RAMBase+0x0D00 
#define OEMRAME 		    EC_RAMBase+0x0E00   // EC_RAMBase+0x0E00 
#define OEMRAMF 		    EC_RAMBase+0x0F00   // EC_RAMBase+0x0F00 

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x100-0x1FF   OEM RAM 1  
//-------------------------------------------------------------------------------
//*******************************************************************************
//#ifdef ECPowerDownModeSupport
#define ECPowerDownCtrl     OEMRAM1

extern XBYTE    g_ECPowerDownCurrentMode;        //    (ECPowerDownCtrl+0x00)
extern XBYTE    g_KernelDelayPowerDownMode;      //    (ECPowerDownCtrl+0x01)
extern XBYTE    g_ECPowerDownPeriodWakeUpTime;   //    (ECPowerDownCtrl+0x02)
extern XWORD    g_OEMDelayPowerDownMode;         //    (ECPowerDownCtrl+0x03)
extern XBYTE    g_ECPowerDownModeTest;           //    (ECPowerDownCtrl+0x05)
//#endif

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x200-0x2FF   OEM RAM 2  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define SPIBufferRAM        OEMRAM2+0x00
extern XBYTE    SPIBuffer[];            // (SPIBufferRAM+0x00)  56 bytes SPI read/write buffer

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x300-0x3FF   OEM RAM 3  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define ECRAM		        OEMRAM3
//Reserved offset 0x00 ~ 0x17
extern XBYTE	SMB_PRTC;               //(ECRAM+0x18)  EC SMB1 Protocol register
extern XBYTE	SMB_STS;		        //(ECRAM+0x19)  EC SMB1 Status register
extern XBYTE	SMB_ADDR;      		    //(ECRAM+0x1A)  EC SMB1 Address register
extern XBYTE	SMB_CMD;   			    //(ECRAM+0x1B)  EC SMB1 Command register
extern XBYTE	SMB_DATA;     		    //(ECRAM+0x1C)  EC SMB1 Data register array (32 bytes)
extern XBYTE	SMB_DATA1[];            //(ECRAM+0x1D)  
extern XBYTE	SMB_BCNT; 			    //(ECRAM+0x3C)  EC SMB1 Block Count register
extern XBYTE	SMB_ALRA;    		    //(ECRAM+0x3D)  EC SMB1 Alarm Address register
extern XBYTE	SMB_ALRD0;   		    //(ECRAM+0x3E)  EC SMB1 Alarm Data register 0
extern XBYTE	SMB_ALRD1;   		    //(ECRAM+0x3F)  EC SMB1 Alarm Data register 1

extern XBYTE    POWER_FLAG1;            //(ECRAM+0x40)  EC power flag 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define adapter_in      	BIT0  	    // 1: AC adapter exist
#define wait_PSW_off    	BIT1  	    // 1: waiting for PSW released
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    POWER_FLAG2;            //(ECRAM+0x41)  EC power flag 2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	SLP_S3_ON         	BIT0        // 1:S3 power status
#define	SLP_S4_ON         	BIT1        // 1:S4 power status
#define	SLP_S5_ON         	BIT2        // 1:S5 power status
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    POWER_FLAG3;            //(ECRAM+0x42)  EC power flag 3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    SYS_MISC1;              //(ECRAM+0x43)  System Misc flag 1  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ACPI_OS         	BIT0        // 1: system in ACPI environment

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE    SYS_MISC2;              //(ECRAM+0x44)  System Misc flag 2  
extern XBYTE    SYS_MISC3;              //(ECRAM+0x45)  System Misc flag 3  

extern XBYTE    EVT_STATUS1;            //(ECRAM+0x46)  Event status flag 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define HDMI_IN		    BIT6        // 1:HDMI 
//#define LAN_IN		    BIT7        // 1:LAN Plug-in
#define DummyFlag           BIT7        // 1:CRT Sense
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE    EVT_STATUS2;            //(ECRAM+0x47)  Event status flag 2
extern XBYTE    EVT_STATUS3;            //(ECRAM+0x48)  Event status flag 3

extern XBYTE    MISC_FLAG1;             //(ECRAM+0x49)  Misc flag 1 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	WL_En        		BIT6  	    // 1:Wireless Enable On 
#define BT_En			    BIT7  	    // 1:BlueTooth Enable On
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE    MISC_FLAG2;             //(ECRAM+0x4A)  Misc flag 2 
extern XBYTE    MISC_FLAG3;             //(ECRAM+0x4B)  Misc flag 3 
extern XBYTE    MISC_FLAG4;             //(ECRAM+0x4C)  Misc flag 4 
extern XBYTE    BrgLevel;               //(ECRAM+0x4D)  Brightness level 
extern XBYTE    CrisisKeyStatus;        //(ECRAM+0x4E)  Crisis key flag
extern XBYTE    PanelId;                //(ECRAM+0x4F)  Panel ID

extern XBYTE    TDIM0_temp;       	    //(ECRAM+0x50)  DRAM 0 temperature
extern XBYTE    TDIM1_temp;       	    //(ECRAM+0x51)  DRAM 1 temperature
extern XBYTE    TPkg_temp;              //(ECRAM+0x52)  
extern XBYTE    TVGA_temp;              //(ECRAM+0x53)  VGA Temperature
extern XBYTE    TPCH_temp;			    //(ECRAM+0x54)  PCH Temperature
extern XBYTE    TSys_temp;              //(ECRAM+0x55)  system Temperature
extern XBYTE    TCPU_temp;              //(ECRAM+0x56)  CPU Temperature
extern XBYTE    PECI_CPU_temp;          //(ECRAM+0x57)  Use PECI interface to read CPU temperature
//Reserved ECRAM offset 0x58 ~ 0x5F

/*  BATTERYS INFORMATION    */
extern XBYTE    BT1_STATUS1;            //(ECRAM+0x60)  Battery 1 status1 flag
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_in         		BIT0	    // 1: Battery 1 exist
#define bat_valid           BIT1   	    // 1: Battery 1 battery idetify OK
#define bat_InCharge   		BIT2   	    // 1: battery 1 in any charge phase
#define bat_Full            BIT3   	    // 1: Battery 1 fully charged
#define bat_Dischg     		BIT4   	    // 1: Battery 1 in discharging
#define bat_Dead       		BIT5   	    // 1: Battery 1 fully discharged
#define bat_abnormal        BIT6   	    // 1: battery 1 abnormal

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE    BT1_STATUS2;            //(ECRAM+0x61)  Battery 1 status2 flag
#define bat_DC         		BIT0	    // 1: Set Battery 1 discharge
#define bat_WC              BIT1   	    // 1: Set Battery 1 wake up charge
#define bat_PC         		BIT2	    // 1: Set Battery 1 pre-charge
#define bat_NC              BIT3   	    // 1: Set Battery 1 normal charge
#define bat_DC_OK           BIT4	    // 1: Battery 1 in discharge
#define bat_WC_OK           BIT5   	    // 1: Battery 1 in wake up charge
#define bat_PC_OK           BIT6	    // 1: Battery 1 in pre-charge
#define bat_NC_OK           BIT7   	    // 1: Battery 1 in normal charge

extern XBYTE    BAT1_temp_L;            //(ECRAM+0x62)  Battery 1 
extern XBYTE    BAT1_temp_H;            //(ECRAM+0x63)  Battery 1 
extern XBYTE    BAT1_volt_L;            //(ECRAM+0x64)  Battery 1
extern XBYTE    BAT1_volt_H;            //(ECRAM+0x65)  Battery 1
extern XBYTE    BAT1_current_L;         //(ECRAM+0x66)  Battery 1
extern XBYTE    BAT1_current_H;         //(ECRAM+0x67)  Battery 1
extern XBYTE    BAT1_RSOC;              //(ECRAM+0x68)  Battery 1
// Never use offset 0x69 of ECRAM
extern XBYTE    BAT1_RMcap_L;           //(ECRAM+0x6A)  Battery 1
extern XBYTE    BAT1_RMcap_H;           //(ECRAM+0x6B)  Battery 1
extern XBYTE    BAT1_FCcap_L;           //(ECRAM+0x6C)  Battery 1
extern XBYTE    BAT1_FCcap_H;           //(ECRAM+0x6D)  Battery 1
extern XBYTE    BAT1_CC_L;    	        //(ECRAM+0x6E)  Battery 1	
extern XBYTE    BAT1_CC_H;   	        //(ECRAM+0x6F)  Battery 1	
extern XBYTE    BAT1_CV_L;    	        //(ECRAM+0x70)  Battery 1
extern XBYTE    BAT1_CV_H;   	        //(ECRAM+0x71)  Battery 1

extern XBYTE    BAT1_ALARM1;            //(ECRAM+0x72)  Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SMBerror0    	BIT0            // error code bit0
#define SMBerror1    	BIT1            // error code bit1
#define SMBerror2      	BIT2            // error code bit2
#define SMBerror3      	BIT3            // error code bit3
#define FullyDsg    	BIT4            // statusfully discharged
#define FullyChg     	BIT5            // statusfully charged
#define Dsg         	BIT6            // statusdischarging
#define Initialized  	BIT7            // statusgauge initialized
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    BAT1_ALARM2;            //(ECRAM+0x73)  Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RemTime_alarm	BIT0            // alarmremaining time
#define RemCap_alarm  	BIT1            // alarmremaining capacity
//#define  				BIT2        	//
#define TermDsg_alarm 	BIT3            // alarmterminate discharge
#define OverTemp_alarm 	BIT4            // alarmover temperature
//#define  				BIT5        	//
#define TermChg_alarm 	BIT6            // alarmterminate charge
#define OverChg_alarm 	BIT7            // alarmover charge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    BT1_STATUS3;            //(ECRAM+0x74)  Battery 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_ForceChg    BIT0            // Battery 1 in force charge mode   
#define bat_ForceDischg BIT1            // Battery 1 in force discharge mode 
#define bat_AL          BIT2            // Battery 1 in auto learning
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x400-0x4FF   OEM RAM 4  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM4 Offset 0x00 ~ 0x0F   Power sequnce control 
#define PowerSequnceRAM     OEMRAM4+0x00

extern XBYTE	SysPowState;			//(PowerSequnceRAM+0x00)    //(byte)
extern XBYTE	PWSeqStep;			    //(PowerSequnceRAM+0x01)    //(byte)
extern XBYTE	DeepSleepCunt;		    //(PowerSequnceRAM+0x02)    //(byte)
extern XWORD    DelayDoPowerSeq;		//(PowerSequnceRAM+0x03)    //(word)
extern XWORD    PowSeqDelay;			//(PowerSequnceRAM+0x05)    //(word)
extern XBYTE    ECAutoPowerOn;		    //(PowerSequnceRAM+0x07)    //(byte)
extern XBYTE	ECWDTRSTNow;			//(PowerSequnceRAM+0x08)    //(byte)
extern XBYTE	CheckPowerStateIndex;   //(PowerSequnceRAM+0x09)    //(byte)
extern XBYTE	SBSWReleaseCunt;		//(PowerSequnceRAM+0x0A)    //(byte)
extern XWORD	PSW_COUNTER;            //(PowerSequnceRAM+0x0B)    //(word)
extern XWORD	HWPG_TIMER;             //(PowerSequnceRAM+0x0D)    //(word)
extern XBYTE	ShutDnCause;     	    //(PowerSequnceRAM+0x0F)    //(byte)
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x10 ~ 0x1F   Thermal variables
#define ThermalRAM     OEMRAM4+0x10
extern XBYTE    VeryHotCnt;    		    //(ThermalRAM + 0x00)   //(byte)	
extern XBYTE    SysVeryHotCnt;		    //(ThermalRAM + 0x01)   //(byte)	
//Reserved offset 0x02 ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x20 ~ 0x27   LED variables
#define LEDRAM     OEMRAM4+0x20
extern XWORD    LED_FLASH_CNT;  		//(LEDRAM+0x00) //(word) LED index
//Reserved offset 0x02 ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x28 ~ 0x2F   LCD variables
#define LCDRAM     OEMRAM4+0x28
extern XBYTE    bBrightness;            //(LCDRAM+0x00) //(byte)
//Reserved offset 0x01 ~ 0x07
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x30 ~ 0x4F   ADC variables
#define ADCRAM     OEMRAM4+0x30
extern XWORD    ADCAvg0;				//(ADCRAM+0x00) //(word)
extern XWORD	ADCAvg1;				//(ADCRAM+0x02) //(word)
extern XWORD	ADCAvg2;			    //(ADCRAM+0x04) //(word)
extern XWORD	ADCAvg3;				//(ADCRAM+0x06) //(word)
extern XWORD	ADCAvg4;				//(ADCRAM+0x08) //(word)
extern XWORD	ADCAvg5;			    //(ADCRAM+0x0A) //(word)
extern XWORD	Fix_ADCAvg0;			//(ADCRAM+0x0C) //(word)
extern XWORD	Fix_ADCAvg1;			//(ADCRAM+0x0E) //(word)

extern XBYTE    ADCDyTable1Index;       //(ADCRAM+0x10) //(byte)
extern XBYTE	ADCDyTable2Index;       //(ADCRAM+0x11) //(byte)
//Reserved offset 0x12 ~ 0x1F
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x50 ~ 0x6F   SMBus center variables
#define SMBusCenterRAM      OEMRAM4+0x50

extern XBYTE	SMBus1Flag1;			//(SMBusCenterRAM+0x00)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define B1_RSOC         BIT0
#define B1_C            BIT1
#define B1_V            BIT2
#define B1_RMcap        BIT3
#define B1_Status       BIT4
#define B1_FCC          BIT5
#define B1_Temp         BIT6
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	SMBus1Flag2;			//(SMBusCenterRAM+0x01)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define B1_CC           BIT0
#define B1_CV           BIT1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	SMBus1Flag3;			//(SMBusCenterRAM+0x02)
extern XBYTE	SMBus1Flag4;		    //(SMBusCenterRAM+0x03)
extern XBYTE	SMBus1Flag5;		    //(SMBusCenterRAM+0x04)

extern XBYTE	SMBus2Flag1;		    //(SMBusCenterRAM+0x05)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PollRemote      BIT0            // Read thermal sensor remote temperature
#define PollLocal       BIT1            // Read thermal sensor local temperature
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE	SMBus2Flag2;		    //(SMBusCenterRAM+0x06)
extern XBYTE	SMBus2Flag3;		    //(SMBusCenterRAM+0x07)
extern XBYTE	SMBus2Flag4;		    //(SMBusCenterRAM+0x08)
extern XBYTE	SMBus2Flag5;		    //(SMBusCenterRAM+0x09)
extern XBYTE	SMBus3Flag1;			//(SMBusCenterRAM+0x0A)
extern XBYTE	SMBusSelection;			//(SMBusCenterRAM+0x0B)
extern XBYTE	F_Service_SMBus1;       //(SMBusCenterRAM+0x0C)
extern XBYTE	F_Service_SMBus2;       //(SMBusCenterRAM+0x0D)
extern XBYTE	F_Service_SMBus3;       //(SMBusCenterRAM+0x0E)
extern XBYTE	F_Service_SMBus4;       //(SMBusCenterRAM+0x0F)
extern XBYTE	SMBus1ByteCunt;	        //(SMBusCenterRAM+0x10)
extern XBYTE	SMBus2ByteCunt;		    //(SMBusCenterRAM+0x11)
extern XBYTE	SMBus3ByteCunt;		    //(SMBusCenterRAM+0x12)
extern XBYTE	SMBus1counter;		    //(SMBusCenterRAM+0x13)
extern XBYTE	SMBus2counter;		    //(SMBusCenterRAM+0x14)
extern XBYTE	SMBus3counter;		    //(SMBusCenterRAM+0x15)
extern XBYTE	SMBus1index;			//(SMBusCenterRAM+0x16)
extern XBYTE	SMBus2index;			//(SMBusCenterRAM+0x17)
extern XBYTE	SMBus3index;			//(SMBusCenterRAM+0x18)
extern XBYTE    SMBus1InUsing;          //(SMBusCenterRAM+0x19)
extern XBYTE    SMBus2InUsing;          //(SMBusCenterRAM+0x1A)
extern XBYTE    SMBus3InUsing;          //(SMBusCenterRAM+0x1B)
extern XBYTE    SMBus1TableSize;        //(SMBusCenterRAM+0x1C)
extern XBYTE    SMBus2TableSize;        //(SMBusCenterRAM+0x1D)
extern XBYTE    SMBus3TableSize;        //(SMBusCenterRAM+0x1E)
extern XBYTE    SMBusXStatus;           //(SMBusCenterRAM+0x1F)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SMBus1_OK       BIT0
#define SMBus1_Fail     BIT1
#define SMBus2_OK       BIT2
#define SMBus2_Fail     BIT3
#define SMBus3_OK       BIT4
#define SMBus3_Fail     BIT5
#define SMBus4_OK       BIT6
#define SMBus4_Fail     BIT7
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0x70 ~ 0x9F   Battery 1 control variables
#define BAT1CtrlRAM     OEMRAM4+0x70
extern XBYTE    BAT1_CtrlStep;          //(BAT1CtrlRAM+0x00)
extern XBYTE    BAT1_ID_Step;           //(BAT1CtrlRAM+0x01)
extern XBYTE    BAT1_1SecTimer;         //(BAT1CtrlRAM+0x02)
extern XBYTE    BAT1_S_Number;          //(BAT1CtrlRAM+0x03)
extern XBYTE    ByteTemp01;             //(BAT1CtrlRAM+0x04)
extern XBYTE    ByteTemp02;             //(BAT1CtrlRAM+0x05)
extern XBYTE    BAT1_ID_TimeOut_CNT;    //(BAT1CtrlRAM+0x06)
extern XBYTE    BAT1_Number;            //(BAT1CtrlRAM+0x07)
extern XBYTE    BAT1_FailCause;         //(BAT1CtrlRAM+0x08)
extern XBYTE    BAT1_FirstDataIndex;    //(BAT1CtrlRAM+0x09)
extern XBYTE	INPUT_CURRENT_LO;       //(BAT1CtrlRAM+0x0A)
extern XBYTE	INPUT_CURRENT_HI;       //(BAT1CtrlRAM+0x0B)
extern XBYTE	CHARGE_CURRENT_LO;      //(BAT1CtrlRAM+0x0C)
extern XBYTE	CHARGE_CURRENT_HI;      //(BAT1CtrlRAM+0x0D)
extern XBYTE	CHARGE_VOLTAGE_LO;      //(BAT1CtrlRAM+0x0E)  
extern XBYTE	CHARGE_VOLTAGE_HI;      //(BAT1CtrlRAM+0x0F)
extern XBYTE	Charger_TimeOut;        //(BAT1CtrlRAM+0x10)
extern XBYTE    WakeUpChrCunt_Min;      //(BAT1CtrlRAM+0x11) 
extern XWORD    PreChrCunt_Min;         //(BAT1CtrlRAM+0x12)
extern XWORD    NormalChrCunt_Min;      //(BAT1CtrlRAM+0x14)
extern XWORD    WakeUpChrCunt;          //(BAT1CtrlRAM+0x16) 
extern XWORD    PreChrCunt;             //(BAT1CtrlRAM+0x18) 
extern XWORD    NormalChrCunt;          //(BAT1CtrlRAM+0x1A)
extern XBYTE    BAT1_OTCunt;            //(BAT1CtrlRAM+0x1C)
extern XBYTE    BAT1_OVCunt;            //(BAT1CtrlRAM+0x1D)
extern XWORD    CHARGE_CURRENT_BK;      //(BAT1CtrlRAM+0x1E)
extern XWORD    CHARGE_VOLTAGE_BK;      //(BAT1CtrlRAM+0x20)

//===============================================================================

//===============================================================================
// OEMRAM4 Offset 0xA0 ~ 0xAF   Power sequnce control 
#define PowerSequnce2RAM    OEMRAM4+0xA0

extern XBYTE    PowerStatusBK;          //(PowerSequnce2RAM+0x00)
extern XWORD    PowerOnWDT;             //(PowerSequnce2RAM+0x01)

//Reserved OEMRAM4 offset 0xB0 ~ 0xEF

//===============================================================================
// OEMRAM4 Offset 0xF0 ~ 0xFF   Event debounce counter 
#define DebounceRAM     OEMRAM4+0xF0

extern XBYTE	DEBOUNCE_CONT1;		    //(DebounceRAM+0x00) 	//(byte)
extern XBYTE	DEBOUNCE_CONT2;		    //(DebounceRAM+0x01) 	//(byte)
extern XBYTE	DEBOUNCE_CONT3;		    //(DebounceRAM+0x02) 	//(byte)
extern XBYTE	DEBOUNCE_CONT4;		    //(DebounceRAM+0x03) 	//(byte) 
extern XBYTE	DEBOUNCE_CONT5;		    //(DebounceRAM+0x04) 	//(byte)
extern XBYTE	DEBOUNCE_CONT6;		    //(DebounceRAM+0x05) 	//(byte)
extern XBYTE	DEBOUNCE_CONT7;		    //(DebounceRAM+0x06) 	//(byte)
extern XBYTE	DEBOUNCE_CONT8;		    //(DebounceRAM+0x07) 	//(byte)
extern XBYTE	DEBOUNCE_CONT9;		    //(DebounceRAM+0x08) 	//(byte) 
extern XBYTE	DEBOUNCE_CONT10;		//(DebounceRAM+0x09) 	//(byte)
extern XBYTE	DEBOUNCE_CONT11;		//(DebounceRAM+0x0A) 	//(byte) 
extern XBYTE	DEBOUNCE_CONT12;		//(DebounceRAM+0x0B) 	//(byte)
extern XBYTE	DEBOUNCE_CONT13;		//(DebounceRAM+0x0C) 	//(byte)
extern XBYTE	DEBOUNCE_CONT14;		//(DebounceRAM+0x0D) 	//(byte)
extern XBYTE	DEBOUNCE_CONT15;		//(DebounceRAM+0x0E) 	//(byte)
extern XBYTE	DEBOUNCE_CONT16;		//(DebounceRAM+0x0F) 	//(byte) 
//===============================================================================

//*******************************************************************************
//-------------------------------------------------------------------------------
//	0x500-0x5FF   OEM RAM 5  
//-------------------------------------------------------------------------------
//*******************************************************************************
//===============================================================================
// OEMRAM5 Offset 0x00 ~ 0x3F   For fan control 
#define FanCtrlRAM      OEMRAM5+0x00
extern XBYTE	Fan1On_Step1;   		// FanCtrlRAM+0x00
extern XBYTE	Fan1On_Step2;   		// FanCtrlRAM+0x01
extern XBYTE	Fan1On_Step3;   		// FanCtrlRAM+0x02
extern XBYTE	Fan1On_Step4;  			// FanCtrlRAM+0x03
extern XBYTE	Fan1On_Step5;   		// FanCtrlRAM+0x04
extern XBYTE	Fan1On_Step6;   		// FanCtrlRAM+0x05
extern XBYTE	Fan1On_Step7;   		// FanCtrlRAM+0x06
extern XBYTE	Fan1On_Step8;   		// FanCtrlRAM+0x07
extern XBYTE	Fan2On_Step1; 			// FanCtrlRAM+0x08
extern XBYTE	Fan2On_Step2; 			// FanCtrlRAM+0x09
extern XBYTE	Fan2On_Step3; 			// FanCtrlRAM+0x0A
extern XBYTE	Fan2On_Step4; 			// FanCtrlRAM+0x0B
extern XBYTE	Fan2On_Step5; 			// FanCtrlRAM+0x0C
extern XBYTE	Fan2On_Step6; 			// FanCtrlRAM+0x0D
extern XBYTE	Fan2On_Step7; 			// FanCtrlRAM+0x0E
extern XBYTE	Fan2On_Step8; 			// FanCtrlRAM+0x0F

extern XBYTE	Fan1Off_Step1;  		// FanCtrlRAM+0x10
extern XBYTE	Fan1Off_Step2;  		// FanCtrlRAM+0x11
extern XBYTE	Fan1Off_Step3;  		// FanCtrlRAM+0x12
extern XBYTE	Fan1Off_Step4;  		// FanCtrlRAM+0x13
extern XBYTE	Fan1Off_Step5;  		// FanCtrlRAM+0x14
extern XBYTE	Fan1Off_Step6;  		// FanCtrlRAM+0x15
extern XBYTE	Fan1Off_Step7;  		// FanCtrlRAM+0x16
extern XBYTE	Fan1Off_Step8;  		// FanCtrlRAM+0x17
extern XBYTE	Fan2Off_Step1; 			// FanCtrlRAM+0x18
extern XBYTE	Fan2Off_Step2; 			// FanCtrlRAM+0x19
extern XBYTE	Fan2Off_Step3; 			// FanCtrlRAM+0x1A
extern XBYTE	Fan2Off_Step4; 			// FanCtrlRAM+0x1B
extern XBYTE	Fan2Off_Step5;			// FanCtrlRAM+0x1C
extern XBYTE	Fan2Off_Step6; 			// FanCtrlRAM+0x1D
extern XBYTE	Fan2Off_Step7; 			// FanCtrlRAM+0x1E
extern XBYTE	Fan2Off_Step8;			// FanCtrlRAM+0x1F

extern XBYTE	Fan1RPM_Step1; 			// FanCtrlRAM+0x20
extern XBYTE	Fan1RPM_Step2; 			// FanCtrlRAM+0x21
extern XBYTE	Fan1RPM_Step3; 			// FanCtrlRAM+0x22
extern XBYTE	Fan1RPM_Step4; 			// FanCtrlRAM+0x23
extern XBYTE	Fan1RPM_Step5; 			// FanCtrlRAM+0x24
extern XBYTE	Fan1RPM_Step6; 			// FanCtrlRAM+0x25
extern XBYTE	Fan1RPM_Step7; 			// FanCtrlRAM+0x26
extern XBYTE	Fan1RPM_Step8; 			// FanCtrlRAM+0x27
extern XBYTE	Fan2RPM_Step1; 			// FanCtrlRAM+0x28
extern XBYTE	Fan2RPM_Step2; 			// FanCtrlRAM+0x29
extern XBYTE	Fan2RPM_Step3; 			// FanCtrlRAM+0x2A
extern XBYTE	Fan2RPM_Step4; 			// FanCtrlRAM+0x2B
extern XBYTE	Fan2RPM_Step5; 			// FanCtrlRAM+0x2C
extern XBYTE	Fan2RPM_Step6; 			// FanCtrlRAM+0x2D
extern XBYTE	Fan2RPM_Step7; 			// FanCtrlRAM+0x2E
extern XBYTE	Fan2RPM_Step8; 			// FanCtrlRAM+0x2F

extern XWORD	RPM1;					// FanCtrlRAM+0x30
extern XWORD	RPM2;					// FanCtrlRAM+0x32
extern XBYTE	Fan1RPM;				// FanCtrlRAM+0x34
extern XBYTE	Fan2RPM;				// FanCtrlRAM+0x35
extern XBYTE	FanLevel;				// FanCtrlRAM+0x36
extern XBYTE	FanLeve2;				// FanCtrlRAM+0x37
extern XBYTE	temperature1;			// FanCtrlRAM+0x38	
extern XBYTE	temperature2;			// FanCtrlRAM+0x39
extern XBYTE	Debugtemperature1;		// FanCtrlRAM+0x3A			
extern XBYTE	Debugtemperature2;		// FanCtrlRAM+0x3B	
extern XBYTE	DummyStep;				// FanCtrlRAM+0x3C
extern XBYTE	FanFullOnCont;			// FanCtrlRAM+0x3D
extern XBYTE	RPMTimeShift;			// FanCtrlRAM+0x3E
extern XBYTE	DebugFan1RPMT;			// FanCtrlRAM+0x3F
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0x40 ~ 0xAF   For PECI function 
#define PECICtrlRAM      OEMRAM5+0x40

extern XBYTE   PECIReadBuffer[];        // PECICtrlRAM + 0x000 offset 0x40 ~ 0x4F
extern XBYTE   PECIWriteBuffer[];       // PECICtrlRAM + 0x010 offset 0x50 ~ 0x5F
extern XBYTE   PECI_CRC8;               // PECICtrlRAM + 0x020 offset 0x60
extern XBYTE   PECI_CompletionCode;     // PECICtrlRAM + 0x021 offset 0x61
extern XBYTE   PECI_PCIConfigAddr[];    // PECICtrlRAM + 0x022 offset 0x62 ~ 0x65
//Reserved offset 0x66 ~ 0x6F
extern XBYTE   PECI_PowerCtrlStep;      // PECICtrlRAM + 0x030 offset 0x70
extern XBYTE   PECI_PowerUnit;          // PECICtrlRAM + 0x031 offset 0x71
extern XBYTE   PECI_EnergyUnit;         // PECICtrlRAM + 0x032 offset 0x72
extern XBYTE   PECI_TimeUnit;           // PECICtrlRAM + 0x033 offset 0x73
extern XBYTE   PECI_PL2Watts;           // PECICtrlRAM + 0x034 offset 0x74
extern XBYTE   PECI_MAXPL2;             // PECICtrlRAM + 0x035 offset 0x75
extern XBYTE   PECI_PL1TDP;             // PECICtrlRAM + 0x036 offset 0x76
extern XBYTE   PECI_PL1Time;            // PECICtrlRAM + 0x037 offset 0x77
extern XBYTE   PECI_Ctrl;               // PECICtrlRAM + 0x038 offset 0x78
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SetPL2Request           BIT0

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE   PECI_AdaptorWatts;       // PECICtrlRAM + 0x039 offset 0x79
extern XBYTE   PECI_SystemWatts;        // PECICtrlRAM + 0x03A offset 0x7A
extern XBYTE   PECI_Algorithm_Delay;    // PECICtrlRAM + 0x03B offset 0x7B
extern LWORD   PECI_ErrorCount;         // PECICtrlRAM + 0x03C offset 0x7C ~ 0x0x7F
extern XBYTE   PECI_StressToolBuf[];    // PECICtrlRAM + 0x040 offset 0x80 ~ 0x9F
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PSTB_RepeatCycle0           0
#define PSTB_RepeatCycle1           1
#define PSTB_RepeatCycle2           2
#define PSTB_RepeatCycle3           3
#define PSTB_RepeatInterval         4           // 10ms timer base
#define PSTB_StopOnError            5
#define PSTB_ClientAddress          6
#define PSTB_WriteLength            7
#define PSTB_ReadLength             8

#define PSTB_CommandSpecificData    9
#define PSTB_CmdCode                PSTB_CommandSpecificData

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE   PSTB_Timer;              // PECICtrlRAM + 0x060 offset 0xA0
extern XBYTE   PSTB_CmdStatus;          // PECICtrlRAM + 0x061 offset 0xA1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ServivePECIStressTool   BIT0

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    PSTB_RepeatIntervalCount;   // PECICtrlRAM + 0x062  offset 0xA2
extern LWORD    PSTB_RepeatCycle;           // PECICtrlRAM + 0x063  offset 0xA3 ~ 0xA6
extern XBYTE    CPUTjmax;			        // PECICtrlRAM + 0x067
extern XBYTE    ReadCPUTjmaxCUNT;           // PECICtrlRAM + 0x068
extern XBYTE    StressToolReadBufIndex;     // PECICtrlRAM + 0x069
//Reserved offset 0xAA ~ 0xAF

//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xC0 ~ 0xCF   For OEM SPI function 
#define SPI_Mouse           OEMRAM5+0xC0

extern XBYTE   SPI_Mouse_Buf[];         //( SPI_Mouse + 0x00)
extern XBYTE   SPI_Mouse_DeltaX;        //( SPI_Mouse + 0x03)
extern XBYTE   SPI_Mouse_DeltaY;        //( SPI_Mouse + 0x04)
extern XBYTE   SPI_Mouse_BYTE1;         //( SPI_Mouse + 0x05)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define Y_Overflow          BIT7
#define X_Overflow          BIT6
#define Y_Signbit           BIT5
#define X_Signbit           BIT4
#define Always1             BIT3
#define MiddleBtn           BIT2
#define RightBtn            BIT1
#define LeftBtn             BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE   SPI_Mouse_XMovement;     //( SPI_Mouse + 0x06)
extern XBYTE   SPI_Mouse_YMovement;     //( SPI_Mouse + 0x07)
extern XBYTE   SPI_Mouse_Buf_Index;     //( SPI_Mouse + 0x08)
extern XBYTE   SPI_Mouse_Misc;          //( SPI_Mouse + 0x09)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SPI_Mouse_Need_Break    BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern XBYTE   SPI_Mouse_ID;            //( SPI_Mouse + 0x0A)

//Reserved offset 0x0A ~ 0x0F
//===============================================================================

//===============================================================================
// OEMRAM5 Offset 0xD0 ~ 0xEF   For OEM SCI qevent function
#define SCI_Qevent_Ctrl     OEMRAM5+0xD0

extern XBYTE 	SCI_Event_In_Index;     //( SCI_Qevent_Ctrl + 0x00);
extern XBYTE 	SCI_Event_Out_Index;    //( SCI_Qevent_Ctrl + 0x01);
extern XBYTE 	SCI_Event_Buffer[];     //( SCI_Qevent_Ctrl + 0x02); // EVENT_BUFFER_SIZE bytes

extern XBYTE 	PD_SCI_Event_In_Index;  //( SCI_Qevent_Ctrl + 0x10);
extern XBYTE 	PD_SCI_Event_Out_Index; //( SCI_Qevent_Ctrl + 0x11);
extern XBYTE 	PD_SCI_Event_Buffer[];  //( SCI_Qevent_Ctrl + 0x12); // PENDING_BUFFER bytes

//===============================================================================
// OEMRAM5 Offset 0xF0 ~ 0xFF   For OEM HSPI function
#define HSPI_Ctrl     OEMRAM5+0xF0

extern XBYTE    HSPI_SelfRamCode_Index; //( HSPI_Ctrl + 0x00);
extern XBYTE    HSPI_tempcmd;           //( HSPI_Ctrl + 0x01);
extern XBYTE    HSPI_FPT_timeout;       //( HSPI_Ctrl + 0x02);
extern XBYTE    HSPI_Misc1;             //( HSPI_Ctrl + 0x03);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define HSPI_ReLoadHSPIRamCode  BIT0    // 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

#endif 
