/*-----------------------------------------------------------------------------
* TITLE: API_DAC.C
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
#if API_DAC_SUPPORT
//*****************************************************************************
// dac struct
//*****************************************************************************
const sDACCtrlStruct code asDACCtrlStruct[] = 
{
    { &DACDAT2,     &GPCRJ2,    BIT2    },
    { &DACDAT3,     &GPCRJ3,    BIT3    },
    { &DACDAT4,     &GPCRJ4,    BIT4    },
    { &DACDAT5,     &GPCRJ5,    BIT5    },
};

//*****************************************************************************
//
// DAC channel[x] enable function, dac channel[x] is not powered down and pin to alt (Func 1).
//
//  parameter :
//      p_dac_enable_channel_x : DAC_Channel_2 | DAC_Channel_3 | DAC_Channel_4 | DAC_Channel_5
//
//  return :
//      none
//
//*****************************************************************************
void DAC_Channelx_Enable(BYTE p_dac_enable_channel_x)
{
    //
    // to check parameter is valided.
    //
    if(p_dac_enable_channel_x < (sizeof(asDACCtrlStruct)/sizeof(sDACCtrlStruct)))
    {
        //
        // pin to alt function.
        //
        *asDACCtrlStruct[p_dac_enable_channel_x].dac_pin_ctrl = ALT;

        //
        // dac channel is not powered down.
        //
        DACPWRDN &= ~asDACCtrlStruct[p_dac_enable_channel_x].dac_pd_ctrl;
    }
}

//*****************************************************************************
//
// DAC channel[x] disable function, dac channel[x] is powered down and pin to input (Func 3).
//
//  parameter :
//      p_dac_disable_channel_x : DAC_Channel_2 | DAC_Channel_3 | DAC_Channel_4 | DAC_Channel_5
//
//  return :
//      none
//
//*****************************************************************************
void DAC_Channelx_Disable(BYTE p_dac_disable_channel_x)
{
    //
    // to check parameter is valided.
    //
    if(p_dac_disable_channel_x < (sizeof(asDACCtrlStruct)/sizeof(sDACCtrlStruct)))
    {
        //
        // pin to input function.
        //
        *asDACCtrlStruct[p_dac_disable_channel_x].dac_pin_ctrl = INPUT;

        //
        // dac channel is powered down.
        //
        DACPWRDN |= asDACCtrlStruct[p_dac_disable_channel_x].dac_pd_ctrl;
    }
}

//*****************************************************************************
//
// DAC channel[x] output 0 ~ AVCC
//
//  parameter :
//      p_dac_channel_x         : DAC_Channel_2 | DAC_Channel_3 | DAC_Channel_4 | DAC_Channel_5
//      p_dac_channel_x_output  : 0 ~ 255
//
//  return :
//      none
//
//*****************************************************************************
void DAC_Channelx_Output(BYTE p_dac_channel_x, BYTE p_dac_channel_x_output)
{
    //
    // to check parameter is valided.
    //
    if(p_dac_channel_x < (sizeof(asDACCtrlStruct)/sizeof(sDACCtrlStruct)))
    {
        //
        // parameter "p_dac_channel_x_output" will be loaded to the DAC for D/A operation.
        //
        *asDACCtrlStruct[p_dac_channel_x].dac_output_reg = p_dac_channel_x_output;
    }
}

//*****************************************************************************
//
// Reading DAC channel[x]
//
//  parameter :
//      p_dac_channel_x : DAC_Channel_2 | DAC_Channel_3 | DAC_Channel_4 | DAC_Channel_5
//
//  return :
//      The output level of DAC channel x.
//
//*****************************************************************************
BYTE DAC_Channelx_Read(BYTE p_dac_channel_x)
{
    BYTE l_dac_levle;

    l_dac_levle = 0x00;
    
    //
    // to check parameter is valided.
    //
    if(p_dac_channel_x < (sizeof(asDACCtrlStruct)/sizeof(sDACCtrlStruct)))
    {
		if( !(DACPWRDN & asDACCtrlStruct[p_dac_channel_x].dac_pd_ctrl) )
		{
	        //
	        // parameter "p_dac_channel_x_output" will be loaded to the DAC for D/A operation.
	        //
	        l_dac_levle = *asDACCtrlStruct[p_dac_channel_x].dac_output_reg;
		}
    }

    return(l_dac_levle);
}
#endif