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
    {0,	44,	0,	0,	&Fan1On_Step1,	&Fan1Off_Step1,	&Fan1RPM_Step1	},	// Level 0 	
    {1,	47,	40,	24,	&Fan1On_Step2,	&Fan1Off_Step2,	&Fan1RPM_Step2	},	// Level 1 	
    {2,	55,	48,	30,	&Fan1On_Step3,	&Fan1Off_Step3,	&Fan1RPM_Step3	},	// Level 2 	
};

//-----------------------------------------------------------------------------
// Fan table 2
//-----------------------------------------------------------------------------
const thermal code ThermalTalbe2[]=
{
	{0,	52,	 0,	0,	&Fan2On_Step1,	&Fan2Off_Step1,	&Fan2RPM_Step1	},	// Level 0 	
	{1,	60,	52,	21,	&Fan2On_Step2,	&Fan2Off_Step2,	&Fan2RPM_Step2	},	// Level 1 	
	{2,	75,	67,	30,	&Fan2On_Step3,	&Fan2Off_Step3,	&Fan2RPM_Step3	},	// Level 2 	
	{3,	127, 80,	38,	&Fan2On_Step4,	&Fan2Off_Step4,	&Fan2RPM_Step4	},	// Level 3 			
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
		temperature1 = PECI_CPU_temp; //TCPU_temp  0x3B
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
		temperature2 = PECI_CPU_temp+5;  // TVGA_temp
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
		if(((Fan1RPM*100)-RPMACC)>RPM1)
		{
			if(FanValue<MaxOutValue)
				FanValue++;
		}
		else if(((Fan1RPM*100)+RPMACC)<RPM1)
		{
			if(FanValue>0)
				FanValue--;
		}

	if(DebugforceFan1RPM!=0) {
		DCR0 = DebugforceFan1RPM;
	}
	else {
		DCR0 = FanValue;
	}
}

void Fan2MainControl(void)
	{
	if(((Fan2RPM*100)-RPMACC)>RPM2)
	{
		if(FanValue2<MaxOutValue)
			FanValue2++;	
	}
	else if(((Fan2RPM*100)+RPMACC)<RPM2)
	{
		if(FanValue2>0)
			FanValue2--;
	}		

	if(DebugforceFan2RPM!=0) {
		DCR1 = DebugforceFan2RPM;
	}
	else {
		DCR1 = FanValue2;
	}
}


//-----------------------------------------------------------------------------
// The function of fan rpm control
//-----------------------------------------------------------------------------
void FanControl(void)
{
//	if(	RPM2==0x0000)
//	{
//		FanValue = FanInitValue;
//	}
	
        Fan1MainControl();
	Fan2MainControl();

//    if(Fan2RPM!=0x00)
//    {
        
//    }
//    else
//    {
//        Fan2MainControl();
//    }
}

void FineTuneFan2PRM(void)
{
	if (Fan2RPM != 0)
	{
		if(((Fan2RPM*50)-RPMACC)>RPM2)
		{
			if(FanValue2 < MaxOutValue)
			{
				FanValue2++;
			}
		}
		else if(((Fan2RPM*50)+RPMACC)<RPM2)
		{
			if(FanValue2>0x00)
			{
				FanValue2--;
			}
		}
	}
	else
	{
		FanValue2 = 0;

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
// Fan full off control
//-----------------------------------------------------------------------------
void FanFullOff(void)
{
	FanValue = 0x00;
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
			RPM1=(2875000/TACH1P/((tach_H*256) + tach_L));
            		//RPM1=(4312500/TACH1P/((tach_H*256) + tach_L));
		}
        else
        {
            RPM1=RPM1Max; 
        }
    }
    else
    {
        RPM1=0x0000;
	FanValue = FanInitValue;
    }
}


