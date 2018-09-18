/*-----------------------------------------------------------------------------
* TITLE: API_ADC.C
*
* Author : Dino
*
* History : 
* ------------------------------
* Version : 1.10
* ------------------------------
*
* Note : To link [api_xxx.o] if related api function be used.
*
*---------------------------------------------------------------------------*/

//*****************************************************************************
// Include all header file
#include <CORE_INCLUDE.H>
#include <API_INCLUDE.H>
//
//*****************************************************************************
#if API_ADC_SUPPORT
//*****************************************************************************
// global variable for adc data
//*****************************************************************************
WORD code g_ADC_Variable_00;
WORD code g_ADC_Variable_01;
WORD code g_ADC_Variable_02;
WORD code g_ADC_Variable_03;
WORD code g_ADC_Variable_04;
WORD code g_ADC_Variable_05;
WORD code g_ADC_Variable_06;
WORD code g_ADC_Variable_07;

BYTE g_ADC_Check_Data_Valid_Index;   // 0 ~ 7
BYTE g_ADC_Channel_Enable_Flag;      // bit7 ~ bit0

//*****************************************************************************
// adc struct
//  CTL_Reg     Dat_MSB     Dat_LSB    Func_Sel     Global_Dat 
//*****************************************************************************
const sADCCtrlStruct code asADCCtrlStruct[] = 
{
 	{ &VCH0CTL, &VCH0DATM,  &VCH0DATL,  &GPCRI0,	&g_ADC_Variable_00  },
 	{ &VCH1CTL, &VCH1DATM,  &VCH1DATL,  &GPCRI1,	&g_ADC_Variable_01  },
 	{ &VCH2CTL, &VCH2DATM,  &VCH2DATL,  &GPCRI2,	&g_ADC_Variable_02  },
 	{ &VCH3CTL, &VCH3DATM,  &VCH3DATL,  &GPCRI3,	&g_ADC_Variable_03  },
 	{ &VCH4CTL, &VCH4DATM,  &VCH4DATL,  &GPCRI4,	&g_ADC_Variable_04  },
 	{ &VCH5CTL, &VCH5DATM,  &VCH5DATL,  &GPCRI5,	&g_ADC_Variable_05  },
 	{ &VCH6CTL, &VCH6DATM,  &VCH6DATL,  &GPCRI6,	&g_ADC_Variable_06  },
 	{ &VCH7CTL, &VCH7DATM,  &VCH7DATL,  &GPCRI7,	&g_ADC_Variable_07  },
};

