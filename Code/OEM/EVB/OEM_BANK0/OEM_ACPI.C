/*-----------------------------------------------------------------------------
 * TITLE: OEM_ACPI.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// The hook function of 62 port data
//  Note : 
//  PM1Step != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_62Port(BYTE PM1Data)
{

}

//----------------------------------------------------------------------------
// The hook function of 66 port command.
//----------------------------------------------------------------------------
void Hook_66Port(BYTE PM1Cmd)
{

}

//----------------------------------------------------------------------------
// Hook function of ACPI command
//----------------------------------------------------------------------------
void Hook_ACPICommand(void)
{

}

//-------------------------------------------------------------------------------
// parameter "QeventSCI" only, For a pulsed SCI
//------------------------------------------------------------------------------
void OEM_ACPI_Gen_Int(void)
{
    ACPI_Gen_Int(QeventSCI);
}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void ResetSCIEvent(void)
{
    
    CLEAR_MASK(PM1STS,SCIEVT);
    ECCheckBurstMode = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: ECQEvent -Setup cause flag for an SCI and start the ACPI_Timer.
 *
 * sci_number = 1 through 255.  The Host uses this number to determine the
 * cause of the SCI.
 * ------------------------------------------------------------------------- */
void ECQEvent(BYTE sci_number, BYTE sci_mode)
{

	SET_MASK(PM1STS,SCIEVT);
    OEM_ACPI_Gen_Int();
}

//----------------------------------------------------------------------------
// Read EC ram Space 
//----------------------------------------------------------------------------
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
    // --example--
	//Tmp_XPntr=(ECRAM|MapIndex);
	//return(*Tmp_XPntr);
	return(0x00);
}

//----------------------------------------------------------------------------
// Write EC ram Space 
//----------------------------------------------------------------------------
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
    // --example--
	//Tmp_XPntr=(ECRAM|MapIndex);
	//*Tmp_XPntr = data1;
}
