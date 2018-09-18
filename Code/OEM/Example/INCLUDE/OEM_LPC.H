/*-----------------------------------------------------------------------------
 * TITLE: OEM_LPC.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *---------------------------------------------------------------------------*/

#ifndef OEM_LPC_H
#define OEM_LPC_H

//----------------------------------------------------------------------------
// Protect mode define
//----------------------------------------------------------------------------
#define ProtectMode_ReadProtection      0x00    // Read protection
#define ProtectMode_WriteProtection     0x40    // Write protection
#define ProtectMode_RWProtection        0x80    // Read+Write protection

extern void HLPC_Protect0Mode(BYTE mode);
extern void HLPC_Protect0Size(BYTE size);
extern void HLPC_Protect1Mode(BYTE mode);
extern void HLPC_Protect1Size(BYTE size);
extern void HLPC_LockProtectRelatedRegisters(void);

//----------------------------------------------------------------------------
// Protect size define
//----------------------------------------------------------------------------
#define ProtectSize_Disable             0x00
#define ProtectSize_4K                  0x01
#define ProtectSize_8K                  0x02
#define ProtectSize_16K                 0x03
#define ProtectSize_32K                 0x04
#define ProtectSize_64K                 0x05
#define ProtectSize_128K                0x06
#define ProtectSize_256K                0x0E
#define ProtectSize_512K                0x07

extern void HLPC_WriteProtect0(void);
extern void HLPC_WriteProtectEnable0(void);
 
#endif