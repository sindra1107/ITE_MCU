/*----------------------------------------------------------------------------
 * TITLE: CORE_TIMERS.H - Header File for Timer.C
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *----------------------------------------------------------------------------*/
 
#ifndef CORE_TIMERS_H
#define CORE_TIMERS_H

//-----------------------------------------------------------------------------
// Timer define
//-----------------------------------------------------------------------------
#define Timer_60u			(0xFFFF-46)
#define Timer_100u			(0xFFFF-76)
#define Timer_150u			(0xFFFF-115)
#define Timer_300u			(0xFFFF-230)
#define Timer_600u			(0xFFFF-460)
#define Timer_500u			(0xFFFF-383)
#define Timer_1ms			(0xFFFF-767)
#define Timer_2ms			(0xFFFF-1534)
#define Timer_5ms			(0xFFFF-3833)
#define Timer_20ms			(0xFFFF-15332)
#define Timer_26ms          (0xFFFF-19942)
#define Timer_30ms	        (0xFFFF-22998)
#define Timer_40ms		    (0xFFFF-30640)
#define Timer_85ms	        (0xFFFF-65534)
#define T_ACPI_BurstTime	Timer_2ms

extern void Load_Timer_A(void);
extern void Enable_Timer_A(void);
extern void Stop_Timer_A(void);
extern void Load_Timer_B(void);
extern void Stop_Timer_B(void);
extern void Init_Timers(void);
//extern void Microsecond_Delay(WORD delay);
extern void Delay1MS (BYTE bMS);
extern void DelayXms(BYTE bMS);
extern void Init_UART(void);
#endif 
