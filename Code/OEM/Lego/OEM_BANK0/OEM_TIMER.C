/*-----------------------------------------------------------------------------
 * TITLE: OEM_TIMER.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Enable internal watch dog and waiting EC reset                 
//----------------------------------------------------------------------------
void InternalWDTNow(void)

{
	WDTCON|=0x01;   // WDTRST = 1 Reset watch dog timer.
	WDTCON|=0x02;   // WDTEN  = 1 Enable watch dog.     
	while(1);       // Wait for watch dog time-out      
}

//----------------------------------------------------------------------------
// Enable internal watch dog
//----------------------------------------------------------------------------
void EnableInternalWDT(void)
{
	CKCON |= 0xC0;		    // set 26 bit counter
	WDTRST = 1;				// reset internal watch dog
	WDTEB = 1;				// enable internal watch dog		
}

//----------------------------------------------------------------------------
// Disable internal watch dog
//----------------------------------------------------------------------------
void DisableInternalWDT(void)
{
	WDTEB = 0;				// Disable internal watch dog
}

//----------------------------------------------------------------------------
// Disable internal watch dog
//----------------------------------------------------------------------------
void ResetInternalWDT(void)
{
	WDTRST = 1;				// Reset internal watch dog counter
}


