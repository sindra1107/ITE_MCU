/*-----------------------------------------------------------------------------
 * TITLE: OEM_LED.H
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

#ifndef OEM_LED_H
#define OEM_LED_H

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void OEM_Write_Leds(BYTE data_byte);
extern void ProcessLED(void);
extern void DebugLED(void);

#endif