/*----------------------------------------------------------------------------
 * Filename: OEM_SMBus.C  For Chipset: ITE.IT85XX
 *
 * Function: The interrupt service method of SMBus function
 *
 * Author  : Dino
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * You may not present,reproduce,distribute,publish,display,modify,adapt,
 * perform,transmit,broadcast,recite,release,license or otherwise exploit
 * any part of this publication in any form,by any means,without the prior
 * written permission of ITE Tech. Inc.	
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// [rblk_bcis] the byte count of read smbus read block protocol
//----------------------------------------------------------------------------
void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc)
{
    SMB_BCNT = rblk_bc;      // For ACPI SMBus EC SMB1 Block Count register
}

//----------------------------------------------------------------------------
// Read thermal sensor OK
//----------------------------------------------------------------------------
void Hook_PollThermal(void)
{

}

//----------------------------------------------------------------------------
// Read thermal sensor fail
//----------------------------------------------------------------------------
void Error_PollThermal(void)
{

}

//----------------------------------------------------------------------------
// For SMBus utility only
//----------------------------------------------------------------------------
void Hook_SMBDebug(void)
{
	DB_SMBusAck1=ACK_Done;			// Transmission done ACK
	DB_SMBusAddr=0x00;
}

void Error_SMBDebug(void)
{
	DB_SMBusAck1=ACK_Error;			// Transmission error ACK
	DB_SMBusAddr=0x00;
}

//----------------------------------------------------------------------------
// Polling batter 1 data OK
//----------------------------------------------------------------------------
void BAT1_Read_OK(void)
{

}

//----------------------------------------------------------------------------
// Polling batter 1 data Fail
//----------------------------------------------------------------------------
void BAT1_Read_Fail(void)
{

}

//----------------------------------------------------------------------------
// SMBus channel table
//----------------------------------------------------------------------------
const sSCS code asSCS1[] = 
{
	// For SMBus channel 1 debug
	// SMBus protocol	Addr	Cmd		Data address	active flag and variable										byte cunt                       
 	{ Cmd_RecvByte,		0x01,	0xFF,	&DB_SMBusData,	DB_R,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	
 	{ Cmd_SendByte,		0x01,	0xFF,	&DB_SMBusData,	DB_S,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadByte,		0x01,	0xFF,	&DB_SMBusData,	DB_RB,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	
 	{ Cmd_WriteByte,	0x01,	0xFF,	&DB_SMBusData,	DB_WB,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadWord,		0x01,	0xFF,	&DB_SMBusData,	DB_RW,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_WriteWord,	0x01,	0xFF,	&DB_SMBusData,	DB_WW,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadBlock,	0x01,	0xFF,	&DB_SMBusData,	DB_RBB,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_WriteBlock,	0x01,	0xFF,	&DB_SMBusData,	DB_WBB,	&DB_SMBusFlag1,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	

	{ Cmd_ReadByte,		SmartBat_Addr,		BATCmd_RSOC,	    &BAT1_RSOC,         B1_RSOC,	&SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00    },
	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_current,	    &BAT1_current_L,    B1_C,		&SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},
 	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_volt,	    &BAT1_volt_L,	    B1_V,		&SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},
	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_RMcap,	    &BAT1_RMcap_L,	    B1_RMcap,   &SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},	
	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_BatStatus,   &BAT1_ALARM1,		B1_Status,  &SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},	
	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_FCcap,	    &BAT1_FCcap_L,	    B1_FCC,	    &SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},	
	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_temp,	    &BAT1_temp_L,	    B1_Temp,	&SMBus1Flag1,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},	
    { Cmd_ReadWord,		SmartBat_Addr,		BATCmd_CC, 	        &BAT1_CC_L,			B1_CC,	    &SMBus1Flag2,	BAT1_Read_OK,   BAT1_Read_Fail, 0x00	},	
	{ Cmd_ReadWord,		SmartBat_Addr,		BATCmd_CV, 	        &BAT1_CV_L,			B1_CV,	    &SMBus1Flag2,	BAT1_Read_OK,	BAT1_Read_Fail, 0x00	},
};

//----------------------------------------------------------------------------
// SMBus channe2 table
//----------------------------------------------------------------------------
const sSCS code asSCS2[] = 
{	
	// For SMBus channel 2 debug
	// SMBus protocol	Addr	Cmd		Data address	active flag and variable										byte cunt     
 	{ Cmd_RecvByte,		0x01,	0xFF,	&DB_SMBusData,	DB_R,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	
 	{ Cmd_SendByte,		0x01,	0xFF,	&DB_SMBusData,	DB_S,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadByte,		0x01,	0xFF,	&DB_SMBusData,	DB_RB,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	
 	{ Cmd_WriteByte,	0x01,	0xFF,	&DB_SMBusData,	DB_WB,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadWord,		0x01,	0xFF,	&DB_SMBusData,	DB_RW,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_WriteWord,	0x01,	0xFF,	&DB_SMBusData,	DB_WW,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadBlock,	0x01,	0xFF,	&DB_SMBusData,	DB_RBB,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_WriteBlock,	0x01,	0xFF,	&DB_SMBusData,	DB_WBB,	&DB_SMBusFlag2,	Hook_SMBDebug,	Error_SMBDebug,	0x00},

	// OEM SMBus2 function
    { Cmd_ReadByte, ThermalAddr,    RemoteCmd,  &TCPU_temp, PollRemote,	&SMBus2Flag1,	Hook_PollThermal,	Error_PollThermal,	0x00	},
    { Cmd_ReadByte, ThermalAddr,    LocalCmd,   &TSys_temp, PollLocal,	&SMBus2Flag1,	Hook_PollThermal,	Error_PollThermal,	0x00	},
};

//----------------------------------------------------------------------------
// SMBus channe2 table
//----------------------------------------------------------------------------
const sSCS code asSCS3[] = 
{	
	// For SMBus channel 3 debug
	// SMBus protocol	Addr	Cmd		Data address	active flag and variable									byte cunt     
 	{ Cmd_RecvByte,	0x01,	0xFF,	&DB_SMBusData,	DB_R,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	
 	{ Cmd_SendByte,	0x01,	0xFF,	&DB_SMBusData,	DB_S,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadByte,	0x01,	0xFF,	&DB_SMBusData,	DB_RB,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},	
 	{ Cmd_WriteByte,0x01,	0xFF,	&DB_SMBusData,	DB_WB,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadWord,	0x01,	0xFF,	&DB_SMBusData,	DB_RW,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_WriteWord,0x01,	0xFF,	&DB_SMBusData,	DB_WW,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_ReadBlock,0x01,	0xFF,	&DB_SMBusData,	DB_RBB,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},
 	{ Cmd_WriteBlock,0x01,	0xFF,	&DB_SMBusData,	DB_WBB,	&DB_SMBusFlag3,	Hook_SMBDebug,	Error_SMBDebug,	0x00},

	// OEM SMBus3 function
	
};

//----------------------------------------------------------------------------
// To clear SMBus channel 1 variables
//----------------------------------------------------------------------------
void ClearSMBus1Variables(void)
{

}

//----------------------------------------------------------------------------
// To clear SMBus channel 2 variables
//----------------------------------------------------------------------------
void ClearSMBus2Variables(void)
{

}

//----------------------------------------------------------------------------
// To clear SMBus channel 3 variables
//----------------------------------------------------------------------------
void ClearSMBus3Variables(void)
{

}

//----------------------------------------------------------------------------
// SMBus Center Variables
//----------------------------------------------------------------------------
const sSSC code asSSC[] = 
{	   
 	{   &SMBus1index,  &SMBus1counter,	&SMBus1ByteCunt, &SMBus1InUsing,  &SMBus1TableSize, &F_Service_SMBus1,   service_smbus1  },	
 	{   &SMBus2index,  &SMBus2counter,	&SMBus2ByteCunt, &SMBus2InUsing,  &SMBus2TableSize, &F_Service_SMBus2,   service_smbus2  },
 	{   &SMBus3index,  &SMBus3counter,	&SMBus3ByteCunt, &SMBus3InUsing,  &SMBus3TableSize, &F_Service_SMBus3,   service_smbus3  },	
};

//----------------------------------------------------------------------------
// To calculate smbus table size.
//----------------------------------------------------------------------------
void CheckSMBusTableSize(void)
{
    SMBus1TableSize = (sizeof(asSCS1)/sizeof(sSCS));
    SMBus2TableSize = (sizeof(asSCS2)/sizeof(sSCS));
    SMBus3TableSize = (sizeof(asSCS3)/sizeof(sSCS));
}

//----------------------------------------------------------------------------
// To service SMBus 
//----------------------------------------------------------------------------
void ServiceSMBus(void)
{
    if(F_Service_SMBus1==SMBus_NeedService)
    {
        F_Service_SMBus1=SMBus_ClearService;
        service_smbus1();
    }

    if(F_Service_SMBus2==SMBus_NeedService)
    {
        F_Service_SMBus2=SMBus_ClearService;
        service_smbus2();
    }

    if(F_Service_SMBus3==SMBus_NeedService)
    {
        F_Service_SMBus3=SMBus_ClearService;
        service_smbus3();
    }
}

//#pragma OT(8, SPEED)
//----------------------------------------------------------------------------
// SMBus channelx service function
//----------------------------------------------------------------------------
void SMBusCenterSelection(BYTE channel) 
{
    XBYTE tempSMBusindex;
    BYTE smbus_cmd;
    BYTE smbus_address;
    XBYTE *smbus_data;
    BYTE smbus_Bcunt;
    BYTE smbus_flag;
    BYTE smbus_protocol;
    
    tempSMBusindex = *asSSC[channel].index;
    
	if(*asSSC[channel].inusing !=0x00)
	{
        //if(*asSSC[channel].serviceflag !=0x00)
        //{
        //    *asSSC[channel].serviceflag =0x00;
        //    (asSSC[channel].servicefunc)();
        //}
        //else
		//{
            (*asSSC[channel].timeout)++;
			if((*asSSC[channel].timeout) > 50) // TotalSMBusChannel x 50 ms
			{
     		    //if((*asSMBus[channel].SMBusSTA & (HOSTA_BSER+HOSTA_FAIL) )!=0x00)
     		    //{
        	    ResetSMBus(channel);
     		    //}
                //else
                //{
                //    *asSMBus[channel].SMBusSTA=0xFE;    // clear bits
                //}
                
			    //**********************************************************************
                //
                //**********************************************************************
                switch(channel)                 // Channel selection.
                {
                    case SMbusCh1:              // Channel 1
                        CLEAR_MASK(*asSCS1[tempSMBusindex].ConditionVar, asSCS1[tempSMBusindex].Conditionflag);
				        (asSCS1[tempSMBusindex].errorfunc)();
                        break;
                        
                    case SMbusCh2:              // Channel 2
                        CLEAR_MASK(*asSCS2[tempSMBusindex].ConditionVar, asSCS2[tempSMBusindex].Conditionflag);
				        (asSCS2[tempSMBusindex].errorfunc)();
                        break;

                    case SMbusCh3:              // Channel 3
                        CLEAR_MASK(*asSCS3[tempSMBusindex].ConditionVar, asSCS3[tempSMBusindex].Conditionflag);
				        (asSCS3[tempSMBusindex].errorfunc)();
                        break;                        
                }
                //**********************************************************************
                //
                //**********************************************************************
                
                *asSSC[channel].inusing = 0x00;
                
				tempSMBusindex++;
                if(tempSMBusindex >= *asSSC[channel].tablesize)
			    {
                    tempSMBusindex=0x00;
			    }
			}
		//}
        *asSSC[channel].index = tempSMBusindex;
	}
	else
	{
        *asSSC[channel].timeout = 0x00; // Clear time-out flag.
        smbus_flag = 0x00;              // Pre-clear need service flag.

        //**********************************************************************
        //
        //**********************************************************************
        switch(channel)                 // Channel selection.
        {
            case SMbusCh1:              // Channel 1
                if(IS_MASK_SET(*asSCS1[tempSMBusindex].ConditionVar, asSCS1[tempSMBusindex].Conditionflag))
                {
                    smbus_flag=0x01;    // Need service.
                }
                break;

            case SMbusCh2:              // Channel 2
                if(IS_MASK_SET(*asSCS2[tempSMBusindex].ConditionVar, asSCS2[tempSMBusindex].Conditionflag))
                {
                    smbus_flag=0x01;    // Need service.
                }
                break;

            case SMbusCh3:              // Channel 3
                if(IS_MASK_SET(*asSCS3[tempSMBusindex].ConditionVar, asSCS3[tempSMBusindex].Conditionflag))
                {
                    smbus_flag=0x01;    // Need service.
                }
                break;

                default:
                    break;
        }
        //**********************************************************************
        //
        //**********************************************************************

		if(smbus_flag==0x00)            // Don't need service.
	    {
			tempSMBusindex++;           // next step.

            if(tempSMBusindex >= *asSSC[channel].tablesize)
			{
                tempSMBusindex=0x00;
			}
            *asSSC[channel].index = tempSMBusindex;
	    }
	    else
	    {	
            *asSSC[channel].inusing = 0x01;
            
			*asSMBus[channel].SMBusCTL=0x00;	// stop transaction
			*asSMBus[channel].SMBusSTA=0xFE;    // clear bits

            //**********************************************************************
            //
            //**********************************************************************
            switch(channel)             // Channel selection.
            {
                case SMbusCh1:
                    smbus_protocol = asSCS1[tempSMBusindex].protocol;
                    smbus_cmd = asSCS1[tempSMBusindex].cmd;
                    smbus_address = asSCS1[tempSMBusindex].address;
                    smbus_data = asSCS1[tempSMBusindex].smbdata;
                    smbus_Bcunt = asSCS1[tempSMBusindex].Bcunt;
                    if(smbus_protocol==Cmd_WriteBlock)
                    {
					    if(smbus_address==0x01)
					    {
						    SMBus1BlockPtr = &DB_SMBusData[0];
						    *asSMBus[channel].SMBusBData = *SMBus1BlockPtr;
					    }					
					    else
					    {
						    SMBus1BlockPtr = asSCS1[tempSMBusindex].smbdata;
						    *asSMBus[channel].SMBusBData = *SMBus1BlockPtr;
					    }
                    }
                    break;

                case SMbusCh2:
                    smbus_protocol = asSCS2[tempSMBusindex].protocol;
                    smbus_cmd = asSCS2[tempSMBusindex].cmd;
                    smbus_address = asSCS2[tempSMBusindex].address;
                    smbus_data = asSCS2[tempSMBusindex].smbdata;
                    smbus_Bcunt = asSCS2[tempSMBusindex].Bcunt;
                    if(smbus_protocol==Cmd_WriteBlock)
                    {
					    if(smbus_address==0x01)
					    {
						    SMBus2BlockPtr = &DB_SMBusData[0];
						    *asSMBus[channel].SMBusBData = *SMBus2BlockPtr;
					    }					
					    else
					    {
						    SMBus2BlockPtr = asSCS2[tempSMBusindex].smbdata;
						    *asSMBus[channel].SMBusBData = *SMBus2BlockPtr;
					    }
                    }
                    break;

                case SMbusCh3:
                    smbus_protocol = asSCS3[tempSMBusindex].protocol;
                    smbus_cmd = asSCS3[tempSMBusindex].cmd;
                    smbus_address = asSCS3[tempSMBusindex].address;
                    smbus_data = asSCS3[tempSMBusindex].smbdata;
                    smbus_Bcunt = asSCS3[tempSMBusindex].Bcunt;
                    if(smbus_protocol==Cmd_WriteBlock)
                    {
					    if(smbus_address==0x01)
					    {
						    SMBus3BlockPtr = &DB_SMBusData[0];
						    *asSMBus[channel].SMBusBData = *SMBus3BlockPtr;
					    }					
					    else
					    {
						    SMBus3BlockPtr = asSCS3[tempSMBusindex].smbdata;
						    *asSMBus[channel].SMBusBData = *SMBus3BlockPtr;
					    }
                    }
                    break;

                default:
                    break;
            }
            //**********************************************************************
            //
            //**********************************************************************

			switch(smbus_protocol)
			{
				case Cmd_Quick:
					break;
					
				case Cmd_SendByte:
					if(smbus_address==0x01)     // Debug mode, for SMBus utility
					{
						PollSMBusSendByte(channel,DB_SMBusAddr,DB_SMBusCmd);
					}
					else
					{
						PollSMBusSendByte(channel,smbus_address,smbus_cmd);
					}
					break;	
					
				case Cmd_RecvByte:
					if(smbus_address==0x01)     // Debug mode, for SMBus utility
					{
						PollSMBusReceiveByte(channel,DB_SMBusAddr);
					}
					else
					{
						PollSMBusReceiveByte(channel,smbus_address);
					}
					break;
					
				case Cmd_ReadByte:
					if(smbus_address==0x01)     // Debug mode, for SMBus utility
					{
						PollReadSMBusByte(channel,DB_SMBusAddr,DB_SMBusCmd);
					}
					else
					{
						PollReadSMBusByte(channel,smbus_address,smbus_cmd);
					}
					break;
					
				case Cmd_WriteByte:
					if(smbus_address==0x01)     // Debug mode, for SMBus utility
					{
						PollWriteSMBusByte(channel,DB_SMBusAddr,DB_SMBusCmd,DB_SMBusData[0]);
					}
					else
					{
						PollWriteSMBusByte(channel,smbus_address,smbus_cmd,*smbus_data);
					}
					break;
					
				case Cmd_ReadWord:
					if(smbus_address==0x01)     // Debug mode, for SMBus utility
					{
						PollReadSMBusWord(channel,DB_SMBusAddr,DB_SMBusCmd);
					}
					else
					{
						PollReadSMBusWord(channel,smbus_address,smbus_cmd);
					}
					break;
					
				case Cmd_WriteWord:
					if(smbus_address==0x01)     // Debug mode, for SMBus utility
					{
						PollWriteSMBusWord(channel,DB_SMBusAddr,DB_SMBusCmd,DB_SMBusData[0],DB_SMBusData[1]);
					}
					else
					{
						Tmp_XPntr = smbus_data;
						Tmp_XPntr1 = Tmp_XPntr+1;
						PollWriteSMBusWord(channel,smbus_address,smbus_cmd,*Tmp_XPntr,*Tmp_XPntr1);
					}
					break;

				case Cmd_ReadBlock:             // Debug mode, for SMBus utility
					*asSSC[channel].bytecount = 0x00;
					if(smbus_address==0x01)
					{
						DB_SMBusBCunt = 0x00;
						PollReadSMBusBlock(channel,DB_SMBusAddr,DB_SMBusCmd);
					}					
					else
					{
						PollReadSMBusBlock(channel,smbus_address,smbus_cmd);
					}
					break;
					
				case Cmd_WriteBlock:            // Debug mode, for SMBus utility
					if(smbus_address==0x01)
					{
                        *asSSC[channel].bytecount = DB_SMBusBCunt;
						PollWriteSMBusBlock(channel,DB_SMBusAddr,DB_SMBusCmd,DB_SMBusBCunt);
					}					
					else
					{
                        *asSSC[channel].bytecount = smbus_Bcunt;
						PollWriteSMBusBlock(channel,smbus_address,smbus_cmd,smbus_Bcunt);
					}
					break;					
					
				default:
                    *asSSC[channel].inusing=0x00;
					break;					
			}
	    }
	}
}

//----------------------------------------------------------------------------
// SMBus service center
//----------------------------------------------------------------------------
void SMBusCenter(void) 
{
    if(++SMBusSelection >= TotalSMBusChannel)
    {
        SMBusSelection=0x00;
    }
    SMBusCenterSelection(SMBusSelection);
}

//----------------------------------------------------------------------------
// Wait SMBus channel x free.
//----------------------------------------------------------------------------
void WatiSMBusCHxFree(BYTE channel)
{
    BYTE tempSMBusindex;
    
    TR1 = 0;                        // Disable timer 1
    ET1 = 0;			            // Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_30ms>>8;	        // set timer1 counter 30 ms 
    TL1 = Timer_30ms;		        // set timer1 counter 30 ms
    TF1 = 0;			            // clear overflow flag
    TR1 = 1;			            // enable timer1	

    tempSMBusindex = *asSSC[channel].index;

	while(*asSSC[channel].inusing !=0x00)
	{
		if((*asSSC[channel].serviceflag == SMBus_NeedService)||
            (IS_MASK_SET(*asSMBus[channel].SMBusIER, asSMBus[channel].IERFlag)&&IS_MASK_SET(*asSMBus[channel].SMBusISR, asSMBus[channel].IERFlag)))
        {
            CLEAR_MASK(*asSMBus[channel].SMBusIER, asSMBus[channel].IERFlag);
            *asSMBus[channel].SMBusISR = asSMBus[channel].IERFlag;
            *asSSC[channel].serviceflag = SMBus_ClearService;
            (asSSC[channel].servicefunc)();
		}
	    else
	    {
			if(TF1)
			{
     		    //if((*asSMBus[channel].SMBusSTA & (HOSTA_BSER+HOSTA_FAIL) )!=0x00)
     		    //{
        	    ResetSMBus(channel);
     		    //}
                //else
                //{
                //    *asSMBus[channel].SMBusSTA=0xFE;    // clear bits
                //}

                //**********************************************************************
                //
                //**********************************************************************
                switch(channel)                 // Channel selection.
                {
                    case SMbusCh1:              // Channel 1
                        CLEAR_MASK(*asSCS1[tempSMBusindex].ConditionVar, asSCS1[tempSMBusindex].Conditionflag);
				        (asSCS1[tempSMBusindex].errorfunc)();
                        break;
                        
                    case SMbusCh2:              // Channel 2
                        CLEAR_MASK(*asSCS2[tempSMBusindex].ConditionVar, asSCS2[tempSMBusindex].Conditionflag);
				        (asSCS2[tempSMBusindex].errorfunc)();
                        break;

                    case SMbusCh3:              // Channel 3
                        CLEAR_MASK(*asSCS3[tempSMBusindex].ConditionVar, asSCS3[tempSMBusindex].Conditionflag);
				        (asSCS3[tempSMBusindex].errorfunc)();
                        break;                        
                }
                //**********************************************************************
                //
                //**********************************************************************
                
                *asSSC[channel].inusing = 0x00;
				tempSMBusindex++;
                if(tempSMBusindex >= *asSSC[channel].tablesize)
			    {
                    tempSMBusindex=0x00;
			    }
                *asSSC[channel].index = tempSMBusindex;
				break;
			}
	    }
	}
    
    TR1 = 0;			    // disable timer1
    TF1 = 0;			    // clear overflow flag
    ET1 = 1;			    // Enable timer1 interrupt
}

#ifdef SMBusChannel4Support
//----------------------------------------------------------------
//Function: Enable SMBus channel 4
//----------------------------------------------------------------
void InitSMBusChannel4(void)
{
    GPCRH1 = ALT;       // SMBCLK3
    GPCRH2 = ALT;       // SMBDAT3
    GCR2 |= SMB4E;      // SMBus Channel 4 Enable.
}
#endif

//----------------------------------------------------------------------------
// 	
//----------------------------------------------------------------------------
void InitSMBus(void)
{
	DB_SMBusAddr=0x00;
	DB_SMBusFlag1=0x00;						
	DB_SMBusFlag2=0x00;			
	DB_SMBusFlag3=0x00;					

	DB_SMBusAck1=0x00;					
	DB_SMBusACDID=0x00;	

    CheckSMBusTableSize();
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollSMBusReceiveByte(BYTE Channel,BYTE Addr)
{	
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 
	    *asSMBus[Channel].SMBusADR=Addr|0x01;	// set address with reading bit	
	    //*asSMBus[Channel].SMBusSTA=0xFE;		// clear bits
	    *asSMBus[Channel].SMBusCTL=(SMbusSRB|HOCTL_SRT|HOCTL_INTREN);   // Start transaction
    }
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollSMBusSendByte(BYTE Channel,BYTE Addr,BYTE cmd)
{	
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 
	    *asSMBus[Channel].SMBusADR=Addr&0xFE;;	// set address with reading bit						
	    *asSMBus[Channel].SMBusCMD=cmd;		// Set data
	    //*asSMBus[Channel].SMBusSTA=0xFE;		// clear bits
	    *asSMBus[Channel].SMBusCTL=(SMbusSRB|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollReadSMBusByte(BYTE Channel,BYTE Addr,BYTE Comd)
{
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {  
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 
	    *asSMBus[Channel].SMBusADR=Addr|0x01;	// set address with reading bit						
	    *asSMBus[Channel].SMBusCMD=Comd;		// Set command
	    //*asSMBus[Channel].SMBusSTA=0xFE;		// clear bits
	    *asSMBus[Channel].SMBusCTL=(SMbusRWB|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollWriteSMBusByte(BYTE Channel,BYTE Addr,BYTE Comd,BYTE data1)
{
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {   
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 	
	    *asSMBus[Channel].SMBusData0=data1;
	    *asSMBus[Channel].SMBusADR=Addr&0xFE;	// set address with reading bit						
	    *asSMBus[Channel].SMBusCMD=Comd;		// Set command
	    //*asSMBus[Channel].SMBusSTA=0xFE;		// clear bits
	    *asSMBus[Channel].SMBusCTL=(SMbusRWB|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollReadSMBusWord(BYTE Channel,BYTE Addr,BYTE Comd)
{
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.    
    }
    else
    {
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 
	    *asSMBus[Channel].SMBusADR=Addr|0x01;	// set address with reading bit						
	    *asSMBus[Channel].SMBusCMD=Comd;		// Set command
	    //*asSMBus[Channel].SMBusSTA=0xFE;		// clear bits
	    *asSMBus[Channel].SMBusCTL=(SMbusRWW|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollWriteSMBusWord(BYTE Channel,BYTE Addr,BYTE Comd,BYTE data1,BYTE data2)
{
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 	
	    *asSMBus[Channel].SMBusData0=data1;
	    *asSMBus[Channel].SMBusData1=data2;
	    *asSMBus[Channel].SMBusADR=Addr&0xFE;	// set address with reading bit						
	    *asSMBus[Channel].SMBusCMD=Comd;		// Set command
	    //*asSMBus[Channel].SMBusSTA=0xFE;		// clear bits
	    *asSMBus[Channel].SMBusCTL=(SMbusRWW|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollReadSMBusBlock(BYTE Channel,BYTE Addr,BYTE Comd)
{
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 
	    *asSMBus[Channel].SMBusADR=Addr|0x01;	// set address with reading bit	
	    *asSMBus[Channel].SMBusCMD=Comd;		// Set command
	    *asSMBus[Channel].SMBusCTL=(SMbusRWBB|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}	

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void PollWriteSMBusBlock(BYTE Channel,BYTE Addr,BYTE Comd,BYTE ByteCunt)
{
    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Table)==SMBus_CanNotUse)
    {
        *asSSC[Channel].inusing=0x00;       // SMBus interface can't be used.                           
    }
    else
    {   
	    *asSMBus[Channel].SMBusIER|=asSMBus[Channel].IERFlag; // Enable interrupt 	
	    *asSMBus[Channel].SMBusData0=ByteCunt;	// set byte count
	    *asSMBus[Channel].SMBusADR=Addr&0xFE;	// set address with reading bit	
	    *asSMBus[Channel].SMBusCMD=Comd;		// Set command
	    *asSMBus[Channel].SMBusCTL=(SMbusRWBB|HOCTL_SRT|HOCTL_INTREN);	// Start transaction
    }
}

//----------------------------------------------------------------------------
// SMBus channel 1 service function
//----------------------------------------------------------------------------
void service_smbus1(void) 
{
	if(SMBus1InUsing)
	{
        CLEAR_MASK(SMBusXStatus, (SMBus1_OK+SMBus1_Fail));
        
        if(IS_MASK_SET(HOSTA_A, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))  // any error
        {
            if(IS_MASK_SET(HOSTA_A, (HOSTA_BSER+HOSTA_FAIL)))
            {
                ResetSMBus(SMbusCh1);               // Reset SMBus
            }
            SET_MASK(SMBusXStatus, SMBus1_Fail);    // SMBus fail
        }
        else                                        // Byte Done Status or Finish Interrupt or no any statys bit
        {
            //*********************************************************************
            // Cmd_ReadBlock
            //*********************************************************************
		    if(asSCS1[SMBus1index].protocol==Cmd_ReadBlock)
		    {                                   
                if(IS_MASK_SET(HOSTA_A, (HOSTA_FINTR+HOSTA_BDS)))   // Only Byte Done Status or Finish Interrupt bit is set.
                {
		            if(SMBus1ByteCunt==0x00)
			        {
				        SMBus1BlockPtr = asSCS1[SMBus1index].smbdata;
				        SMBus1ByteCunt = D0REG_A;

				        if(SMBus1ByteCunt>32)
				        {
					        SMBus1ByteCunt=32;	    // DB_SMBusData[] max 32 bytes
				        }
							
				        SMB_BCNT = SMBus1ByteCunt;
				        DB_SMBusBCunt = SMBus1ByteCunt;
							
				        *SMBus1BlockPtr = HOBDB_A;  // read data1
				        SMBus1ByteCunt--;
		            }
			        else
			        {
				        SMBus1BlockPtr++;
				        *SMBus1BlockPtr=HOBDB_A;
				        SMBus1ByteCunt--;
				        if(SMBus1ByteCunt==0x01)
				        {
					        SET_MASK(HOCTL_A,HOCTL_LABY);
				        }
			        }
					
			        if(SMBus1ByteCunt!=0x00)                // Byte count isn't 0.
			        {
				        HOSTA_A=0xFE;
				        SET_MASK(IER1,Int_SMBUS0);
			        }
                    else                                    // Byte count is 0.
                    {
				        CLEAR_MASK(HOCTL_A,HOCTL_LABY);
                        SET_MASK(SMBusXStatus, SMBus1_OK);  // SMBus protocol OK
                    }
                }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus1_Fail);    // SMBus fail
                }
		    }
	        //*********************************************************************
            // Cmd_WriteBlock
            //*********************************************************************
		    else if(asSCS1[SMBus1index].protocol==Cmd_WriteBlock)
		    {
			    if(IS_MASK_SET(HOSTA_A, (HOSTA_FINTR+HOSTA_BDS)))   // Only Byte Done Status or Finish Interrupt bit is set.
			    {
					SMBus1ByteCunt--;
					if(SMBus1ByteCunt==0x00)
					{
						SET_MASK(SMBusXStatus, SMBus1_OK);  // SMBus protocol OK
					}
					else  
					{
						SMBus1BlockPtr++;
						HOBDB_A=*SMBus1BlockPtr;
						
						HOSTA_A=0xFE;
						SET_MASK(IER1,Int_SMBUS0);
					}
			    }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus1_Fail);    // SMBus fail
                }
		    }
		    //******************************************************************************************
	        // Cmd_SendByte, Cmd_RecvByte, Cmd_ReadByte, Cmd_WriteByte, Cmd_ReadWord and Cmd_WriteWord 
	        //******************************************************************************************
		    else
		    {
                if(IS_MASK_SET(HOSTA_A, HOSTA_FINTR))       // Only Finish Interrupt bit is set.
                {
		            *asSCS1[SMBus1index].smbdata = D0REG_A; // read data byte 1
			        if(asSCS1[SMBus1index].protocol==Cmd_ReadWord)  // read word protocol
			        {
				        Tmp_XPntr = asSCS1[SMBus1index].smbdata;
				        Tmp_XPntr++;
				        *Tmp_XPntr=D1REG_A;                 // read data byte 2
			        }
                    SET_MASK(SMBusXStatus, SMBus1_OK);      // SMBus protocol OK
                }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus1_Fail);    // SMBus protocol Fail
                }
		    }
		}
	}

    if(IS_MASK_SET(SMBusXStatus, (SMBus1_Fail+SMBus1_OK)))  // SMBus protocol Fail or OK
    {
        HOSTA_A=0xFE;                               // Clear Host Status register.
	    SMBus1InUsing = 0;                          // Clear smbus in used flag.
        CLEAR_MASK(*asSCS1[SMBus1index].ConditionVar, asSCS1[SMBus1index].Conditionflag);   // clear OEM smbus service flag.
        
        if(IS_MASK_SET(SMBusXStatus, SMBus1_Fail))  // if protocol fail
        {
            (asSCS1[SMBus1index].errorfunc)();      // OEM error hook function
        }
        else                                        // protocol OK
        {
            (asSCS1[SMBus1index].hookfunc)();       // OEM OK hook function
        }
        CLEAR_MASK(SMBusXStatus, (SMBus1_OK+SMBus1_Fail));  // To clear flag
    }
}

//----------------------------------------------------------------------------
// SMBus channel 2 service function
//----------------------------------------------------------------------------
void service_smbus2(void) 
{
	if(SMBus2InUsing)
	{
        CLEAR_MASK(SMBusXStatus, (SMBus2_OK+SMBus2_Fail));
        
        if(IS_MASK_SET(HOSTA_B, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))  // any error
        {
            if(IS_MASK_SET(HOSTA_B, (HOSTA_BSER+HOSTA_FAIL)))
            {
                ResetSMBus(SMbusCh2);               // Reset SMBus
            }
            SET_MASK(SMBusXStatus, SMBus2_Fail);    // SMBus fail
        }
        else                                        // Byte Done Status or Finish Interrupt or no any statys bit
        {
            //*********************************************************************
            // Cmd_ReadBlock
            //*********************************************************************
		    if(asSCS2[SMBus2index].protocol==Cmd_ReadBlock)
		    {                                   
                if(IS_MASK_SET(HOSTA_B, (HOSTA_FINTR+HOSTA_BDS)))   // Only Byte Done Status or Finish Interrupt bit is set.
                {
		            if(SMBus2ByteCunt==0x00)
			        {
				        SMBus2BlockPtr = asSCS2[SMBus2index].smbdata;
				        SMBus2ByteCunt = D0REG_B;

				        if(SMBus2ByteCunt>32)
				        {
					        SMBus2ByteCunt=32;	    // DB_SMBusData[] max 32 bytes
				        }
							
				        SMB_BCNT = SMBus2ByteCunt;
				        DB_SMBusBCunt = SMBus2ByteCunt;
							
				        *SMBus2BlockPtr = HOBDB_B;  // read data1
				        SMBus2ByteCunt--;
		            }
			        else
			        {
				        SMBus2BlockPtr++;
				        *SMBus2BlockPtr=HOBDB_B;
				        SMBus2ByteCunt--;
				        if(SMBus2ByteCunt==0x01)
				        {
					        SET_MASK(HOCTL_B,HOCTL_LABY);
				        }
			        }
					
			        if(SMBus2ByteCunt!=0x00)                // Byte count isn't 0.
			        {
				        HOSTA_B=0xFE;
				        SET_MASK(IER1,Int_SMBUS1);
			        }
                    else                                    // Byte count is 0.
                    {
				        CLEAR_MASK(HOCTL_B,HOCTL_LABY);
                        SET_MASK(SMBusXStatus, SMBus2_OK);  // SMBus protocol OK
                    }
                }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus2_Fail);    // SMBus fail
                }
		    }
	        //*********************************************************************
            // Cmd_WriteBlock
            //*********************************************************************
		    else if(asSCS2[SMBus2index].protocol==Cmd_WriteBlock)
		    {
			    if(IS_MASK_SET(HOSTA_B, (HOSTA_FINTR+HOSTA_BDS)))   // Only Byte Done Status or Finish Interrupt bit is set.
			    {
					SMBus2ByteCunt--;
					if(SMBus2ByteCunt==0x00)
					{
						SET_MASK(SMBusXStatus, SMBus2_OK);  // SMBus protocol OK
					}
					else  
					{
						SMBus2BlockPtr++;
						HOBDB_B=*SMBus2BlockPtr;
						
						HOSTA_B=0xFE;
						SET_MASK(IER1,Int_SMBUS1);
					}
			    }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus2_Fail);    // SMBus fail
                }
		    }
		    //******************************************************************************************
	        // Cmd_SendByte, Cmd_RecvByte, Cmd_ReadByte, Cmd_WriteByte, Cmd_ReadWord and Cmd_WriteWord 
	        //******************************************************************************************
		    else
		    {
                if(IS_MASK_SET(HOSTA_B, HOSTA_FINTR))       // Only Finish Interrupt bit is set.
                {
		            *asSCS2[SMBus2index].smbdata = D0REG_B; // read data byte 1
			        if(asSCS2[SMBus2index].protocol==Cmd_ReadWord)  // read word protocol
			        {
				        Tmp_XPntr = asSCS2[SMBus2index].smbdata;
				        Tmp_XPntr++;
				        *Tmp_XPntr=D1REG_B;                 // read data byte 2
			        }
                    SET_MASK(SMBusXStatus, SMBus2_OK);      // SMBus protocol OK
                }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus2_Fail);    // SMBus protocol Fail
                }
		    }
		}
	}

    if(IS_MASK_SET(SMBusXStatus, (SMBus2_Fail+SMBus2_OK)))  // SMBus protocol Fail or OK
    {
        HOSTA_B=0xFE;                               // Clear Host Status register.
	    SMBus2InUsing = 0;                          // Clear smbus in used flag.
        CLEAR_MASK(*asSCS2[SMBus2index].ConditionVar, asSCS2[SMBus2index].Conditionflag);   // clear OEM smbus service flag.
        
        if(IS_MASK_SET(SMBusXStatus, SMBus2_Fail))  // if protocol fail
        {
            (asSCS2[SMBus2index].errorfunc)();      // OEM error hook function
        }
        else                                        // protocol OK
        {
            (asSCS2[SMBus2index].hookfunc)();       // OEM OK hook function
        }
        CLEAR_MASK(SMBusXStatus, (SMBus2_OK+SMBus2_Fail));  // To clear flag
    }
}

//----------------------------------------------------------------------------
// SMBus channel 3 service function
//----------------------------------------------------------------------------
void service_smbus3(void) 
{
	if(SMBus3InUsing)
	{
        CLEAR_MASK(SMBusXStatus, (SMBus3_OK+SMBus3_Fail));
        
        if(IS_MASK_SET(HOSTA_C, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))  // any error
        {
            if(IS_MASK_SET(HOSTA_C, (HOSTA_BSER+HOSTA_FAIL)))
            {
                ResetSMBus(SMbusCh3);               // Reset SMBus
            }
            SET_MASK(SMBusXStatus, SMBus3_Fail);    // SMBus fail
        }
        else                                        // Byte Done Status or Finish Interrupt or no any statys bit
        {
            //*********************************************************************
            // Cmd_ReadBlock
            //*********************************************************************
		    if(asSCS3[SMBus3index].protocol==Cmd_ReadBlock)
		    {                                   
                if(IS_MASK_SET(HOSTA_C, (HOSTA_FINTR+HOSTA_BDS)))   // Only Byte Done Status or Finish Interrupt bit is set.
                {
		            if(SMBus3ByteCunt==0x00)
			        {
				        SMBus3BlockPtr = asSCS3[SMBus3index].smbdata;
				        SMBus3ByteCunt = D0REG_C;

				        if(SMBus3ByteCunt>32)
				        {
					        SMBus3ByteCunt=32;	    // DB_SMBusData[] max 32 bytes
				        }
							
				        SMB_BCNT = SMBus3ByteCunt;
				        DB_SMBusBCunt = SMBus3ByteCunt;
							
				        *SMBus3BlockPtr = HOBDB_C;  // read data1
				        SMBus3ByteCunt--;
		            }
			        else
			        {
				        SMBus3BlockPtr++;
				        *SMBus3BlockPtr=HOBDB_C;
				        SMBus3ByteCunt--;
				        if(SMBus3ByteCunt==0x01)
				        {
					        SET_MASK(HOCTL_C,HOCTL_LABY);
				        }
			        }
					
			        if(SMBus3ByteCunt!=0x00)                // Byte count isn't 0.
			        {
				        HOSTA_C=0xFE;
				        SET_MASK(IER2,Int_SMBUS2);
			        }
                    else                                    // Byte count is 0.
                    {
				        CLEAR_MASK(HOCTL_C,HOCTL_LABY);
                        SET_MASK(SMBusXStatus, SMBus3_OK);  // SMBus protocol OK
                    }
                }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus3_Fail);    // SMBus fail
                }
		    }
	        //*********************************************************************
            // Cmd_WriteBlock
            //*********************************************************************
		    else if(asSCS3[SMBus3index].protocol==Cmd_WriteBlock)
		    {
			    if(IS_MASK_SET(HOSTA_C, (HOSTA_FINTR+HOSTA_BDS)))   // Only Byte Done Status or Finish Interrupt bit is set.
			    {
					SMBus3ByteCunt--;
					if(SMBus3ByteCunt==0x00)
					{
						SET_MASK(SMBusXStatus, SMBus3_OK);  // SMBus protocol OK
					}
					else  
					{
						SMBus3BlockPtr++;
						HOBDB_C=*SMBus3BlockPtr;
						
						HOSTA_C=0xFE;
						SET_MASK(IER2,Int_SMBUS2);
					}
			    }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus3_Fail);    // SMBus fail
                }
		    }
		    //******************************************************************************************
	        // Cmd_SendByte, Cmd_RecvByte, Cmd_ReadByte, Cmd_WriteByte, Cmd_ReadWord and Cmd_WriteWord 
	        //******************************************************************************************
		    else
		    {
                if(IS_MASK_SET(HOSTA_C, HOSTA_FINTR))       // Only Finish Interrupt bit is set.
                {
		            *asSCS3[SMBus3index].smbdata = D0REG_C; // read data byte 1
			        if(asSCS3[SMBus3index].protocol==Cmd_ReadWord)  // read word protocol
			        {
				        Tmp_XPntr = asSCS3[SMBus3index].smbdata;
				        Tmp_XPntr++;
				        *Tmp_XPntr=D1REG_C;                 // read data byte 2
			        }
                    SET_MASK(SMBusXStatus, SMBus3_OK);      // SMBus protocol OK
                }
                else                                        // No any bit is set of host status register.
                {
                    SET_MASK(SMBusXStatus, SMBus3_Fail);    // SMBus protocol Fail
                }
		    }
		}
	}

    if(IS_MASK_SET(SMBusXStatus, (SMBus3_Fail+SMBus3_OK)))  // SMBus protocol Fail or OK
    {
        HOSTA_C=0xFE;                               // Clear Host Status register.
	    SMBus3InUsing = 0;                          // Clear smbus in used flag.
        CLEAR_MASK(*asSCS3[SMBus3index].ConditionVar, asSCS3[SMBus3index].Conditionflag);   // clear OEM smbus service flag.
        
        if(IS_MASK_SET(SMBusXStatus, SMBus3_Fail))  // if protocol fail
        {
            (asSCS3[SMBus3index].errorfunc)();      // OEM error hook function
        }
        else                                        // protocol OK
        {
            (asSCS3[SMBus3index].hookfunc)();       // OEM OK hook function
        }
        CLEAR_MASK(SMBusXStatus, (SMBus3_OK+SMBus3_Fail));  // To clear flag
    }
}

//----------------------------------------------------------------------------
// The function of checking smbus need service
// Note : 
//      Always return SMBus_ClearService, if SMBusCenter is no use function.
//----------------------------------------------------------------------------
BYTE CheckSMBusNeedService(void)
{
    if((F_Service_SMBus1==SMBus_NeedService)||(F_Service_SMBus2==SMBus_NeedService)||(F_Service_SMBus3==SMBus_NeedService))
    {
        return(SMBus_NeedService);
    }

    // Always return SMBus_ClearService, if SMBusCenter is no use function.
    return(SMBus_ClearService);
}