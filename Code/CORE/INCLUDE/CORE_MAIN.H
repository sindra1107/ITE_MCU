/*-----------------------------------------------------------------------------
 * TITLE: CORE_MAIN.H
 * 
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#ifndef CORE_MAIN_H
#define CORE_MAIN_H 

#define Only_Timer1msEvent  0x01
#define All_TimerEvent      0x00

#define Normal_MainService  0xFF
 
static void main(void);
extern void main_service(void);
static void service_unlock(void);
static void service_Low_LVEvent(void);

static void service_1mS(void); 
static void Timer1msEvent(void);
static void Timer5msEvent(void);
static void Timer10msEventA(void);
static void Timer10msEventB(void);
static void Timer50msEventA(void);
static void Timer50msEventB(void);
static void Timer50msEventC(void);
static void Timer100msEventA(void);
static void Timer100msEventB(void);
static void Timer100msEventC(void);
static void Timer500msEventA(void);
static void Timer500msEventB(void);
static void Timer500msEventC(void);
static void Timer1SecEventA(void);
static void Timer1SecEventB(void);
static void Timer1SecEventC(void);
static void Timer1MinEvent(void);

#endif  

