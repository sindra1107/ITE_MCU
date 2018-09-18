/*-----------------------------------------------------------------------------
 * TITLE: OEM_Debug.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//------------------------------------------------------------
// Debug function
//------------------------------------------------------------
void RamDebug(unsigned char dbgcode)
{
  	PORT_BYTE_PNTR ClearIndex;
 	PORT_BYTE_PNTR byte_register_pntr;
    BYTE index;
  	BYTE i;
	
    byte_register_pntr = DebugRamAddr+DebugRamRange;          
    index = *byte_register_pntr;
    *byte_register_pntr +=1;
	
    if ( *byte_register_pntr == DebugRamRange )
   	{
   		*byte_register_pntr = 0;
       	ClearIndex= DebugRamAddr;

		for (i=0x00;i<DebugRamRange;i++)
     	{
         	*ClearIndex=0x00;
           	ClearIndex++;
     	}
  	}

	byte_register_pntr = DebugRamAddr + index;
    *byte_register_pntr = dbgcode;
}