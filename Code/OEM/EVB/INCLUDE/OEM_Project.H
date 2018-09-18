/*----------------------------------------------------------------------------
 * Filename: OEM_PROJECT.H  For Chipset: ITE.IT85XX
 *
 * Function: Project function selection.
 * 
 * Copyright (c) 2009 - , ITE Tech. Inc. All Rights Reserved. 
 *
 *---------------------------------------------------------------------------*/

#ifndef OEM_Project_H
#define OEM_Project_H

//*****************************************************************************
// Kernel code feature
//*****************************************************************************
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function define
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ITE_EVBoard

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function Setting and selection
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define EC_Signature_Flag	    0xB5    // For 8518 crystal free

//-----------------------------------------------------------------------------
// PS2 interface
//-----------------------------------------------------------------------------
#define TouchPad_only           TRUE    // True : Only touch pad device in this project
                                        /* Note : If TouchPad_only is set, remeber to call 
                                            PowerOffClearTPPendingData() function in power off sequnce
                                            include (S3, S4, and S5)¡C*/   

#if TouchPad_only                                     
#define MultiplexedModes        FALSE   // 0 : Doesn't support multiplexed modes.
#define PS2IFHotPlugHotSwap     FALSE   // 1 : Support PS2 interface hot-plug, hot-swap
//#define Hook_Func_DisableTP           // Support "Hook_DisableInternalTB" for EC on/off touchpad
#else
#define MultiplexedModes        TRUE    // 1 : Support multiplexed modes.
#define PS2IFHotPlugHotSwap     FALSE   // 1 : Support PS2 interface hot-plug, hot-swap
#endif

//-----------------------------------------------------------------------------
// Keyboard scan
//-----------------------------------------------------------------------------
#define KB_FnStickKey           FALSE   // True : for Fn stick key function
//#define KB_HW_KeyScan                 // To support hardward keyscan


//*****************************************************************************
// UART debug interface
// Timer 2 baudrate = Fosc / 32 / (0x10000-RCAP2)¡C
//*****************************************************************************
//#define UART_Debug        // Define : enable Tx debug (GPIO B1)

#ifdef UART_Debug 
// 9600 bps-------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xE2  
// 9600 bps-------------------------

// 19200 bps------------------------
//#define R2HV                  0xFF
//#define R2LV                  0xF1  
// 19200 bps------------------------

// 57600 bps------------------------
#define R2HV                    0xFF
#define R2LV                    0xFB  
// 57600 bps------------------------
#endif


//*****************************************************************************
// OEM code feature
//*****************************************************************************
//#define ECPowerDownModeSupport

#ifdef ECPowerDownModeSupport
//#define ECPowerDownModeStressTest
#endif

#endif
