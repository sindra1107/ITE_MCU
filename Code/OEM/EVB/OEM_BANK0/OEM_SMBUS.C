/*----------------------------------------------------------------------------
 * Filename: OEM_SMBus.C  For Chipset: ITE.IT85XX
 *
 * Function: The interrupt service method of SMBus function
 *
 * Author  : Dino
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>
 
//----------------------------------------------------------------------------
// [rblk_bcis] the byte count of read smbus read block protocol
//----------------------------------------------------------------------------
void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc)
{

}