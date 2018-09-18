
#ifndef OEM_MAIN_H
#define OEM_MAIN_H

#define Only_Timer1msEvent  0x01
#define All_TimerEvent      0x00

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void Hook_Timer1msEvent(IBYTE EventId);
extern void Hook_Timer5msEvent(void);
extern void Hook_Timer10msEventA(void);
extern void Hook_Timer10msEventB(void);
extern void Hook_Timer50msEventA(void);
extern void Hook_Timer50msEventB(void);
extern void Hook_Timer50msEventC(void);
extern void Hook_Timer100msEventA(void);
extern void Hook_Timer100msEventB(void);
extern void Hook_Timer100msEventC(void);
extern void Hook_Timer500msEventA(void);
extern void Hook_Timer500msEventB(void);
extern void Hook_Timer500msEventC(void);
extern void Hook_Timer1SecEventA(void);
extern void Hook_Timer1SecEventB(void);
extern void Hook_Timer1SecEventC(void);
extern void Hook_Timer1MinEvent(void);
extern void service_OEM_1(void);
extern void service_OEM_2(void);
extern void service_OEM_3(void);
extern void service_OEM_4(void);
extern void Hook_main_service_H(void);
extern void Hook_main_service_L(void);
extern BYTE Hook_Only_Timer1msEvent(void);
extern BYTE OEM_SkipMainServiceFunc(void);

#endif
