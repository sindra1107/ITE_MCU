/*----------------------------------------------------------------------------
 * Filename: OEM_Power.H  For Chipset: ITE.IT85XX
 *
 * Function: Power sequnce control function example
 *
 * Author  : Dino
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_POWER_H
#define OEM_POWER_H

//-----------------------------------------------------------------------------
// Define
//-----------------------------------------------------------------------------
#define	SYSTEM_S0			0x10
#define	SYSTEM_S3			0x33
#define	SYSTEM_S4			0x44
#define	SYSTEM_S5			0x55
#define	SYSTEM_S5_S0		0x50
#define	SYSTEM_S4_S0		0x40
#define	SYSTEM_S3_S0		0x30
#define	SYSTEM_S0_S3		0x03
#define	SYSTEM_S0_S4		0x04
#define	SYSTEM_S0_S5		0x05
#define	SYSTEM_EC_WDTRST	0xFF

//-----------------------------------------------------------------------------
// Shutdown cause
//-----------------------------------------------------------------------------
#define SC_S0SLPOff		    0x01	// System shutdown by S3/S4/S5 Off
#define SC_S3S4SLPOff		0x02	// System shutdown by S3/S4/S5 fail Off
#define SC_4SEC		        0x03	// System shutdown by power button 4 sec overwrite
#define SC_CPUHOT		    0x04	// System shutdown by CPU too hot to shutdown
#define SC_HWPGSx_S0Off		0x05	// System shutdown by HWPG Fail in Sx_S0 power sequence
#define SC_HWPS0Off		    0x06	// System shutdown by HWPG Fail in S0
#define SC_PowerOnWatchDog  0x07    // System shutdown by Power on WDT

#define SC_EC_0x0000        0xEC    // EC code reset
#define SC_ExtWatchDog      0xFF    // external watch-dog
#define SC_IntWatchDog      0xFE    // internal watch-dog
#define SC_ECColdBoot       0xFC    // EC VSTBY or WRST reset

//-----------------------------------------------------------------------------
// System status define
//-----------------------------------------------------------------------------
#define SystemIsS0          SysPowState==SYSTEM_S0
#define SystemIsS3          SysPowState==SYSTEM_S3
#define SystemIsS4          SysPowState==SYSTEM_S4
#define SystemIsS5          SysPowState==SYSTEM_S5

#define SystemNotS0         SysPowState!=SYSTEM_S0
#define SystemNotS3         SysPowState!=SYSTEM_S3
#define SystemNotS4         SysPowState!=SYSTEM_S4
#define SystemNotS5         SysPowState!=SYSTEM_S5

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void CheckPowerState(void);
extern void Oem_TriggerS3S0(void);
extern void Oem_TriggerS4S0(void);
extern void Oem_TriggerS5S0(void);
extern void Oem_S5S0Sequence(void);
extern void Oem_S4S0Sequence(void);
extern void Oem_S3S0Sequence(void);

extern void EnterDeepSleep(void);
extern BYTE CheckEnterDeepSleep(void);

extern void MoniterHWPG(void);
extern void Oem_SysPowerContrl(void);
extern void Oem_TriggerS0S3(BYTE causecode);
extern void Oem_TriggerS0S4(BYTE causecode);
extern void Oem_TriggerS0S5(BYTE causecode);
extern void Oem_S0S3Sequence(void);
extern void Oem_S0S4Sequence(void);
extern void Oem_S0S5Sequence(void);
extern void CheckResetSource(void);

extern void S5_S0Variable(void);
extern void S4_S0Variable(void);
extern void S3_S0Variable(void);
extern void S0_S5Variable(void);
extern void S0_S4Variable(void);
extern void S0_S3Variable(void);

extern void CheckSLP_S3(void);
extern void CheckSLP_S4(void);
extern void CheckSLP_S5(void);
extern void PulseSBPowerButton(void);
extern void CheckSBPowerButton(void);

typedef struct PowerSEQ
{
    FUNCT_PTR_B_V	func;	// Do step function
	WORD	delay;			// delay time (ms) 
	BYTE	checkstatus;	// step function is check pin status (EX: slp_s3 HWPG ...)
} sPowerSEQ;
#endif