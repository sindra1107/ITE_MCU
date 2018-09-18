/*-----------------------------------------------------------------------------
 * TITLE: CORE_HSPI.C
 *
 * Copyright (c) 2009- , ITE Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Disable HSPI interface pins 
//----------------------------------------------------------------------------
void GPIO_HSPI_INIT(void)
{
	GPCRH3 = INPUT;                 // Set input mode
	GPCRH4 = INPUT;                 // Set input mode
	GPCRH5 = INPUT;                 // Set input mode
	GPCRH6 = INPUT;                 // Set input mode
    SET_MASK(RSTC4,RSPI);           // Reset SPI
}

//----------------------------------------------------------------------------
// Enable HSPI interface
//----------------------------------------------------------------------------
void Enable_HSPI(void)
{
    #ifdef HSPI_DefferingMode
    CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt 
    ISR7 = Int_DeferredSPI;         // W/C interrupt status
    #endif
    
	GPCRH3 = ALT;                   // Set HSPI mode
	GPCRH4 = ALT;                   // Set HSPI mode
	GPCRH5 = ALT;                   // Set HSPI mode
	GPCRH6 = ALT;                   // Set HSPI mode

    #ifdef HSPI_DefferingMode
    HINSTC1 = (ENDPI+ENDEI);        // Host Instruction Control 1 
    #else
    HINSTC1 = 0x00;
    #endif
    
    HSPICTRL3R = 0x10;			    // set bit4 for not SST SPI ROM
								    // clear bit4 for SST SPI ROM or set bit4 for not SST SPI ROM
                           		    // For phoenix bios 
	//FLHCTRL1R = 0x00;			    // Flash Control Register 1
	HCTRL2R = 0x10;				    // Host Control 2 Register

    #ifdef HSPI_DefferingMode
    //ISR7 = Int_DeferredSPI;       // W/C interrupt status
    SET_MASK(IER7,Int_DeferredSPI); // Enable interrupt 
    #endif
}

//----------------------------------------------------------------------------
// Disable HSPI interface
//----------------------------------------------------------------------------
void Disable_HSPI(void)
{
    #ifdef HSPI_DefferingMode
    CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt 
    ISR7 = Int_DeferredSPI;         // W/C interrupt status
    //HCTRL2R = 0x80;
    #endif

    HCTRL2R=0x00;

	GPCRH3 = INPUT;                 // Set input mode
	GPCRH4 = INPUT;                 // Set input mode
	GPCRH5 = INPUT;                 // Set input mode
	GPCRH6 = INPUT;                 // Set input mode
    SET_MASK(RSTC4,RSPI);           // Reset SPI
}

#pragma ot(8, SPEED)
//----------------------------------------------------------------------------
// Instructino is valid
//----------------------------------------------------------------------------
void HSPI_RamCode(void)
{
    if(DSADR2==HSPI_ECCodeSpaceAddr)    // EC code space
    {
        ISR7 = Int_DeferredSPI;         // W/C interrupt status
        HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
        
        HSPI_FPT_timeout = 0x00;

        TR1 = 0;                        // Disable timer 1
	    ET1 = 0;			            // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = T_HSPI_ISRTime>>8;	    // set timer1 counter xx ms 
        TL1 = T_HSPI_ISRTime;	        // set timer1 counter xx ms
        TF1 = 0;			            // clear overflow flag
        TR1 = 1;                        // enable timer1

        while(1)
        {
            if(IS_MASK_SET(ISR7, Int_DeferredSPI))
            {
                ISR7 = Int_DeferredSPI;     // W/C interrupt status
                HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
                            
                TH1 = T_HSPI_ISRTime>>8;    // set timer1 counter xx ms 
                TL1 = T_HSPI_ISRTime;	    // set timer1 counter xx ms
                TF1 = 0; 
                HSPI_FPT_timeout = 0x00;
                continue;
            }

            if(TF1)
            {
                if(++HSPI_FPT_timeout>=35 )    // 3 sec EC auto wake up from ram code.
                { 
				    HSPI_FPT_timeout = 0xFF;
				    break;
                }
                TH1 = T_HSPI_ISRTime>>8;	    // set timer1 counter xx ms 
                TL1 = T_HSPI_ISRTime;		    // set timer1 counter xx ms
                TF1 = 0;			            // clear overflow flag
            }
        }
                
        WinFlashMark = 0x33;
        TR1 = 0;			    // disable timer1
 	    TF1 = 0;			    // clear overflow flag
	    ET1 = 1;			    // Enable timer1 interrupt
 
        #pragma asm
        LJMP    main
        #pragma endasm
    }
    else                                    // Not EC code space
    {
        ISR7 = Int_DeferredSPI;             // W/C interrupt status
        HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction
        SET_MASK(IER7,Int_DeferredSPI);     // Enable HSPI interrupt
    }
}

#pragma ot(8, SPEED)
//----------------------------------------------------------------------------
// Host send idle command to EC
//----------------------------------------------------------------------------
void HSPI_CmdRamCode(void)
{
	RamcodeCmd = 0x00;

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
        #ifdef HSPI_DefferingMode
        if(IS_MASK_SET(ISR7, Int_DeferredSPI))
        {
            ISR7 = Int_DeferredSPI;             // W/C interrupt status
            HINSTC1 = DISSV+DISS+ENDPI+ENDEI;   // Allow instruction 
        }
        #endif
        
  		if(RamCodePort==0x64)
		{
			if( IS_MASK_CLEAR(KBHISR,IBF)) continue;
        	if( IS_MASK_CLEAR(KBHISR,C_D)) 
        	{
                RamcodeCmd = KBHIDIR;
                continue;
        	}
            else
            {
       		    RamcodeCmd = KBHIDIR;
            }
  		}
		else if(RamCodePort==0x66)
		{
        	if ( IS_MASK_CLEAR(PM1STS,P_IBF)) continue;
        	if ( IS_MASK_CLEAR(PM1STS,P_C_D)) 
            {
                RamcodeCmd = PM1DI;
                continue;
            }
            else
            {
        	    RamcodeCmd = PM1DI;
            }
		}		
		else if(RamCodePort==0x6C)
		{
        	if ( IS_MASK_CLEAR(PM2STS,P_IBF)) continue;
        	if ( IS_MASK_CLEAR(PM2STS,P_C_D)) 
        	{
                RamcodeCmd = PM2DI;
                continue;
        	}
            else
            {
        	    RamcodeCmd = PM2DI;
            }
		}	
		
        if ( RamcodeCmd == 0x55)
     	{
     		WinFlashMark = 0x33;
        	break;
  		}
		else if ( RamcodeCmd == 0xAF)
     	{
            //#ifdef HSPI_DefferingMode
            //HCTRL2R = 0x80;	
            HCTRL2R=0x00;
            CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrupt 
            ISR7 =Int_DeferredSPI;  // W/C interrupt status
	        GPCRH3 = INPUT;         // Set input mode
	        GPCRH4 = INPUT;         // Set input mode
	        GPCRH5 = INPUT;         // Set input mode
	        GPCRH6 = INPUT;         // Set input mode
            SET_MASK(RSTC4,RSPI);   // Reset SPI
            //#endif
            
			WDTRST = 1;			// Reset watch dog timer
			WDTEB = 1;			// Enable watch dog
       		while(1);			// Wait for watch dog time-out
        }
	}

	_nop_();

	GPCRH0 = ALT;

    #pragma asm
    EXTRN CODE (main)
    LJMP    main
    #pragma endasm

}

//-----------------------------------------------------------------------------
// Changing PLL frequency function
//-----------------------------------------------------------------------------
void ChangePLLFrequency(BYTE newseting)
{
    if(newseting!=PLLFREQR)
    {
        PLLFREQR = newseting;
        PLLCTRL = 1;
        DisableAllInterrupt();
	    PCON =2 ;             	// enter sleep mode
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();
	    _nop_();	
    }
}

//-----------------------------------------------------------------------------
// Changing SPI flash read mode
//-----------------------------------------------------------------------------
void ChangeSPIFlashReadMode(BYTE Mode)
{
    BYTE restore;
    restore = FLHCTRL1R;
    CLEAR_MASK(restore, SPIFR0+SPIFR1);
    
    switch(Mode)
    {
        case SPIReadMode_0:
            break;
            
        case SPIReadMode_1:
            SET_MASK(restore, SPIFR0);
            break;  
            
        case SPIReadMode_2:
            SET_MASK(restore, SPIFR1);
            break;
            
        case SPIReadMode_3:
            SET_MASK(restore, SPIFR0+SPIFR1);
            break;
            
        default:
            break;
    }
    FLHCTRL1R = restore;
}

//-----------------------------------------------------------------------------
// Changing HSPI requestmode
//-----------------------------------------------------------------------------
void ChangeHSRSMode(BYTE Mode)
{
    BYTE restore;

    restore=0x00;
    
    switch(Mode)
    {
        case HSPI_RequestSelection_0:
            break;
            
        case HSPI_RequestSelection_1:
            SET_MASK(restore, BIT3);
            break;  
            
        case HSPI_RequestSelection_2:
            SET_MASK(restore, BIT4);
            break;
            
        case HSPI_RequestSelection_3:
            SET_MASK(restore, BIT3+BIT4);
            break;
            
        default:
            break;
    }
    
    HSPICTRL2R = restore+BIT2;
}