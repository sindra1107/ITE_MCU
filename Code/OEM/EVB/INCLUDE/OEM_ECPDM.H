/*----------------------------------------------------------------------------
 * Filename: OEM_ECPDM.H  For Chipset: ITE.IT85XX
 *
 * Function: The example of EC power down mode control.
 *
 * Author  : Dino
 * 
 * Copyright (c) 2012 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_ECPDM_H
#define OEM_ECPDM_H
 
//#ifdef ECPowerDownModeSupport
#define EC_PD_Normal            0x00
#define EC_PD_Idle              0x01
#define EC_PD_DeepDoze          0x02
#define EC_PD_DeepSleep         0x03

#define EC_KernelEventPending   0x01
#define EC_KernelEventClear     0x00

//--------------------------------------------------
// Time based is 10ms
//--------------------------------------------------
#define EC_PD_DelayIsr_Int1     10      // 100ms
#define EC_PD_DelayPS2IF        100     // 1000ms
#define EC_PD_DelayKBIF         100     // 1000ms

extern void Hook_ECExitIdleMode(void);
extern void Hook_ECExitDeepDozeMode(void);
extern void Hook_ECExitDeepSleepMode(void);
extern void Hook_ECPrepareEnterIdleMode(void);
extern void Hook_ECPrepareEnterDeepDozeMode(void);
extern void Hook_ECPrepareEnterDeepSleepMode(void);
extern BYTE Hook_ECAllowPowerDownMode(void);
extern void Hook_OEMDelayPowerDownMode(XWORD x10ms_delay);

extern void SetPeriodWakeUpTimerForPDMode(BYTE period, WORD keepwakeuptime);
extern void ECPowerDownModeManager(void);
extern void ECEnterIdleMode(void);
extern void ECEnterDeepDozeMode(void);
extern void ECEnterDeepSleepMode(void);
extern void ECPowerDownModeSelection(BYTE PDMode);
extern void KernelDelayPowerDownMode(BYTE x10ms_delay);
extern BYTE ECAllowPowerDownMode(void);
extern void ECExitIdleMode(void);
extern void ECExitDeepDozeMode(void);
extern void ECExitDeepSleepMode(void);
extern void ECPrepareEnterIdleMode(void);
extern void ECPrepareEnterDeepDozeMode(void);
extern void ECPrepareEnterDeepSleepMode(void);
extern void ECPowerDownEnableExternalTimer1(void);
extern void ECDisableExternalTimer1(void);
//#endif

#endif