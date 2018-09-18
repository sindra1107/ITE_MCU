/*----------------------------------------------------------------------------
 * Filename: OEM_Power.C  For Chipset: ITE.IT85XX
 *
 * Function: Power sequnce control function example
 *
 * Author  : Dino
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

void PF_DNBSWON_ON(void)
{
	DNBSWON_ON();
} 

void PF_DNBSWON_OFF(void)
{
	DNBSWON_OFF();
}

void PF_RSMRST_ON(void)
{
	RSMRST_ON();
}

void PF_RSMRST_OFF(void)
{
	RSMRST_OFF();
}

void PF_RVCC_ON(void)
{
    RSMRST_ON();
    Delay1MS(5);        // Delay 5ms for rsmrst
    S5_ON();            // Turn on S5 power
    Delay1MS(20);       // Delay 20ms for rsmrst
        
    #ifdef HSPI
    Enable_HSPI();      // Enable HSPI interface if HSPI is supported
    #endif
        
    Delay1MS(5);        // Delay 5ms for rsmrst
    RSMRST_OFF(); 
}

void PF_RVCC_OFF(void)
{
    RSMRST_ON();
    Delay1MS(20);       // Delay 20ms for rsmrst
    S5_OFF();
}

void PF_SUSON_ON(void)
{
	SUSON_ON();
}

void PF_SUSON_OFF(void)
{
	SUSON_OFF();
}

void PF_MAINON_ON(void)
{
	MAINON_ON();
}

void PF_MAINON_OFF(void)
{
	MAINON_OFF();
}

void PF_VRON_ON(void)
{
	VRON_ON();
}

void PF_VRON_OFF(void)
{
	VRON_OFF();
}

void PF_ECPWROK_ON(void)
{
	ECPWROK_ON();
}

void PF_ECPWROK_OFF(void)
{
	ECPWROK_OFF();
}

BYTE PF_Read_SLPS3(void)
{
	if(Read_SLPS3())
	{
		SET_MASK(POWER_FLAG2,SLP_S3_ON);
		return(1);
	}
	return(0);
}

BYTE PF_Read_SLPS4(void)
{
	if(Read_SLPS4())
	{
        SET_MASK(POWER_FLAG2,SLP_S4_ON);
		return(1);
	}
	return(0);
}

BYTE PF_Read_SLPS5(void)
{
	if(Read_SLPS5())
	{
		SET_MASK(POWER_FLAG2,SLP_S5_ON);
		return(1);
	}
	return(0);
}

BYTE PF_Read_SLPA(void)
{
	if(Read_SLPA())
	{
		return(1);
	}
	return(0);
}

//BYTE PF_Read_SUSACK(void)
//{
//    if(Read_SUSACK())
//    {
//		return(1);
//    }
//    return(0);
//}

BYTE PF_Read_SLP_SUS(void)
{
    if(Read_SLP_SUS())
    {
        return(1);
    }
    return(0);
}

BYTE PF_Read_HWPG(void)
{
	if(Read_HWPG())
	{
		HWPG_TIMER = 0x00;
		return(1);
	}
	else
	{
		HWPG_TIMER++;
   		if(HWPG_TIMER>T_HWPG)
   		{
			Oem_TriggerS0S5(SC_HWPGSx_S0Off);
			HWPG_TIMER = 0x00;
		}
		return(0);
	}
}

void PF_LOMDIS_ON(void)
{

}

void PF_LOMDIS_OFF(void)
{

}

void PF_LANPOWER_ON(void)
{

}

void PF_LANPOWER_OFF(void)
{

}

void PF_VOLMUTE_ON(void)
{
	VOLMUTE_ON();
}

void PF_VOLMUTE_OFF(void)
{
	VOLMUTE_OFF();
}

void PF_USB_ON(void)
{
    USB_On_ON();
}

void PF_USB_OFF(void)
{
    USB_On_OFF();
}

void PF_WLan_Power_ON(void)
{
    WLAN_PWR_EN_ON();
}

void PF_WLan_Power_OFF(void)
{
    WLAN_PWR_EN_OFF();
}

void PF_EC_ODD_EN_ON(void)
{
    EC_ODD_EN_ON();
}

void PF_EC_ODD_EN_OFF(void)
{
    EC_ODD_EN_OFF();
}

void PF_Disable_HSPI(void)
{
    #ifdef HSPI
    Disable_HSPI();  
    #endif	
}

//-------------------------------------------------------------------------------------
//  Do S5 -> S0 power sequnce
//-------------------------------------------------------------------------------------
const sPowerSEQ code asPowerSEQS5S0[]=  
{
	{ 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ PF_DNBSWON_OFF, 		0,      0,  },
	{ PF_RVCC_ON, 			0,		0,  },
	{ Hook_A20ON, 		    0,		0,  },
	{ Hook_KBRSTOFF, 		0,		0,  },
	{ Hook_SMIOFF, 		    0,		0,  },
	{ Hook_SCIOFF, 		    0,		0,  },
	{ PF_DNBSWON_ON, 		120,    0,  },
    { PF_Read_SLPA, 		0,		1,  },
	{ PF_Read_SLPS5, 		0,		1,  },
    { PF_Read_SLPS4, 		0,		1,  },
	{ PF_Read_SLPS3, 		0,		1,  },
	{ PF_DNBSWON_OFF, 		0,		0,  },	
	{ PF_SUSON_ON, 			0,		0,  },
	{ PF_USB_ON, 		    5,		0,  },
	{ PF_VOLMUTE_ON,		0,		0,  },
	{ PF_MAINON_ON, 		10,		0,  },
	{ PF_WLan_Power_ON,     0,		0,  },
	{ PF_EC_ODD_EN_ON,      0,		0,  }, 
	{ PF_Read_HWPG, 		10,     1,  },
    { InitSio, 				10,     0,  },
	{ PF_VRON_ON, 			100, 	0,  },	
	{ PF_ECPWROK_ON, 		0,      0,  },
	{ S5_S0Variable, 	    0,		0,  },	// always in the end of tabel
}; 

//-------------------------------------------------------------------------------------
//  Do S0 -> S5 power sequnce
//-------------------------------------------------------------------------------------
const sPowerSEQ code asPowerSEQS0S5[]=  
{
	{ 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ PF_DNBSWON_OFF, 	    0,		0,  },	
	{ PF_Disable_HSPI,      0,      0,  },
    { PF_ECPWROK_OFF, 	    10,		0,  },	  
	{ PF_VRON_OFF, 	        10,		0,  },	
    { PF_EC_ODD_EN_OFF,     0,		0,  },
    { PF_WLan_Power_OFF,    0,		0,  },	
    { PF_MAINON_OFF, 	    0,		0,  },	  
    { PF_USB_OFF, 	        0,		0,  },	 
	{ Hook_KBRSTON, 	    0,		0,  },	
    { Hook_A20OFF,          0,		0,  },
	{ Hook_SMION, 		    0,		0,  },
	{ Hook_SCION, 		    0,		0,  },
    { PF_SUSON_OFF, 	    10,		0,  },	
    { PF_RVCC_OFF, 	        0,		0,  },	  
	//{ PF_DNBSWON_ON, 	    0,		0,  },	
	{ S0_S5Variable, 	    0,		0,  },  // always in the end of tabel	
}; 

//-------------------------------------------------------------------------------------
//  Do S4 -> S0 power sequnce
//-------------------------------------------------------------------------------------
const sPowerSEQ code asPowerSEQS4S0[]= 
{
	{ 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ PF_DNBSWON_OFF, 		0,      0,  },
	{ PF_RVCC_ON, 			0,		0,  },      
	{ Hook_A20ON, 		    0,		0,  },
	{ Hook_KBRSTOFF, 		0,		0,  },
	{ Hook_SMIOFF, 		    0,		0,  },
	{ Hook_SCIOFF, 		    0,		0,  },
	{ PF_DNBSWON_ON, 		120,    0,  },
    { PF_Read_SLPA, 		0,		1,  },
	{ PF_Read_SLPS5, 		0,		1,  },
    { PF_Read_SLPS4, 		0,		1,  },
	{ PF_Read_SLPS3, 		0,		1,  },
	{ PF_DNBSWON_OFF, 		0,		0,  },	
	{ PF_SUSON_ON, 			0,		0,  },
	{ PF_USB_ON, 		    5,		0,  },
	{ PF_VOLMUTE_ON,		0,		0,  },
	{ PF_MAINON_ON, 		10,		0,  },
	{ PF_WLan_Power_ON,     0,		0,  },
	{ PF_EC_ODD_EN_ON,      0,		0,  },
	{ PF_Read_HWPG, 		10,	    1,  },
    { InitSio, 				10,     0,  },
	{ PF_VRON_ON, 			100,	0,  },	
	{ PF_ECPWROK_ON, 		0,      0,  },
    { S4_S0Variable, 	    0,		0	},	// always in the end of tabel
}; 

//-------------------------------------------------------------------------------------
//  Do S0 -> S4 power sequnce
//-------------------------------------------------------------------------------------
const sPowerSEQ code asPowerSEQS0S4[]=  
{
	{ 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ PF_DNBSWON_OFF, 	    0,		0,  },	
    { PF_Disable_HSPI,      0,      0,  },
    { PF_ECPWROK_OFF, 	    10,		0,  },	  
	{ PF_VRON_OFF, 	        10,		0,  },	
    { PF_EC_ODD_EN_OFF,     0,		0,  },
    { PF_WLan_Power_OFF,    0,		0,  },	
    { PF_MAINON_OFF, 	    0,		0,  },	  
    { PF_USB_OFF, 	        0,		0,  },	 
	{ Hook_KBRSTON, 	    0,		0,  },	
    { Hook_A20OFF,          0,		0,  },
	{ Hook_SMION, 		    0,		0,  },
	{ Hook_SCION, 		    0,		0,  },
    { PF_SUSON_OFF, 	    10,		0,  },	
    { PF_RVCC_OFF, 	        0,		0,  },	  
	//{ PF_DNBSWON_ON, 	    0,		0,  },	
    { S0_S4Variable, 	    0,		0	},  // always in the end of tabel	
}; 

//-------------------------------------------------------------------------------------
//  Do S3 -> S0 power sequnce
//-------------------------------------------------------------------------------------
const sPowerSEQ code asPowerSEQS3S0[]= 
{
	{ 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ Hook_A20ON, 		    0,		0,  },
	{ Hook_KBRSTOFF, 		0,		0,  },
	{ PF_VOLMUTE_ON, 		0,		0,  },
	{ Hook_SMIOFF, 		    0,		0,  },
	{ Hook_SCIOFF, 		    0,		0,  },
    { PF_DNBSWON_OFF, 		0,		0,  },	
    { PF_USB_ON, 		    5,		0,  },
	{ PF_MAINON_ON, 		10,		0,  },
	{ PF_WLan_Power_ON,     0,		0,  },
	{ PF_EC_ODD_EN_ON,      0,		0,  },
	{ PF_Read_HWPG, 		10,	    1,  },
    { InitSio, 				10,     0,  },
	{ PF_VRON_ON, 			100,	0,  },	
	{ PF_ECPWROK_ON, 		0,      0,  },
	{ S3_S0Variable, 	    0,		0,  },	// always in the end of tabel
}; 

//-------------------------------------------------------------------------------------
//  Do S0 -> S3 power sequnce
//-------------------------------------------------------------------------------------
const sPowerSEQ code asPowerSEQS0S3[]=  
{
	{ 0x0000, 				0,		0,  },	// Dummy step always in the top of tabel
	{ PF_DNBSWON_OFF, 	    0,		0,  },	
    { PF_ECPWROK_OFF, 	    10,		0,  },	
    { PF_VRON_OFF, 	        10,		0,  },	
    { PF_WLan_Power_OFF,    0,		0,  },
	{ PF_EC_ODD_EN_OFF,     0,		0,  },
    { PF_MAINON_OFF, 	    0,		0,  },
    //{ PF_USB_OFF, 		    0,		0,  },      
	{ Hook_KBRSTON, 	    0,		0,  },	
    { Hook_A20OFF,          0,		0,  },
	//{ Hook_SMION, 		    0,		0,  },
	//{ Hook_SCION, 		    0,		0,  },
	{ S0_S3Variable, 	    0,		0,  },  // always in the end of tabel	
}; 

//-----------------------------------------------------------------------------
//  The OEM variable of Sx -> S0
//-----------------------------------------------------------------------------
void OEM_SX_S0CommVar(void)
{
    CheckPowerStateIndex = 0x00;
}

//-----------------------------------------------------------------------------
//  The variable of Sx -> S0
//-----------------------------------------------------------------------------
void SX_S0CommVar(void)
{
	SysPowState=SYSTEM_S0;
	InitThermalChip();
	InitThermalTable1();
    InitThermalTable2();
	ResetSCIEvent();
#if CIRFuncSupport
	Reset_CIR();
#endif    
    OEM_SX_S0CommVar();
    InitSMBus();
}

//-----------------------------------------------------------------------------
// The variable of S5 -> S0
//-----------------------------------------------------------------------------
void S5_S0Variable(void)
{
	SX_S0CommVar();
}

//-----------------------------------------------------------------------------
// The variable of S4 -> S0
//-----------------------------------------------------------------------------
void S4_S0Variable(void)
{
    SX_S0CommVar();

}

//-----------------------------------------------------------------------------
// The variable of S3 -> S0
//-----------------------------------------------------------------------------
void S3_S0Variable(void)
{
	SX_S0CommVar();

}

//-----------------------------------------------------------------------------
//  The OEM variable of S0 -> Sx
//-----------------------------------------------------------------------------
void OEM_S0_SXCommVar(void)
{
    CheckPowerStateIndex = 0x00;
    CLEAR_MASK(SYS_MISC1,ACPI_OS);
}

//-----------------------------------------------------------------------------
//  The variable of S0 -> Sx
//-----------------------------------------------------------------------------
void S0_SXCommVar(void)
{
#ifdef PECI_Support
    PECI_ClearPSTVariables();
#endif
    
#if TouchPad_only
    PowerOffClearTPPendingData();
#endif    
	CLEAR_MASK(KBHISR,SYSF);
    Ccb42_SYS_FLAG=0;
	Hook_KBRSTON();
	Hook_A20OFF();
#if CIRFuncSupport	
	Init_CIR();
#endif
	InitSMBus();

    OEM_S0_SXCommVar();
}

//-----------------------------------------------------------------------------
//  The variable of S0 -> S5
//-----------------------------------------------------------------------------
void S0_S5Variable(void)
{
    SysPowState=SYSTEM_S5;
    S0_SXCommVar();

}

//-----------------------------------------------------------------------------
//  The variable of S0 -> S4
//-----------------------------------------------------------------------------
void S0_S4Variable(void)
{
    SysPowState=SYSTEM_S4;
    S0_SXCommVar();
    
}

//-----------------------------------------------------------------------------
// The variable of S0 -> S3
//-----------------------------------------------------------------------------
void S0_S3Variable(void)
{
	SysPowState=SYSTEM_S3;
	S0_SXCommVar();
    
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS3S0(void)
{
    if(SystemIsS0)
    {
        return;
    }
    
	SysPowState=SYSTEM_S3_S0;
	PWSeqStep = 1;
	PowSeqDelay = 0x00;
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS4S0(void)
{
    if(SystemIsS0)
    {
        return;
    }
    
    SysPowState=SYSTEM_S4_S0;
    PWSeqStep = 1;
    PowSeqDelay = 0x00;
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS5S0(void)
{
    if(SystemIsS0)
    {
        return;
    }
    
    SysPowState=SYSTEM_S5_S0;
	PWSeqStep = 1;
	PowSeqDelay = 0x00;
}

//----------------------------------------------------------------------------
// S5 to S0 sequnce
//----------------------------------------------------------------------------
void Oem_S5S0Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        } 
    }

	while(PWSeqStep<(sizeof(asPowerSEQS5S0)/sizeof(sPowerSEQ)))
	{	
		if(asPowerSEQS5S0[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS5S0[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS5S0[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS5S0[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS5S0[PWSeqStep].delay;
			    PWSeqStep++;
			}  
			break;
		}	
	}
}

//----------------------------------------------------------------------------
// S4 to S0 sequnce
//----------------------------------------------------------------------------
void Oem_S4S0Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        }
    }

    while(PWSeqStep<(sizeof(asPowerSEQS4S0)/sizeof(sPowerSEQ)))
    {	
        if(asPowerSEQS4S0[PWSeqStep].checkstatus==0x00)	// Do function
        {
            (asPowerSEQS4S0[PWSeqStep].func)();
            PowSeqDelay = asPowerSEQS4S0[PWSeqStep].delay;
            PWSeqStep++;
            if(PowSeqDelay!=0x00)
            {
                break;
            }
        }
        else											// Check input status pin
        {
            if((asPowerSEQS4S0[PWSeqStep].func)())
            {
                PowSeqDelay = asPowerSEQS4S0[PWSeqStep].delay;
                PWSeqStep++;
            }
            break;
        }	
    }
}

//----------------------------------------------------------------------------
// S3 to S0 sequnce
//----------------------------------------------------------------------------
void Oem_S3S0Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        }
    }

	while(PWSeqStep<(sizeof(asPowerSEQS3S0)/sizeof(sPowerSEQ)))
	{	
		if(asPowerSEQS3S0[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS3S0[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS3S0[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS3S0[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS3S0[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}	
	} 
}

//-----------------------------------------------------------------------------
// Check SUSB and SUSC
//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
//The function of checking slp s3
//------------------------------------------------------------------------------
void CheckSLP_S3(void)
{
	CLEAR_MASK(POWER_FLAG2, SLP_S3_ON);
	if(Read_SLPS3())
    {
        SET_MASK(POWER_FLAG2, SLP_S3_ON);
    }   
}

//------------------------------------------------------------------------------
//The function of checking slp s4
//------------------------------------------------------------------------------
void CheckSLP_S4(void)
{
	CLEAR_MASK(POWER_FLAG2, SLP_S4_ON);
	if(Read_SLPS4())
    {
        SET_MASK(POWER_FLAG2, SLP_S4_ON);
    } 
}

//------------------------------------------------------------------------------
//The function of checking slp s5
//------------------------------------------------------------------------------
void CheckSLP_S5(void)
{
    CLEAR_MASK(POWER_FLAG2, SLP_S5_ON);
	if(Read_SLPS5())
    {
        SET_MASK(POWER_FLAG2, SLP_S5_ON);
    }  
}

void DoPowerStatus(void)
{
    BYTE presentstatus;

    presentstatus = (POWER_FLAG2&(SLP_S3_ON+SLP_S4_ON+SLP_S5_ON));
    if(PowerStatusBK != presentstatus)      // To make sure all SLP is checked.
    {
        PowerStatusBK = presentstatus;
        return;
    }
    
	switch(POWER_FLAG2 & (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON)) 
	{
		case 0: 	                        // goto S5
            switch (SysPowState) 
            {
                case SYSTEM_S0 :
                    Oem_TriggerS0S5(SC_S0SLPOff);
                    break;
                    
                case SYSTEM_S4 :
                    break;
                    
                case SYSTEM_S3 :
                    Oem_TriggerS0S5(SC_S3S4SLPOff);
                    break;           
            }
           	break;

		case (SLP_S3_ON+SLP_S4_ON+SLP_S5_ON): // goto S0
            switch (SysPowState) 
            {
                case SYSTEM_S3 :
                    Oem_TriggerS3S0();
                    break;
                    
                case SYSTEM_S4 :
                    Oem_TriggerS4S0();
                    break;
                    
                case SYSTEM_S5 :			             
                    Oem_TriggerS5S0();
                     break;
            }
            break;            

        case (SLP_S4_ON+SLP_S5_ON):             // goto S3
            switch (SysPowState) 
            {
                case SYSTEM_S0 :
                    Oem_TriggerS0S3(0x30);
                    break;
            }
            break;

        case SLP_S5_ON:                         // goto S4
            switch (SysPowState) 
            {
                case SYSTEM_S0 :
                    Oem_TriggerS0S4(0x40);
                    break;
            }
            break;
	}
}

//------------------------------------------------------------------------------
void CheckPowerState(void)
{
    switch(CheckPowerStateIndex)
    {
        case 0:
            CheckSLP_S3();          // Check SLP_S3#(or SUS_B#)
            CheckPowerStateIndex ++;
            break;

        case 1:
            CheckSLP_S4();          // Check SLP_S4#
            CheckPowerStateIndex ++;
            break;
            
        case 2:
            CheckSLP_S5();          // Check SLP_S5#(or SUS_C#)
            CheckPowerStateIndex ++;
            break;

        case 3:
            DoPowerStatus();
            CheckPowerStateIndex = 0x00;
            break;

        default:
            CheckPowerStateIndex = 0x00;
            break;
    }
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S3(BYTE causecode)
{
    if(SystemIsS3)
    {
        return;
    }
    
	ShutDnCause = causecode;		// setup shutdown case
	SysPowState=SYSTEM_S0_S3;
	PWSeqStep = 1;
	PowSeqDelay = 0x00;
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S4(BYTE causecode)
{
    if(SystemIsS4)
    {
        return;
    }
    
    ShutDnCause = causecode;		// setup shutdown case
    SysPowState=SYSTEM_S0_S4;
    PWSeqStep = 1;
    PowSeqDelay = 0x00;
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Oem_TriggerS0S5(BYTE causecode)
{
    if(SystemIsS5)
    {
        return;
    }
    
	ShutDnCause = causecode;		// setup shutdown case 
    SysPowState=SYSTEM_S0_S5;
	PWSeqStep = 1;
	PowSeqDelay = 0x00;
}

//-----------------------------------------------------------------------------
// process POWER OFF sequence
// entry: 	1¡Bpower shutdown case
//			2¡BS5 off or not
// Shutdown cause:
//	1:	0x8A command of 66 port
// 	2:	0x8B command of 66 port
//	3:	4secs Overrided
// 	4:	HWPG low
//	5:	0x8C command of 66 port
// 	6:	0x8D command of 66 port
//	7:	temperature to high
// 	8:
//	9:	Init. thermal chip fail
// 	10:	Check SLP // S0 -> S4
//	11:	Check SLP // S3 -> S5
// 	12:	Check SLP // S0 -> S5

//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// S0 to S3 sequnce
//----------------------------------------------------------------------------
void Oem_S0S3Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        }
    }

	while(PWSeqStep<(sizeof(asPowerSEQS0S3)/sizeof(sPowerSEQ)))
	{	
		if(asPowerSEQS0S3[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS0S3[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS0S3[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS0S3[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS0S3[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}	
	}           
}


//----------------------------------------------------------------------------
// S0 to S4 sequnce
//----------------------------------------------------------------------------
void Oem_S0S4Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        }
    }

    while(PWSeqStep<(sizeof(asPowerSEQS0S4)/sizeof(sPowerSEQ)))
    {	
        if(asPowerSEQS0S4[PWSeqStep].checkstatus==0x00)	// Do function
        {
            (asPowerSEQS0S4[PWSeqStep].func)();
            PowSeqDelay = asPowerSEQS0S4[PWSeqStep].delay;
            PWSeqStep++;
            if(PowSeqDelay!=0x00)
            {
                break;
            }
        }
        else											// Check input status pin
        {
            if((asPowerSEQS0S4[PWSeqStep].func)())
            {
                PowSeqDelay = asPowerSEQS0S4[PWSeqStep].delay;
                PWSeqStep++;
            }
            break;
        }	
    }       
}

//-----------------------------------------------------------------
// S0 to S5 sequnce
//-----------------------------------------------------------------
void Oem_S0S5Sequence(void)
{
    if ( PowSeqDelay != 0x00 )
    {
        PowSeqDelay--; 				//1m Sec count base
        if ( PowSeqDelay != 0x00 )
        {
            return;
        }
    }

	while(PWSeqStep<(sizeof(asPowerSEQS0S5)/sizeof(sPowerSEQ)))
	{	
		if(asPowerSEQS0S5[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS0S5[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS0S5[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS0S5[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS0S5[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}	
	}  
}

/* ----------------------------------------------------------------------------
 * FUNCTION: check Enter Deep Sleep mode
 *      Timer base : 500 ms
 * ------------------------------------------------------------------------- */
