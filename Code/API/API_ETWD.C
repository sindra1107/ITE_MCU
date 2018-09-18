/*-----------------------------------------------------------------------------
* TITLE: API_ETWD.C
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

//*****************************************************************************
// Include all header file
#include <CORE_INCLUDE.H>
#include <API_INCLUDE.H>
//
//*****************************************************************************
#if API_ETWD_SUPPORT
//*****************************************************************************
// ETWD Controlling Table
//*****************************************************************************
const sETWD_Reg code asETWD_Reg[] = 
{
    //-------------------------------------------------------------------------
    // ETWCTRL ,   ET2PSR,     ET2CNTLLR,      ET2CNTLHR,      ET2CNTLH2R, INT_En_Reg, INT_Stus_Reg 
    //
    {  &ETWCTRL,  &ET2PSR,    &ET2CNTLLR,     &ET2CNTLHR,     &ET2CNTLH2R,    &IER7,  &ISR7,  Int_ET2Intr },  // ExternalTimer_2
};

//*****************************************************************************
//
//  To enable external timer 2, (24bit count-down timer)
//
//  parameter :
//      p_et_time : 1 ~ 86400000 (ms)
//
//  return :
//      none
//
//  ******
//  note : Calculate Cycle Time (ms)
//	
//			32 Hz : (1/32)*1000(ms)	   = 1000/32 = 31.25 = 3125/100
//		  1024 Hz : (1/1024)*1000(ms)  = 1000/1024
//       32768 Hz : (1/32768)*1000(ms) = 1000/32768
//      
//  ******
//
//*****************************************************************************
void Enable_External_Timer_2(LWORD p_et_time)
{
    LWORD l_time_out_ms;
    BYTE l_psr;

    if((p_et_time!=0x00)&&(p_et_time<=86400000))   // valid setting
    {
        if(p_et_time>16000000)                      // External Timer Prescaler Select 32 Hz
        {
            l_psr = ETPS_32_Hz;
            l_time_out_ms = (p_et_time / 3125)*100;
        }
        else if(p_et_time>500000)                   // External Timer Prescaler Select 1.024 KHz
        {
            l_psr = ETPS_1_024_KHz;
            l_time_out_ms = (p_et_time / 1000)*1024;
        }
        else                                        // External Timer Prescaler Select 32.768 KHz
        {
            l_psr = ETPS_32_768_KHz;
            l_time_out_ms = (p_et_time * 3276)/100;
        }
				
				#if DEF_TIMER_OVERFLOW_FLAG_USE_ISRx
				*asETWD_Reg[0].ETWD_intc_isr = asETWD_Reg[0].ETWD_intc_ctrl;
				#endif
				
        *asETWD_Reg[0].ETWD_psr = l_psr;   // Prescaler

        *asETWD_Reg[0].ETWD_cntlh2r = (BYTE)(l_time_out_ms>>16); // To enable a "time_out_ms" timer
        *asETWD_Reg[0].ETWD_cntlhr = (BYTE)(l_time_out_ms>>8);
        *asETWD_Reg[0].ETWD_cntllr = (BYTE)(l_time_out_ms);
    }
}

//*****************************************************************************
//
//  To disable external timer 2, (24bit count-down timer)
//
//  parameter :
//      none 
//
//  return :
//      none
//
//*****************************************************************************
void Disable_External_Timer_2_INT58(void)
{
	//
	// Disable INT58 
	//
	CLEAR_MASK((*asETWD_Reg[0].ETWD_intc_ier), asETWD_Reg[0].ETWD_intc_ctrl);
	//
	// Clear INT58 Status
	//
	*asETWD_Reg[0].ETWD_intc_isr = asETWD_Reg[0].ETWD_intc_ctrl;
}

//****************************************************************************
//
//  To check external timer 2 has counted down to zero or not.
//  If external timer 2 has counted down to zero, return "ExternalTimer_TC" and R/C ETxTC bit.
//
//  Parameter :
//      none
//
//  Return :
//      ExternalTimer_TC     : external timer has counted down to zero.
//      ExternalTimer_NoTC   : external timer counting
//
//****************************************************************************
BYTE Check_External_Timer_2_Terminal_Count(void)
{    
    #if DEF_TIMER_OVERFLOW_FLAG_USE_ISRx
    //
    // Read INT58 Status & Clear it
    //
    if(IS_MASK_SET(*asETWD_Reg[0].ETWD_intc_isr , asETWD_Reg[0].ETWD_intc_ctrl))
    {
        *asETWD_Reg[0].ETWD_intc_isr = asETWD_Reg[0].ETWD_intc_ctrl;
        return(ExternalTimer_TC);
    }
    else
    {
        return(ExternalTimer_NoTC);
    }
    
    #else
    //
    //-----------
    //
    BYTE l_read_clear;
    if(IS_MASK_SET((*asETWD_Reg[0].ETWD_ctrl), BIT3))
    {
        l_read_clear = *asETWD_Reg[0].ETWD_ctrl;   // RC
        return(ExternalTimer_TC);
    }
    else
    {
        return(ExternalTimer_NoTC);
    }   
    #endif
}

//*****************************************************************************
//
//  To enable external watchdog timer
//
//  parameter :
//
//      p_wdt_time : 
//              1000 ~ 1800000 (ms)
//
//  return :
//      none
//
//*****************************************************************************
void Enable_External_WDT(LWORD p_wdt_time)
{
    BYTE l_psr;
    LWORD l_time_out_ms;
    
    if(p_wdt_time>=1000)
    {
        //
        // valid setting, 1sec ~ 30min
        //
        if(p_wdt_time<=1800000)
        {
            if(p_wdt_time>60000)
            {
                //
                // External Timer Prescaler Select 32 Hz
                //
                l_psr = ETPS_32_Hz;
                l_time_out_ms = (p_wdt_time / 3125)*100;
            }
            else if(p_wdt_time>1800)
            {
                //
                // External Timer Prescaler Select 1.024 KHz
                //
                l_psr = ETPS_1_024_KHz;
                l_time_out_ms = (p_wdt_time / 1000)*1024;
            }
            else
            {
                //
                // External Timer Prescaler Select 32.768 KHz
                //
                l_psr = ETPS_32_768_KHz;
                l_time_out_ms = (p_wdt_time * 3276)/100;
            }

            //
            // Prescaler Register
            //
            ETPSR = l_psr;

            //
            // To enable external timer 1 is necessary.
            //
			ETCNTLHR = 0xFF;
            ETCNTLLR = 0xFF;

            //
            // Select clock after prescaler of the external timer 1
            //
            SET_MASK(ETWCFG, (EWDSRC+EWDKEYEN));
            
            //
            // External WDT can be stopped by setting EWDSCEN bit
            //
            SET_MASK(ETWCTRL, EWDSCMS);
            
            //
            // External WDT is counting
            //
            CLEAR_MASK(ETWCTRL, EWDSCEN);

            //
            // External WDT Counter High
            //
            EWDCNTHR = (BYTE)(l_time_out_ms>>8);

            //
            // External WDT Counter Low
            //
            EWDCNTLR = (BYTE)(l_time_out_ms);
        }
    }
}

//*****************************************************************************
//
//  To re-start external watchdog timer
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Reset_External_WDT(void)
{
    //
    // External WDT is re-started (touched) if 5Ch is written to this register. 
    // Writing with other values causes an External Watchdog Reset. This function is enabled by EWDKEYEN bit.
    //
    EWDKEYR = ExternalWDTKeyRestart;
}

//*****************************************************************************
//
//  To disable external watchdog timer
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Disable_External_WDT(void)
{
    //
    // External WDT Stop Count Enable
    //
    SET_MASK(ETWCTRL, EWDSCEN);
    //
    // External WDT is re-started (touched) if 5Ch is written to this register. 
    // Writing with other values causes an External Watchdog Reset. This function is enabled by EWDKEYEN bit.
    //
    EWDKEYR = ExternalWDTKeyRestart;
}
#endif