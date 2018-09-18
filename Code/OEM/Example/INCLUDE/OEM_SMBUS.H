/*----------------------------------------------------------------------------
 * Filename: OEM_SMBus.H  For Chipset: ITE.IT85XX
 *
 * Author  : Dino
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#ifndef OEM_SMBUS_H
#define OEM_SMBUS_H

#define TotalSMBusChannel	3
#define ACK_Done			0x33
#define ACK_Error			0x44
#define ACK_Start           0xFF

#define	SMbusQ		        0x00	// Quick command
#define	SMbusSRB	        0x04	// Send Byte command and Receive Byte command
#define SMbusRWB	        0x08	// Read byte command Write byte command
#define	SMbusRWW	        0x0C	// Read word command Write word command
#define	SMbusRWBB	        0x14	// Read block command Write block command

#define Cmd_Quick		    0x00
#define Cmd_SendByte	    0x01
#define Cmd_RecvByte	    0x02
#define	Cmd_ReadByte	    0x03
#define	Cmd_WriteByte	    0x04
#define Cmd_ReadWord	    0x05
#define Cmd_WriteWord	    0x06
#define Cmd_ReadBlock	    0x07
#define Cmd_WriteBlock	    0x08

//-----------------------------------------------------------------------------
// SMBus table define
//-----------------------------------------------------------------------------
extern void PollSMBusSendByte(BYTE Channel,BYTE Addr,BYTE cmd);
extern void PollSMBusReceiveByte(BYTE Channel,BYTE Addr);
extern void PollReadSMBusByte(BYTE Channel,BYTE Addr,BYTE Comd);
extern void PollWriteSMBusByte(BYTE Channel,BYTE Addr,BYTE Comd,BYTE data1);
extern void PollReadSMBusWord(BYTE Channel,BYTE Addr,BYTE Comd);
extern void PollWriteSMBusWord(BYTE Channel,BYTE Addr,BYTE Comd,BYTE data1,BYTE data2);
extern void PollReadSMBusBlock(BYTE Channel,BYTE Addr,BYTE Comd);
extern void PollWriteSMBusBlock(BYTE Channel,BYTE Addr,BYTE Comd,BYTE ByteCunt);
extern void InitSMBus(void); 	
extern void service_smbus1(void);
extern void service_smbus2(void);
extern void service_smbus3(void);
extern void ClearSMBus1Variables(void);
extern void ClearSMBus2Variables(void);
extern void ClearSMBus3Variables(void);
extern void CheckSMBusTableSize(void);
extern void ServiceSMBus(void);
extern void SMBusCenterSelection(BYTE channel);
extern void SMBusCenter(void);
extern void WatiSMBusCHxFree(BYTE channel);
extern void InitSMBusChannel4(void);
extern BYTE CheckSMBusNeedService(void);
extern void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc);

typedef struct SCS
{
	BYTE	protocol;
    BYTE  	address;
    BYTE  	cmd;
    XBYTE 	*smbdata;	
	BYTE	Conditionflag;
	XBYTE	*ConditionVar;
	FUNCT_PTR_V_V	hookfunc;
	FUNCT_PTR_V_V	errorfunc;
	BYTE	Bcunt;
	//BYTE	data1;
	//BYTE	data2;
} sSCS;

typedef struct SSC
{
    XBYTE 	*index;	
	XBYTE	*timeout;
    XBYTE   *bytecount;
    XBYTE	*inusing;
    XBYTE   *tablesize;
    XBYTE   *serviceflag;
	FUNCT_PTR_V_V	servicefunc;
} sSSC;

extern sSSC code asSSC[];
extern sSCS code asSCS1[];
extern sSCS code asSCS2[];
extern sSCS code asSCS3[];

#endif