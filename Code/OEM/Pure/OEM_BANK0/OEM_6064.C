/*-----------------------------------------------------------------------------
 * TITLE: OEM_6064.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// The function of 60 port
//  Note : 
//  KBHIStep != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_60Port(BYTE KBHIData)
{

}

//----------------------------------------------------------------------------
// The function of 64 port
//----------------------------------------------------------------------------
void Hook_64Port(BYTE KBHICmd)
{

}

//-----------------------------------------------------------------------
// kbcmd : keyboard command from 0x60 port 
//-----------------------------------------------------------------------
void Hook_Keyboard_Cmd(BYTE kbcmd)
{

}

//-----------------------------------------------------------------------
// kbcmdp : keyboard command parameter from 0x60 port 
// for example keyboard command (0xED, 0xF0, 0xF3)
//-----------------------------------------------------------------------
void Hook_Keyboard_Cmd_Parameter(BYTE kbcmdp)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0xD4 command
//-----------------------------------------------------------------------
void Hook_Mouse_D4Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x90 command
//-----------------------------------------------------------------------
void Hook_Mouse_90Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x91 command
//-----------------------------------------------------------------------
void Hook_Mouse_91Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x92 command
//-----------------------------------------------------------------------
void Hook_Mouse_92Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x93 command
//-----------------------------------------------------------------------
void Hook_Mouse_93Cmd(BYTE mscmd)
{

}