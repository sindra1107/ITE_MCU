/*-----------------------------------------------------------------------------
 * TITLE: CORE_HSPI.H
 *
 * Copyright (c) 2009- , ITE Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#ifndef CORE_HSPI_H
#define CORE_HSPI_H

#define HSPI_ECCodeSpaceAddr    0x18    // EC code space is 0x18xxxx

#define PLLFreqSetting03        0x03    // 32.3 MHZ PLL frequency
#define PLLFreqSetting05        0x05    // 46.0 MHZ PLL frequency
#define PLLFreqSetting07        0x07    // 64.5 MHZ PLL frequency

#define SPIReadMode_0           0x00    // Read cycle
#define SPIReadMode_1           0x01    // Fast read cycle
#define SPIReadMode_2           0x02    // Fast read dual output
#define SPIReadMode_3           0x03    // Fast read dual input/output

#define HSPI_RequestSelection_0 0x00    // Setting 0, 1, 2, and 3
#define HSPI_RequestSelection_1 0x01    // Setting 6 and 7
#define HSPI_RequestSelection_2 0x02    // Setting 5
#define HSPI_RequestSelection_3 0x03    // Reserved

extern void FuncAt_0xFE00(void);
extern void GPIO_HSPI_INIT(void);
extern void Enable_HSPI(void);
extern void Disable_HSPI(void);
extern void HSPI_RamCode(void);
extern void HSPI_CmdRamCode(void);
extern void ChangePLLFrequency(BYTE newseting);
extern void ChangeSPIFlashReadMode(BYTE Mode);
extern void ChangeHSRSMode(BYTE Mode);

#endif