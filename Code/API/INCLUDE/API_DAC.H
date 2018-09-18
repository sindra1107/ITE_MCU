/*-----------------------------------------------------------------------------
* TITLE: API_DAC.H
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

#ifndef API_DAC_H
#define API_DAC_H

#define API_DAC_SUPPORT 		0
#if API_DAC_SUPPORT
//*****************************************************************************
// DAC channel selection
//*****************************************************************************
#define DAC_Channel_2    0
#define DAC_Channel_3    1
#define DAC_Channel_4    2
#define DAC_Channel_5    3

//*****************************************************************************
// Function prototype
//*****************************************************************************
extern void DAC_Channelx_Enable(BYTE p_dac_enable_channel_x);
extern void DAC_Channelx_Disable(BYTE p_dac_disable_channel_x);
extern void DAC_Channelx_Output(BYTE p_dac_channel_x, BYTE p_dac_channel_x_output);
extern BYTE DAC_Channelx_Read(BYTE p_dac_channel_x);

//*****************************************************************************
// dac registers struct
//*****************************************************************************
typedef struct DACCtrlStruct
{
    BYTE     *dac_output_reg;	
	BYTE 	 *dac_pin_ctrl;		
    BYTE     dac_pd_ctrl;		
} sDACCtrlStruct;

#endif
#endif

