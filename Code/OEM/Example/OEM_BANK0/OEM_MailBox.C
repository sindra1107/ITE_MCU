/*-----------------------------------------------------------------------------
 * TITLE: OEM_MAILBOX.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

void HandleMailBox(void)
{
	if(SystemNotS0)
	{
		return;
	}

	if(MBox_Cmd==0x00)
	{
		return;
	}

	switch(MBox_Cmd)
	{
		case MBox_Cmd_ReadByte:
  			Tmp_XPntr=((MBox_ECRamAddrH<<8)+MBox_ECRamAddrL);
			MBox_ECRamData1 = *Tmp_XPntr;
			break;

		case MBox_Cmd_WriteByte:
			Tmp_XPntr=((MBox_ECRamAddrH<<8)+MBox_ECRamAddrL);
			*Tmp_XPntr=MBox_ECRamData1;
			break;

		default:
			break;

	}
	
	MBox_Cmd = 0x00;

}


void ClearMBoxBuffer(void)
{
	BYTE index;
	for(index=0x00;index<MBoxBufferSize;index++)
	{
		BRAM[index]=0x00;
	}
}