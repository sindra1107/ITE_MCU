/*-----------------------------------------------------------------------------
* TITLE: API_SSPI.C
*
* Author : Dino
*
* History : 
* ------------------------------
* Version : 1.10
* ------------------------------
*
* Note : To link [api_xxx.o] if related api function be used.
*
*---------------------------------------------------------------------------*/
 
//*****************************************************************************
// Include all header file
#include <CORE_INCLUDE.H>
#include <API_INCLUDE.H>
//
//*****************************************************************************
#if API_SSPI_SUPPORT
//*****************************************************************************
//
// Init SPI interface function
//
//  parameter :
//      SPI_Channel_0   SPI channel 0 enable.
//      SPI_Channel_1   SPI channel 1 enable.
//      SPI_Channel_0N1 SPI channel 0 and 1 enable.
//
//  return :
//      none
//
//*****************************************************************************
void Init_SPIInterface_API(BYTE channel, BYTE supportbusy)
{
    BYTE settingOK;

    settingOK = 0x01;   // Pr-set OK
    
    if(channel==SPI_Channel_0)
    {
        GCR1 |= SPICTRL_0;
        SSCE0 =ALT;
    }
    else if(channel==SPI_Channel_1)
    {
        GCR1 |= SPICTRL_1;
        SSCE1 =ALT;
    }
    else if(channel==SPI_Channel_0N1)
    {
        GCR1 |= (SPICTRL_0+SPICTRL_1);
        SSCE0 =ALT;
        SSCE1 =ALT;
    }
    else
    {
        GCR1 &= ~(SPICTRL_0+SPICTRL_1);
        settingOK = 0x00;
    }

    if(settingOK==0x01)
    {
        if(supportbusy == SPI_SupportBusy)
        {
            GCR1 |= SSSPIBP;
        }
        
        SSCK = ALT;
        SMOSI = ALT;
        SMISO = ALT;

        //SPICTRL1 |= (SCKFREQ2+NTREN);     // 100b: 1/10 FreqEC, Interrupt Enable, 4-wire
        SPICTRL1 |= SCKFREQ2+CLPOL+CLPHS;   // 100b: 1/10 FreqEC, Interrupt Disable, 4-wir, mode 3
    }
}

//*****************************************************************************
//
// Disable SPI interface function
//
//  parameter :
//      SPI_Channel_0   SPI channel 0 disable.
//      SPI_Channel_1   SPI channel 1 disable.
//      SPI_Channel_0N1 SPI channel 0 and 1 disable.
//
//  return :
//      none
//
//*****************************************************************************
void Disable_SPIInterface_API(BYTE channel)
{
    if(channel==SPI_Channel_0)              // Disable SPI channel 0
    {
        GCR1 &= ~(SPICTRL_0+SSSPIBP);
        SSCE0 =INPUT;
        
        if(IS_MASK_CLEAR(GCR1, SPICTRL_1))  // If SPI cnannel 1 is disabled or no used.
        {
            SSCK = INPUT;
            SMOSI = INPUT;
            SMISO = INPUT;
        }
    }
    else if(channel==SPI_Channel_1)         // Disable SPI channel 1
    {
        GCR1 &= ~(SPICTRL_1+SSSPIBP);
        SSCE1 =INPUT;

        if(IS_MASK_CLEAR(GCR1, SPICTRL_0))  // If SPI cnannel 0 is disabled or no used.
        {
            SSCK = INPUT;
            SMOSI = INPUT;
            SMISO = INPUT;
        }
    }
    else if(channel==SPI_Channel_0N1)       // Disable SPI channel 0 and 1.
    {
        GCR1 &= ~(SPICTRL_0+SPICTRL_1+SSSPIBP);
        SSCE0 =INPUT;
        SSCE1 =INPUT;
        SSCK = INPUT;
        SMOSI = INPUT;
        SMISO = INPUT;
    }
}

//*****************************************************************************
//
// Example for enabling SPI interface channel 0 function.
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void Enable_SPIInterface0_API(void)
{
    Init_SPIInterface_API(SPI_Channel_0, SPI_NoSupportBusy);
}

