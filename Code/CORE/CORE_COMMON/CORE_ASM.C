/*-----------------------------------------------------------------------------
 * TITLE: CORE_ASM.H
 *
 * Author : Dino
 *
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------
// init bank mechanism to code bank 0
//-----------------------------------------------------------------
void ResetBANKDATA(void)
{
    #pragma asm
    EXTRN CODE (?B_SWITCH0)
    CALL    ?B_SWITCH0
    #pragma endasm
}