/*-----------------------------------------------------------------------------
 * TITLE: OEM_CIR.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

#if CIRFuncSupport
#define CIRCompareOffset	7

const BYTE code RC6PowerKey[]={	0x95,0x55,0xA5,0xF5 }; 	// RC6 power key

//----------------------------------------------------------------------------
// The function of CIR wake up system 
//----------------------------------------------------------------------------
void Hook_CIRWakeUp(void)
{
    BYTE cirdata;
    if(SystemIsS3 || SystemIsS4 || SystemIsS5)
	{
		CLEAR_MASK(C0SCK, SCKS);  		// CIR unselect slow clock
		for(ITempB01=0x00;ITempB01<CIRCompareOffset;ITempB01++)
		{
            cirdata=C0DR;
			_nop_();
		}

		for(ITempB01=0x00;ITempB01<sizeof(RC6PowerKey);ITempB01++)
		{
			cirdata=C0DR;
			if(cirdata != RC6PowerKey[ITempB01])
			{
				ClearCIR();
				return;
			}
		}
	
		if(SystemIsS3)
		{
			CIRS3WakeUp();
		}
		else
		{
			CIRS4S5WakeUp();
		}
	}
}

//----------------------------------------------------------------------------
// The function of CIR S4/S5 wake up system 
//----------------------------------------------------------------------------
void CIRS4S5WakeUp(void)
{
	Oem_TriggerS5S0();
	SET_MASK(C0MSTCR, CIR_RESET);		//CIR Reset
}

//----------------------------------------------------------------------------
// The function of CIR S3 wake up system 
//----------------------------------------------------------------------------
void CIRS3WakeUp(void)
{
	Oem_TriggerS3S0();
	SET_MASK(C0MSTCR, CIR_RESET);		//CIR Reset
}
#endif

//----------------------------------------------------------------------------
// The function of CIR Initialization
//----------------------------------------------------------------------------
void Init_CIR(void)
{ 	
	GPCRC0 = 0X00;				// CIR RX (8512 only) Set GPIO to ALT function.
	CLEAR_MASK(C0RCR, CIR_RXEN);    // RX Disable     		
	C0BDHR = 0x00;				// BaudRate 
	C0BDLR = 0x33;
	C0MSTCR = 0x08;    			// FIFO Threshold = 17 Bytes
	C0CFR = 0x0B;				// Carrier Freqency = 38KHz 	

	bConfirmCirRIM();  			// Write receiver enter an inactive mode
	bClearCirFIFO();		  	// Clear FIFO

	C0IER = 0x82;				// CIR Interrupt Enable
  								// CIR receive available interrupt   
	SET_MASK(IELMR1, Int_CIR);  // CIR Interrupt must use Edge-Trig
	SET_MASK(IER1, Int_CIR);    // Enable INT15 CIR Interrupt
    ISR1 = Int_CIR;             // Clear INT15 pending Status
	SET_MASK(C0RCR, CIR_RXEN);  // RX enable         
}

//----------------------------------------------------------------------------
// The function of CIR module reset
//----------------------------------------------------------------------------
void Reset_CIR(void)
{
	SET_MASK(RSTC2, RCIR);		// Reset CIR module
	CLEAR_MASK(IER1, Int_CIR);  // Disable INT15 CIR Interrupt
    ISR1 = Int_CIR;             // Clear INT15 pending Status
}

//----------------------------------------------------------------------------
// The function of clearing CIR FIFO
//----------------------------------------------------------------------------
void bClearCirFIFO(void)
{
	SET_MASK(C0MSTCR, CIR_FIFOCLR);			    // Write 1 for Clearing FIFO data
	_nop_();
	while(IS_MASK_SET(C0MSTCR, CIR_FIFOCLR))	// Wait FIFO Clear Done
	{
		;					
	}
}

//----------------------------------------------------------------------------
// The function of confirming CIR receiver inactive mode
//----------------------------------------------------------------------------
void bConfirmCirRIM(void)
{
	SET_MASK(C0RCR, CIR_RXACT);		        // Write 1 for clearing Receive Active
	_nop_();
	while(IS_MASK_SET(C0RCR, CIR_RXACT))    // Wait CIR receiver enter an inactive mode
	{
		;					
	}
}

//----------------------------------------------------------------------------
// The function of clearing CIR
//----------------------------------------------------------------------------
void ClearCIR(void) 
{
	CLEAR_MASK(C0RCR, CIR_RXEN);    // RX Disable   
	bConfirmCirRIM();  			// Write receiver enter an inactive mode
 	bClearCirFIFO();		  	// Clear FIFO
 	SET_MASK(C0RCR, CIR_RXEN);  // RX enable 
} 

//----------------------------------------------------------------------------
// The function of CIR Interrupt service routine
//----------------------------------------------------------------------------
void service_cir(void)
{
#if CIRFuncSupport
	Hook_CIRWakeUp();
#endif
}