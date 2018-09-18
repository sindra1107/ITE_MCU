/*-----------------------------------------------------------------------------
 * TITLE: CORE_PORT6064.H - prototypes for CORE_PORT6064.C.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

#ifndef CORE_PORT6064_H
#define CORE_PORT6064_H

void service_pci1(void);
void ResponseKBData(BYTE RData);
void SetHandleCmdData(BYTE step);

void KeyboardCmd(BYTE data_byte);
BBYTE Set_Overlay_Mask(BBYTE data_byte, FLAG bit_state);
//BYTE Read_Input_Port_1(void);
BYTE Read_Output_Port_2(void);
void Core_60Port(BYTE KBHIData);
void Core_64Port(BYTE KBHICmd);
void Cmd_AE(void);
void Cmd_A8(void);

#endif 
