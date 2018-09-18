/*-----------------------------------------------------------------------------
 * TITLE: CORE_INIT.H
 *
 * Author : Dino
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
 
#ifndef CORE_INIT_H
#define CORE_INIT_H

//-----------------------------------------------------------------------------
// Base address select 0x00:2E/2F 0x01:4E/4F 0x02:User define  
//-----------------------------------------------------------------------------
#define Core_Init_BADR          0x02    // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define SWCBALR | SWCBAHR 
#define Core_Init_SWCBAHR       0x00    // I/O Port High Byte 
#define Core_Init_SWCBALR       0x4E    // I/O Port Low  Byte
#define Core_Init_I2EC          0x43    // Enable I2EC R/W and log 80 port 
#define Core_Init_FMSSR	        0x1F	// 0x1F 2M Bytes Share Rom 	
                                        // 0x0F 1M Bytes Share Rom 
							            // 0x07 512K Bytes Share Rom

#define LED_CTRL_INIT 		(MASK(SCROLL) | MASK(NUM) | MASK(CAPS) | MASK(OVL))
#define SAVE_KBD_STATE_INIT (maskAUXENAB + (2 << shiftCODESET))
#define CCB42_INIT			DISAB_KEY
#define EXT_CB2_INIT    	0x22		
#define SAVE_TYPEMATIC_INIT 0x2A

extern void Core_Initialization(void);
extern void Core_Init_ClearRam(void);
extern void Core_Init_Regs(void);

typedef struct REG_INIT
{
    XBYTE 	*address;
    BYTE  	initdata;
} sREG_INIT;

#endif