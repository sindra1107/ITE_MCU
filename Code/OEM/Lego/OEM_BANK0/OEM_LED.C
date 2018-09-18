/*-----------------------------------------------------------------------------
 * TITLE: OEM_LED.C
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
 * FUNCTION:   OEM_Write_Leds
 *
 * Write to SCROLL LOCK, NUM LOCK, CAPS LOCK, and any custom LEDs (including
 * an "Fn" key LED).
 *
 * Input: data (LED_ON bit) = Data to write to the LEDs
 *         bit 0 - SCROLL, Scroll Lock
 *         bit 1 - NUM,    Num Lock
 *         bit 2 - CAPS,   Caps Lock
 *         bit 3 - OVL,    Fn LED
 *         bit 4 - LED4,   Undefined
 *         bit 5 - LED5,   Undefined
 *         bit 6 - LED6,   Undefined
 *         bit 7 - LED7,   Undefined
 *
 * Updates Led_Data variable and calls send_leds if appropriate.
 * ------------------------------------------------------------------------- */
void OEM_Write_Leds(BYTE data_byte)
{
    Led_Data = data_byte;
    if ( data_byte & BIT1 )
    {
	   	Hook_NUMLED_ON();
    }
 	else
 	{
		Hook_NUMLED_OFF();
 	}
	
    if ( data_byte & BIT2 )
    {
		Hook_CAPLED_ON();
    }
	else
	{
		Hook_CAPLED_OFF();
	}
}

//-----------------------------------------------------------------
// LED pattern
//-----------------------------------------------------------------
//#define  BATLED_LEN      6
#define  PWRLED_LEN      6

//const WORD code BattLEDPattern[]= 
//{
//	//-------------------------------------------------------------
// 	//	BAT_FUL BAT_CHG BAT_DSG BAT_OUT BAT_LOW BAT_FAIL     
//  	//-------------------------------------------------------------
// 		0x0000, 0x5555, 0x0000, 0x0000, 0x0000, 0x0000,  	// Battery LED1 
// 		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   	// Battery LED2 
//};

const WORD code PowerLEDPattern[]= 
{
  	//--------------------------------------------------------------------------
  	// 	S0      S3   	S4      S5      index4  index5    					 
	//--------------------------------------------------------------------------
  		0xFFFF, 0x5555, 0x4444, 0x0000, 0x0000, 0x0000,		//	Power LED1
      	0x0000, 0x5555, 0x4444, 0x0000, 0x0000,	0x0000,		// 	Power LED2
};

//----------------------------------------------------------------------------
// Turn on/off LEDs according to machine status.
// Executed once per 1 sec
// for example:
//		 ->BIT14	
// 		1010101010101010
// 		0101010101010101
//				  <-BIT3 				
//----------------------------------------------------------------------------
void ProcessLED(void) 
{
	BYTE bat_index, pwr_index;   
    
   	LED_FLASH_CNT <<= 1;
	if(LED_FLASH_CNT == 0)	LED_FLASH_CNT=0x0001;

    /* Power LED control method */
    pwr_index=0;                // pre-set S0                  
    
	if(SystemIsS5)              // pre-set S5    
	{
		pwr_index=3;
	}
	if(SystemIsS4)              // pre-set S4   
	{
		pwr_index=2;
	}
	if(SystemIsS3)              // pre-set S3    
	{
		pwr_index=1;
	}

	if(PowerLEDPattern[pwr_index] & LED_FLASH_CNT)	// setup power LED
	{	
		PWRLED1_ON();
	} 
	else 
	{	
		PWRLED1_OFF();
	}
//	if(PowerLEDPattern[PWRLED_LEN+pwr_index] & LED_FLASH_CNT) 
//	{
//	    PWRLED2_ON();	 
//	} 
//	else 
//	{
//	    PWRLED2_OFF();	 
//	}
    
#if 0
    /* Battery LED control method */
    bat_index = 0x03;           // pre-set battery out 


	if(BattLEDPattern[bat_index] & LED_FLASH_CNT) 
	{		
		BATLED1_ON();
	} 
	else 
	{		
		BATLED1_OFF();
	}
	
	if(BattLEDPattern[BATLED_LEN+bat_index] & LED_FLASH_CNT)	 
	{		
		BATLED2_ON();
	} 
	else 
	{		
		BATLED2_OFF();
	}
#endif
}

//----------------------------------------------------------------------------
// The function of turning on all LED		
//----------------------------------------------------------------------------
void TurnOnAllLED(void)
{
	PWRLED1_ON();
//	BATLED1_ON();
//	BATLED2_ON();
//    NUMLED_ON();
//    CAPLED_ON();
}

//----------------------------------------------------------------------------
// The function of turning off all LED		
//----------------------------------------------------------------------------
void TurnOffAllLED(void)
{
	PWRLED1_OFF();
//	BATLED1_OFF();
//	BATLED2_OFF();
//    NUMLED_OFF();
//    CAPLED_OFF();
}
//----------------------------------------------------------------------------
// The function of debuging LED			
//----------------------------------------------------------------------------
void DebugLED(void) 
{

}
