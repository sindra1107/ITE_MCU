/*-----------------------------------------------------------------------------
 * TITLE: OEM_FAN.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// Smart Fan control
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fan table 1   2009/08/18 Rev.01
//-----------------------------------------------------------------------------
const thermal code ThermalTalbe1[]=
{
    {0,	38,	0,	0,	&Fan1On_Step1,	&Fan1Off_Step1,	&Fan1RPM_Step1	},	// Level 0 	
    {1,	50,	36,	30,	&Fan1On_Step2,	&Fan1Off_Step2,	&Fan1RPM_Step2	},	// Level 1 	
    {2,	55,	48,	34,	&Fan1On_Step3,	&Fan1Off_Step3,	&Fan1RPM_Step3	},	// Level 2 	
    {3,	60,	53,	37,	&Fan1On_Step4,	&Fan1Off_Step4,	&Fan1RPM_Step4	},	// Level 3 	
    {4,	65,	58,	40,	&Fan1On_Step5,	&Fan1Off_Step5,	&Fan1RPM_Step5	},	// Level 4 	
    {5,	70,	63,	43,	&Fan1On_Step6,	&Fan1Off_Step6,	&Fan1RPM_Step6	},	// Level 5 	
    {6,	75,	68,	46,	&Fan1On_Step7,	&Fan1Off_Step7,	&Fan1RPM_Step7	},	// Level 6 	
    {7,127, 73, 56, &Fan1On_Step8,	&Fan1Off_Step8,	&Fan1RPM_Step8	},	// Level 7 		
};

//-----------------------------------------------------------------------------
// Fan table 2
//-----------------------------------------------------------------------------
const thermal code ThermalTalbe2[]=
{
	{0,	38,	 0,	0,	&Fan2On_Step1,	&Fan2Off_Step1,	&Fan2RPM_Step1	},	// Level 0 	
	{1,	50,	36,	30,	&Fan2On_Step2,	&Fan2Off_Step2,	&Fan2RPM_Step2	},	// Level 1 	
	{2,	55,	48,	34,	&Fan2On_Step3,	&Fan2Off_Step3,	&Fan2RPM_Step3	},	// Level 2 	
	{3,	60,	53,	37,	&Fan2On_Step4,	&Fan2Off_Step4,	&Fan2RPM_Step4	},	// Level 3 	
	{4,	65,	58,	40,	&Fan2On_Step5,	&Fan2Off_Step5,	&Fan2RPM_Step5	},	// Level 4 	
	{5,	70,	63,	43,	&Fan2On_Step6,	&Fan2Off_Step6,	&Fan2RPM_Step6	},	// Level 5 	
	{6,	75,	68,	46,	&Fan2On_Step7,	&Fan2Off_Step7,	&Fan2RPM_Step7	},	// Level 6 	
	{7,127, 73,	56,	&Fan2On_Step8,	&Fan2Off_Step8,	&Fan2RPM_Step8	},	// Level 7 		
};

//-----------------------------------------------------------------------------
// The function of check fan rpm 1
//-----------------------------------------------------------------------------	
void CheckFanRPM1(void)
{
	BYTE FanLevel_t = FanLevel;	
	BYTE Fan1RPM_t = Fan1RPM;

	if(Debugtemperature1==0x00)
	{
		temperature1 = TCPU_temp;
	}
	else
	{
		temperature1 = Debugtemperature1;
	}
		
	if(FanLevel_t <((sizeof(ThermalTalbe1)/sizeof(thermal))-1))
	{
		if(temperature1> *ThermalTalbe1[FanLevel_t].FanOn)
		{
			FanLevel_t += 1;
		}
	}
	
	if (FanLevel_t>0)
	{
		if (temperature1< *ThermalTalbe1[FanLevel_t].FanOff)
		{			
			FanLevel_t-=1;
		}
	}
		
	FanLevel = FanLevel_t;	
	Fan1RPM = *ThermalTalbe1[FanLevel_t].RPM;

}

//-----------------------------------------------------------------------------
// The function of check fan rpm 2
//-----------------------------------------------------------------------------
void CheckFanRPM2(void)
{
	BYTE FanLevel_t = FanLeve2;	
	BYTE Fan1RPM_t = Fan2RPM;

	if(Debugtemperature2==0x00)
	{
		temperature2 = TSys_temp;
	}
	else
	{
		temperature2 = Debugtemperature2;
	}
		
	if(FanLevel_t <((sizeof(ThermalTalbe2)/sizeof(thermal))-1))
	{
		if(temperature2> *ThermalTalbe2[FanLevel_t].FanOn)
		{
			FanLevel_t += 1;
		}
	}
	
	if (FanLevel_t>0)
	{
		if (temperature2< *ThermalTalbe2[FanLevel_t].FanOff)
		{			
			FanLevel_t-=1;
		}
	}
		
	FanLeve2 = FanLevel_t;	
	Fan2RPM = *ThermalTalbe2[FanLevel_t].RPM;
}

void Fan1MainControl(void)
{
	if(Fan1RPM>=Fan2RPM)
	{	
		if(((Fan1RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan1RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}
	}
	else
	{
		if(((Fan2RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan2RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}		
	}
}

void Fan2MainControl(void)
{
	if(Fan2RPM>=Fan1RPM)
	{
		if(((Fan2RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan2RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}			
	}
    else
	{	
		if(((Fan1RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
			FanValue++;	
		}
		else if(((Fan1RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0x00)
			FanValue--;	
		}
	}
}

//-----------------------------------------------------------------------------
// The function of fan rpm control
//-----------------------------------------------------------------------------
void FanControl(void)
{
	if(	RPM1==0x0000)
	{
		FanValue = FanInitValue;
	}
	
    if(Fan1RPM!=0x00)
    {
        Fan1MainControl();
    }
    else
    {
        Fan2MainControl();
    }
}


//-----------------------------------------------------------------------------
// Init. thermal table 1
//-----------------------------------------------------------------------------
void InitThermalTable1(void)
{
	BYTE index;
	index=0x00;
	while(index<(sizeof(ThermalTalbe1)/sizeof(thermal)))
	{
		*ThermalTalbe1[index].FanOn=ThermalTalbe1[index].CFanOn;
		*ThermalTalbe1[index].FanOff=ThermalTalbe1[index].CFanOff;
		*ThermalTalbe1[index].RPM=ThermalTalbe1[index].CRPM;
		index++;
	}
}

//-----------------------------------------------------------------------------
// Init. thermal table 2
//-----------------------------------------------------------------------------
void InitThermalTable2(void)
{
	BYTE index;
	index=0x00;
	while(index<(sizeof(ThermalTalbe2)/sizeof(thermal)))
	{
		*ThermalTalbe2[index].FanOn=ThermalTalbe2[index].CFanOn;
		*ThermalTalbe2[index].FanOff=ThermalTalbe2[index].CFanOff;
		*ThermalTalbe2[index].RPM=ThermalTalbe2[index].CRPM;
		index++;
	}
}

//-----------------------------------------------------------------------------
// Fan full on control
//-----------------------------------------------------------------------------
void FanFullOn(void)
{
	FanValue = MaxOutValue;
	FanFullOnCont = FullOnCounter;		    //2sec
}

//-----------------------------------------------------------------------------
// Fan full off control
//-----------------------------------------------------------------------------
void FanFullOff(void)
{
	FanValue = 0x00;
}

//-----------------------------------------------------------------------------
// Fan Init on control
//-----------------------------------------------------------------------------
void FanInitOn(void)
{
	FanValue = FanInitValue;
	FanFullOnCont = FullOnCounter;		    //2sec
	//if(IS_MASK_SET(ThermalFlag, ThermalInitOK))
    //{   
	//    TCPU_temp = 85;
    //}
    //else
    //{
    //    TCPU_temp = 70;
    //}
}

//-----------------------------------------------------------------------------
// The function of get fan RPM
//-----------------------------------------------------------------------------
void GetRPM1(void)
{
    BYTE tach_H;
    BYTE tach_L;

    tach_H = F1TMRR;
    tach_L = F1TLRR;
    if((tach_H!=0x00)||(tach_L!=0x00))
    {
		if(((tach_H*256) + tach_L)<RPM1Max)
		{
            RPM1=(4312500/TACH1P/((tach_H*256) + tach_L));
		}
        else
        {
            RPM1=RPM1Max; 
        }
    }
    else
    {
        RPM1=0x0000;
    }
}


//-----------------------------------------------------------------------------
// The function of smart fan
//-----------------------------------------------------------------------------
void FanManager(void)
{
	if(FanFullOnCont!=0x00)
	{
		FanFullOnCont--;
        GetRPM1();
		return;
	}

	if(DebugFan1RPMT==0x00)			    // In normal control mode
	{
		if((Fan1RPM!=0x00)||(Fan2RPM!=0x00))
		{
            GetRPM1();
			FanControl();
		}
		else
		{
			if(FanValue != 0x00)
			{
				RPM1=0x0000;
				FanFullOff();
			}
		}
	}
	else											// In RPM debug mode
	{
		GetRPM1();
		if(	RPM1==0x0000)
		{
			FanValue = FanInitValue;
		}
		else
		{
			if(((DebugFan1RPMT*100)-RPMACC)>RPM1)
			{
				if(FanValue<MaxOutValue)
				FanValue++;	
			}
			else if(((DebugFan1RPMT*100)+RPMACC)<RPM1)
			{
				if(FanValue>0x00)
				FanValue--;	
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Moniter temperature
//-----------------------------------------------------------------------------
const sTooHot code asTooHot[]=
{
	{ &TCPU_temp, 	CpuTooHot, &VeryHotCnt, 	CpuTooHotTimes },
	{ &TSys_temp,   SysTooHot, &SysVeryHotCnt, 	SysTooHotTimes }	
};

void MoniterTemprature(void)
{
	BYTE index=0x00;
	while(index<(sizeof(asTooHot)/sizeof(sTooHot)))
	{
		if((*asTooHot[index].Temprature) >=asTooHot[index].Limit)
		{
			*asTooHot[index].Counter += 1;
			if(*asTooHot[index].Counter>asTooHot[index].Times)
			{
				Oem_TriggerS0S5(SC_CPUHOT);
			}
		}
		else
		{
			*asTooHot[index].Counter = 0x00;
		}
		index++;
	}	

}

//-----------------------------------------------------------------------------
// Function Name : ReadCPUTemp
//-----------------------------------------------------------------------------
void ReadCPUTemp(void) 
{
    if(SystemIsS0)
    {
        // Use PECI interface to read cpu temperature
        #ifdef PECI_Support
            #if ReadCPUTemperature
            if(CPUTjmax==0x00)         // Need to read CPU Tjmax
            {
                PECI_ReadCPUTJMAX();
            }
            else
            {
                PECI_ReadCPUTemp();     // Use PECI interface to read cpu temperature
            }
            #endif
        #endif 
        
        // Use thermal sensor to read cpu temperature
        //SET_MASK(SMBus2Flag1, PollRemote);
    }
}


//-----------------------------------------------------------------------------
// Function Name : ReadSysTemp
//-----------------------------------------------------------------------------
void ReadSysTemp(void) 
{
    if(SystemIsS0)
    {
        SET_MASK(SMBus2Flag1, PollLocal);
    }
}

//-----------------------------------------------------------------------------
// Function Name : InitThermalChip
//-----------------------------------------------------------------------------
void InitThermalChip(void)
{
    
    
}    
