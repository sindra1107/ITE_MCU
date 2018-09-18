/*-----------------------------------------------------------------------------
 * TITLE: OEM_ACPI.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Handle OEM ACPI command
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Handle OEM ACPI command 8x.
//----------------------------------------------------------------------------
void OEM_ACPI_Cmd_80(void)
{
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))  // ACPI mode
    {
        if(IS_MASK_CLEAR(PM1STS,BURST)) // Non-burst mode
        {
            ECCheckBurstMode = 1;
        }
    }
}

void OEM_ACPI_Cmd_81(void)
{
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))  // ACPI mode
    {
        if(IS_MASK_CLEAR(PM1STS,BURST)) // Non-burst mode
        {
            ECCheckBurstMode = 1;
        }
  	}
}

void OEM_ACPI_Cmd_82(void)
{
    ECCheckBurstMode = 1;
}

void OEM_ACPI_Cmd_83(void)
{
    ECCheckBurstMode = 0;
}

void OEM_ACPI_Cmd_84(void)
{
	ITempB05 = 0x00;
	if (SCI_Event_Out_Index != SCI_Event_In_Index)
	{  
		ITempB05 = SCI_Event_Buffer[SCI_Event_Out_Index];
    	SCI_Event_Out_Index++;
    	if (SCI_Event_Out_Index >= EVENT_BUFFER_SIZE) 
		{
           	SCI_Event_Out_Index = 0;
   		}
   		if (SCI_Event_Out_Index == SCI_Event_In_Index)
         	CLEAR_MASK(PM1STS,SCIEVT);

		SendFromAcpi(ITempB05);
	}
	else
	{
		CLEAR_MASK(PM1STS,SCIEVT);
	}
}

void OEM_ACPI_Cmd_86(void)
{
    SET_MASK(SYS_MISC1,ACPI_OS);
}

void OEM_ACPI_Cmd_87(void)
{
    CLEAR_MASK(SYS_MISC1,ACPI_OS);
}

void OEM_ACPI_Cmd_8E(void)
{
	SET_MASK(UtilityFlag, SMBusDebug);
}
void OEM_ACPI_Cmd_8F(void)
{
	CLEAR_MASK(UtilityFlag, SMBusDebug);
}

//----------------------------------------------------------------------------
// Handle OEM ACPI command Dx.
//----------------------------------------------------------------------------
void OEM_ACPI_Cmd_D8(void)
{
    FanFullOn();
	RamProgram(0X66);
}

void OEM_ACPI_Cmd_DD(void)
{
	RamProgram(0X66);
}


//----------------------------------------------------------------------------
// The hook function of 62 port data
//  Note : 
//  PM1Step != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_62Port(BYTE PM1Data)
{
    switch(PM1Data)
    {

        default:
        break;
    }
}

//----------------------------------------------------------------------------
// The hook function of 66 port command.
//----------------------------------------------------------------------------
void Hook_66Port(BYTE PM1Cmd)
{
    switch(PM1Cmd)
    {
        case 0x80:
        OEM_ACPI_Cmd_80();
        break;

        case 0x81:
        OEM_ACPI_Cmd_81();
        break;

        case 0x82:
        OEM_ACPI_Cmd_82();
        break;

        case 0x83:
        OEM_ACPI_Cmd_83();
        break;

        case 0x84:
        OEM_ACPI_Cmd_84();
        break;

        case 0x86:
        OEM_ACPI_Cmd_86();
        break;

        case 0x87:
        OEM_ACPI_Cmd_87();
        break;

        case 0x8E:
        OEM_ACPI_Cmd_8E();
        break;

        case 0x8F:
        OEM_ACPI_Cmd_8F();
        break;

        case 0xD8:
        OEM_ACPI_Cmd_D8();
        break;

        case 0xDD:
        OEM_ACPI_Cmd_DD();
        break;

        default:
        break;
    }
}

//----------------------------------------------------------------------------
// Hook function of ACPI command
//----------------------------------------------------------------------------
void Hook_ACPICommand(void)
{
#if ACPI_Smbus
	OSSMbusComd();		// ACPI SMBus command
#endif	
}

//-------------------------------------------------------------------------------
// parameter "QeventSCI" only, For a pulsed SCI
//------------------------------------------------------------------------------
void OEM_ACPI_Gen_Int(void)
{
    ACPI_Gen_Int(QeventSCI);
}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void ResetSCIEvent(void)
{
    SCI_Event_In_Index = 0;
    SCI_Event_Out_Index = 0;

    #if ACPI_QEventPending
    PD_SCI_Event_In_Index = 0;
    PD_SCI_Event_Out_Index = 0;
    #endif
    
    CLEAR_MASK(PM1STS,SCIEVT);

    ECCheckBurstMode = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: ECQEvent -Setup cause flag for an SCI and start the ACPI_Timer.
 *
 * sci_number = 1 through 255.  The Host uses this number to determine the
 * cause of the SCI.
 * ------------------------------------------------------------------------- */
