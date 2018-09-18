/*-----------------------------------------------------------------------------
* TITLE: API_SSPI.H
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
 
#ifndef API_SSPI_H
#define API_SSPI_H

#define API_SSPI_SUPPORT 		0
#if API_SSPI_SUPPORT

#ifndef SPI_Channel_0
#define SPI_Channel_0       0x00
#endif

#ifndef SPI_Channel_1
#define SPI_Channel_1       0x01
#endif

#ifndef SPI_Channel_0N1
#define SPI_Channel_0N1     0x02
#endif

#ifndef SPI_SupportBusy
#define SPI_SupportBusy     0x01
#endif

#ifndef SPI_NoSupportBusy
#define SPI_NoSupportBusy   0x00
#endif

#ifndef SSCK
#define SSCK                GPCRA6
#endif

#ifndef SMOSI
#define SMOSI               GPCRC3
#endif

#ifndef SMISO
#define SMISO               GPCRC5
#endif

#ifndef SSCE1
#define SSCE1               GPCRG0
#endif

#ifndef SSCE0
#define SSCE0               GPCRG2
#endif

extern void Init_SPIInterface_API(BYTE channel, BYTE supportbusy);
extern void Disable_SPIInterface_API(BYTE channel);
extern void Enable_SPIInterface0_API(void);
extern void SPITransmissionEnd_API(void);
extern void SPIWriteByte_API(BYTE spidata, BYTE channel);
extern void SPIWriteWord_API(BYTE MSB, BYTE LSB, BYTE channel);
extern BYTE SPIReadByte_API(BYTE channel);
extern WORD SPIReadWord_API(BYTE channel);

#endif
#endif