void GetRPM2(void)
{
    BYTE tach_H;
    BYTE tach_L;

    tach_H = F2TMRR;
    tach_L = F2TLRR;
    if((tach_H!=0x00)||(tach_L!=0x00))
    {
		if(((tach_H*256) + tach_L)<RPM2Max)
		{
		RPM2=(2875000/TACH2P/((tach_H*256) + tach_L));
            	//	RPM2=(4312500/TACH2P/((tach_H*256) + tach_L));
		}
        else
        {
            RPM2=RPM2Max; 
        }
    }
    else
    {
        RPM2=0x0000;
	FanValue2=FanInitValue;
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
        GetRPM2();
		return;
	}

	if(DebugFan1RPMT==0x00)			    // In normal control mode
	{
		GetRPM1();
		if((Fan2RPM!=0x00)) // ||(Fan2RPM!=0x00)
		{
            		GetRPM2();
			FineTuneFan2PRM();
		}
		else
		{
			if(FanValue != 0x00)
			{
				RPM2=0x0000;
				FanFullOff();
			}
		}
		FanControl();
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
// Function Name : ReadDGPUTemp
//-----------------------------------------------------------------------------
void ReadDgpuTemp(void) 
{
    if(SystemIsS0)
    {
    	PORT_BYTE_PNTR byte_register_pntr;
        LWORD LWORDTemp;    
        XBYTE Status;
	
        //if ( IS_MASK_CLEAR(TESTMODE,b3D_GB_det) ) return;

	//SMB_CHANEL = 0x03;
        //SMB_ADDR = 0x82;
        //SMB_CMD = 0x01;
        //SMB_BCNT = 0x04;
        Status = FALSE;
  
	if(SmBusI2CAddress==0x00) {
            byte_register_pntr = &ATIDGPUTemp;
//            *(byte_register_pntr + 0) = 0x0F;
//           *(byte_register_pntr + 1) = 0x00;
//            *(byte_register_pntr + 2) = 0x01;
//            *(byte_register_pntr + 3) = 0xC5; 

//            if (bWSMBusBlock(DefAtiVgaSMBusCH, SMbusWBK, DefAtiVgaSMBusAddr, 0x01, &ATIDGPUTemp, 0x04,SMBus_NoPEC))
//            {
                //SMB_CHANEL = 0x03;
                //SMB_ADDR = 0x82;
                //SMB_CMD = 0x03;
        	//20130923      if (bRSMBusBlock(DefAtiVgaSMBusCH, SMbusRBK, DefAtiVgaSMBusAddr, 0x03, &ATIDGPUTemp))
                if (bRWSMBus(DefAtiVgaSMBusCH, SMbusRB, DefAtiVgaSMBusAddr, 0x00, &ATIDGPUTemp, SMBus_NoPEC))
                {
//                    LWORDTemp = ATIDGPUTemp;
//                    LWORDTemp = LWORDTemp >> 9;
//                    TVGA_temp = (BYTE)LWORDTemp;
                    Status = TRUE;
                }   
//            }
	} else {
//	    if (bWSMBusBlock(DefAtiVgaSMBusCH, SMbusWBK, SmBusI2CAddress, 0x01, &ATIDGPUTemp, 0x04, SMBus_NoPEC))
//	    {
		//SMB_CHANEL = 0x03;
		//SMB_ADDR = 0x82;
		//SMB_CMD = 0x03;
		//20130923		if (bRSMBusBlock(DefAtiVgaSMBusCH, SMbusRBK, DefAtiVgaSMBusAddr, 0x03, &ATIDGPUTemp))
		if(GPU_Therm_Method==0x01) {
			if (bRSMBusBlockLS(DefAtiVgaSMBusCH, SMbusRBK, SmBusI2CAddress, NowScanCmd, &ATIDGPUTemp,0x04))
			{
				LWORDTemp = ATIDGPUTemp;
				LWORDTemp = LWORDTemp >> 9;
				TVGA_temp = (BYTE)LWORDTemp;
				Status = TRUE;
			}
//	    }
		}

		if(GPU_Therm_Method==0x02) {
			if (bRSMBusBlockLS(DefAtiVgaSMBusCH, SMbusRW, SmBusI2CAddress, NowScanCmd, &ATIDGPUTemp,0x02))
			{
				LWORDTemp = ATIDGPUTemp;
				LWORDTemp = LWORDTemp >> 9;
				TVGA_temp = (BYTE)LWORDTemp;
				Status = TRUE;
			}
		}

	if(GPU_Therm_Method==0x03) {
		if (bSMBusReceiveByte(DefAtiVgaSMBusCH, SmBusI2CAddress, &ATIDGPUTemp))
		{
			LWORDTemp = ATIDGPUTemp;
			LWORDTemp = LWORDTemp >> 9;
			TVGA_temp = (BYTE)LWORDTemp;
			Status = TRUE;
		}
	}
	
	if(GPU_Therm_Method==0x04) {		
		bSMBusSendByte(DefAtiVgaSMBusCH, DefAtiVgaSMBusAddr, 0x00); 
		if (bRSMBusBlockLS(DefAtiVgaSMBusCH, SMbusRBK, SmBusI2CAddress, 0x00, &ATIDGPUTemp, 1))
		{
			LWORDTemp = ATIDGPUTemp;
			LWORDTemp = LWORDTemp >> 9;
			TVGA_temp = (BYTE)LWORDTemp;
			Status = TRUE;
		}
	}

	if(GPU_Therm_Method==0x05) {		
		bWSMBusBlock(DefAtiVgaSMBusCH, SMbusWBK, SmBusI2CAddress, 0x00, 0x00, 0x01,SMBus_NoPEC);
		if (bRSMBusBlockLS(DefAtiVgaSMBusCH, SMbusRBK, SmBusI2CAddress, 0x00, &ATIDGPUTemp, 1))
		{
			LWORDTemp = ATIDGPUTemp;
			LWORDTemp = LWORDTemp >> 9;
			TVGA_temp = (BYTE)LWORDTemp;
			Status = TRUE;
		}
	}


		
	}

        if (Status)
        {
            Cark_Test01 = 0;
            //CLEAR_MASK(DeviceFailFlag1, bATIGPUSMBusFail);      
        }
        else
        {
            //SET_MASK(DeviceFailFlag1, bATIGPUSMBusFail);
            Cark_Test01++;
        }
    }
}
   
