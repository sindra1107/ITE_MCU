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

#define EVENT_BUFFER_SIZE   9
#define PENDING_BUFFER      8

#define ACPICmdSCI          0x00
#define QeventSCI           0x01

#define SCIMode_Normal      0x00    // For OEM SCI event
#define SCIMode_Pending     0x01
#define SCIMode_Force       0x02
#define SCIMode_ACPI_SMBus  0x03

extern void Hook_62Port(BYTE PM1Data);
extern void Hook_66Port(BYTE PM1Cmd);
extern void Hook_ACPICommand(void);

extern void ECQEvent(BYTE sci_number, BYTE sci_mode);
extern void PendingECQEvent(BYTE sci_number);
extern void Get_PendingECQEvent(void);
extern BYTE Hook_ReadMapECSpace(BYTE MapIndex);
extern void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1);

extern void OSSMbusComd(void);
extern BYTE vOSSMbusWBlcok(void);
extern BYTE vOSSMbusRBlcok(void);
extern BYTE vOSSMbusRByte(void);
extern BYTE vOSSMbusRWord(void);
extern BYTE vOSSMbusWBYTE(void);
extern BYTE vOSSMbusWWord(void);
extern void DummyFunction(void);
extern void OEM_ACPI_Gen_Int(void);
extern void ResetSCIEvent(void);

typedef struct ECRamSS
{
	XBYTE	*addr;
	FUNCT_PTR_V_V	hookfunc;
} sECRamSS;
#endif
