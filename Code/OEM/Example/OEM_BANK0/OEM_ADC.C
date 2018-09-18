/*-----------------------------------------------------------------------------
 * TITLE: OEM_ADC.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// The Table of scaning ADC
//----------------------------------------------------------------------------
#ifdef ScanDyChannel1
const sADCDyinput code asADCDyInput1[]=
{
	#ifdef DyCh0
	{   DyCh0,  &ADCAvg0 	},
	#endif
	
	#ifdef DyCh1
	{   DyCh1,  &ADCAvg1 	},
	#endif

	#ifdef DyCh2
	{   DyCh2,  &ADCAvg2 	}
	#endif	
};
#endif

#ifdef ScanDyChannel2
const sADCDyinput code asADCDyInput2[]=
{
	#ifdef DyCh3
	{   DyCh3,  &ADCAvg3 	},
	#endif
	
	#ifdef DyCh4
	{   DyCh4,  &ADCAvg4 	},
	#endif

	#ifdef DyCh5
	{   DyCh5,  &ADCAvg5 	}
	#endif	
};
#endif

//----------------------------------------------------------------------------
// The function of disabling ADC channel
//----------------------------------------------------------------------------
void DisableADCChannel(void)
{
	VCH0CTL=0x1F;
	VCH1CTL=0x1F;
	VCH2CTL=0x1F;
	VCH3CTL=0x1F;
	DisableADCModule();
}

//----------------------------------------------------------------------------
// The function of Enabling ADC channel
//----------------------------------------------------------------------------
void EnableADCChannel(void)
{
    Init_ADC();
}

void EnableADCFixChannel(void)
{
#ifdef FixCh0
	VCH0CTL=FixCh0;
#endif

#ifdef FixCh1
	VCH1CTL=FixCh1;
#endif
}

void EnableADCDyChannel(void)
{
#ifdef ScanDyChannel1
	VCH2CTL=asADCDyInput1[ADCDyTable1Index].channelsel;
#endif

#ifdef ScanDyChannel2
	VCH3CTL=asADCDyInput2[ADCDyTable2Index].channelsel;
#endif
}

//----------------------------------------------------------------------------
// The function of scaning ADC channel
//----------------------------------------------------------------------------
void ScanADCFixChannel(void)
{
#ifdef FixCh0
    if(IS_MASK_SET(VCH0CTL, DATVAL))
    {
        VCH0CTL |= 0x80;        // write clear data vaild flag
        Fix_ADCAvg0 = (VCH0DATM*0xFF)+VCH0DATL;
    }
#endif	

#ifdef FixCh1
    if(IS_MASK_SET(VCH1CTL, DATVAL))
    {
        VCH1CTL |= 0x80;        // write clear data vaild flag
        Fix_ADCAvg1 = (VCH1DATM*0xFF)+VCH1DATL;
    }
#endif	
}

void ScanADCDyChannel1(void)
{
#ifdef ScanDyChannel1
    if(IS_MASK_SET(VCH2CTL, DATVAL))
    {
        *asADCDyInput1[ADCDyTable1Index].var = VCH2DATM;
        *(asADCDyInput1[ADCDyTable1Index].var+1) = VCH2DATL;
        ADCDyTable1Index++;
        if(ADCDyTable1Index >= (sizeof(asADCDyInput1)/sizeof(sADCDyinput)))
        {
            ADCDyTable1Index = 0x00;
        }
        
        VCH2CTL = asADCDyInput1[ADCDyTable1Index].channelsel;  // write clear data vaild flag
    }
#endif	
}

void ScanADCDyChannel2(void)
{
#ifdef ScanDyChannel2
    if(IS_MASK_SET(VCH3CTL, DATVAL))
    {
        *asADCDyInput2[ADCDyTable2Index].var = VCH3DATM;
        *(asADCDyInput2[ADCDyTable2Index].var+1) = VCH3DATL;
        ADCDyTable2Index++;
        if(ADCDyTable2Index >= (sizeof(asADCDyInput2)/sizeof(sADCDyinput)))
        {
            ADCDyTable2Index = 0x00;
        }
        
        VCH3CTL = asADCDyInput2[ADCDyTable2Index].channelsel;  // write clear data vaild flag
    }
#endif	
}

//----------------------------------------------------------------------------
// Disable ADC module
//----------------------------------------------------------------------------
void DisableADCModule(void)
{
	CLEAR_MASK(ADCCFG, ADCEN);
}

//----------------------------------------------------------------------------
// Enable ADC module
//----------------------------------------------------------------------------
void EnableADCModule(void)
{
	SET_MASK(ADCCFG, ADCEN);
}

//----------------------------------------------------------------------------
// Init ADC module
//----------------------------------------------------------------------------
void Init_ADC(void)
{
	ADCDyTable1Index = 0x00;
    ADCDyTable2Index = 0x00;
    EnableADCFixChannel();
    EnableADCDyChannel();
    EnableADCModule();
}