void ECQEvent(BYTE sci_number, BYTE sci_mode)
{
    #if ACPI_QEventPending
    if((sci_mode == SCIMode_Normal)||(sci_mode == SCIMode_Pending))
    {
        if(sci_mode == SCIMode_Normal)
        {
            if(PD_SCI_Event_In_Index!=PD_SCI_Event_Out_Index)
            {
                PendingECQEvent(sci_number);
                return;
            }
        }
    
        if(IS_MASK_SET(PM1STS,P_IBF)||IS_MASK_SET(KBHISR, IBF))
        {
            if(sci_mode == SCIMode_Pending)
            {
                if(PD_SCI_Event_Out_Index==0x00)
                {
                    PD_SCI_Event_Out_Index = PENDING_BUFFER-1;
                }
                else
                {
                    PD_SCI_Event_Out_Index--;
                }
            }
            else
            {
                PendingECQEvent(sci_number);
            }
            return;
        } 
    }
    #endif
    
	ITempB05 = SCI_Event_In_Index; 			// Get the input index.
	SCI_Event_Buffer[ITempB05] = sci_number; // Put the SCI number in the buffer.
 	ITempB05++;    							// Increment the index. 
 	if (ITempB05 >= EVENT_BUFFER_SIZE) 
	{
     	ITempB05 = 0;
 	}
 											// If the buffer is not full, update the input index.
  	if (ITempB05 != SCI_Event_Out_Index) 
	{
   		SCI_Event_In_Index = ITempB05;
    }
    
	SET_MASK(PM1STS,SCIEVT);
    OEM_ACPI_Gen_Int();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PendingECQEvent(BYTE sci_number)
{
    BYTE index;
    
    #if ACPI_QEventPending
    
	index = PD_SCI_Event_In_Index; 			    // Get the input index.
	PD_SCI_Event_Buffer[index] = sci_number;    // Put the SCI number in the buffer.
 	index++;    							    // Increment the index. 
 	if(index >= PENDING_BUFFER) 
	{
     	index = 0;
 	}
 											    // If the buffer is not full, update the input index.
  	if(index != PD_SCI_Event_Out_Index) 
	{
   		PD_SCI_Event_In_Index = index;
    }
    #endif
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Get_PendingECQEvent(void)

{
    BYTE sci_number;
    
    #if ACPI_QEventPending
    if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
	    if (PD_SCI_Event_Out_Index != PD_SCI_Event_In_Index)
	    {  
		    sci_number = PD_SCI_Event_Buffer[PD_SCI_Event_Out_Index];
    	    PD_SCI_Event_Out_Index++;
    	    if(PD_SCI_Event_Out_Index >= PENDING_BUFFER) 
		    {
           	    PD_SCI_Event_Out_Index = 0;
   		    }

            ECQEvent(sci_number, SCIMode_Pending);
	    }
    }
    #endif
}

//----------------------------------------------------------------------------
// Read EC ram Space 
//----------------------------------------------------------------------------
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
	Tmp_XPntr=(ECRAM|MapIndex);
	return(*Tmp_XPntr);	
}

void SpecialFunc_01(void)
{

}

//----------------------------------------------------------------------------
// Do hook function when write EC ram Space 
//----------------------------------------------------------------------------
const sECRamSS code asECRamSS[] = 
{	
    {&MISC_FLAG1,    SpecialFunc_01		},		
};

void WriteECRamSpecialFunc(XBYTE *xdptr)        //81 EC write command
{
	BYTE index;
	index=0x00;
	while(index<(sizeof(asECRamSS)/sizeof(sECRamSS)))
	{
		if(xdptr == asECRamSS[index].addr)
		{
			(asECRamSS[index].hookfunc)();
			break;
		}
		index++;
	}
}

//----------------------------------------------------------------------------
// Write EC ram Space 
//----------------------------------------------------------------------------
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
	Tmp_XPntr=(ECRAM|MapIndex);
	*Tmp_XPntr = data1;

#if HookFucnofWriteECRam
    WriteECRamSpecialFunc(Tmp_XPntr);
#endif	
}

#if ACPI_Smbus
//----------------------------------------------------------------------------
// process OS SMBus command
//----------------------------------------------------------------------------
// ACPI response to writes to SMBus Protocol register. 
const FUNCT_PTR_B_V code vOSSMbusComd_table[16] =
{								//the low nibble of SMB_PRTC
	DummyFunction,		//0x00	
	DummyFunction,		//0x01
	DummyFunction,		//0x02-Write Quick Command 
	DummyFunction,		//0x03-Read Quick Command
	DummyFunction,		//0x04-Send Byte
	DummyFunction,		//0x05-Receive Byte
	vOSSMbusWBYTE,		//0x06-Write Byte
	vOSSMbusRByte,		//0x07-Read Byte
	vOSSMbusWWord,		//0x08-Write Word
	vOSSMbusRWord,		//0x09-Read Word
	vOSSMbusWBlcok,		//0x0A-Write Block
	vOSSMbusRBlcok,		//0x0B-Read Block
	DummyFunction,		//0x0C-Process Call
	DummyFunction,		//0x0D-Write Block-Read Block Process Call
	DummyFunction,		//0x0E
	DummyFunction		//0x0F
};

void OSSMbusComd(void)
{
	if((SMB_PRTC != 0x00)&&(SMB_ADDR == 0x16))
	{
  		SMB_STS = 0x00;
     	SMB_PRTC &= 0x0F;
      	if((vOSSMbusComd_table[SMB_PRTC])())
      	{
     		SMB_STS = 0x80;
      	}
		else
		{
			SMB_STS = 0x5A;
		}
      	SMB_PRTC = 0x00;
        
        if(IS_MASK_SET(SYS_MISC1,ACPI_OS)) 
        {
            ECQEvent(PowerManagement, SCIMode_ACPI_SMBus);
        }
        else
        {
            ECQEvent(PowerManagement, SCIMode_Force);
        }
  	}
}

BYTE vOSSMbusWBlcok(void)
{
  	return (bRSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vOSSMbusRBlcok(void)
{
  	return (bRSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vOSSMbusRByte(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusRWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusWBYTE(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vOSSMbusWWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

void DummyFunction(void)
{

}
#endif

