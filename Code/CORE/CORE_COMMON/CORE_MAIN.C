/*-----------------------------------------------------------------------------
 * TITLE: CORE_MAIN.C - Main Program for KBC firmware.
 *
 * Main processing loop (interrupt driven) for the keyboard controller/scanner.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

/* ----------------------------------------------------------------------------
 *  FUNCTION: main - Main service loop.
 *
 *  Wait in idle state until an IRQ causes an exit from idle.  If the IRQ
 *  handler posted a service request (via bSERVICE) then dispatch control to
 *  the appropriate service handler.  Otherwise, go back to idle state.  After
 *  all service requests have been handled, return to idle state.
 * ------------------------------------------------------------------------- */
void main(void)
{
	DisableAllInterrupt();
	SP = 0xC0;					// Setting stack pointer
    ResetBANKDATA();            // init bank mechanism to code bank 0
    
	if(Hook_ECRetunrMainFuncKeepCondition()==0x33)  // Exit from follow mode or EC scatch ROM
	{
		CLEAR_MASK(FBCFG,SSMC); // disable scatch ROM
		_nop_();
	    MPRECF = 0x01;
	    _nop_();
	    MPRECF = 0x01;
	    _nop_(); 
	    MPRECF = 0x01;
	    _nop_();
	    MPRECF = 0x01;
	    _nop_();
	    _nop_();
        WinFlashMark = 0x00;
        //ResetBANKDATA();        // init bank mechanism to code bank 0
        Hook_ECExitFollowMode();
        Init_Timers();
		EnableModuleInterrupt();    
	}
	else
	{
		Core_Initialization();
		Oem_Initialization();
        InitEnableInterrupt();
        #ifdef UART_Debug
        Init_UART();
        printf("\n************************************");
        printf("\nEC Init OK !!!");
        printf("\n************************************");
        #endif
	}

	while(1)
   	{
        if(OEM_SkipMainServiceFunc()==Normal_MainService)
        {
    		main_service();
    		EnableModuleInterrupt();
    		_nop_();
    		_nop_();
    		_nop_();
    		_nop_();

            #if TouchPad_only

            #else
            if(PS2CheckPendingISR()==0x00)
            {
                ScanAUXDeviceStep();
            }
            #endif

            #ifdef SMBusServiceCenterFunc
    		if((Service==0x00)&&(Service1==0x00)&&(CheckSMBusNeedService()==SMBus_ClearService))
            #else
            if((Service==0x00)&&(Service1==0x00))
            #endif
    		{
         		PCON=1;      		// enter idle mode
    		}
        }
  	} 
}

/* ----------------------------------------------------------------------------
 * FUNCTION: main_service - Check for new/more service requests.
 *
 * Check for a request flag.  The check is done according to priority.  If a
 * request flag is set, handle the request and loop back to get the flags
 * again.  Do not follow through to check the next flag.  The flags are to be
 * checked in order.
 * ------------------------------------------------------------------------- */
