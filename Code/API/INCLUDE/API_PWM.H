/*-----------------------------------------------------------------------------
* TITLE: API_PWM.H
*
* Author : Dino
*
* History : 
* ------------------------------
* Version : 1.00
* ------------------------------
*
* Note : To link [api_xxx.o] if related api function be used.
*
*---------------------------------------------------------------------------*/

#ifndef API_PWM_H
#define API_PWM_H

#define API_PWM_SUPPORT 		0
#if API_PWM_SUPPORT
//*****************************************************************************
//
//*****************************************************************************
//
// The PWMi output signal duty cycle (in %, when INVPi is 0) is: (DCRi)/(CTR+1) x 100
// The PWMi output signal cycle time is : (CiCPRS + 1) x (CTR + 1) x T clk
// The PWMi output signal cycle frequency is : FreqEC / ((CiCPRS + 1) x (CTR + 1))
//
//*****************************************************************************
// PWM channel selection
//*****************************************************************************
#define PWM_Channel_0       0
#define PWM_Channel_1       1
#define PWM_Channel_2       2
#define PWM_Channel_3       3
#define PWM_Channel_4       4
#define PWM_Channel_5       5
#define PWM_Channel_6       6
#define PWM_Channel_7       7

#define PWM_PrescalerC4     0
#define PWM_PrescalerC6     1
#define PWM_PrescalerC7     2

#define PWM_CTR1            0
#define PWM_CTR2            1
#define PWM_CTR3            2

#define PWM_EC_Frequence            9200000 // 9.2 MHz
#define PWM_EC_Frequence_32_768K    3276800 // 32.768 KHz note : (x100)
#define PWM_Duty_Cycle_CTRx_Min     120

//*****************************************************************************
//
//*****************************************************************************
#define PWM_NoReg   (BYTE *) 0xFFFF  // No register with this

//*****************************************************************************
// Function prototype
//*****************************************************************************
extern void PWM_Channelx_Output_Duty(BYTE p_channel_x, BYTE p_duty);
extern WORD PWM_Channelx_Register_Clock_Prescaler(BYTE p_channel_x, BYTE p_Prescaler, unsigned long P_channel_frequence);
extern void PWM_Channelx_Enable(BYTE p_channel_x);
extern void PWM_Channelx_Disable(BYTE p_channel_x);
extern void PWM_Channelx_Clock_Prescaler_Selection(BYTE p_channel_x, BYTE p_Prescaler);
extern BYTE PWM_Channelx_Clock_Prescaler_Setting_Read(BYTE p_channel_x);
extern void PWM_Set_Prescaler_Clock_Frequency_Select(BYTE p_cpr_group, WORD P_psdv);
extern void PWM_Set_Cycle_Time_Register(BYTE p_ctr_group, BYTE P_ctr_value);
extern WORD PWM_Channelx_Register_Clock_Prescaler_Low_Frequency(BYTE p_channel_x, BYTE p_Prescaler, unsigned long P_channel_frequence);

//*****************************************************************************
// pwm registers struct
//*****************************************************************************
typedef struct PWMCtrlStruct
{
    BYTE    *pwm_cycle_time_reg;	
	BYTE 	*pwm_cpr_reg_lsb;
    BYTE 	*pwm_cpr_reg_msb;
    BYTE 	*pwm_pcfsr_reg;
    BYTE 	pwm_pcfsr_ctrl_bit0;
} sPWMCtrlStruct;

typedef struct PWMStruct
{
    BYTE     *pwm_duty_cycle_reg;
    BYTE     *pwm_prescaler_clock_source_select_reg;
    BYTE     *pwm_ctrl_pin;
} sPWMStruct;

#endif
#endif

