/*----------------------------------------------------------------------------
 * Filename: OEM_PM3H  For Chipset: ITE.IT85XX
 *
 * Copyright (c) 2010 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#ifndef OEM_PMC3_H
#define OEM_PMC3_H

extern void service_pci4(void);

extern void PMC3Output(BYTE value);
extern void PMC3SetDataCounter(BYTE cunt);

extern void PMC3_Cmd_60(void);
extern void PMC3_Cmd_61(void);
extern void PMC3_Cmd_62(void);
extern void PMC3_Cmd_63(void);
extern void PMC3_Cmd_64(void);
extern void PMC3_Cmd_65(void);
extern void PMC3_Cmd_66(void);
extern void PMC3_Cmd_67(void);
extern void PMC3_Cmd_68(void);
extern void PMC3_Cmd_69(void);
extern void PMC3_Cmd_6A(void);
extern void PMC3_Cmd_6B(void);
extern void PMC3_Cmd_6C(void);
extern void PMC3_Cmd_6D(void);
extern void PMC3_Cmd_6E(void);
extern void PMC3_Cmd_6F(void);

extern void PMC3_Data_60(void);
extern void PMC3_Data_61(void);
extern void PMC3_Data_62(void);
extern void PMC3_Data_63(void);
extern void PMC3_Data_64(void);
extern void PMC3_Data_65(void);
extern void PMC3_Data_66(void);
extern void PMC3_Data_67(void);
extern void PMC3_Data_68(void);
extern void PMC3_Data_69(void);
extern void PMC3_Data_6A(void);
extern void PMC3_Data_6B(void);
extern void PMC3_Data_6C(void);
extern void PMC3_Data_6D(void);
extern void PMC3_Data_6E(void);
extern void PMC3_Data_6F(void);

extern void PMC3_Cmd_0X(void);
extern void PMC3_Cmd_1X(void);
extern void PMC3_Cmd_2X(void);
extern void PMC3_Cmd_3X(void);
extern void PMC3_Cmd_4X(void);
extern void PMC3_Cmd_5X(void);
extern void PMC3_Cmd_6X(void);
extern void PMC3_Cmd_7X(void);
extern void PMC3_Cmd_8X(void);
extern void PMC3_Cmd_9X(void);
extern void PMC3_Cmd_AX(void);
extern void PMC3_Cmd_BX(void);
extern void PMC3_Cmd_CX(void);
extern void PMC3_Cmd_DX(void);
extern void PMC3_Cmd_EX(void);
extern void PMC3_Cmd_FX(void);

extern void PMC3_Cmd_0XData(void);
extern void PMC3_Cmd_1XData(void);
extern void PMC3_Cmd_2XData(void);
extern void PMC3_Cmd_3XData(void);
extern void PMC3_Cmd_4XData(void);
extern void PMC3_Cmd_5XData(void);
extern void PMC3_Cmd_6XData(void);
extern void PMC3_Cmd_7XData(void);
extern void PMC3_Cmd_8XData(void);
extern void PMC3_Cmd_9XData(void);
extern void PMC3_Cmd_AXData(void);
extern void PMC3_Cmd_BXData(void);
extern void PMC3_Cmd_CXData(void);
extern void PMC3_Cmd_DXData(void);
extern void PMC3_Cmd_EXData(void);
extern void PMC3_Cmd_FXData(void);

#endif