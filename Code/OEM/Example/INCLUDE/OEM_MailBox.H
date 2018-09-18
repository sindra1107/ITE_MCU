/*-----------------------------------------------------------------------------
 * TITLE: OEM_MAILBOX.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef	OEM_MailBox_H
#define OEM_MailBox_H

#define MBoxBufferSize			10				// bytes

#define MBox_Cmd				BRAM[0]
#define MBox_ECRamAddrH			BRAM[1]
#define MBox_ECRamAddrL			BRAM[2]
#define MBox_ECRamData1			BRAM[3]
#define MBox_ECRamData2			BRAM[4]

#define MBox_Cmd_ReadByte		0x01
#define MBox_Cmd_WriteByte		0x02

extern void HandleMailBox(void);
extern void ClearMBoxBuffer(void);

#endif