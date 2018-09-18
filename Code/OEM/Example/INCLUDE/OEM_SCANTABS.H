/*-----------------------------------------------------------------
 * TITLE: OEM_SCANTABS.H - RC Table(s) for Scan Matix
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *----------------------------------------------------------------*/

#ifndef OEM_SCANTABS_H
#define OEM_SCANTABS_H


const BYTE code Rc_ROM_Tables[];
const BYTE code KB_S3WakeUP_Tables[];
const BYTE code EtKey_S3WakeUP_Tables[];
const FUNCT_PTR_V_B code HotKey_Fn_Fx[];

extern void Hook_Setup_Scanner_Pntr(void);
extern void Hook_keyboard(BYTE KSIValus, BYTE KSOValus);
extern void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus);
extern void Hook_SetGPIOScanPinH(void);
extern void Hook_SetGPIOScanPinL(void);
extern void Hook_SetGPIOScanPinCtrl(void);
extern void OEM_Hook_Send_Key(BYTE table_entry, BYTE event);
extern BYTE OEM_Hook_Skip_Send_Key(void);
extern void Hook_Fn_Key_Make(void);
extern void Hook_Fn_Key_Break(void);
extern BYTE Hook_calc_index_comb_BIT6(void);
extern BYTE Hook_calc_index_comb_BIT7(void);

typedef struct BootHotKeyStruct	
{
	BYTE	        matrix;
	FUNCT_PTR_V_B   pfunction;
}sBootHotKeyStruct;

#endif