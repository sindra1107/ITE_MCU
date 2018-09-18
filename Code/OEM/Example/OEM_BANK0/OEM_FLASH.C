/*-----------------------------------------------------------------------------
 * TITLE: OEM_FLASH.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

void SetLPCClockFreeRun(void)
{
	GPCRH0 = OUTPUT;
	CLEAR_MASK(GPDRH,BIT(0));
}


//----------------------------------------------------------------------------
// The function of flashing
//----------------------------------------------------------------------------
void LPC_RamCode(void)
{
	RamcodeCmd = 0x00;

	SET_MASK(SMECCS,HOSTWA);	// Host write allow 

	if(RamCodePort==0x64)
	{
		KBHIKDOR = 0xFA;
	}
	else if(RamCodePort==0x66)
	{
		PM1DO = 0xFA;
	}	
	else if(RamCodePort==0x6C)
	{
		PM2DO = 0xFA;
	}		
 	while(1)
  	{
  		if(RamCodePort==0x64)
		{
			if( IS_MASK_CLEAR(KBHISR,IBF)) continue;
        	if( IS_MASK_CLEAR(KBHISR,C_D)) continue;
       		RamcodeCmd = KBHIDIR;
  		}
		else if(RamCodePort==0x66)
		{
        	if ( IS_MASK_CLEAR(PM1STS,P_IBF)) continue;
        	if ( IS_MASK_CLEAR(PM1STS,P_C_D)) continue;
        	RamcodeCmd = PM1DI;
		}		
		else if(RamCodePort==0x6C)
		{
        	if ( IS_MASK_CLEAR(PM2STS,P_IBF)) continue;
        	if ( IS_MASK_CLEAR(PM2STS,P_C_D)) continue;
        	RamcodeCmd = PM2DI;
		}	
		
        if ( RamcodeCmd == 0x55)
     	{
     		WinFlashMark = 0x33;
        	break;
  		}
		else if ( RamcodeCmd == 0xAF)
     	{
			WDTRST = 1;			// Reset watch dog timer
			WDTEB = 1;			// Enable watch dog
       		while(1);			// Wait for watch dog time-out
        }
        else if ( RamcodeCmd == 0xD7)   // For AMI BIOS
        {
            CLEAR_MASK(SMECCS,HOSTWA);  // Host write not allow
            _nop_();
            _nop_();
            SET_MASK(SMECCS,HOSTWA);	// Host write allow 
        }
	}

  	CLEAR_MASK(SMECCS,HOSTWA);  // Host write not allow

	_nop_();

	GPCRH0 = ALT;

    main();
}

//----------------------------------------------------------------------------
// The function of Scratch rom
//----------------------------------------------------------------------------
void RamProgram(BYTE useport)
{ 
    SetLPCClockFreeRun();
	RamCodePort = useport;
	DisableAllInterrupt();

	Tmp_XPntr = 0x700;
    
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt
        #endif
    Tmp_code_pointer = (void *)HSPI_CmdRamCode;
    #else
	Tmp_code_pointer = (void *)LPC_RamCode;
    #endif
	
   	for(ITempB01=0;ITempB01<255;ITempB01++)
   	{
		*Tmp_XPntr = *Tmp_code_pointer;
      	Tmp_XPntr++;
   		Tmp_code_pointer++;
   	}
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    
	RamCode();
}


//----------------------------------------------------------------------------
// SPI read & write example
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// The example of SPI protect all
//----------------------------------------------------------------------------
void OEM_SPIProtectAll(void)
{
	Do_SPI_Write_Status(SPIStatus_ProtectAll);
	Do_SPI_Write_Disable();
}

void OEM_SPIUnlockAll(void)
{
	Do_SPI_Write_Status(SPIStatus_UnlockAll);
	Do_SPI_Write_Enable();    
}    
//----------------------------------------------------------------------------
// The example of writing external ram 0x200 ~ 0x2FF to SPI ROM 0x010000 ~ 0x0100FF
//----------------------------------------------------------------------------
void OEM_Write_SPI_256Bytes(void)
{
	Do_SPI_Write_Status(SPIStatus_UnlockAll);
	Do_SPI_Write_Enable();
	Do_SPI_Erase(SPICmd_Erase4KByte,0x01,0x00,0x00);
	Do_SPI_Write_Enable();
	Do_SPI_Write_256Bytes(&SPIBuffer,0x01,0x00,0x00);
	Do_SPI_Write_Disable();
}

//----------------------------------------------------------------------------
// The example of reading SPI ROM 0x010000 ~ 0x0100FF to external ram 0x200 ~ 0x2FF
//----------------------------------------------------------------------------
void OEM_Read_SPI_256Bytes(void)
{
	Do_SPI_Read_256Bytes(&SPIBuffer,0x01,0x00,0x00);
}

//-----------------------------------------------------------------------------
// The example of reading SPI ID
//		Note : SPI ID always save to array SPIIDBuf[]
//-----------------------------------------------------------------------------
void OEM_SPI_Read_ID(void)
{
	Do_SPI_Read_ID();
}

//----------------------------------------------------------------------------
// The example of SPI read status
//----------------------------------------------------------------------------
BYTE OEM_SPIReadStatus(void)
{
	Do_SPI_Read_Status();
	return(SPIReadStatus);
}