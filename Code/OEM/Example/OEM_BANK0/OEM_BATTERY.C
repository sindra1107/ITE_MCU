/*-----------------------------------------------------------------------------
 * TITLE: OEM_BATTERY.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//****************************************************************************
// The function of smart battery
//****************************************************************************

const sbatINFO code BATDeviceNameTable[] =
{
//   Id     Device name  
    {0x01,   	"XXXXXXX"       },	    // model 1
    {0x02,   	"YYYYYY"        },	    // model 2
    {0x03,   	"TW932SM"       },      // model 3
};

const sbatFirstData code BAT1_FirstDataTable[] =
{
//   command     address of variable  
    {BATCmd_temp,       &BAT1_temp_L        },	
    {BATCmd_volt,   	&BAT1_volt_L        },
    {BATCmd_current,   	&BAT1_current_L     },
    {BATCmd_RSOC,       &BAT1_RSOC          },	
    {BATCmd_RMcap,      &BAT1_RMcap_L       },
    {BATCmd_FCcap,      &BAT1_FCcap_L       },
    {BATCmd_CC,   	    &BAT1_CC_L          },	
    {BATCmd_CV,   	    &BAT1_CV_L          },
    {BATCmd_BatStatus,  &BAT1_ALARM1        },
};

//----------------------------------------------------------------------------
// Get battery device name and checking battery is supported or not
//----------------------------------------------------------------------------
void BAT1ID_CheckDeviceName(void)
{
	BYTE index;                     // Battery item count
	BYTE BCunt;                     // Battery name count

    if(bRSMBusBlock(SmartBatChannel, SMbusRBK, SmartBat_Addr, BATCmd_Dname, &SMB_DATA))
    {
	    for(index=0x00;index<(sizeof(BATDeviceNameTable)/sizeof(sbatINFO));index++) // Compare all support list
	    {
		    Tmp_XPntr = &SMB_DATA;
		    for(BCunt=0x00;BCunt<SMB_BCNT;BCunt++)  // compare all char
		    {
			    if(BATDeviceNameTable[index].DeviceName[BCunt]!= *Tmp_XPntr)
			    {
    				break;                      // fail , point to next
			    }
			    Tmp_XPntr++;
		    }                                   // End of For Loop for check device name is meet
		
		    if(BCunt==SMB_BCNT)                 // meet design name
		    {
                BAT1_Number  = BATDeviceNameTable[index].DeviceNO;
                BAT1IdentifyNextStep();         // next step                  
			    return;
		    }                                   // End of meet battery device name
	    }                                       // End of FOR loop for check battery device name 

        BAT1_SetFail(Bat_NoSupport);            // battery isn't supportd model

    }         // End of Read SMBUS Block function
    else
    {
        BAT1_ID_TimeOut_CNT--;
        if(BAT1_ID_TimeOut_CNT==0x00)           // time out
        {   
            SetBAT1CtrlStep(BAT_Step_WC);       // Go to wake up charge
        }
    }
}

//----------------------------------------------------------------------------
// Set battery 1 fail
//----------------------------------------------------------------------------
void BAT1_SetFail(BYTE failcause)
{
    BAT1_FailCause = failcause;
    SetBAT1CtrlStep(BAT_Step_SetFail);
}

//----------------------------------------------------------------------------
// If battery is pluged out Clear variables
//----------------------------------------------------------------------------
void BAT1_PlugOutClrVariables(void)
{
    BAT1_temp_L= 0x00;	
    BAT1_volt_L = 0x00;
    BAT1_current_L = 0x00;
    BAT1_RSOC = 0x00;	
    BAT1_RMcap_L = 0x00;
    BAT1_FCcap_L = 0x00;
    BAT1_CC_L = 0x00;	
    BAT1_CV_L = 0x00;
    BAT1_temp_H= 0x00;	
    BAT1_volt_H = 0x00;
    BAT1_current_H = 0x00;
    BAT1_RMcap_H = 0x00;
    BAT1_FCcap_H = 0x00;
    BAT1_CC_H = 0x00;	
    BAT1_CV_H = 0x00;
    BAT1_ALARM1 = 0x00;
    BAT1_ALARM2 = 0x00;
    
    BT1_STATUS2 = 0x00;
    BT1_STATUS1 &= bat_in;      // Don't chear bat_in flag
    BT1_STATUS3 = 0x00;
    
    BAT1_CtrlStep = 0x00;
    BAT1_ID_Step = 0x00;
    BAT1_1SecTimer = 0x00;
    BAT1_S_Number = 0x00;
    BAT1_ID_TimeOut_CNT = 0x00;
    BAT1_Number = 0x00;
    BAT1_FirstDataIndex = 0x00;
    Charger_TimeOut = 0x00;
    WakeUpChrCunt_Min = 0x00;
    PreChrCunt_Min = 0x00;
    NormalChrCunt_Min = 0x00;
    WakeUpChrCunt = 0x00;
    PreChrCunt = 0x00;
    NormalChrCunt = 0x00;
    BAT1_OTCunt = 0x00;
    BAT1_OVCunt = 0x00; 
    CHARGE_CURRENT_BK = 0x00;
    CHARGE_VOLTAGE_BK = 0x00;
}

//----------------------------------------------------------------------------
// Polling battery 1 data function
//----------------------------------------------------------------------------
void PollingBAT1Data(void)
{
    SMBus1Flag1 |= (B1_RSOC+B1_C+B1_V+B1_RMcap+B1_Status+B1_FCC+B1_Temp);
    SMBus1Flag2 |= (B1_CC+B1_CV);
}

//----------------------------------------------------------------------------
// Battery 1 protect function
//----------------------------------------------------------------------------
void BAT1Protection(void)
{
    WORD voltage;
    
    if(IS_MASK_SET(BAT1_ALARM2, OverTemp_alarm))    // OT protect
    {
        if(++BAT1_OTCunt > BatOTTimeOut)
        {
            BAT1_SetFail(Bat_OverTemperature);      // battery over temperature
        }
    }
    else
    {
        BAT1_OTCunt = 0x00;
    }

    voltage = (BAT1_volt_H*256)+BAT1_volt_L;        // OV protect
    if(voltage > BATOverVoltage)
    {
        if(++BAT1_OVCunt > BatOVTimeOut)
        {
            BAT1_SetFail(Bat_OverVoltage);          // battery over voltage
        }
    }
    else
    {
        BAT1_OVCunt = 0x00;
    }
}

//----------------------------------------------------------------------------
// Set battery 1 identify re-try counter
//----------------------------------------------------------------------------
void SetBAT1IDTimeOutCNT(void)
{
    BAT1_ID_TimeOut_CNT = BatIDTimeOut;
}

//----------------------------------------------------------------------------
// First time to get battery design voltage and checking SMBus communication is OK
//----------------------------------------------------------------------------
void BAT1ID_GetDesignVoltage(void)
{
    WORD DVTemp;
    if(bRWSMBus(SmartBatChannel, SMbusRW, SmartBat_Addr, BATCmd_DVolt, &ByteTemp01, SMBus_NoPEC))
    {
        DVTemp = (ByteTemp02*256)+ByteTemp01;   // Get Main battery desgin voltage
        if(DVTemp<8400)
        {
            BAT1_S_Number = 0x02;       // Main battery is 2s
        }
        else if(DVTemp<12600)
        {
            BAT1_S_Number = 0x03;       // Main battery is 3s
        }
        else
        {
            BAT1_S_Number = 0x04;       // Main battery is 4s
        } 
        BAT1IdentifyNextStep();         // next step 
        ByteTemp01 = 0x00;
        ByteTemp02 = 0x00;
    }
    else
    {
        BAT1_ID_TimeOut_CNT--;
        if(BAT1_ID_TimeOut_CNT==0x00)   // time out
        {   
            SetBAT1CtrlStep(BAT_Step_WC);// Go to wake up charge
        }
    }
}

//----------------------------------------------------------------------------
// Battery Authentication if necessary
//----------------------------------------------------------------------------
void BAT1ID_CheckBatAuth(void)
{
    BAT1IdentifyNextStep();         // next step 
}

//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
void BAT1ID_PollingFirstData(void)
{
    if(BAT1_FirstDataIndex < (sizeof(BAT1_FirstDataTable)/sizeof(sbatFirstData)))
    {
        if(bRWSMBus(SmartBatChannel, SMbusRW, SmartBat_Addr, BAT1_FirstDataTable[BAT1_FirstDataIndex].Cmd, 
            BAT1_FirstDataTable[BAT1_FirstDataIndex].Var, SMBus_NoPEC))
        {
            BAT1_FirstDataIndex++;
        }
        else
        {
            BAT1_ID_TimeOut_CNT--;
            if(BAT1_ID_TimeOut_CNT==0x00)       // time out
            {   
                SetBAT1CtrlStep(BAT_Step_WC);   // Go to wake up charge
            }
        }
    }
    else
    {
        BAT1IdentifyNextStep();                 // next step 
    }
}

//----------------------------------------------------------------------------
// Battery 1 init. OK
//----------------------------------------------------------------------------
void BAT1ID_InitOK(void)
{
	SET_MASK(BT1_STATUS1, bat_valid);
    if(IS_MASK_SET(POWER_FLAG1, adapter_in))
    {
        SetBAT1CtrlStep(BAT_Step_PC);           // Go to Pre-Charge
    }
    else                                        //Battery only
    {
        SetBAT1CtrlStep(BAT_Step_DC);           // Go to discharge
    }
}

//----------------------------------------------------------------------------
// The function of identify main battery
//----------------------------------------------------------------------------
void IdentifyBAT1(void)
{
    switch(BAT1_ID_Step)
    {
        case BATID_Step_GetDV:      // First time to get battery design voltage and checking SMBus communication is OK
            BAT1ID_GetDesignVoltage();
            break;

        case BATID_Step_Auth:       // Battery Authentication if necessary
            BAT1ID_CheckBatAuth();
            break;

        case BATID_Step_MFName:     // Get manufacturer name and checking battery is supported
            BAT1ID_CheckDeviceName();
            break;

        case BATID_Step_FirstData:  // Polling first data
            BAT1ID_PollingFirstData();
            break;

        case BATID_Step_InitOK:     // Init_OK,prepare Discharge/Pre-Charge ***(always at last step)***
            BAT1ID_InitOK();
            break;
            
        default:
            break;
    }
}

//----------------------------------------------------------------------------
// The function of setting battery 1 control step
//----------------------------------------------------------------------------
void SetBAT1CtrlStep(BYTE ctrlstep)
{
    BAT1_CtrlStep = ctrlstep;
    Charger_TimeOut = 0x00;
    
    switch(BAT1_CtrlStep)
    {
        case BAT_Step_ID:
            SetBAT1IDTimeOutCNT();
            BAT1_ID_Step = BATID_Step_GetDV;
            break;

        case BAT_Step_WC:
            BT1_STATUS1 &= ~(bat_InCharge+bat_Dischg+bat_Full);
            BT1_STATUS2 = 0x00;
            WakeUpChrCunt = 0x0000;
            WakeUpChrCunt_Min = 0x00;
            CLEAR_MASK(BT1_STATUS1, bat_valid);
            SET_MASK(BT1_STATUS2, bat_WC);
            break;
            
        case BAT_Step_PC:
            BT1_STATUS1 &= ~(bat_InCharge+bat_Dischg+bat_Full);
            BT1_STATUS2 = 0x00;
            PreChrCunt = 0x0000;
            PreChrCunt_Min = 0x0000;
            SET_MASK(BT1_STATUS2, bat_PC);
            break;
            
        case BAT_Step_NC:
            BT1_STATUS1 &= ~(bat_InCharge+bat_Dischg+bat_Full);
            BT1_STATUS2 = 0x00;
            NormalChrCunt = 0x0000;
            NormalChrCunt_Min = 0x0000;
            CHARGE_CURRENT_BK = 0x00;
            CHARGE_VOLTAGE_BK = 0x00;
            SET_MASK(BT1_STATUS2, bat_NC);
            break;
            
        case BAT_Step_DC:
            BT1_STATUS1 &= ~(bat_InCharge+bat_Dischg+bat_Full);
            BT1_STATUS2 = 0x00;
            SET_MASK(BT1_STATUS2, bat_DC);
            break;            

        case BAT_Step_FullyChg:
            BT1_STATUS1 &= ~(bat_InCharge+bat_Dischg+bat_Full);
            SET_MASK(BT1_STATUS1, bat_Full); 
            BT1_STATUS2 = 0x00;
            break;
    }
}

//----------------------------------------------------------------------------
// The function of going to next step of identify control step
//----------------------------------------------------------------------------
void BAT1IdentifyNextStep(void)
{
    BAT1_ID_Step++;
    if(BAT1_ID_Step==BATID_Step_FirstData)
    {
        BAT1_FirstDataIndex = 0x00;
    }
    SetBAT1IDTimeOutCNT();
}

//----------------------------------------------------------------------------
// The function of on / off charge pin
//----------------------------------------------------------------------------
void Hook_BAT1_ChargePinON(BYTE on_off)
{
    if(on_off==0x01)        // Enable charge pin
    {
        DC_OFF();
    }
    else                    // Disable charge pin
    {
        DC_ON();
    }
}

void BAT1_CheckFullyCharged(void)
{
    if((BAT1_CtrlStep==BAT_Step_PC)||(BAT1_CtrlStep==BAT_Step_NC))
    {
        if(IS_MASK_SET(BAT1_ALARM1, FullyChg))
        {
            if(DisableCharger()==0x01)          // Disable charger first, then go to fully charged step
            {
                SetBAT1CtrlStep(BAT_Step_FullyChg);
            }
        }
    }
}

void BAT1_CheckFullyDisCharged(void)
{
    if(BAT1_CtrlStep==BAT_Step_DC)
    {
        if(IS_MASK_SET(BAT1_ALARM1, FullyDsg))
        {
            SetBAT1CtrlStep(BAT_Step_FullyDisChg);
        }
    }
}

//----------------------------------------------------------------------------
// The function of pre-charge
//----------------------------------------------------------------------------
void BAT1_SETPreCharge(void)
{
    if(SmartCharger_Support)
    {
	    CHARGE_CURRENT_LO=BAT1_CURR_PRECHG;
	    CHARGE_CURRENT_HI=BAT1_CURR_PRECHG>>8;	
	    CHARGE_VOLTAGE_LO=BAT1_VOLT_PRECHG;
	    CHARGE_VOLTAGE_HI=BAT1_VOLT_PRECHG>>8;	
	    INPUT_CURRENT_LO=InputCurrent;
	    INPUT_CURRENT_HI=InputCurrent >> 8;
        if(SetSmartCharger()!=0x00)
        {
            Charger_TimeOut++;
            if(Charger_TimeOut>ChargerSettingTimeOut)
            {
                SetBAT1CtrlStep(BAT_Step_ChargerFail);  // Go to smart charger fail
            }
        }
        else
        {
            Hook_BAT1_ChargePinON(1);
            SET_MASK(BT1_STATUS2, bat_PC_OK);
            SET_MASK(BT1_STATUS1, bat_InCharge);
            Charger_TimeOut = 0x00;
        }
    }
    else
    { 
        // *** Set DAC CC CV value here ***
        Hook_BAT1_ChargePinON(1);
        SET_MASK(BT1_STATUS2, bat_PC_OK);
        SET_MASK(BT1_STATUS1, bat_InCharge);
    }
}

//----------------------------------------------------------------------------
// The function of battery 1 Pre charge
//----------------------------------------------------------------------------
void BAT1_PreCharge(void)
{
    WORD cctemp;
    if(IS_MASK_SET(POWER_FLAG1, adapter_in))
    { 
        if(IS_MASK_CLEAR(BT1_STATUS2, bat_PC_OK))
        {
            PreChrCunt = 0x00;
            BAT1_SETPreCharge();
        }
        else
        {
            PreChrCunt++;
            if((PreChrCunt%6000)==0)            // 1 min re-enable smart charger
            {
                BAT1_SETPreCharge();
                PreChrCunt = 0x0000;
                PreChrCunt_Min++;
                if(PreChrCunt_Min>BatPCTimeOut) // Over 2hr
                {
                    BAT1_SetFail(Bat_PreChargeFail);    // Pre_charge charge time-out
                }
            }
            else if((PreChrCunt%600)==0)        // 6sec
            {
                cctemp = (BAT1_CC_H*256)+BAT1_CC_L; 
                if(cctemp>Bat1_PC2NC_Cap)
                {
                    SetBAT1CtrlStep(BAT_Step_NC);   // Go to battery normal charge
                }
            }
        }
    }
    else
    {
        SetBAT1CtrlStep(BAT_Step_DC);           // Go to discharge
    }
}

//----------------------------------------------------------------------------
// The function of setting battery 1 normal charge
//----------------------------------------------------------------------------
void BAT1_SETNormalCharge(void)
{
    WORD temp;

    if(SmartCharger_Support)
    {
        temp = (BAT1_CC_H*256)+BAT1_CC_L;
        CHARGE_CURRENT_BK = (BAT1_CC_H*256)+BAT1_CC_L;
        temp *=SC_Current_Sense;
	    CHARGE_CURRENT_LO=(BYTE)temp;
	    CHARGE_CURRENT_HI=temp>>8;
	    CHARGE_VOLTAGE_LO=BAT1_CV_L;
	    CHARGE_VOLTAGE_HI=BAT1_CV_H;
	    INPUT_CURRENT_LO=InputCurrent;
	    INPUT_CURRENT_HI=InputCurrent >> 8;
        if(SetSmartCharger()!=0x00)
        {
            Charger_TimeOut++;
            if(Charger_TimeOut>ChargerSettingTimeOut)
            {
                SetBAT1CtrlStep(BAT_Step_ChargerFail);  // Go to smart charger fail
            }
        }
        else
        {
            Hook_BAT1_ChargePinON(1);
            SET_MASK(BT1_STATUS2, bat_NC_OK);
            SET_MASK(BT1_STATUS1, bat_InCharge);
            Charger_TimeOut = 0x00;
        }
    }
    else
    { 
        // *** Set DAC CC CV value here ***
        Hook_BAT1_ChargePinON(1);
        SET_MASK(BT1_STATUS2, bat_NC_OK);
        SET_MASK(BT1_STATUS1, bat_InCharge);
    }
}

//----------------------------------------------------------------------------
// The function of battery 1 normal charge
//----------------------------------------------------------------------------
void BAT1_NormalCharge(void)
{
	if(IS_MASK_SET(POWER_FLAG1, adapter_in))
    {   
        if(IS_MASK_CLEAR(BT1_STATUS2, bat_NC_OK))
        {
            CHARGE_CURRENT_BK=((BAT1_CC_H<<8)+BAT1_CC_L);
            NormalChrCunt = 0x0000;
            BAT1_SETNormalCharge();
        }
        else
        {
            NormalChrCunt++;
            if(CHARGE_CURRENT_BK != (BAT1_CC_H*256)+BAT1_CC_L)
            {
                CHARGE_CURRENT_BK=((BAT1_CC_H<<8)+BAT1_CC_L);
                BAT1_SETNormalCharge();
            }
            else
            {
                if((NormalChrCunt%6000)==0)             // 1 min re-enable smart charger
                {
                    NormalChrCunt_Min++;
                    if(NormalChrCunt_Min>BatNCTimeOut)  // 8hr
                    {
                        BAT1_SetFail(Bat_NormalChargeFail); // Normal charge time-out
                    }
                    BAT1_SETNormalCharge();
                    NormalChrCunt = 0x0000;
                }
            }
        }
    }
    else
    {
        SetBAT1CtrlStep(BAT_Step_DC);           // Go to discharge
    }
}

//----------------------------------------------------------------------------
// The function of waking up charge
//----------------------------------------------------------------------------
void BAT1_SETWakeUpCharge(void)
{
    if(SmartCharger_Support)
    {
	    CHARGE_CURRENT_LO=BAT1_CURR_WUCHG;        
	    CHARGE_CURRENT_HI=BAT1_CURR_WUCHG>>8;	
	    CHARGE_VOLTAGE_LO=BAT1_VOLT_WUCHG;
	    CHARGE_VOLTAGE_HI=BAT1_VOLT_WUCHG>>8;	
	    INPUT_CURRENT_LO=InputCurrent;
	    INPUT_CURRENT_HI=InputCurrent >> 8;
        
        if(SetSmartCharger()!=0x00)     // Fail
        {
            Charger_TimeOut++;
            if(Charger_TimeOut>ChargerSettingTimeOut)
            {
                SetBAT1CtrlStep(BAT_Step_ChargerFail);  // Go to smart charger fail
            }
        }
        else                            // OK
        {
            Hook_BAT1_ChargePinON(1);
            SET_MASK(BT1_STATUS2, bat_WC_OK);
            SET_MASK(BT1_STATUS1, bat_InCharge);
            Charger_TimeOut = 0x00;
        }
    }
    else
    {
        // *** Set DAC CC CV value here ***
        Hook_BAT1_ChargePinON(1);
        SET_MASK(BT1_STATUS2, bat_WC_OK);
        SET_MASK(BT1_STATUS1, bat_InCharge);
    }
}

//----------------------------------------------------------------------------
// Battery 1 wake up charge
//----------------------------------------------------------------------------
void BAT1WakeUpCharge(void)
{
    if(IS_MASK_SET(POWER_FLAG1, adapter_in))
    {
        if(IS_MASK_CLEAR(BT1_STATUS2, bat_WC_OK))
        {
            BAT1_SETWakeUpCharge();
        }
        else
        {
            WakeUpChrCunt++;
            if((WakeUpChrCunt%6000)==0)             // 1 min re-enable smart charger
            {
                BAT1_SETWakeUpCharge();
                WakeUpChrCunt = 0x0000;
                WakeUpChrCunt_Min++;
                if(WakeUpChrCunt_Min>BatWCTimeOut)  // Over 1hr
                {
                    BAT1_SetFail(Bat_WakeUpChargeFail); // Wake up charge time-out
                }
            }
            else if((WakeUpChrCunt%600)==0)         // 6 sec Check SMBus OK or not
            {
                if(bRWSMBus(SmartBatChannel, SMbusRW, SmartBat_Addr, BATCmd_RMcap, &BAT1_RMcap_L, SMBus_NoPEC))
                {
                    SetBAT1CtrlStep(BAT_Step_ID);   // Identify main battery
                }
            }
        }
    }
    else
    {
        BAT1_SetFail(Bat_Weak);             // main battery too low and AC doesn't plue-in
    }
}

//----------------------------------------------------------------------------
// Battery 1 discharge
//----------------------------------------------------------------------------
void BAT1DisCharge(void)
{
	if(IS_MASK_SET(POWER_FLAG1, adapter_in))
	{
        if(IS_MASK_SET(BT1_STATUS3, bat_ForceDischg))
        {
    	    if(IS_MASK_CLEAR(BT1_STATUS2,bat_DC_OK))
    	    {
        	    DisableCharger();
    	    }
        }
        else
        {
            SetBAT1CtrlStep(BAT_Step_PC);
        }
    }
    else
    {
    	if(IS_MASK_CLEAR(BT1_STATUS2,bat_DC_OK))
    	{
        	DisableCharger();
    	}
	}
}

//----------------------------------------------------------------------------
// Battery 1 fully charged
//----------------------------------------------------------------------------
void BAT1FullyCharged(void)
{
    if(IS_MASK_CLEAR(POWER_FLAG1, adapter_in))
    {
        SetBAT1CtrlStep(BAT_Step_DC);           // Go to discharge
    }
}

//----------------------------------------------------------------------------
// Battery 1 fully discharged
//----------------------------------------------------------------------------
void BAT1FullyDisharged(void)
{
    if(IS_MASK_SET(POWER_FLAG1, adapter_in))
    {

    }
    else
    {

    }
}

//----------------------------------------------------------------------------
// Check Battery 1 discharge low cap
//----------------------------------------------------------------------------
void BAT1CheckDisChargeLow(void)
{
    if(IS_MASK_SET(BT1_STATUS2,bat_DC_OK))
    {

    }
}

//----------------------------------------------------------------------------
// Battery 1 abnormal
//----------------------------------------------------------------------------
void BAT1SetFail(void)
{
    if(DisableCharger()==0x01)          // Disable charger first, then go to BAT_Step_Fail step
    {
        BAT1_PlugOutClrVariables();
        SetBAT1CtrlStep(BAT_Step_Fail);
    }
}

//----------------------------------------------------------------------------
// Force charge Battery 1
//----------------------------------------------------------------------------
void BAT1ForceCharge(void)
{

}

//----------------------------------------------------------------------------
// Force discharge Battery 1
//----------------------------------------------------------------------------
void BAT1ForceDischarge(void)
{

}

//----------------------------------------------------------------------------
// Battery 1 in auto learning
//----------------------------------------------------------------------------
void BAT1AutoLearning(void)
{

}

//----------------------------------------------------------------------------
// Check Battery 1 force charge / force discharge / auto learning
//----------------------------------------------------------------------------
void BAT1ForceStep(void)
{
    if(IS_MASK_SET(BT1_STATUS3, bat_ForceChg))
    {
        if(IS_MASK_SET(POWER_FLAG1, adapter_in))
        {
            if(IS_MASK_SET(BT1_STATUS1, bat_Dischg))
            {
                SetBAT1CtrlStep(BAT_Step_PC);           // Go to Pre-Charge
            }
        }
    }
    else if(IS_MASK_SET(BT1_STATUS3, bat_ForceDischg))
    {
        if(IS_MASK_SET(POWER_FLAG1, adapter_in))
        {
            if(IS_MASK_SET(BT1_STATUS1, bat_InCharge))
            {
                SetBAT1CtrlStep(BAT_Step_DC);           // Go to Discharge
            }
        }
    }
    else if(IS_MASK_SET(BT1_STATUS3, bat_AL))
    {

    }   
}

//----------------------------------------------------------------------------
// The function of main battery control center  (10ms timer base)
//----------------------------------------------------------------------------
void Battey1ControlCenter(void) 
{
    if(IS_MASK_CLEAR(BT1_STATUS1, bat_in))  // If battery 1 isn't exit, return function.
    {
        return;             
    }

	if(IS_MASK_SET(BT1_STATUS1, bat_valid)) // If battery 1 identify OK
	{
		BAT1_1SecTimer++;
		if(BAT1_1SecTimer>100)      // 1 sec
		{
			BAT1_1SecTimer = 0x00;
		    PollingBAT1Data();      // Polling battery 1 data every 1sec
            BAT1Protection();       // Check battery normal or abnormal every 1sec
		}

        BAT1ForceStep();            // Check Battery 1 force charge / force discharge / auto learning
        
        if(IS_MASK_SET(POWER_FLAG1, adapter_in))
        {
            BAT1_CheckFullyCharged();   // Check battery fully charged or not
        }
        else
        {
            BAT1_CheckFullyDisCharged();// Check battery fully discharged or not
        }
	}

	switch(BAT1_CtrlStep)           // Battery 1 control step
	{
		case BAT_Step_ID:           // Identify main battery
			IdentifyBAT1();
			break;	
    
		case BAT_Step_WC:           // Battery wake up charge
            BAT1WakeUpCharge();
			break;

        case BAT_Step_PC:           // Battery pre-charge
            BAT1_PreCharge();
            break;

        case BAT_Step_NC:           // Battery normal charge
            BAT1_NormalCharge();    
            break;            
				
		case BAT_Step_DC:           // Battery discharge       
		    BAT1DisCharge();
            BAT1CheckDisChargeLow();
			break;

        case BAT_Step_FullyChg:     // Battery fully charged
            BAT1FullyCharged();
            break;

        case BAT_Step_FullyDisChg:  // Battery fully discharged
            BAT1FullyDisharged();
            break;

        case BAT_Step_SetFail:      // Battery abnormal
            BAT1SetFail();
            break;

        case BAT_Step_Fail:         // Battery abnormal need main battery plug-out to reset
			break;     

        case BAT_Step_ForceDC:      // Battery force discharge
            BAT1ForceDischarge();
            break;

        case BAT_Step_ForceC:       // Battery force charge
            BAT1ForceCharge();
            break;            

        case BAT_Step_AutoLN:       // Battery auot learning
            BAT1AutoLearning();
            break; 
            
        case BAT_Step_ChargerFail:  // Smart charger abnormal
            break;

		case BAT_Step_Out:          // Battery plug out
			break;
            
		default:                    // Unknow step
			break;
	}
}

//****************************************************************************
// The function of smart charger
//****************************************************************************
//----------------------------------------------------------------------------
// The function of setting charger CC CV IC 
// return : 
//          0 : charger setting OK
//          !=0 charger setting fail
//----------------------------------------------------------------------------
BYTE SetSmartCharger(void)
{   //if return 0,it represent as battery will enter charging success.
    BYTE doneindex;
    doneindex = 0x00;

    if(!bRWSMBus(SmartChargerChannel, SMbusWW, Charger_Addr, C_InputCurrent, &INPUT_CURRENT_LO, SMBus_NoPEC))
    {
        doneindex++;    //SMBUS fail to set input current
    }
    if(!bRWSMBus(SmartChargerChannel, SMbusWW, Charger_Addr, C_ChargeVoltage, &CHARGE_VOLTAGE_LO, SMBus_NoPEC))
    {
        doneindex++;    //SMBUS fail to set charge voltage
    }
    if(!bRWSMBus(SmartChargerChannel, SMbusWW, Charger_Addr, C_ChargeCurrent, &CHARGE_CURRENT_LO, SMBus_NoPEC))  
    {
        doneindex++;    //SMBUS fail to set charge current
    }
    return(doneindex); 
}

//----------------------------------------------------------------------------
// The function of disable charger
// return
//  0 : disable charger fail
//  1 : disable charger OK
//----------------------------------------------------------------------------
BYTE DisableCharger(void)
{
    BYTE result;
    result = 0x00;
    if(SmartCharger_Support)
    {
        CHARGE_CURRENT_LO=00;
	    CHARGE_CURRENT_HI=00;
	    CHARGE_VOLTAGE_LO=00;
	    CHARGE_VOLTAGE_HI=00;
	    INPUT_CURRENT_LO=00;
	    INPUT_CURRENT_HI=00; 
        if(SetSmartCharger()!=0x00)
        {
            Charger_TimeOut++;
            if(Charger_TimeOut>ChargerSettingTimeOut)
            {
                SetBAT1CtrlStep(BAT_Step_ChargerFail);  // Go to smart charger fail
            }
            result = 0x00;
        }
        else
        {                
            if(IS_MASK_SET(POWER_FLAG1, adapter_in))    // AC mode disable charger
            {
                if(IS_MASK_SET(BT1_STATUS3, bat_ForceDischg))
                {
                    Hook_BAT1_ChargePinON(0);
                }
                else
                {
                    Hook_BAT1_ChargePinON(1);
                }
            }
            else
            {
                Hook_BAT1_ChargePinON(0);
                SET_MASK(BT1_STATUS2, bat_DC_OK);       // DC mode disable charger
                SET_MASK(BT1_STATUS1, bat_Dischg);
            }
            Charger_TimeOut = 0x00;
            result = 0x01;
        }
    }
    else
    {
        // *** Set DAC CC CV value here ***
        if(IS_MASK_SET(POWER_FLAG1, adapter_in))    // AC mode disable charger
        {
            if(IS_MASK_SET(BT1_STATUS3, bat_ForceDischg))
            {
                Hook_BAT1_ChargePinON(0);
            }
            else
            {
                Hook_BAT1_ChargePinON(1);
            }
        }
        else                                        // DC mode disable charger
        {
            Hook_BAT1_ChargePinON(0);
            SET_MASK(BT1_STATUS2, bat_DC_OK);
            SET_MASK(BT1_STATUS1, bat_Dischg);
        }
        result = 0x01;
    }	    
    return(result);
}
