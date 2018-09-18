/*-----------------------------------------------------------------------------
 * TITLE: CORE_FLASH.C
 *
 * Author : Dino
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// Always at 0xFF00 of code space
//-----------------------------------------------------------------------------
void RamCode(void)
{

}

//-----------------------------------------------------------------------------
// The function start address always at 0xFE00 (refer to link file)
//-----------------------------------------------------------------------------
void FuncAt_0xFE00(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    FlashECCode();
}

//-----------------------------------------------------------------------------
// The function of EC flash
//-----------------------------------------------------------------------------
void FlashECCode(void)
{
	RamcodeCmd = 0x00;
	RamcodeSend = 0x00;

    PM1DO = 0x33;		// ACK

 	while(1) 
  	{	
  		if( IS_MASK_SET(KBHISR,IBF))
  		{
			RamcodeCmd = KBHIDIR;
			continue;
		}
		if( IS_MASK_CLEAR(PM1STS,P_IBF) ) continue;
		if( IS_MASK_CLEAR(PM1STS,P_C_D) ) continue;
		RamcodeCmd = PM1DI;

		if(RamcodeSend==1)
		{
			ECINDDR = RamcodeCmd;
			RamcodeSend = 0x00;
			continue;
		}

		if(RamcodeCmd==0x01)
		{
			ECINDAR3 = EC_Indirect_Selection;   // Enter follow mode
   			ECINDAR2 = 0xFF;
			ECINDAR1 = 0xFE;
   			ECINDAR0 = 0x00;   		// FFFFExx = 0xFF   
   			ECINDDR = 0x00;			// SCE# high level
		}
		else if(RamcodeCmd==0x02)
		{							// Send SPI command
			ECINDAR1 = 0xFD;
			RamcodeSend = 1;
		}
		else if(RamcodeCmd==0x03)
		{							// write byte to spi
			RamcodeSend = 1;
		}
		else if(RamcodeCmd==0x04)
		{	
			//while(IS_MASK_SET(PM1STS,P_OBF));
			PM1DO=ECINDDR;			// Read byte from spi			
		}
		else if(RamcodeCmd==0x05)
		{	
			ECINDAR3 = 0x00;     	//Exit follow mode
			ECINDAR2 = 0x00;
		}
		else if(RamcodeCmd==0xFC)
		{	
			WinFlashMark = 0x33;
			break;
		}
		else if(RamcodeCmd==0xFD)
		{
        	WDTRST = 1;				// Reset watch dog timer
			WDTEB = 1;				// Enable watch dog
       		while(1);				// Wait for watch dog time-out				
		}
		else if(RamcodeCmd==0xFE)
		{	
			BRAM[63]=0x55;
        	WDTRST = 1;				// Reset watch dog timer
			WDTEB = 1;				// Enable watch dog
       		while(1);				// Wait for watch dog time-out
		}
 	}

	main();
}

//-----------------------------------------------------------------------------
// The function of reading SPI status ( command 0x05)
//	After this function, spi status will save to SPIReadStatus
//-----------------------------------------------------------------------------
void SPI_Read_Status(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read status command

	SPIReadStatus = ECINDDR;		// Save status Register to SPIReadStatus
	
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of Write SPI status ( command 0x01)
//	After this function, the value of SPIWriteStatus will write to spi status
//-----------------------------------------------------------------------------
void SPI_Write_Status(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WREN;			// Write enable	
	
    if(SPIID==SSTID)
	{
		ECINDAR1 = 0xFE;
		ECINDDR = 0xFF;				// SCE# high level
		ECINDAR1 = 0xFD;
		ECINDDR = SPICmd_EWSR;		// Enable Write Status Register
	}    
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WRSR;			// Write status command
	ECINDDR = SPIWriteStatus;		// Write SPIWriteStatus to spi status register

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of reading SPI ID (command 0x9F)
//	After this function, spi id will save to array SPIIDBuf[] 
//-----------------------------------------------------------------------------
void SPI_Read_ID(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_DeviceID;  // Manufacture ID command
	for(SPIIndex=0x00;SPIIndex<4;SPIIndex++)
	{
		SPIIDBuf[SPIIndex] = ECINDDR;
	}
	SPIID = SPIIDBuf[0];	

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	ECINDAR3 = 0x00;     	//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of reading SPI ID (command 0xAB)
//	After this function, spi id will save to array SPIIDBuf[] 
//-----------------------------------------------------------------------------
void SPI_Read_ID_CmdAB(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_RDID;		    // Read ID command
    ECINDDR = 0x00;		            // Read ID command addr2
    ECINDDR = 0x00;		            // Read ID command addr1
    ECINDDR = 0x00;		            // Read ID command addr0
    
	for(SPIIndex=0x00;SPIIndex<4;SPIIndex++)
	{
		SPIIDBuf[SPIIndex] = ECINDDR; 
	}
	SPIID = SPIIDBuf[0];	

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	ECINDAR3 = 0x00;     	//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of Erasing SPI
//-----------------------------------------------------------------------------
void SPI_Erase(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_BUSY+SPIStatus_WEL))==SPIStatus_WriteEnable)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPIAEraseCmd;			// Send erase command
	for(SPIIndex=0x00;SPIIndex<3;SPIIndex++)
	{
		ECINDDR = SPIAddrCycle[SPIIndex];
	}								// Send address cycle

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level

	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of SPI write enable
//-----------------------------------------------------------------------------
void SPI_Write_Enable(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WREN;			// Write enable	
	
    if(SPIID==SSTID)
    {
        ECINDAR1 = 0xFE;
        ECINDDR = 0xFF;				// SCE# high level
        ECINDAR1 = 0xFD;
        ECINDDR = SPICmd_EWSR;		// Enable Write Status Register
    }
    
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x02) // Check write enable and spi not busy
        {
            break;
        } 
	}

	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of SPI write disable
//-----------------------------------------------------------------------------
void SPI_Write_Disable(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_WRDI;			// Write disable	

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x00) // Check write disable and spi not busy
        {
            break;
        } 
	}

	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//-----------------------------------------------------------------------------
// The function of other SPI write 256 bytes
//-----------------------------------------------------------------------------
void Other_SPI_Write_256Bytes(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_BYTEProgram;   // Send Program One Data Byte command

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	SPIIndex = 0x00;
	do
	{
		ECINDDR = *SPIDataPointer;
		SPIIndex++;
		SPIDataPointerLowByte++;
	}while(SPIIndex!=0x00);		    // Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

//-----------------------------------------------------------------------------
// The function of SST SPI write 256 bytes (for Word AAI command)
//-----------------------------------------------------------------------------
void SST_SPI_Write_256Bytes(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_AAIWordProgram;    // Auto Address Increment Programming

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	SPIIndex = 0x00;
	do
	{ 
		ECINDDR = *SPIDataPointer;
		SPIIndex++;
		SPIDataPointerLowByte++;

	    if((SPIIndex%2)==0x00)
	    {
		    ECINDAR1 = 0xFE;
		    ECINDDR = 0xFF;					// SCE# high level
		    ECINDAR1 = 0xFD;
		    ECINDDR = SPICmd_ReadStatus;	// Read Status Register
		    while(1)						// waiting spi free
		    {
			    if((ECINDDR&SPIStatus_BUSY)==0x00)
        	    {
            	    break;
                } 
		    }	
                
            if(SPIIndex!=0x00)
            {
		        ECINDAR1 = 0xFE;
		        ECINDDR = 0xFF;						    // SCE# high level
		        ECINDAR1 = 0xFD;
		        ECINDDR = SPICmd_AAIWordProgram;		// Auto Address Increment Programming
            }
	    }
	}while(SPIIndex!=0x00);					// Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_WRDI;          // Write disable

    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

//-----------------------------------------------------------------------------
// The function of old SST SPI write 256 bytes
//-----------------------------------------------------------------------------
void Old_SST_SPI_Write_256Bytes(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_AAIProgram;    // Auto Address Increment Programming

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	SPIIndex = 0x00;
	do
	{
		ECINDDR = *SPIDataPointer;
		SPIIndex++;
		SPIDataPointerLowByte++;

	    ECINDAR1 = 0xFE;
	    ECINDDR = 0xFF;					// SCE# high level
	    ECINDAR1 = 0xFD;
	    ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	    while(1)						// waiting spi free
	    {
		    if((ECINDDR&SPIStatus_BUSY)==0x00)
            {
                break;
            } 
	    }	

        if(SPIIndex!=0x00)
        {
	        ECINDAR1 = 0xFE;
	        ECINDDR = 0xFF;			    // SCE# high level
	        ECINDAR1 = 0xFD;       
            ECINDDR = SPICmd_AAIProgram;    // Auto Address Increment Programming
        }
	}while(SPIIndex!=0x00);		    // Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_WRDI;          // Write disable


    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
    WNCKR = 0x00;                   // Delay 15.26 us
	//ECINDAR1 = 0xFE;
	//ECINDDR = 0xFF;					// SCE# high level
	//ECINDAR1 = 0xFD;
	//ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	//while(1)						// waiting spi free
	//{
	//	if((ECINDDR&(SPIStatus_BUSY+SSTSPIStatus_AAI))==0x00)
    //    {
    //        break;
    //    } 
	//}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

//-----------------------------------------------------------------------------
// The function of SPI write 256 bytes
//-----------------------------------------------------------------------------
void SPI_Write_256Bytes(void)
{
    if(SPIID==SSTID)
    {
        if(SSTDeviceID==SSTID_Old) 
        {
            LoadSPIFucnToRam(Old_SST_SPI_Write_256Bytes);   // Load function to ram
        }
        else
        {
	        LoadSPIFucnToRam(SST_SPI_Write_256Bytes);	// Load function to ram
        }
    }
    else
    {
	    LoadSPIFucnToRam(Other_SPI_Write_256Bytes);	// Load function to ram
    }  
}


//-----------------------------------------------------------------------------
// The function of SPI read 256 bytes
//-----------------------------------------------------------------------------
void SPI_Read_256Bytes(void)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;						// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_HighSpeedRead;		// High-Speed Read

	ECINDDR = SPIAddrCycle[0];			// For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	ECINDDR = 0x00;						// dummy byte
	
	SPIIndex = 0x00;
	do
	{
		*SPIDataPointer = ECINDDR;;
		SPIIndex++;
		SPIDataPointerLowByte++;
	}while(SPIIndex!=0x00);					// Send 256 bytes

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

//-----------------------------------------------------------------------------
// Eflash_Write_1Byte
//-----------------------------------------------------------------------------
void Eflash_Write_1Byte(void)
{
    ECINDAR3 = 0x4F; 
    ECINDAR2 = 0xFF;
    ECINDAR0 = 0x00;                        // FFFFExx = 0xFF  
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                         // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;            // Read Status Register
    while(1)                                // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
    }                                                               
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                         // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_BYTEProgram;           // Send Program One Data Byte command
    ECINDDR = SPIAddrCycle[0];              // For 256 bytes function limite
    ECINDDR = SPIAddrCycle[1];
    ECINDDR = SPIAddrCycle[2];
    SPIIndex = 0x00;
    ECINDDR = SPIIDBuf[0];
    ECINDAR1 = 0xFE;
    ECINDDR = 0xFF;                         // SCE# high level
    ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_ReadStatus;            // Read Status Register
    while(1)                                // waiting spi free
    {
        if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
    }       
    ECINDAR3 = 0x00;                        // Exit follow mode
    ECINDAR2 = 0x00;                           // 
}


//-----------------------------------------------------------------------------
// The function of loading function to external ram 0x600 ~ 0x6FF
//-----------------------------------------------------------------------------
void LoadSPIFucnToRam(FUNCT_PTR_V_V funcpoint)
{
	Tmp_XPntr = 0x600;
	Tmp_code_pointer = funcpoint;

	ITempB01 = 0x00;
	do
	{
		*Tmp_XPntr = *Tmp_code_pointer;
      	Tmp_XPntr++;
   		Tmp_code_pointer++;
		ITempB01++;
	}while(ITempB01!=0x00);
}

//-----------------------------------------------------------------------------
// The function for ITE flash utility
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void ITE_Flash_Utility(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(FlashECCode);		// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
}

//*****************************************************************************
// OEM FUNCTION CALL
//*****************************************************************************
//-----------------------------------------------------------------------------
// The function for oem code write spi status
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_Status(BYTE statusvalue)
{
	SPIWriteStatus = statusvalue;
	
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Write_Status);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
	EnableAllInterrupt();				// Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code read spi status
//		Note : SPI status always save to SPIReadStatus
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_Status(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_Status);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
	EnableAllInterrupt();				// Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code read spi ID (command 0x9F)   
//		Note : SPI ID always save to array SPIIDBuf[]
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_ID(void)
{
	DisableAllInterrupt();			// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_ID);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM
	FuncAt_0xFE00();				// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);         // disable scatch ROM
	EnableAllInterrupt();		    // Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code read spi ID (command 0xAB)
//		Note : SPI ID always save to array SPIIDBuf[]
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_ID_CmdAB(void)
{
	DisableAllInterrupt();			// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_ID_CmdAB);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM
	FuncAt_0xFE00();				// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);         // disable scatch ROM
	EnableAllInterrupt();		    // Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code erase spi
//		Input : 1 EraseCmd --> Only support SPICmd_Erase4KByte, 
//								SPICmd_Erase32KByte, and SPICmd_Erase64KByte.
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Erase(BYTE EraseCmd, BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	SPIAEraseCmd = EraseCmd;
	SPIAddrCycle[0] = Addr2;
	SPIAddrCycle[1] = Addr1;
	SPIAddrCycle[2] = Addr0;
			
	DisableAllInterrupt();			// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Erase);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       	// enable scatch ROM
	FuncAt_0xFE00();				// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);         // disable scatch ROM
	EnableAllInterrupt();		    // Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code write spi 256 bytes
//		Input : 1 DataPointer --> Pointe to external memory
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_256Bytes(XBYTE *DataPointer, BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	SPIDataPointer = DataPointer;
	SPIAddrCycle[0] = Addr2;
	SPIAddrCycle[1] = Addr1;
	SPIAddrCycle[2] = Addr0;
			
	DisableAllInterrupt();				// Disable all interrupt 
	SPI_Write_256Bytes();               // Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
	EnableAllInterrupt();				// Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code read spi 256 bytes to external memory
//		Input : 1 DataPointer --> Pointe to external memory
//				2 Addr2	   --> A23 ~ A16
//				3 Addr1	   --> A15 ~ A8
//				4 Addr0	   --> A7  ~ A0
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Read_256Bytes(XBYTE *DataPointer, BYTE Addr2, BYTE Addr1, BYTE Addr0)
{
	SPIDataPointer = DataPointer;
	SPIAddrCycle[0] = Addr2;
	SPIAddrCycle[1] = Addr1;
	SPIAddrCycle[2] = Addr0;
			
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Read_256Bytes);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
	EnableAllInterrupt();				// Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code spi write enable
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_Enable(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Write_Enable);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
	EnableAllInterrupt();				// Enable all interrupt 
}

//-----------------------------------------------------------------------------
// The function for oem code spi write disable
//-----------------------------------------------------------------------------
#pragma ot(7, SIZE)
void Do_SPI_Write_Disable(void)
{
	DisableAllInterrupt();				// Disable all interrupt 
	LoadSPIFucnToRam(SPI_Write_Disable);	// Load function to ram
	SET_MASK(FBCFG,SSMC);       		// enable scatch ROM
	FuncAt_0xFE00();					// do function in extern ram 0x600
	CLEAR_MASK(FBCFG,SSMC);       		// disable scatch ROM
	EnableAllInterrupt();				// Enable all interrupt 
}

//-----------------------------------------------------------------------------
// Do_Eflash_Write_1Byte
//-----------------------------------------------------------------------------
#pragma ot(7, speed)
void Do_Eflash_Write_1Byte(BYTE OneByte,BYTE Addr2,BYTE Addr1,BYTE Addr0)
{
    SPIIDBuf[0] = OneByte;
    SPIAddrCycle[0] = Addr2;
    SPIAddrCycle[1] = Addr1;
    SPIAddrCycle[2] = Addr0;
    DisableAllInterrupt();                   // Disable all interrupt
    LoadSPIFucnToRam(SPI_Write_Enable);
    SET_MASK(FBCFG,SSMC);                    // enable scatch ROM
    FuncAt_0xFE00();                         // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                  // disable scatch ROM
    LoadSPIFucnToRam(Eflash_Write_1Byte);    // Load function to ram
    SET_MASK(FBCFG,SSMC);                    // enable scatch ROM
    FuncAt_0xFE00();                         // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                  // disable scatch ROM
    LoadSPIFucnToRam(SPI_Write_Disable);   // Load function to ram
    SET_MASK(FBCFG,SSMC);                    // enable scatch ROM
    FuncAt_0xFE00();                         // do function in extern ram 0x600
    CLEAR_MASK(FBCFG,SSMC);                  // disable scatch ROM
    EnableAllInterrupt();                    // Enable all interrupt 
}


//*****************************************************************************
//
//
//  parameter :
//      add2
//      add1
//      add0
//      selection
//      length
//      bufferindex
//
//  return :
//      none
//
//*****************************************************************************
void ECIndirectFastRead(BYTE add2, BYTE add1, BYTE add0, BYTE selection, WORD length, XBYTE *bufferindex)
{
    BYTE ECINDAR3_Store;
    BYTE FLHCTRL3R_Store;

    ECINDAR3_Store = ECINDAR3;
    FLHCTRL3R_Store = FLHCTRL3R;
    
    if(selection==SPI_selection_internal || selection==SPI_selection_external)
    {
        if(selection==SPI_selection_internal)   // internal
        {
            ECINDAR3 = 0x40; 
        }
        else                                    // external
        {
            ECINDAR3 = 0x00; 
            CLEAR_MASK(FLHCTRL3R, BIT0);
        }

        ECINDAR2 = add2;                        // start address
        ECINDAR1 = add1;
        ECINDAR0 = add0;

        while(length)
        {
            ECINDAR2 = add2;                    // start address
            ECINDAR1 = add1;
            ECINDAR0 = add0;
            *bufferindex = ECINDDR;

            if(++add0 == 0x00)
            {
                if(++add1 == 0x00)
                {
                    add2++;
                }
            }
            bufferindex++;                      // external ram pointer ++
            length--;
        }

        ECINDAR3 = ECINDAR3_Store;
        FLHCTRL3R = FLHCTRL3R_Store;
    }
}

//*****************************************************************************
// Read_Eflash_Byte
//*****************************************************************************
BYTE Read_Eflash_Byte(BYTE FA2,BYTE FA1,BYTE FA0)
{
    ECINDAR3 = 0x40;
	ECINDAR2 = FA2;
	ECINDAR1 = FA1;
	ECINDAR0 = FA0;
	return ECINDDR;
}

//*****************************************************************************
// Do_SW_Mirror
//*****************************************************************************
void Do_SW_Mirror()
{
    FLHCTRL3R = 0x18;    // Mirror code after WDT , Enable FSPI , FSCK/FSCE#/FMISO/FMOSI are normal operation .
    
    WDTRST = 1;          // Reset watch dog timer
    WDTEB = 1;           // Enable watch dog
    while(1);            // Wait for watch dog time-out

}

//*****************************************************************************
//
//
//  parameter :
//      selection : SPI_selection_internal | SPI_selection_external
//
//  return :
//      none
//
//*****************************************************************************
void Init_EC_Indirect_Selection(BYTE selection)
{
    if(selection==SPI_selection_internal)   // Internal
    {
        EC_Indirect_Selection = 0x4F;
    }
    else                                    // external
    {
        EC_Indirect_Selection = 0x0F;
    }
}
