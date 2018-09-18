/*-----------------------------------------------------------------------------
 * TITLE: OEM_HOSTIF.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

const BYTE code initsio_table[]=
{
				// Configure and Enable Logical Device 06h(KBD)
	0x07 ,0x06,	// Select Logical Device 06h(KBD)
  	0x70 ,0x01,	// Set IRQ=01h for Logical Device 06h(KBD)
  	0x30 ,0x01,	// Enable Logical Device 06h(Mouse)
				// Configure and Enable Logical Device 05h(Mouse)
 	0x07 ,0x05,	// Select Logical Device 05h(Mouse)
  	0x70 ,0x0C,	// Set IRQ=0Ch for Logical Device 05h(Mouse)
	0x30 ,0x01,	// Enable Logical Device 05h(Mouse)
				// Enable Logical Device 11h(PM1)
   	0x07 ,0x11,	// Select Logical Device 11h(PM1)
  	0x70 ,0x00,	// Clear IRQ=0 for  Logical Device 11h(PM1)
 	0x30 ,0x01,	// Enable Logical Device 11h(PM1)
				// Enable Logical Device 12h(PM2)
	0x07 ,0x12,	// Select Logical Device 12h(PM2)
	0x70 ,0x00,	// Clear IRQ=0 for  Logical Device 12h(PM2)
	0x30 ,0x01,	// Enable Logical Device 12h(PM2)
				// Enable Logical Device 04h(MSWC)
 	0x07 ,0x04,	// Logical Device 04h(MSWC)
 	0x30 ,0x00,	// Enable MSWC 


	0x07 ,0x10,	// Logical Device 10h(BRAM)
	0x62 ,0x03,
	0x63 ,0x80,	// BRAMLD address is 0x380 (index) and 0x381 (data)
    //0xF3 ,0x00, // P80 value begin of BRAM
    //0xF4 ,0x1F, // P80 value end of BRAM
    //0xF5 ,0x20, // P80 value index of BRAM
	0x30 ,0x01,	// Enable BRAM
	
				// Enable Logical Device 0Fh(Shared Memory)
 	0x07 ,0x0F,	// Logical Device 0Fh(Shared Memory)
#ifdef SysMemory2ECRam	
 				// Define EC internal RAM base address on LPC memory space.
	0xF5 ,0xC0,	// H2RAM-HLPC Base Address Bits [15:12] (HLPCRAMBA[15:12]) high nibble	
	0xF6 ,0xFF,	// H2RAM-HLPC Base Address Bits [23:16] (HLPCRAMBA[23:16]) 	
#endif
	0x30 ,0x01,	// MSWC Shared Memory
 	//0xF4 ,0x09,	// MSWC Shared Memory

#ifdef PMC3_Support
    0x07 ,0x17,	// Select Logical Device 17h(PM3)
	0x62 ,0x06, // IO Port 6A4		
	0x63 ,0xA4, //
	0x60 ,0x06, // IO Port 6A0		
	0x61 ,0xA0, //
	0x70 ,0x01,	// Clear IRQ=1 for  Logical Device 13h(PM3)
	0x30 ,0x01,	// Enable Logical Device 17h(PM3)
#endif

};
//----------------------------------------------------------------------------
// Init super IO function
//----------------------------------------------------------------------------
void InitSio(void)
{
    BYTE code * data_pntr;
    BYTE cnt;

  	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	SET_MASK(IBCTL,CSAE);

    cnt=0;
    data_pntr=initsio_table;
    while(cnt < (sizeof(initsio_table)/2) )
    {
        IHIOA=0;              // Set indirect Host I/O Address
        IHD=*data_pntr;
        while( IS_MASK_SET(IBCTL,CWIB));
        data_pntr ++;

        IHIOA=1;              // Set indirect Host I/O Address
        IHD=*data_pntr;
        while( IS_MASK_SET(IBCTL,CWIB));
        data_pntr ++;
        cnt ++;
    }

 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);
}

//----------------------------------------------------------------------------
// Init system memory cycle to EC external ram 
//----------------------------------------------------------------------------
void InitSysMemory2ECRam(void)
{
	HRAMW0BA = 0xA0;					// Define RAM window 0 base address 0xA00
	HRAMW0AAS |= HostRamSize256Byte;	// Host RAM Window 0 Size 256 bytes
	//HRAMWC |= Window0En;
}

