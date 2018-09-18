/*----------------------------------------------------------------------------
 * Filename: OEM_PM2.H  For Chipset: ITE.IT85XX
 *
 * Copyright (c) 2010 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#ifndef OEM_PMC2_H
#define OEM_PMC2_H

void service_pci3(void);
extern void Hook_68Port(BYTE PM2Data);
extern void Hook_6CPort(BYTE PM2Cmd);

#endif