//*****************************************************************************
//
// ADC analog accuracy initialization
//
//  parameter :
//      none
//
//  return :
//      none
//
//  note :
//      *** only once after VSTBY power on ***
//
//*****************************************************************************
void ADC_Initialization(void)
{
    //
    // bit3 : start adc accuracy initialization
    //
    SET_MASK(ADCSTS, BIT3);
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    //
    // bit3 : stop adc accuracy initialization
    //
    CLEAR_MASK(ADCSTS, BIT3);
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//*****************************************************************************
//
// ADC module enable
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ADC_Module_Enable(void)
{
    BYTE *lp_adc_reg_1932h;
    
    //
    // For IT85xx and IT82xx Chip & Before F Version
    //
    if((ECHIPID1==0x85) || (ECHIPID1==0x82))
    {
        if((ECHIPVER&0x0F)<=0x06)
        {
            //
            // bit2 ~ bit0 : default 0x02, SAR ADC 2 - 7
            //
            ADCGCR |= (BIT0+BIT1+BIT2);	

            //
            // 1932h : bit3 ~ bit1 : interval time of SAR ADC 2 - 7
            //
            lp_adc_reg_1932h = (BYTE *)0x1932;
            SET_MASK((*lp_adc_reg_1932h), (BIT3+BIT2+BIT1));
        }
    }

    //
    // bit 5 : adc conversion time select 0 (ADCCTS0)
    // ADC channel conversion time 
    // ADCCTS1, ADCCTS0     :   11b                 01b                 00b or 10b
    // conversion time (us) :   200*(SCLKDIV+1)     103.2*(SCLKDIV+1)   30.8*(SCLKDIV+1) 
    //
    // bit 0 : adc module enable/disable
    //
    ADCCFG = (BIT5+BIT0);

    //
    // bit7 : automatic hardware calibration enable
    //
    //KDCTL = BIT7;

    //
    // reset index for "ADC_Check_Channelx_Data_Valid" function
    //
    //g_ADC_Check_Data_Valid_Index = 0x00;
}

//*****************************************************************************
//
// ADC module disable
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ADC_Module_Disable(void)
{
    //
    // bit 0 : adc module disable
    //
    CLEAR_MASK(ADCCFG, BIT0);

    //
    // reset index
    //
    //g_ADC_Check_Data_Valid_Index = 0x00;
}

//*****************************************************************************
//
// ADC channel[x] enable function
//
//  parameter :
//      p_adc_enable_channel_x : 
//      ADC_Channel_0 | ADC_Channel_1 | ADC_Channel_2 | ADC_Channel_3
//      ADC_Channel_4 | ADC_Channel_5 | ADC_Channel_6 | ADC_Channel_7
//
//  return :
//      none
//
//*****************************************************************************
void ADC_Channelx_Enable(BYTE p_adc_enable_channel_x)
{
    BYTE l_adc_channel_index;
    
    //
    // one or more adc channel need to enable.
    //
    if(p_adc_enable_channel_x != 0x00)
    {
        for(l_adc_channel_index=0x00; l_adc_channel_index<(sizeof(asADCCtrlStruct)/sizeof(sADCCtrlStruct)); l_adc_channel_index++)
        {
            //
            // adc channel[x] is supported
            //
            if(IS_MASK_SET(p_adc_enable_channel_x, BIT(l_adc_channel_index)))
            {
                //
                // set channel enable flag
                //
                SET_MASK(g_ADC_Channel_Enable_Flag, BIT(l_adc_channel_index));
                
                //
                // enable adc channel[x] function pin
                //
                *asADCCtrlStruct[l_adc_channel_index].adc_pin_ctrl = ALT;

                //
                // bit4 ~ bit0 : indicates voltage channel[x] input is selected for measurement
                // bit 7 : WC data valid flag
                //
                // channel 0, 1, 2, and 3
                //
                if(l_adc_channel_index<4)
                {
                    *asADCCtrlStruct[l_adc_channel_index].adc_ctrl = (BIT7+l_adc_channel_index);
                }
                else
                {
                    //
                    // bit4 : voltage channel enable/disable
                    // channel 4, 5, 6, and 7
                    //
                    *asADCCtrlStruct[l_adc_channel_index].adc_ctrl = (BIT7+BIT4);
                }
            }
        }

        //
        // enable adc module
        //
        ADC_Module_Enable();
    }
}

//*****************************************************************************
//
// ADC channel[x] disable function
//
//  parameter :
//      p_adc_disable_channel_x : 
//      ADC_Channel_0 | ADC_Channel_1 | ADC_Channel_2 | ADC_Channel_3
//      ADC_Channel_4 | ADC_Channel_5 | ADC_Channel_6 | ADC_Channel_7
//
//  return :
//      none
//
//*****************************************************************************
void ADC_Channelx_Disable(BYTE p_adc_disable_channel_x)
{
    BYTE l_adc_channel_index;
    
    //
    // one or more adc channel need to disable.
    //
    if(p_adc_disable_channel_x != 0x00)
    {
        for(l_adc_channel_index=0x00; l_adc_channel_index<(sizeof(asADCCtrlStruct)/sizeof(sADCCtrlStruct)); l_adc_channel_index++)
        {
            //
            // adc channel[x] need to disable
            //
            if(IS_MASK_SET(p_adc_disable_channel_x, BIT(l_adc_channel_index)))
            {
                //
                // clear channel enable flag
                //
                CLEAR_MASK(g_ADC_Channel_Enable_Flag, BIT(l_adc_channel_index));
                
                //
                // input pin
                //
                *asADCCtrlStruct[l_adc_channel_index].adc_pin_ctrl = INPUT;

                //
                // bit4 ~ bit0 : indicates voltage channel[x] input is selected for measurement
                // bit 7 : WC data valid flag
                //
                // channel 0, 1, 2, and 3
                //
                if(l_adc_channel_index<4)
                {
                    *asADCCtrlStruct[l_adc_channel_index].adc_ctrl = (BIT7+0x1F);
                }
                else
                {
                    //
                    // bit4 : voltage channel enable/disable
                    // channel 4, 5, 6, and 7
                    //
                    *asADCCtrlStruct[l_adc_channel_index].adc_ctrl = (BIT7);
                }
            }
        }
    }
}

//*****************************************************************************
//
//  To check data valid flag of adc channel x
//
//  parameter :
//      none
//
//  return :
//      none
//
//  note : 
//      1ms time based
//
//*****************************************************************************
void ADC_Check_Channelx_Data_Valid(void)
{
     BYTE l_adc_datam;
     BYTE l_adc_datal;

    //
    // ADC module is enabled
    //
    if(IS_MASK_SET(ADCCFG, BIT0))
    {
        //
        // one or more adc channel is enabled
        //
        if(g_ADC_Channel_Enable_Flag!=0x00)
        {
            //
            // find adc channel enabled
            //
            while(g_ADC_Check_Data_Valid_Index < (sizeof(asADCCtrlStruct)/sizeof(sADCCtrlStruct)))
            {
                if(IS_MASK_SET(g_ADC_Channel_Enable_Flag, BIT(g_ADC_Check_Data_Valid_Index)))
                {
                    //
                    // data valid of channel [g_ADC_Check_Data_Valid_Index]
                    //
                    if(IS_MASK_SET(ADCDVSTS, BIT(g_ADC_Check_Data_Valid_Index)))
                    {
                        //
                        // read adc data msb
                        //
                        l_adc_datam = *asADCCtrlStruct[g_ADC_Check_Data_Valid_Index].adc_datm;

                        //
                        // read adc data lsb
                        //
                        l_adc_datal = *asADCCtrlStruct[g_ADC_Check_Data_Valid_Index].adc_datl;

                        //
                        // save to global variable
                        //
                        *asADCCtrlStruct[g_ADC_Check_Data_Valid_Index].adc_value = (l_adc_datam<<8)+l_adc_datal;

                        //
                        // W/C data valid flag
                        //
                        SET_MASK(ADCDVSTS, BIT(g_ADC_Check_Data_Valid_Index));
                    }

                    //
                    // next channel for next cycle
                    //
                    g_ADC_Check_Data_Valid_Index++;
                    break;
                }
                else
                {
                    //
                    // find next enable channel
                    //
                    g_ADC_Check_Data_Valid_Index++;
                }
            }

            //
            // only adc channel 0 ~ 7 are valided
            //
            if(g_ADC_Check_Data_Valid_Index >= (sizeof(asADCCtrlStruct)/sizeof(sADCCtrlStruct)))
            {
                g_ADC_Check_Data_Valid_Index = 0x00;
            }
        }
    }
}

//*****************************************************************************
//
//  To read adc data from global variable of table "asADCCtrlStruct[]"
//
//  parameter :
//      p_adc_channel_x : 0 ~ 7
//
//  return :
//      lw_adc_data : adc data of channel [p_adc_channel_x]
//
//*****************************************************************************
WORD ADC_Get_Channelx_ADC_Data(BYTE p_adc_channel_x)
{
    WORD lw_adc_data;

    //
    // read data from global variable
    //
    lw_adc_data = *asADCCtrlStruct[p_adc_channel_x].adc_value;

    //
    // return data
    //
    return(lw_adc_data);
}
#endif