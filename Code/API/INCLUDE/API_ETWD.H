/*-----------------------------------------------------------------------------
* TITLE: API_ETWD.H
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

#ifndef API_ETWD_H
#define API_ETWD_H

#define API_ETWD_SUPPORT 		0
#if API_ETWD_SUPPORT
//*****************************************************************************
//
//*****************************************************************************
#define ETPS_32_768_KHz				0x00
#define ETPS_1_024_KHz				0x01
#define ETPS_32_Hz					0x02

//ETWCFG
#define EWDSRC						BIT4
#define	EWDKEYEN				    BIT5

//ETWCTRL
#define	EWDSCMS				    	BIT4
#define	EWDSCEN				    	BIT5

#define ExternalTimer_TC            1                   // The external timer has counted down to zero
#define ExternalTimer_NoTC          0                   // The external timer counting

#define ExternalWDTKeyRestart       0x5C                // External WDT is re-started (touched)

#define DEF_TIMER_OVERFLOW_FLAG_USE_ISRx 	1			// 0 : Use ET2TC as time out flag
														// 1 : Use INT Status as time out flag
//*****************************************************************************
// Function prototype
//*****************************************************************************
extern void Enable_External_Timer_2(LWORD p_et_time);
extern void Disable_External_Timer_2_INT58(void);
extern BYTE Check_External_Timer_2_Terminal_Count(void);
extern void Enable_External_WDT(LWORD p_wdt_time);
extern void Reset_External_WDT(void);
extern void Disable_External_WDT(void);

//*****************************************************************************
// ETWD registers struct
//*****************************************************************************
typedef struct ETWD_Reg
{
	BYTE	*ETWD_ctrl;     // external timer x control register
	BYTE	*ETWD_psr;      // external timer x prescaler register
	BYTE	*ETWD_cntllr;   // external timer x counter low byte
	BYTE	*ETWD_cntlhr;   // external timer x counter high byte
	BYTE	*ETWD_cntlh2r;  // external timer x counter high byte2
	BYTE    *ETWD_intc_ier; // external timer interrupt enable register.
	BYTE    *ETWD_intc_isr; // external timer interrupt status register.
	BYTE    ETWD_intc_ctrl; // external timer interrupt control bit of register.
} sETWD_Reg;

#endif
#endif
