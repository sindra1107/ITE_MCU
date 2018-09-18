#ifndef	OEM_Debug_H
#define OEM_Debug_H

#define DebugRamAddr 0x800
#define DebugRamRange 0xFF

extern void RamDebug(unsigned char dbgcode);

#endif