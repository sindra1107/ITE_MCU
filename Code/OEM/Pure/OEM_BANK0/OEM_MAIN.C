/*-----------------------------------------------------------------------------
 * TITLE: OEM_MAIN.C - OEM specific code
 *
 * Some "HOOKS" from CHIPHOOK.C are copied into this file in order to replace
 * (or augment) core functions.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//------------------------------------------------------------
// Hook 1ms events
// EventId is 0 ~ 9 cycle
//------------------------------------------------------------
void Hook_Timer1msEvent(IBYTE EventId)
{

}

//------------------------------------------------------------
// Hook 5ms events
//------------------------------------------------------------
void Hook_Timer5msEvent(void)
{

}

//------------------------------------------------------------
// Hook 10ms events
//------------------------------------------------------------
void Hook_Timer10msEventA(void)
{
    #ifdef ECPowerDownModeSupport
    ECPowerDownModeManager();
    #endif
}

//------------------------------------------------------------
// Hook 10ms events
//------------------------------------------------------------
void Hook_Timer10msEventB(void)
{

}

//------------------------------------------------------------
// Hook 50ms events A
//------------------------------------------------------------
void Hook_Timer50msEventA(void)
{

}

//------------------------------------------------------------
// Hook 50ms events B
//------------------------------------------------------------
void Hook_Timer50msEventB(void)
{

}

//------------------------------------------------------------
// Hook 50ms events C
//------------------------------------------------------------
void Hook_Timer50msEventC(void)
{

}

//------------------------------------------------------------
// Hook 100ms events A
//------------------------------------------------------------
void Hook_Timer100msEventA(void)
{

}

//------------------------------------------------------------
// Hook 100ms events B
//------------------------------------------------------------
void Hook_Timer100msEventB(void)
{

}

//------------------------------------------------------------
// Hook 100ms events C
//------------------------------------------------------------
void Hook_Timer100msEventC(void)
{

}

//------------------------------------------------------------
// Hook 500ms events A
//------------------------------------------------------------
void Hook_Timer500msEventA(void)
{

}

//------------------------------------------------------------
// Hook 500ms events B
//------------------------------------------------------------
void Hook_Timer500msEventB(void)
{
    
}

//------------------------------------------------------------
// Hook 500ms events C
//------------------------------------------------------------
void Hook_Timer500msEventC(void)
{
    
}

//------------------------------------------------------------
// Hook 1sec events A
//------------------------------------------------------------
void Hook_Timer1SecEventA(void)
{

}

//------------------------------------------------------------
// Hook 1sec events B
//------------------------------------------------------------
void Hook_Timer1SecEventB(void)
{

}

//------------------------------------------------------------
// Hook 1sec events C
//------------------------------------------------------------
void Hook_Timer1SecEventC(void)
{

}

//------------------------------------------------------------
// Hook1min events
//------------------------------------------------------------
void Hook_Timer1MinEvent(void)
{

}

//------------------------------------------------------------
// service_OEM_1
//------------------------------------------------------------
void service_OEM_1(void)
{

}

//------------------------------------------------------------
// service_OEM_2
//------------------------------------------------------------
void service_OEM_2(void)
{

}

//------------------------------------------------------------
// service_OEM_3
//------------------------------------------------------------
void service_OEM_3(void)
{

}

//------------------------------------------------------------
// service_OEM_4
//------------------------------------------------------------
void service_OEM_4(void)
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
void Hook_main_service_H(void) 
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
void Hook_main_service_L(void) 
{

}

//------------------------------------------------------------
// Timer event control function
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
//------------------------------------------------------------
BYTE Hook_Only_Timer1msEvent(void)
{

// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
    return(All_TimerEvent);
}

//----------------------------------------------------------------------------
// OEM_SkipMainServiceFunc
//  Note:
//      1. Always return(0xFF|Normal_MainService) to run normal main_service function.
//      2. If you don't understand the use of OEM_SkipMainServiceFunc function, don't change anything.
//----------------------------------------------------------------------------
BYTE OEM_SkipMainServiceFunc(void)
{
    
    // Return :
    return(Normal_MainService);
}