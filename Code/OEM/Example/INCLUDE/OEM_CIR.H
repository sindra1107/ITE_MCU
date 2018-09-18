/*-----------------------------------------------------------------------------
 * TITLE: OEM_CIR.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef	OEM_CIR_H
#define OEM_CIR_H

extern void Hook_CIRWakeUp(void);
extern void CIRS4S5WakeUp(void);
extern void CIRS3WakeUp(void);
extern void Init_CIR(void);
extern void Reset_CIR(void);
extern void bClearCirFIFO(void);
extern void bConfirmCirRIM(void);
extern void service_cir(void);
extern void ClearCIR(void);

#endif