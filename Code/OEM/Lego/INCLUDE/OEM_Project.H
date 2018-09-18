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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ITE EC Function Setting and selection
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define HW_Mirror_Only_Once   TRUE   // TRUE : Support HW Mirror Once
                                     // FALSE: Support Always Mirrir

//#define Enable_HW_Mirror_Function

/*
EC_Signature_Flag Usage

bit 7:
    1b: Disable.
    0b: Enable PWM blinking during hardware started mirror sequence.

    Enable PWM blinking during hardware started mirror sequence if EC_Signature_Addr is not 00h.
    (Disable PWM blinking during hardware started mirror sequence if EC_Signature_Addr is 00h.)

bit 6:
    0b: Disable.
    1b: Suspend internal-to-external clock switching request.
        When this bit is set, the internal clock would act as a temporary clock to enable EC to configure some GPIO
        setting before the external crystal is ready to work.
        This bit is available only when the EC_Signature_Flag¡¦s bit 4 is 0.
        Refer to section 7.6.3.8 PLL Clock Source Status (PLLCSS).
    
bit 5:
    1b: Disable
    EC_Signature_Addr must be AAh.
    0b: Enable FSPI I/F and mirror function.
    EC_Signature_Addr indicates the compared range ADDR [17:10] between e-flash and SPI flash.
    The compared range is up to 128K-byte and is multiple of 4K-byte.
    ADDR[17] must be 0b. ADDR[11:10] must be 11b.

bit 4:
    0b: 32.768 kHz is oscillated by the external crystal connected to CK32K and CK32KE pins.
    1b: The ¡§Crystal-Free¡¨ feature is enabled and 32.768kHz is from the internal clock generator.

bit 3:
    0b: Use implicit format to describe the EC code base and the 16B-signature must be inside the EC code.
    15th and 16th byte must be 55h and 55h and the EC code base is located at the origin of this 4K block of
    16B-signature.
    For example, let the address of 1st byte be ADDR1[23:0], then the EC code base is loated at
    (ADDR1[23:12] * 2^12).
    1b: Use explicit format to describe the EC code base and the 16B-signature must be outside the EC code.
    15th byte indicates the EC code base address bit 23-16.
    16th byte indicates the EC code base address bit 15-12.
    The 15th/16th is don¡¦t-care if the 16B-signature is on e-flash.

bit 2:
    1b: Don¡¦t check the CRC-16 after mirror
    11th and 12th byte must be 5Ah and 5Ah.
    0b: Check the CRC-16 after mirror and uC halt if CRC is corrupted.
    11th byte indicates the expected high byte of CRC-16 after mirror code from SPI flash to eflash.
    12th byte indicates the expected low byte of CRC-16 after mirror code from SPI flash to eflash.
    The CRC-16 calculate except 16B-signature.

bit 1:
    It must be 0b.
    8th byte¡¦s bit 0:
    0b: Blinking on PWM0 if b7 = 0
    1b: Blinking on PWM1 if b7 = 0
*/

#ifdef Enable_HW_Mirror_Function
//Enable mirror
#define EC_Signature_Flag	    0x94    // Enable HW MIRROR Function
#define EC_Signature_Addr	    0x7F    // 0x3F:64K ,0x7F:128K
#else
//Disable mirror
#define EC_Signature_Flag	    0xB4    // Disable HW MIRROR Function
#define EC_Signature_Addr	    0xAA    // Must be set 0xAA,if Disable the Mirror
#endif				            

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
#define PECI_Support                // Define : support PECI function
//#define ECPowerDownModeSupport

#ifdef ECPowerDownModeSupport
//#define ECPowerDownModeStressTest
#endif

//*****************************************************************************
//-----------------------------------------------------------------------------
// OEM support function selection
//-----------------------------------------------------------------------------
//*****************************************************************************
#define ADCFuncSupport			FALSE   // True : support ADC function

#define LEDFuncSupport          TRUE   // True : support LEC control function

//-----------------------------------------------------------------------------
// Fan & Thermal
//-----------------------------------------------------------------------------
#define SmartFanSupport         TRUE    // True : Support smart fan control function
#define GetCPUTempSupport       TRUE    // True : get cpu temperature via PECI or thermal sensor per second

//-----------------------------------------------------------------------------
// PECI
//-----------------------------------------------------------------------------
#ifdef PECI_Support
#define ReadCPUTemperature      TRUE    // 1 : Getting CPU temperature via PECI interface
#define ReadDRAMTemperature     FALSE   // 1 : Getting DRAM temperature via PECI interface
#define ACTurboControlAlgorithm FALSE
#endif

//-----------------------------------------------------------------------------
// OEM_Event.C Debounce time setting
//-----------------------------------------------------------------------------
#define T_AC_DEBOUNCE    	    5       // 50 ms (timebase: 10 ms)
#define T_PSW_DEBOUNCE   	    5    	// 50 ms (timebase: 10 ms)
#define T_BAT_DEBOUNCE   	    15      // 150 ms (timebase: 10 ms)
#define T_PSWOFF         	    500 	// 5 secs (timebase: 10ms) EC 5sec override turn off system power
#define T_EXTEVT_DEBOUNCE 	    10      // 100 ms (timebase: 10 ms)

//-------------------------------------
// KBC  SMBus/I2C interface device
// define Smbus Chanel and address
//-------------------------------------
// SMbus Device list :
#define DefAtiVgaSMBusCH		SMbusChA
#define DefAtiVgaSMBusAddr    	0x9E    

//-------------------------------------
//	Status LED behavior
//-------------------------------------
#define	STATUS_LED_POWERON		0x01
#define	STATUS_LED_NOT_PAIRED	0x02
#define STATUS_LED_PAIRING		0x04
#define STATUS_LED_PAIRED		0x08
#define	STATUS_LED_POWEROFF		0x10
#endif
