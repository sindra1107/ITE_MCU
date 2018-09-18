/*-----------------------------------------------------------------------------
 * TITLE: CORE_TIMERS.C
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *----------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// FUNCTION: Load_Timer_A - Load Timer A to time-out in 5 mS.
//----------------------------------------------------------------------------
void Load_Timer_A(void)
{   						// Assume the 8051 clock source is Ring Oscillator 
	//TL0 = Timer_5ms;    	// Reload timer
	//TH0 = Timer_5ms>>8;	// 5ms
	TL0 = Timer_1ms;      	// Reload timer
	TH0 = Timer_1ms>>8;	    // 1ms
    TF0 = 0;				// Clear overflow flag
}

//----------------------------------------------------------------------------
// FUNCTION: Enable_Timer_A - Load the 5 mS timer if not already enabled.
//----------------------------------------------------------------------------
void Enable_Timer_A(void)
{
 	Load_Timer_A();			// Reload timer0 
 	TR0 = 1;				// Enable timer0
}

//----------------------------------------------------------------------------
// FUNCTION: Stop_Timer_A - Stop the 5 mS timer.
//----------------------------------------------------------------------------
void Stop_Timer_A(void)
{
	TR0 = 0;				// Disable timer0
	TF0 = 0;				// Clear timer0 overflow flag
}

//----------------------------------------------------------------------------
// FUNCTION: Load_Timer_B - Load Timer B to time-out in 150 microseconds.
//----------------------------------------------------------------------------
void Load_Timer_B(void)
{   
    TL1 = Timer_2ms;      	// Reload timer
    TH1 = Timer_2ms>>8; 	// 2ms
	TF1 = 0;				// Clear overflow flag		
	TR1 = 1;				// Enable timer1
}

//----------------------------------------------------------------------------
// FUNCTION: Stop_Timer_B - Stop the timer B.  Timer 1 is used as Timer B.
//----------------------------------------------------------------------------
void Stop_Timer_B(void)
{
	TR1 = 0;				// Disable timer1	
	TF1 = 0;				// Clear overflow flag	
	F_Service_SEND = 0;		// Clear service sned flag
}

//----------------------------------------------------------------------------
// FUNCTION: Init_Timers
//----------------------------------------------------------------------------
void Init_Timers(void)
{
    TF0 = TR0 = 0;        	// Stop timer0 and clear interrupt
	//TL0 = Timer_5ms;    	// Reload timer
	//TH0 = Timer_5ms>>8;	// 5ms
	TL0 = Timer_1ms;      	// Reload timer
	TH0 = Timer_1ms>>8;	    // 1ms
	TMOD  = 0x11;			// Timer0 and timer1 are 16 bits timer
    TR0 = 1;                // Start timer0 running
    ET0 = 1;				// Enable timer0 interrupt
							
    TF1 = TR1 = 0;       	// Stop timer 1 and clear interrupt
    TL1 = Timer_2ms;      	// Reload timer
    TH1 = Timer_2ms>>8; 	// 2ms
    //TR1 = 1;           	// Start timer1 
    ET1 = 1;				// Enable timer1 interrupt
}

//----------------------------------------------------------------------------
// FUNCTION: Microsecond_Delay - Delay a number of microseconds.
// Input:  Code for delay.
//----------------------------------------------------------------------------
//void Microsecond_Delay(WORD delay)
//{
//  do 
//	{
//      delay--;        
//  } while (delay);                      
//}

//----------------------------------------------------------------------------
// Delay 1ms function use timer 1                     
//----------------------------------------------------------------------------
void Delay1MS(BYTE bMS)
{	
    TR1 = 0;				// Disable timer1
	ET1 = 0;				// Disable timer1 interrupt
	DisableAllInterrupt();
	for (;bMS!=0;bMS--)
	{
		TH1=Timer_1ms>>8;	// Re-load 1ms timer
    	TL1=Timer_1ms;
        TF1=0;				// Clear overflow flag
		TR1=1;				// enable timer
		while (!TF1);		// waiting for time-out
	    TR1=0;				// Disable timer
		TF1=0;				// Clear overflow flag
	}

	EnableAllInterrupt();   // Enable timer1 interrupt 
	ET1 = 1;								
	//TR1=1;			    // Enable timer1	
}

//----------------------------------------------------------------------------
// Delay Xms function                  
//----------------------------------------------------------------------------
void DelayXms(BYTE bMS)
{
    TR1 = 0;
	ET1 = 0;			// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
	for (;bMS!=0;bMS--)
	{
		TH1=Timer_1ms>>8;
    	TL1=Timer_1ms;
        TF1=0;
		TR1=1;
		while (!TF1);
        TR1=0;
		TF1=0;
	}
	ET1 = 1;	
}

//----------------------------------------------------------------------------
// INIT UART
//----------------------------------------------------------------------------
void Init_UART(void)
{
#ifdef UART_Debug
   	//GPCRB0=ALT;
    GPCRB1=ALT;
    SCON=0x40;
    T2CON &= 0xF0;               /* EXEN2=0; TR2=0; C/T2#=0; CP/RL2#=0; */
    T2CON |= 0x30;               /* RCLK = 1; TCLK=1; */
    T2MOD=0x00;
    RCAP2H=R2HV;
    RCAP2L=R2LV;
    TR2=1;
    TI = 1;
#endif    
}