void main_service(void) 
{
    #ifdef SMBusServiceCenterFunc
    while((Service!=0x00)||(Service1!=0x00)||(CheckSMBusNeedService()==SMBus_NeedService))
    #else
    while((Service!=0x00)||(Service1!=0x00))
    #endif
    {
        //-----------------------------------
        // Host command/data service
        //-----------------------------------
        if(F_Service_PCI)
        {
            F_Service_PCI=0;
            service_pci1();
            continue;
        }

        //-----------------------------------
        // Service unlock
        //-----------------------------------
        if(F_Service_UNLOCK)
        {
            F_Service_UNLOCK=0;
            service_unlock();
            continue;
        }

        //-----------------------------------
        // Send byte from KBC
        //-----------------------------------
        if(F_Service_SEND)
        {
            F_Service_SEND=0;
            service_send();
            continue;
        }

        //-----------------------------------
        // Send PS2 interface data	
        //-----------------------------------
        if(F_Service_Send_PS2)
        {
            F_Service_Send_PS2=0;
            service_PS2_data();
            continue;
        }

        //-----------------------------------
        // process PS2 interface data
        //-----------------------------------
        if(F_Service_PS2)
        {
            F_Service_PS2=0;
            service_ps2();
            continue;
        }

        //-----------------------------------
        // process SMBus interface data
        //-----------------------------------
        #ifdef SMBusServiceCenterFunc
        ServiceSMBus();
        #endif

        //-----------------------------------
        // 1 millisecond elapsed
        //-----------------------------------
        if(F_Service_MS_1)
        {
            F_Service_MS_1=0;
            service_1mS();
            continue;
        }

        //-----------------------------------
        // Secondary Host command/data service
        //-----------------------------------
        if(F_Service_PCI2)
        {
            F_Service_PCI2=0;
            service_pci2();
            continue;
        }

        //-----------------------------------
        // Keyboard scanner service
        //-----------------------------------
        if(F_Service_KEY)
        {
            F_Service_KEY=0;
            service_scan();
            continue;
        }

        //-----------------------------------
        //
        //-----------------------------------
        Hook_main_service_H();
        
        //-----------------------------------
        // Low level event
        //-----------------------------------
        if(F_Service_Low_LV)
        {
            F_Service_Low_LV=0;
            service_Low_LVEvent();
            continue;
        } 

        //-----------------------------------
        // Third Host command/data service
        //-----------------------------------
        if(F_Service_PCI3)
        {
            F_Service_PCI3=0;
            service_pci3();
            continue;
        }

        //-----------------------------------
        // CIR IRQ
        //-----------------------------------
        if(F_Service_CIR)
        {
            F_Service_CIR=0;
            service_cir();
            continue;
        }

        //-----------------------------------
        // fourth command/data service
        //-----------------------------------
        if(F_Service_PCI4)
        {
            F_Service_PCI4=0;
            service_pci4();
            continue;
        }

        //------------------------------------
        // service_OEM_1
        //------------------------------------
        if(F_Service_OEM_1)
        {
            F_Service_OEM_1=0;
            service_OEM_1();
            continue;
        }

        //------------------------------------
        // service_OEM_2
        //------------------------------------
        if(F_Service_OEM_2)
        {
            F_Service_OEM_2=0;
            service_OEM_2();
            continue;
        }

        //------------------------------------
        // service_OEM_3
        //------------------------------------
        if(F_Service_OEM_3)
        {
            F_Service_OEM_3=0;
            service_OEM_3();
            continue;
        }

        //------------------------------------
        // service_OEM_4
        //------------------------------------
        if(F_Service_OEM_4)
        {
            F_Service_OEM_4=0;
            service_OEM_4();
            continue;
        }

        //-----------------------------------
        //
        //-----------------------------------
        Hook_main_service_L();
    }
}

static void service_Low_LVEvent(void)
{
	if((KBPendingTXCount != KBPendingRXCount )||(scan.kbf_head != scan.kbf_tail))
	{
		SetServiceSendFlag();
	}

    if(IS_MASK_SET(KBHISR,P_IBF))
    {
  	    F_Service_PCI = 1;
    }
    
    if(IS_MASK_SET(PM1STS,P_IBF))
    {
  	    F_Service_PCI2 = 1;
    }
}

//----------------------------------------------------------------------------
// FUNCTION: service_unlock
// Unlock aux devices and re-enable Host interface IRQ if it is ok to do so.
//----------------------------------------------------------------------------
static void service_unlock(void)
{
	Unlock_Scan();
}

//------------------------------------------------------------
// Polling events
//------------------------------------------------------------
void service_1mS(void)
{
	Timer1msEvent();
	Timer1msCnt++;
    if(Timer1msCnt>=10)
    {
        Timer1msCnt = 0x00;
    }

    if(Hook_Only_Timer1msEvent()==Only_Timer1msEvent)
    {   
        return;
    }

    if((Timer1msCnt%5)==0x00)
    {
	    Timer5msEvent();
	    Timer5msCnt++;
	    if ( Timer5msCnt & 1 )  	// 10ms events
	    {
            Timer10msEventA();
	    }
	    else
	    {
		    Timer10msEventB();
     	    switch( Timer5msCnt )   // Share Loading Branch Control
    	    {
       		    case 2: Timer50msEventA();
                    break;
          	    case 4: Timer50msEventB();
             	    break;
        	    case 6: Timer50msEventC();
              	    break;
          	    case 8: Timer100msCntB++;
         		    if ( Timer100msCntB & 1 )
             	    {
                  	    Timer100msEventA();
              	    }
             	    else
             	    {
                   	    Timer100msEventB();
              	    }
               	    break;

           	    default:        
				    Timer5msCnt=0;
              	    break;
     	    }

    	    if ( Timer5msCnt == 0x00 )
    	    {       			// 50msec
          	    Timer100msCnt ++;
          	    if ( Timer100msCnt & 1 )
         	    {
             	    Timer100msEventC();
          	    }
         	    else
     		    {       		// 100msec
          		    switch( Timer100msCnt )
              	    {
                	    case 2:	Timer500msEventA();
                 		    break;
                 	    case 4:	Timer500msEventB();
                      	    break;
                 	    case 6:	Timer500msEventC();
                     	    break;
                 	    case 8:	Timer1SecEventA();
                     	    break;
					    case 10: 	Timer1SecEventB();
                     	    break;	
                 	    case 12:	Timer500msEventA();
                      	    break;
                	    case 14:	Timer500msEventB();
                      	    break;
               		    case 16: 	Timer500msEventC();
                      	    break;
                 	    case 18: 	Timer1SecEventC();
                     	    break;
                  	    default:        // 1 Sec
                      	    Timer100msCnt = 0;
                  		    Timer1SecCnt ++;
                    	    if ( Timer1SecCnt == 60 )
                      	    {
                         	    Timer1MinEvent();
                         	    Timer1SecCnt=0;
                     	    }
                    	    break;
          		    }
              	}
       		}
   		}
	} 
}