BYTE CheckEnterDeepSleep(void)
{
	BYTE resault;
	resault = 0x00;
    
    if(SystemIsS0)		                        // if system in S0
        resault = 0x01;	
    if(SystemIsS3)		                        // if system in S3
        resault = 0x01;	
    if(IS_MASK_SET(POWER_FLAG1,adapter_in))		// AC power exist
        resault = 0x01;	
    if(IS_MASK_SET(POWER_FLAG1,wait_PSW_off))	// power switch pressed
        resault = 0x01;	

	if(resault == 0x00)
	{
		if(DeepSleepCunt<10)        // Delay 500 ms for EC deep sleep mode
		{
			DeepSleepCunt++;
			resault = 0x02;
		}
		else
		{
			resault = 0x00;
			DeepSleepCunt = 0x00;
		}
	}
    else
    {
        DeepSleepCunt = 0x00;
    }

	switch(resault)
	{
		case 0:
			return(1);
			break;

		case 1:
			DeepSleepCunt=0x00;
			return(0);
			break;

		case 2:
			return(0);
			break;
	}
    return(0);
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Enter Deep Sleep mode
 * ------------------------------------------------------------------------- */
void EnterDeepSleep(void)
{
	IER0=0x00;				
	IER1=0x00;
	IER2=0x00;
	IER3=0x00;
	IER4=0x00;

	DisableAllInterrupt();

							// Disable module
	DisableADCChannel();	// Disable ADC
	DACPWRDN=0x3F;			// Disable DAC		

	KSOL = 0xFF;
	KSOH1 = 0xFF;
	KSOH2 = 0xFF;
	
	//*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************
	GPCRD0 = ALT;			// SUSB to alternate pin	
	GPCRD1 = ALT;			// ACIN to alternate pin
	GPCRE4 = ALT;			// pwrsw to alternate pin
	GPCRE5 = ALT;			// NOVO Button to alternate pin  
	//*************************************************************************

	CGCTRL1R = 0xFF;
	CGCTRL2R = 0xFF;
	CGCTRL3R = 0xFF;

	//*************************************************************************
	// Set WUC interrupt function
	//*************************************************************************
   	WUENR2 = 0x23;      	// Wake-up enable WU25 for pwrsw
                           	// Wake-up enable WU20 for SUSB
                           	// Wake-up enable WU21 for acin

  	WUEMR2 = 0x20;      	// Wake-up Falling-edge WU25 for pwrsw
                            // Wake-up Rising-edge WU20 for SUSB
                            // Wake-up Rising-edge WU21 for ACIN

	WUENR4 = 0x01;         	// Wake-up enable WU40 for NOVO Button
   	WUEMR4 = 0x01;         	// Wake-up Edge WU40 for NOVO	 

   	IER0 |= (Int_WKO20+Int_WKINTAD);    // enable int 1 for  SUSB
   							            // enable int 5 for  NOVO button	
   	IER1 |= Int_WKO25;	    // enable int 14 for  pwrsw
	IER3 |= Int_WKO21;	    // enable int 31 for  ACIN

   	ISR0 = (Int_WKO20+Int_WKINTAD);     // clear int 1 for  SUSB
   							            // clear int 5 for  NOVO button	
   	ISR1 = Int_WKO25;	    // clear int 14 for  pwrsw
	ISR3 = Int_WKO21;	    // clear int 31 for  ACIN
	//*************************************************************************

	WUESR1 = 0xFF;			// clear wakeup status
	WUESR2 = 0xFF;
	WUESR3 = 0xFF;
	WUESR4 = 0xFF;

	_nop_();
	_nop_();

	EnableAllInterrupt();
	PLLCTRL = 1;
	PCON =2 ;             	// enter sleep mode

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	WUENR1 = 0x00;	
	WUENR2 = 0x00;	
	WUENR3 = 0x00;	
	WUENR4 = 0x00;	

	IER0=0x00;				
	IER1=0x00;
	IER2=0x00;
	IER3=0x00;
	IER4=0x00;

	//*************************************************************************
	//
	//*************************************************************************	
	GPCRD0 = INPUT;			// SUSB to alternate pin	
	GPCRD1 = INPUT;			// ACIN to alternate pin
	GPCRE4 = INPUT;			// pwrsw to alternate pin
	GPCRE5 = INPUT;			// NOVO Button to alternate pin  
	//*************************************************************************

	WUESR1 = 0xff;
	WUESR2 = 0xff;
	WUESR3 = 0xff;
	WUESR4 = 0xff;

	CGCTRL1R = 000;
	CGCTRL2R = 0x00;
	CGCTRL3R = 0x00;
    
#if ADCFuncSupport  
	EnableADCChannel();		// enable ADC	
#endif	

	DACPWRDN=0x00;			// enable DAC	
	Enable_Any_Key_Irq();	// Enable Keyboard
	Init_Timers();
}

//-----------------------------------------------------------------------------
// The function of checking HWPG
//-----------------------------------------------------------------------------
void MoniterHWPG(void)
{
    if(SystemIsS0)
    {
        if(!Read_HWPG()) 
        {
            HWPG_TIMER++;
            if(HWPG_TIMER>T_HWPG)
            {
                Oem_TriggerS0S5(SC_HWPS0Off);
                HWPG_TIMER = 0x00;
            }
        }
        else
        {
             HWPG_TIMER = 0x00;
        }
    }
}

//----------------------------------------------------------------------------
// EC auto power on function
//----------------------------------------------------------------------------
void CheckAutoS5S0(void)
{
	if(ECAutoPowerOn==1)
	{
		ECAutoPowerOn = 0;
		DelayDoPowerSeq = 1000;
		Oem_TriggerS5S0();
	}
	
	if(ECWDTRSTNow)
	{
		ECWDTRSTNow = 0;
		SysPowState = SYSTEM_EC_WDTRST;
	}
}

//-----------------------------------------------------------------------------
// Handle System Power Control
// Called by service_1mS -> Timer1msEvent -> Hook_Timer1msEvent
//-----------------------------------------------------------------------------
void Oem_SysPowerContrl(void)
{
	if(SystemIsS0)
	{
		//if (!Read_LPCRST())
		//{

		//}
	}

    // Check if delay doing PowerSeq is needed.
    if ( DelayDoPowerSeq != 0x00 )
    {
        DelayDoPowerSeq--; 		
        if ( DelayDoPowerSeq != 0x00 )
        {
            return;
        }
    }

    if((SystemIsS0)||(SystemIsS3)||(SystemIsS4)||(SystemIsS5))
    {
        CheckPowerState();
    }

    // Check current System PowerState to see what should we do.
    switch (SysPowState)
    {
        case SYSTEM_S0: 
			MoniterHWPG();
			break;

        case SYSTEM_S3: 
         	break;

        case SYSTEM_S4:
            break;

        case SYSTEM_S5:
			CheckAutoS5S0();
            break;

        case SYSTEM_S4_S0:
            Oem_S4S0Sequence();
            break;

        case SYSTEM_S5_S0:
			Oem_S5S0Sequence();
			break;
				
        case SYSTEM_S3_S0:
			Oem_S3S0Sequence();
            break;

        case SYSTEM_S0_S3:
			Oem_S0S3Sequence();
            break;

        case SYSTEM_S0_S4:
            Oem_S0S4Sequence();
            break;

        case SYSTEM_S0_S5:
			Oem_S0S5Sequence();
         	break;
				
		case SYSTEM_EC_WDTRST:
			InternalWDTNow();
			break;

        default:
         	SysPowState=SYSTEM_S5;
         	break;
    }
}


void CheckResetSource(void)
{
    switch(RSTStatus&0x03)
    {
        case 0:
        case 1:
            if(GPCRA0==0x84)
            {
                ShutDnCause = SC_ECColdBoot;
            }
            else
            {
                ShutDnCause = SC_EC_0x0000;
            }
            break;
            
        case 2:
            if(GPCRA0==0x84)
            {
                ShutDnCause = SC_IntWatchDog;
            }
            else
            {
                ShutDnCause = SC_EC_0x0000;
            }
            break;         

        case 3:
            if(GPCRA0==0x84)
            {
                ShutDnCause = SC_ExtWatchDog;
            }
            else
            {
                ShutDnCause = SC_EC_0x0000;
            }
            
            break;
    }
}

//-----------------------------------------------------------------------------
// The function of pulsing S.B. power button 100ms
//-----------------------------------------------------------------------------
void PulseSBPowerButton(void)
{
    DNBSWON_ON();
    SBSWReleaseCunt = 20;   // decrease timer base is 10ms total time 200ms
}

//-----------------------------------------------------------------------------
// The function of releasing S.B. power button
//-----------------------------------------------------------------------------
void CheckSBPowerButton(void)
{
	if(SBSWReleaseCunt!=0x00)
	{
		SBSWReleaseCunt--;
		if(SBSWReleaseCunt==0x00)
		{
			DNBSWON_OFF();
		}
	}
}
