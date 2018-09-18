/*-----------------------------------------------------------------------------
 * TITLE: OEM_FLASH.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef	OEM_FLASH_H
#define	OEM_FLASH_H

extern void RamProgram(BYTE useport);
extern void LPC_RamCode(void);
extern void OEM_SPIProtectAll(void);
extern void OEM_SPIUnlockAll(void);
extern void OEM_Write_SPI_256Bytes(void);
extern void OEM_Read_SPI_256Bytes(void);
extern void OEM_SPI_Read_ID(void);
extern BYTE OEM_SPIReadStatus(void);
#endif