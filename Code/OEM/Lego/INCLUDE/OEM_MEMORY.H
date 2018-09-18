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
#define wait_PSW_off    	BIT0  	    // 1: waiting for PSW released
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    POWER_FLAG2;            //(ECRAM+0x41)  EC power flag 2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	SLP_S3_ON         	BIT0        // 1:S3 power status
#define	SLP_S4_ON         	BIT1        // 1:S4 power status
#define	SLP_S5_ON         	BIT2        // 1:S5 power status

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern XBYTE    SYS_MISC1;              //(ECRAM+0x43)  System Misc flag 1  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ACPI_OS         	BIT0        // 1: system in ACPI environment

extern XBYTE    EVT_STATUS1;            //(ECRAM+0x46)  Event status flag 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define HDMI_IN		    BIT6        // 1:HDMI 
//#define LAN_IN		    BIT7        // 1:LAN Plug-in
#define DummyFlag           BIT7        // 1:CRT Sense

extern XBYTE    MISC_FLAG1;             //(ECRAM+0x49)  Misc flag 1 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define	WL_En        		BIT6  	    // 1:Wireless Enable On 
#define BT_En			    BIT7  	    // 1:BlueTooth Enable On

extern XBYTE    TDIM0_temp;       	    //(ECRAM+0x50)  DRAM 0 temperature
extern XBYTE    TDIM1_temp;       	    //(ECRAM+0x51)  DRAM 1 temperature
extern XBYTE    TPkg_temp;              //(ECRAM+0x52)  
extern XBYTE    TVGA_temp;              //(ECRAM+0x53)  VGA Temperature
extern XBYTE    TPCH_temp;			    //(ECRAM+0x54)  PCH Temperature
extern XBYTE    TSys_temp;              //(ECRAM+0x55)  system Temperature
extern XBYTE    TCPU_temp;              //(ECRAM+0x56)  CPU Temperature
extern XBYTE    PECI_CPU_temp;          //(ECRAM+0x57)  Use PECI interface to read CPU temperature

extern XBYTE	ATIDGPUTemp;            //(ECRAM+0x58); (58~5B)

extern XBYTE		SmBusI2CAddress;		// ECRAM+0x60
extern XBYTE		NowScanCmd;		//ECRAM+0x61
extern XBYTE		GPU_Therm_Method;				//ECRAM+0x62

extern XBYTE   Cark_Test01;         //_at_(ECRAM+0xA0);

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
// OEMRAM4 Offset 0x20 ~ 0x27   LED variables
#define LEDRAM     OEMRAM4+0x20
extern XWORD    LED_FLASH_CNT;  		//(LEDRAM+0x00) //(word) LED index
//Reserved offset 0x02 ~ 0x0F

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
extern XBYTE  DebugforceFan1RPM;		// 
extern XBYTE  DebugforceFan2RPM;		//

extern XBYTE	FanFullOnCont;			// FanCtrlRAM+0x3D
extern XBYTE	DebugFan1RPMT;			// FanCtrlRAM+0x3F

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
