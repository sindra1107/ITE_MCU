/*-----------------------------------------------------------------------------
 * TITLE: OEM_ACPI.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef	OEM_ACPI_H
#define	OEM_ACPI_H

extern void Hook_62Port(BYTE PM1Data);
extern void Hook_66Port(BYTE PM1Cmd);
extern void Hook_ACPICommand(void);
extern void ECQEvent(BYTE sci_number, BYTE sci_mode);
extern BYTE Hook_ReadMapECSpace(BYTE MapIndex);
extern void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1);
extern void OEM_ACPI_Gen_Int(void);
extern void ResetSCIEvent(void);

#endif