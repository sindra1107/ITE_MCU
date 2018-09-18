/*----------------------------------------------------------------------------
 * Filename: OEM_ECPDM.C  For Chipset: ITE.IT85XX
 *
 * Function: The example of EC power down mode control.
 *
 * Author  : Dino
 * 
 * Copyright (c) 2012 - , ITE Tech. Inc. All Rights Reserved. 
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

#ifdef ECPowerDownModeSupport
//*****************************************************************************
//
// The hook function of EC prepare to enter idle mode.
// For OEM feature use.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Hook_ECPrepareEnterIdleMode(void)
{

}

//*****************************************************************************
//
// The hook function of EC prepare to enter deep doze mode.
// For OEM feature use.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Hook_ECPrepareEnterDeepDozeMode(void)
{

}

//*****************************************************************************
//
// The hook function of EC prepare to enter deep sleep mode.
// For OEM feature use.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Hook_ECPrepareEnterDeepSleepMode(void)
{

}

//*****************************************************************************
//
// The EC exit idle mode hook function.
// For OEM feature use.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Hook_ECExitIdleMode(void)
{
  
}

//*****************************************************************************
//
// The EC exit deep doze mode hook function.
// For OEM feature use.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Hook_ECExitDeepDozeMode(void)
{

}

//*****************************************************************************
//
// The EC exit deep sleep mode hook function.
// For OEM feature use.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Hook_ECExitDeepSleepMode(void)
{

}

//*****************************************************************************
//
// The hook function of checking EC can enter any power down mode or not.
// For OEM feature use.
//
//  Note : 10ms time based.
//          
//
//  parameter :
//      none
//
//  return :
//      "EC_PD_Idle"        EC can enter idle mode
//      "EC_PD_DeepDoze"    EC can enter deep doze mode
//      "EC_PD_DeepSleep"   EC can enter deep sleep mode
//      "EC_PD_Normal"      EC no power down mode
//
//*****************************************************************************
BYTE Hook_ECAllowPowerDownMode(void)
{
    BYTE ECLastPDMode;

    ECLastPDMode = EC_PD_Normal;    // Pre-set normal mode

    //-------------------------------------------------------
    // To add OEM feature condition here (start)
    // Idle / deep doze / deep sleep


    ECLastPDMode = g_ECPowerDownModeTest;  // For testing only.





    // To add OEM feature condition here (end)
    //-------------------------------------------------------
    
    if(ECLastPDMode != EC_PD_Normal)
    {   
        //
        // To set externel timer1 for period wake up EC from power down mode here.
        //
        SetPeriodWakeUpTimerForPDMode(3,50);
    }

    return(ECLastPDMode);
}

//*****************************************************************************
//
// After "x10ms_delay" x 10 ms, OEM feature allow firmware enter power down mode
//  Note : time based is 10ms.
//
//  parameter :
//      x10ms_delay 0 ~ 0xFFFF, time based is 10ms
//
//  return :
//      none
//
//*****************************************************************************
void Hook_OEMDelayPowerDownMode(XWORD x10ms_delay)
{
    #ifdef ECPowerDownModeStressTest
    g_OEMDelayPowerDownMode=0x00;
    #else
    if((x10ms_delay>g_OEMDelayPowerDownMode)||(x10ms_delay=0x00))
    {
        g_OEMDelayPowerDownMode = x10ms_delay;
    }
    #endif
}


//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//
// If you don't understand the use of following function, doesn't change anything.
//
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//
// The hook function of setting externel timer1 for period wake up EC from power down mode.
// For OEM feature use.
//
//  parameter :
//      period : 0          --> disable externel timer. No period wake up EC from power down mode.
//               1 ~ 120    --> wake up EC per 1 ~ 120 seconds.
//               Other      --> wake up EC per 120 seconds.
//               Time based is 1 second.
//
//      keepwakeuptime : 0 ~ 65536
//               Time based is 10 ms.
//
//  return :
//      none
//
//*****************************************************************************
void SetPeriodWakeUpTimerForPDMode(BYTE period, WORD keepwakeuptime)
{
    if(period>120)
    {
        g_ECPowerDownPeriodWakeUpTime=120;
    }
    else
    {
        g_ECPowerDownPeriodWakeUpTime=period;
    }

    Hook_OEMDelayPowerDownMode(keepwakeuptime);
}

//*****************************************************************************
//
// EC power down mode manager.
// 10ms time based is required.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECPowerDownModeManager(void)
{
    BYTE NewPDMode;

    NewPDMode = ECAllowPowerDownMode();     // EC normal/idle/deep doze/deep sleep mode. 
    ECPowerDownModeSelection(NewPDMode);    // EC enter normal/idle/deep doze/deep sleep mode.
}

//*****************************************************************************
//
// Finel check kernel code can enter which power down mode.
//
//  parameter :
//      none
//
//  return :
//      EC_KernelEventClear : Kernel code no timer event pending
//      EC_KernelEventPending : Timer event pending of kernel code
//
//*****************************************************************************
BYTE KernelEnterPowerDownMode(void)
{
    if(IS_MASK_SET(KBHISR, IBF)||IS_MASK_SET(PM1STS,P_IBF)||
        PS2StartBit||IS_MASK_SET(PSSTS3, TDS)||IS_MASK_SET(PSSTS2, TDS)||IS_MASK_SET(PSSTS1, TDS))
    {
        return(EC_KernelEventPending);
    }
    else
    {
        return(EC_KernelEventClear);
    }
}

//*****************************************************************************
//
// The EC enter idle mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
#pragma ot(8, SPEED)
void ECEnterIdleMode(void)
{
    if(KernelEnterPowerDownMode()==EC_KernelEventPending)
    {
        ECExitIdleMode();       // To exit idle mode
        EnableAllInterrupt();   // Enalbe all interrupt 
    }
    else
    {
        ECPowerDownEnableExternalTimer1();
        g_ECPowerDownCurrentMode = EC_PD_Idle;
        
        EnableAllInterrupt();
        _nop_();
        _nop_();
        _nop_();
        _nop_();  
        
        if(Isr_Int1_Occur==0)
        {
            PCON=1;             // enter idle mode
            _nop_();
            _nop_();
            _nop_();
            _nop_();
            _nop_();
            _nop_();
            _nop_();
            _nop_();
        }

        ECExitIdleMode();
        g_ECPowerDownCurrentMode = EC_PD_Normal;
    }
}

//*****************************************************************************
//
// The EC enter deep doze mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
#pragma ot(8, SPEED)
void ECEnterDeepDozeMode(void)
{
    if(KernelEnterPowerDownMode()==EC_KernelEventPending)
    {
        ECExitDeepDozeMode();
        EnableAllInterrupt();
    }
    else
    {
        ECPowerDownEnableExternalTimer1();
        g_ECPowerDownCurrentMode = EC_PD_DeepDoze;

        EnableAllInterrupt();
        _nop_();
        _nop_();
        _nop_();
        _nop_(); 

        if(Isr_Int1_Occur==0)
        {
        	PLLCTRL = 3;        
        	PCON |=2 ;           // enter deep doze mode
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        }
        
        ECExitDeepDozeMode();
        g_ECPowerDownCurrentMode = EC_PD_Normal;
    }
}

//*****************************************************************************
//
// The EC enter deep sleep mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
#pragma ot(8, SPEED)
void ECEnterDeepSleepMode(void)
{
    if(KernelEnterPowerDownMode()==EC_KernelEventPending)
    {
        ECExitDeepSleepMode();
        EnableAllInterrupt();
    }
    else
    {
        ECPowerDownEnableExternalTimer1();
        g_ECPowerDownCurrentMode = EC_PD_DeepSleep;

        EnableAllInterrupt();
        _nop_();
        _nop_();
        _nop_();
        _nop_(); 

        if(Isr_Int1_Occur==0)
        {
        	PLLCTRL = 1;
        	PCON =2 ;           // enter sleep mode
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        	_nop_();
        }

        ECExitDeepSleepMode();
        g_ECPowerDownCurrentMode = EC_PD_Normal;
    }
}

//*****************************************************************************
//
// The EC power down mode selection
//
//  parameter :
//      "EC_PD_Idle"        EC enter idle mode
//      "EC_PD_DeepDoze"    EC enter deep doze mode
//      "EC_PD_DeepSleep"   EC enter deep sleep mode
//
//  return :
//      none
//
//*****************************************************************************
void ECPowerDownModeSelection(BYTE PDMode)
{
    if(PDMode==EC_PD_Idle)
    {
        ECPrepareEnterIdleMode();
        ECEnterIdleMode();
    }
    else if(PDMode==EC_PD_DeepDoze)
    {
        ECPrepareEnterDeepDozeMode();
        ECEnterDeepDozeMode();
    }
    else if(PDMode==EC_PD_DeepSleep)
    {
        ECPrepareEnterDeepSleepMode();
        ECEnterDeepSleepMode();
    }
    else        // Illegal parameter or normal mode
    {

    }

}

//*****************************************************************************
//
// After "x10ms_delay" x 10 ms, kernel allow firmware enter power down mode
//  Note : time based is 10ms.
//
//  parameter :
//      x10ms_delay 0 ~ 255
//
//  return :
//      none
//
//*****************************************************************************
void KernelDelayPowerDownMode(BYTE x10ms_delay)
{
    #ifdef ECPowerDownModeStressTest
    g_KernelDelayPowerDownMode=0x00;
    #else
    if((x10ms_delay>g_KernelDelayPowerDownMode)||(x10ms_delay=0x00))
    {
        g_KernelDelayPowerDownMode = x10ms_delay;
    }
    #endif
}

//*****************************************************************************
//
// To check kernel code can enter which power down mode.
//
//  parameter :
//      none
//
//  return :
//      EC_KernelEventClear : Kernel code no timer event pending
//      EC_KernelEventPending : Timer event pending of kernel code
//
//*****************************************************************************
BYTE KernelTimerEventPending(void)
{
    BYTE eventpending;
    BYTE l_Service, l_Service1;

    l_Service = Service & (~BIT5);      // F_Service_MS_1
    l_Service1 = Service1& (~BIT0);     // F_Service_Low_LV
    
    #ifdef SMBusServiceCenterFunc
    if((l_Service!=0x00)||(l_Service1!=0x00)||(CheckSMBusNeedService()==SMBus_NeedService))
    #else
    if((l_Service!=0x00)||(l_Service1!=0x00))
    #endif
    {
        eventpending = 0x01;
    }
    else
    {
        eventpending = 0x00;

        if(scan.kbf_tail != scan.kbf_head)  // Keyboard buffer
        {
            eventpending++;
        }
        if(MSPending==0x33)                 // PS2 interface data pending
        {
            eventpending++;
        }  
        
        if(Timer_A.fbit.TMR_SCAN!=0)        // EC scaning internel keyboard
        {
            eventpending++;
        }

        //if(TPACKCounter!=0)               //
        //{
        //    eventpending++;
        //}

        if(AUXInactiveCounter!=0x00)
        {
            eventpending++;
        }

        #if PS2IFHotPlugHotSwap
        if(ECSendtoAUXFlag)
        {
            eventpending++;
        }
        #endif

        if(IS_MASK_SET(PSSTS1, SS)||IS_MASK_SET(PSSTS2, SS)||IS_MASK_SET(PSSTS3, SS)||PS2StartBit == 1)
        {
            eventpending++;
        }

        if(IS_MASK_SET(KBHISR, IBF)||IS_MASK_SET(PM1STS,P_IBF))
        {
            eventpending++;
        }
    }
    
    if(eventpending==0x00)                      // no event pending
    {
        if(g_KernelDelayPowerDownMode!=0x00)
        {
            g_KernelDelayPowerDownMode--;
        }

        if(g_OEMDelayPowerDownMode!=0x00)
        {
            g_OEMDelayPowerDownMode--;
        }

        if((g_KernelDelayPowerDownMode==0x00) && (g_OEMDelayPowerDownMode==0x00))
        {
            return(EC_KernelEventClear);
        }
        else
        {
            return(EC_KernelEventPending);
        }
  
    }
    else
    {
        return(EC_KernelEventPending);
    }
}

//*****************************************************************************
//
// To check EC can enter any power down mode or not.
//
//  parameter :
//      none
//
//  return :
//      "EC_PD_Idle"        EC can enter idle mode
//      "EC_PD_DeepDoze"    EC can enter deep doze mode
//      "EC_PD_DeepSleep"   EC can enter deep sleep mode
//      "EC_PD_Normal"      EC no power down mode
//
//*****************************************************************************
BYTE ECAllowPowerDownMode(void)
{
    BYTE PDMode;
    BYTE KernelPDAllow;

    PDMode = EC_PD_Normal;                              // Pre-set normal mode

    if(KernelTimerEventPending()==EC_KernelEventClear)  // If no kernel event pending  
    {
        PDMode = Hook_ECAllowPowerDownMode();           // Hook function of checking power down condition. 
    }
    else                                                // kernel doesn't allow EC enter power down mode.
    {
                                                        
    }

    return(PDMode);
}

//*****************************************************************************
//
// The EC prepare to enter idle mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECPrepareEnterIdleMode(void)
{
    DisableAllInterrupt();
    Isr_Int1_Occur = 0;

    //----------------------
    // OEM feature
    //----------------------
    Hook_ECPrepareEnterIdleMode();      // Always at the start

    //----------------------
    // Stop internel timer 0
    //----------------------
    Stop_Timer_A();

    //----------------------
    // LPC Interface
    //----------------------
    WUESR4 = BIT2;                      // Clear WU42 wakeup status
	WUENR4 |= BIT2;                     // Enable WU42

    ISR0 = Int_WKINTAD;			        // Clear INT5 interrupt flag
    SET_MASK(IER0, Int_WKINTAD);        // Enable INT5
}

//*****************************************************************************
//
// The EC exit idle mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECExitIdleMode(void)
{
    //----------------------
    // LPC Interface
    //----------------------
    CLEAR_MASK(WUENR4, BIT2);               // Disable WU42  
    WUESR4 = BIT2;                          // Clear WU42 wakeup status

    //----------------------
    // INT5
    //----------------------
    CLEAR_MASK(IER0, Int_WKINTAD);          // Disable INT5
    ISR0 = Int_WKINTAD;			            // Clear INT5 interrupt flag
    
    //----------------------
    // Disable external timer 1 interrupt
    //----------------------
    ECDisableExternalTimer1();

    //----------------------
    // Enable internel timer 0
    //----------------------
    Enable_Timer_A();

    //----------------------
    // OEM feature
    //----------------------
    Hook_ECExitIdleMode();          // Always at the start
}

//*****************************************************************************
//
// The EC prepare to enter deep doze mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECPrepareEnterDeepDozeMode(void)
{
    DisableAllInterrupt();
    Isr_Int1_Occur=0;

    //----------------------
    // OEM feature
    //----------------------
    Hook_ECPrepareEnterDeepDozeMode();  // Always at the start

    //----------------------
    // PS2 Interface
    //----------------------
    if(IS_MASK_SET(AuxFlags[0], DEVICE_IS_ATTACHED))    // PS2-0
    {
        WUEMR1 |= BIT1;             // PS2DAT0
        WUESR1 = BIT1;              // Clear WU42 wakeup status
        WUENR1 |= BIT1;             // Enable WU42
    }

    if(IS_MASK_SET(AuxFlags[1], DEVICE_IS_ATTACHED))    // PS2-1
    {
        WUEMR1 |= BIT3;             // PS2DAT1
        WUESR1 = BIT3;              // Clear WU42 wakeup status
        WUENR1 |= BIT3;             // Enable WU42
    }

    if(IS_MASK_SET(AuxFlags[2], DEVICE_IS_ATTACHED))    // PS2-2
    {
        WUEMR1 |= BIT5;             // PS2DAT2
        WUESR1 = BIT5;              // Clear WU42 wakeup status
        WUENR1 |= BIT5;             // Enable WU42
    }

    //----------------------
    // LPC Interface
    //----------------------
    WUESR4 = BIT2;                  // Clear WU42 wakeup status
	WUENR4 |= BIT2;                 // Enable WU42

    ISR0 = Int_WKINTAD;			    // Clear INT5 interrupt flag
    SET_MASK(IER0, Int_WKINTAD);    // Enable INT5

    //----------------------
    // Internel keyboard
    //----------------------
    WUEMR3 = 0xFF;                  // KSI0 ~ KSI7 falling edge
    WUESR3 = 0xFF;                  // Clear WU20 ~ WU27 wakeup status
    WUENR3 = 0xFF;                  // Enable WU20 ~ WU27

    ISR1 = Int_WKINTC;              // Clear INT13 interrupt flag
    SET_MASK(IER1,Int_WKINTC);      // Enable INT13
    
}

//*****************************************************************************
//
// The EC exit deep doze mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECExitDeepDozeMode(void)
{
    //----------------------
    // LPC Interface
    //----------------------
    CLEAR_MASK(WUENR4, BIT2);               // Disable WU42  
    WUESR4 = BIT2;                          // Clear WU42 wakeup status

    //----------------------
    // PS2 Interface
    //----------------------
    CLEAR_MASK(WUENR1, (BIT1+BIT3+BIT5));
    WUESR1 = BIT1+BIT3+BIT5;                // Clear WU42 wakeup status  

    //----------------------
    // INT5
    //----------------------
    CLEAR_MASK(IER0, Int_WKINTAD);          // Disable INT5
    ISR0 = Int_WKINTAD;			            // Clear INT5 interrupt flag

    //----------------------
    // Disable external timer 1 interrupt
    //----------------------
    ECDisableExternalTimer1();
    
    //----------------------
    // Internel keyboard
    //----------------------
    WUENR3 = 0x00;                          // Disable WU20 ~ WU27 (KSI0 ~ KSI7)
    WUESR3 = 0xFF;                          // Clear WU20 ~ WU27 wakeup status
	CLEAR_MASK(IER1,Int_WKINTC);            // Disable INT13
    ISR1 = Int_WKINTC;                      // Write to clear INT13

    //----------------------
    // Enable internel timer
    //----------------------
    Init_Timers();
    
    //----------------------
    // OEM feature
    //----------------------
    Hook_ECExitDeepDozeMode();              // Always at the start
}

//*****************************************************************************
//
// The EC prepare to enter deep sleep mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECPrepareEnterDeepSleepMode(void)
{
    DisableAllInterrupt();
    Isr_Int1_Occur=0;

    //----------------------
    // OEM feature
    //----------------------
    Hook_ECPrepareEnterDeepSleepMode(); // Always at the start

    //----------------------
    // Internel keyboard
    //----------------------
    WUEMR3 = 0xFF;                      // KSI0 ~ KSI7 falling edge
    WUESR3 = 0xFF;                      // Clear WU20 ~ WU27 wakeup status
    WUENR3 = 0xFF;                      // Enable WU20 ~ WU27

    ISR1 = Int_WKINTC;                  // Clear INT13 interrupt flag
    SET_MASK(IER1,Int_WKINTC);          // Enable INT13
}

//*****************************************************************************
//
// The EC exit deep sleep mode
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECExitDeepSleepMode(void)
{
    //----------------------
    // Internel keyboard
    //----------------------
    WUENR3 = 0x00;                          // Disable WU20 ~ WU27 (KSI0 ~ KSI7)
    WUESR3 = 0xFF;                          // Clear WU20 ~ WU27 wakeup status
	CLEAR_MASK(IER1,Int_WKINTC);            // Disable INT13
    ISR1 = Int_WKINTC;                      // Write to clear INT13

    //----------------------
    // Disable external timer 1 interrupt
    //----------------------
    ECDisableExternalTimer1();

    //----------------------
    // Enable internel timer
    //----------------------
    Init_Timers();
        
    //----------------------
    // OEM feature
    //----------------------
    Hook_ECExitDeepSleepMode();     // Always at the start  
}

//*****************************************************************************
//
// To enable external timer 1 for period wake up EC from power down mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECPowerDownEnableExternalTimer1(void)
{
    #ifdef ECPowerDownModeStressTest

    #else
    WORD timersetting;
    
    if(g_ECPowerDownPeriodWakeUpTime!=0x00)
    {
        timersetting = (WORD)(g_ECPowerDownPeriodWakeUpTime*32);
        
        CLEAR_MASK(CGCTRL1R, BIT6);     // ETWD clock operation

        ETPSR = 0x02;                   // Prescaler 32 HZ 	
        ETCNTLHR = timersetting>>8;     //
        ETCNTLLR = timersetting;        // "g_ECPowerDownPeriodWakeUpTime" second

        ISR3 = Int_EXTimer;             // Write to clear external timer 1 interrupt 
        SET_MASK(IER3, Int_EXTimer);    // Enable external timer 1 interrupt 
    }
    #endif
}

//*****************************************************************************
//
// To disable external timer 1 after wake up EC from power down mode.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void ECDisableExternalTimer1(void)
{
    #ifdef ECPowerDownModeStressTest

    #else
    CLEAR_MASK(IER3, Int_EXTimer);  // Disable external timer 1 interrupt 
    ISR3 = Int_EXTimer;             // Write to clear external timer 1 interrupt 
    #endif
}

#endif