//------------------------------------------------------------
// 1ms events
//------------------------------------------------------------
void Timer1msEvent(void)
{
    ReSendPS2PendingData();
    Hook_Timer1msEvent(Timer1msCnt);
}

//------------------------------------------------------------
// 5ms events
//------------------------------------------------------------
void Timer5msEvent(void)
{
    F_Service_Low_LV = 1;
	if (Timer_A.fbit.TMR_SCAN) 
	{
        #ifdef KB_HW_KeyScan
        HW_KB_Check_TM();
        #else
  		F_Service_KEY = 1;		// Request scanner service. 
  		#endif  // KB_HW_KeyScan
  	}
    Hook_Timer5msEvent();
}

//------------------------------------------------------------
// 10ms events
//------------------------------------------------------------
void Timer10msEventA(void)
{
    SetStartScanAUXFlag();
	Hook_Timer10msEventA();	
}

//------------------------------------------------------------
// 10ms events
//------------------------------------------------------------
void Timer10msEventB(void)
{
	Hook_Timer10msEventB();	 
}

//------------------------------------------------------------
// 50ms events A
//------------------------------------------------------------
void Timer50msEventA(void)
{
	Hook_Timer50msEventA();
}

//------------------------------------------------------------
// 50ms events B
//------------------------------------------------------------
void Timer50msEventB(void)
{
	Hook_Timer50msEventB();
}

//------------------------------------------------------------
// 50ms events C
//------------------------------------------------------------
void Timer50msEventC(void)
{
	Hook_Timer50msEventC();
}

//------------------------------------------------------------
// 100ms events A
//------------------------------------------------------------
void Timer100msEventA(void)
{
	Hook_Timer100msEventA();
}

//------------------------------------------------------------
// 100ms events B
//------------------------------------------------------------
void Timer100msEventB(void)
{
	Hook_Timer100msEventB();
}

//------------------------------------------------------------
// 100ms events C
//------------------------------------------------------------
void Timer100msEventC(void)
{
	Hook_Timer100msEventC();
}

//------------------------------------------------------------
// 500ms events A
//------------------------------------------------------------
void Timer500msEventA(void)
{
	Hook_Timer500msEventA();
}

//------------------------------------------------------------
// 500ms events B
//------------------------------------------------------------
void Timer500msEventB(void)
{
	Hook_Timer500msEventB();
}

//------------------------------------------------------------
// 500ms events C
//------------------------------------------------------------
void Timer500msEventC(void)
{
	Hook_Timer500msEventC();
}

//------------------------------------------------------------
// 1sec events A
//------------------------------------------------------------
void Timer1SecEventA(void)
{	
	Hook_Timer1SecEventA();
}

//------------------------------------------------------------
// 1sec events B
//------------------------------------------------------------
void Timer1SecEventB(void)
{
	Hook_Timer1SecEventB();
}

//------------------------------------------------------------
// 1sec events C
//------------------------------------------------------------
void Timer1SecEventC(void)
{
	Hook_Timer1SecEventC();
}

//------------------------------------------------------------
// 1min events
//------------------------------------------------------------
void Timer1MinEvent(void)
{
    Hook_Timer1MinEvent();
}

