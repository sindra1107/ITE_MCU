/*-----------------------------------------------------------------------------
 * TITLE: OEM_6064.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_6064_H
#define OEM_6064_H

extern void Hook_60Port(BYTE KBHIData);
extern void Hook_64Port(BYTE KBHICmd);

extern void Hook_Keyboard_Cmd(BYTE kbcmd);
extern void Hook_Keyboard_Cmd_Parameter(BYTE kbcmdp);

extern void Hook_Mouse_D4Cmd(BYTE mscmd);
extern void Hook_Mouse_90Cmd(BYTE mscmd);
extern void Hook_Mouse_91Cmd(BYTE mscmd);
extern void Hook_Mouse_92Cmd(BYTE mscmd);
extern void Hook_Mouse_93Cmd(BYTE mscmd);

#endif
