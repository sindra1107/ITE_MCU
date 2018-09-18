/*----------------------------------------------------------------------------
 * Filename: OEM_PM2.C  For Chipset: ITE.IT85XX
 *
 * Copyright (c) 2010 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// The function of debuging 68 port
//----------------------------------------------------------------------------
void Hook_68Port(BYTE PM2Data)
{

}

//----------------------------------------------------------------------------
// The function of debuging 6C port
//----------------------------------------------------------------------------
void Hook_6CPort(BYTE PM2Cmd)
{

}

//----------------------------------------------------------------------------
// Process Command/Data received from System via 68/6C interface
//----------------------------------------------------------------------------
void service_pci3(void)
{
    if ( IS_MASK_CLEAR(PM2STS,P_IBF) )  
    {
		return; 
    }
	
	if ( PM2STS & P_C_D)	// Command port
	{
        PM2DataCount =0;
   		PM2Cmd  = PM2DI;	// Load command
		EnablePMCIBFInt();			
		Hook_6CPort(PM2Cmd);    // Handle command		
	}
	else					// Data port
	{
        PM2Data = PM2DI;
        EnablePMCIBFInt();
        if (PM2DataCount!=0x00) 
        {
		    Hook_68Port(PM2Cmd);   // Handle command data
		    PM2DataCount--;
	    }
	}
}

