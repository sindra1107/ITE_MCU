/*-----------------------------------------------------------------------------
 * TITLE: OEM_TIMER.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *---------------------------------------------------------------------------*/
 
#ifndef OEM_TIMER_H
#define OEM_TIMER_H

#define T_HSPI_ISRTime      Timer_85ms

extern void InternalWDTNow(void);
extern void EnableInternalWDT(void);
extern void DisableInternalWDT(void);
extern void ResetInternalWDT(void);

#endif