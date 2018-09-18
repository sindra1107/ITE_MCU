/*-----------------------------------------------------------------------------
 * TITLE: OEM_PECI.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_PECI_H
#define OEM_PECI_H

#define PECI_Softwave_AWFCS 0       // 1 : softwave calculate AW_FCS
                                    // 0 : H.W. calculate AW_FCS
#define PECI_HostID         0x01    // Host ID = PECI_HostID << 1 (bit7 ~ bit0)
                                        
//-----------------------------------------------------------------------------
// Define CPU address
//-----------------------------------------------------------------------------
#define PECI_CPU_ADDR       0x30

//-----------------------------------------------------------------------------
// Define processor Tjmax
//-----------------------------------------------------------------------------
#define PECI_CPU_Tjmax      100
#define PECI_Read_TjmaxTO   10      // Re-try to read CPU Tjmax via PECI

//-----------------------------------------------------------------------------
// Define PECI command
//-----------------------------------------------------------------------------
#define PECI_CMD_GetDIB             0xF7
#define PECI_CMD_Pin                0x00
#define PECI_CMD_GetTemp            0x01
#define PECI_CMD_RdPkgConfig        0xA1  
#define PECI_CMD_WrPkgConfig        0xA5  
#define PECI_CMD_RdIAMSR            0xB1
#define PECI_CMD_WrIAMSR            0xB5
#define PECI_CMD_RdPCIConfig        0x61
#define PECI_CMD_WrPCIConfig        0x65
#define PECI_CMD_RdPCIConfigLocal   0xE1
#define PECI_CMD_WrPCIConfigLocal   0xE5

//-----------------------------------------------------------------------------
// Define completion code
//-----------------------------------------------------------------------------
#define PECI_CC_Valid           0x40
#define PECI_CC_TimeOut         0x80
#define PECI_CC_Ignored         0x90

// ----------------------------------------------------------------------------
// PECI3.0 power control parameter
// ----------------------------------------------------------------------------
#define PowerLimit2Max          PECI_MAXPL2
#define PowerLimit1TDP          PECI_PL1TDP
#define PowerLimit1Tau          PECI_PL1Time
#define ACPowerWatts            65      // Set 65w adaptor
#define PowerLimit2Max_Value    60      // Set power limit 2 max xx watts
#define PowerLimit1_TDP         45      // Setting initial TDP value if BIOS doesn't set it. (watts)
#define AlgorithmDelayTime      100     // (500ms) timer base 5ms 

// ----------------------------------------------------------------------------
// PECI3.0 domain parameter definition
// ----------------------------------------------------------------------------
#define PECI_Domain_0           0x00
#define PECI_Domain_1           0x01

// ----------------------------------------------------------------------------
// The index definition of PECI3.0 read/write Pkg command
// ----------------------------------------------------------------------------
#define PECI_Index_PTR          2       // Package temperature read
#define PECI_Index_TTR          16      // Read the Maximum Allowed Processor Temperature
#define PECI_Index_DRCTR        22      // DRAM rank channel temperature read
#define PECI_Index_PPL1         26      // Power limit 1
#define PECI_Index_PPL2         27      // Power limit 2
#define PECI_Index_PPSU         28      // Power SKU unit
#define PECI_Index_PPSL         29      // Package power and time limit information
#define PECI_Index_PPSH         30      // Package power and time limit information

// ----------------------------------------------------------------------------
// The address definition of PECI3.0 read MSR
// ----------------------------------------------------------------------------
#define MC0_CTL                 0x400

// ----------------------------------------------------------------------------
// CPU Power control step via PECI
// ----------------------------------------------------------------------------
#define PECI_Step_Start         0x01
#define PECI_Step_ReadPSKUUnit  0x02    // Read power SKU unit
#define PECI_Step_ReadPL1       0x03    // Read power limit 1
#define PECI_Step_WritePL1      0x04    // Write power limit 1
#define PECI_Step_Algorithm     0x05

#define PECI_Step_Stop          0x10    // 
#define PECI_Step_StopRequest   0x11

// ----------------------------------------------------------------------------
// PECI Stress Tool
// ----------------------------------------------------------------------------
#define BufferLength            24      // buffer is 24 bytes

extern void Init_PECI(void);
extern void PECI_HostEnable(void);
extern void PECI_HostDisable(void);
extern BYTE PECI_CheckHostBusy(void);
extern BYTE PECI_CheckHostFinish(void);
extern void ResetPECIStatus(void);
extern void PECI_HostControl(BYTE control);
extern BYTE PECI_Ping(BYTE addr, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_GetDIB(BYTE addr, XBYTE *ReadData, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_GetTemp(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_RdPkgConfig(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry, BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_WrPkgConfig(BYTE addr, XBYTE *WriteData, BYTE Domain, BYTE Retry, BYTE Index, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen);
extern BYTE PECI_RdIAMSR(BYTE addr, XBYTE *ReadData, BYTE Domain, BYTE Retry, BYTE ProcessorID, BYTE LSB, BYTE MSB, BYTE ReadLen, BYTE WriteLen);
extern void PECI_ClearTCVariables(void);
extern void PECI_ClearPowerSKUUnit(void);
extern BYTE PECI_ReadPowerUnit(void);
extern BYTE PECI_WritePowerLimit1(void);
extern BYTE PECI_ReadPowerLimit1(void);
extern void PECI_ACToDCModeTurboCtrl(void);
extern void PECI_SETPL2Watts(BYTE watts);
extern void PECI_WritePowerLimit2(BYTE watts);
extern void PECI_ReadPowerLimit2(void);
extern void PECI_ReadCPUTemp(void);
extern void PECI_ReadCPUTJMAX(void);
extern void PECI_ReadDRAMTemperature(void);
extern void PECI_ReadPkgTemperature(void);
extern void PECI_ReadMSRExample(void);
extern void PECI_CheckCurrentPlatformPower(void);
extern void PECI_ACTurboControlAlgorithm(void);
extern void ChecknSetAdaptorWatts(void);
extern void PECI_PowerCtrlCenter(void);
extern void SetPECIPowerCtrlStep(BYTE step);

extern void ProcessPSTCmd(void);
extern void PECI_PSTIssueCmd(void);
extern void PECI_PSTEndCmd(void);
extern void PECI_PSTWriteBuffer(void);
extern void PECI_PSTReadBuffer(void);
extern void PECI_PSTReadErrorCount(void);
extern void PECI_PSTReadStatus(void);
extern void PECI_ClearPSTVariables(void);
extern void PECI_SendBufferData(void);

#endif