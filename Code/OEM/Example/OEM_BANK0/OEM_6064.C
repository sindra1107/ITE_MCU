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

//-----------------------------------------------------------------------
// Handle command 80 - 
//----------------------------------------------------------------------- 
void OEM_Cmd_80(void)
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command 81 - 
//-----------------------------------------------------------------------
void OEM_Cmd_81(void)
{
	SetHandleCmdData(2);
}

//-----------------------------------------------------------------------
// Handle command 94 - 
//-----------------------------------------------------------------------
void OEM_Cmd_94(void)
{
    RamProgram(0x64);	// For AMI BISO flash utility
}

//-----------------------------------------------------------------------
// Handle command B4 - Phoenix flash command for SPI rom
//-----------------------------------------------------------------------
void OEM_Cmd_B4(void)
{
    RamProgram(0x64);
}

//-----------------------------------------------------------------------
// Handle command D8 - 
//-----------------------------------------------------------------------
void OEM_Cmd_D8(void)
{
    RamProgram(0x64);
}

//-----------------------------------------------------------------------
// Handle command D9 - 
//-----------------------------------------------------------------------
void OEM_Cmd_D9(void)
{
	SetHandleCmdData(1);
}

//-----------------------------------------------------------------------
// Handle command DD - 
//-----------------------------------------------------------------------
void OEM_Cmd_DD(void)
{
    RamProgram(0x64);
}

//-----------------------------------------------------------------------
// Process command data 80 - 
//-----------------------------------------------------------------------
void OEM_Cmd_80Data(void)
{
	ResponseKBData(Hook_ReadMapECSpace(KBHIData));
}

//-----------------------------------------------------------------------
// Process command data 81 - 
//-----------------------------------------------------------------------
void OEM_Cmd_81Data(void)
{
  	if (KBHIStep == 2)
	{
     	KBHIData1=KBHIData;  	// address
	}
	else
	{
		Hook_WriteMapECSpace(KBHIData1,KBHIData);
 	}
}

//-----------------------------------------------------------------------
// Process command data D9 - 
//-----------------------------------------------------------------------
void SendVerFunction(BYTE code* cpntr)
{
    BYTE index;
    index = 0x00;
    
    while(1)
    {
        if(*cpntr=='$')
        {
            Data_To_Host(*cpntr);
            break;
        }
        else
        {
            Data_To_Host_nWait(*cpntr);
        }
        cpntr++;

        index++;
        if(index>32)
        {
            break;
        }
    }
}

void OEM_Cmd_D9Data(void)
{
    BYTE index;
    index=0x00;

    switch(KBHIData)
    {
        case 1:         // 1: revision desciption
            SendVerFunction(P_rev);   
            break;
            
        case 2:         // 2: platform information
            SendVerFunction(P_model);         
            break;            
    
        case 3:         // 3: last updated date
            SendVerFunction(P_date);                
            break;

        case 4:         // 4: internal revision
            Data_To_Host_nWait(P_digit[0]);
            Data_To_Host(P_digit[1]);
            break;

        default:
            break;
    }
}

//----------------------------------------------------------------------------
// The function of 60 port
//  Note : 
//  KBHIStep != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_60Port(BYTE KBHIData)
{
    switch(KBHIData)
    {
        case 0x80:
        OEM_Cmd_80Data();
        break;

        case 0x81:
        OEM_Cmd_81Data();
        break;

        case 0xD9:
        OEM_Cmd_D9Data();
        break;
            

        default:
        break;
    }
}

//----------------------------------------------------------------------------
// The function of 64 port
//----------------------------------------------------------------------------
void Hook_64Port(BYTE KBHICmd)
{
    switch(KBHICmd)
    {
        case 0x80:
        OEM_Cmd_80();
        break;

        case 0x81:
        OEM_Cmd_81();
        break;

        case 0x94:
        OEM_Cmd_94();
        break;

        case 0xB4:
        OEM_Cmd_B4();
        break;

        case 0xD8:
        OEM_Cmd_D8();
        break;

        case 0xD9:
        OEM_Cmd_D9();
        break;

        case 0xDD:
        OEM_Cmd_DD();
        break;

        default:
        break;
    }
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