//*****************************************************************************
//
// To end the SPI transmission
//
//  parameter :
//      none
//
//  return :
//      none
//
//*****************************************************************************
void SPITransmissionEnd_API(void)
{
    BYTE l_time_out;
    
    //
    // To end SPI Transmission
    //
    SPISTS = TRANEND;

    //
    // To wait "Transfer End Flag"
    //
    for(l_time_out=0x00; l_time_out<100; l_time_out++)
    {
        if(IS_MASK_SET(SPISTS, TRANENDIF))
        {
            break;
        }
        WNCKR = 0x00; 
    }

    //
    // W/C Transfer End Flag
    //
    SPISTS = TRANENDIF;
}

//*****************************************************************************
//
// To write byte of SPI interface.  (Blocking mode)
//
//  parameter :
//      spidata : 
//      channel : SPI_Channel_0 || SPI_Channel_1.
//
//  return :
//      none
//
//*****************************************************************************
void SPIWriteByte_API(BYTE spidata, BYTE channel)
{
    SPIDATA = spidata;

    SET_MASK(SPICTRL2, BLKSEL);    // Blocking selection.
    CLEAR_MASK(SPICTRL2, CHRW);    // Write cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
    }
    
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    
    SPITransmissionEnd_API();
}

//*****************************************************************************
//
// To write word of SPI interface.  (Blocking mode)
//
//  parameter :
//      MSB : msb of word.
//      LSB : lsb of word.
//      channel : SPI_Channel_0 || SPI_Channel_1.
//
//  return :
//      none
//
//*****************************************************************************
void SPIWriteWord_API(BYTE MSB, BYTE LSB, BYTE channel)
{
    SPIDATA = MSB;

    SET_MASK(SPICTRL2, BLKSEL);    // Blocking selection.
    CLEAR_MASK(SPICTRL2, CHRW);    // Write cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        
        SPIDATA = LSB;
        SET_MASK(SPISTS, CH0START);
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        
        SPIDATA = LSB;
        SET_MASK(SPISTS, CH1START);
    }
    
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    SPITransmissionEnd_API();
}

//*****************************************************************************
//
// To read byte of SPI interface.   (Blocking mode)
//
//  parameter :
//      channel : SPI_Channel_0 || SPI_Channel_1.
//
//  return :
//      l_spi_byte : SPI data.
//
//*****************************************************************************
BYTE SPIReadByte_API(BYTE channel)
{
    BYTE l_spi_byte;
    
    l_spi_byte = 0x00;
    
    SET_MASK(SPICTRL2, BLKSEL);    // Blocking selection.
    SET_MASK(SPICTRL2, CHRW);      // Read cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
    }

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    
    l_spi_byte = SPIDATA;

    SPITransmissionEnd_API();
    
    return(l_spi_byte);
}

//*****************************************************************************
//
// To read word of SPI interface.   (Blocking mode)
//
//  parameter :
//      channel : SPI_Channel_0 || SPI_Channel_1.
//
//  return :
//      l_spi_word : word SPI data.
//
//*****************************************************************************
WORD SPIReadWord_API(BYTE channel)
{
    WORD l_spi_word;
    
    l_spi_word = 0x00;
    
    SET_MASK(SPICTRL2, BLKSEL);    // Blocking selection.
    SET_MASK(SPICTRL2, CHRW);      // Read cycle.

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
    }

    _nop_();
    _nop_();
    _nop_();
    _nop_();

    //
    // read LSB
    //
    l_spi_word += SPIDATA;

    if(channel==SPI_Channel_0)
    {
        SET_MASK(SPISTS, CH0START);
    }
    else if(channel==SPI_Channel_1)
    {
        SET_MASK(SPISTS, CH1START);
    }

    _nop_();
    _nop_();
    _nop_();
    _nop_();

    //
    // read MSB
    //
    l_spi_word += (SPIDATA*256);

    SPITransmissionEnd_API();

    return(l_spi_word);
}
#endif