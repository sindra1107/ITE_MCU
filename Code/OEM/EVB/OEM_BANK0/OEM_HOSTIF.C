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

#ifdef ITE_EVBoard
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

    //#if SysMemory2ECRam	
    //0x07 ,0x0F,	// Logical Device 0Fh(Shared Memory)
 				// Define EC internal RAM base address on LPC memory space.
	//0xF5 ,0x00,	// H2RAM-HLPC Base Address Bits [15:12] (HLPCRAMBA[15:12]) high nibble	
	//0xF6 ,0x80,	// H2RAM-HLPC Base Address Bits [23:16] (HLPCRAMBA[23:16]) 	
	//0x30 ,0x01,	// MSWC Shared Memory
	//#endif

    //0x07 ,0x10, // Logical Device 10h(BRAM)
    //0x60 ,0x00,
    //0x61 ,0x70, // BRAMLD address is 0x500 index and 0x501 data
    //0x62 ,0x00,
    //0x63 ,0x72, // BRAMLD address is 0x500 index and 0x501 data
    //0xF3 ,0x80,
    //0xF4 ,0x3F,
    //0x30 ,0x01, // Enable BRAM

 	0x07 ,0x01,	// Uart1 
	0x30 ,0x01,	// Enable Logical Device 01h(uart1)

    0x07 ,0x02,	// Uart2
	0x30 ,0x01,	// Enable Logical Device 01h(uart1)
};
#endif

//----------------------------------------------------------------------------
// Init super IO function
//----------------------------------------------------------------------------
void InitSio(void)
{
    #ifdef ITE_EVBoard
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
    #endif
}
