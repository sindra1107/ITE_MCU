/*-----------------------------------------------------------------------------
 * TITLE: OEM_INIT.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Oem_StartUp
//----------------------------------------------------------------------------
void Oem_StartUp(void)
{

}

//----------------------------------------------------------------------------
// Oem_Initialization - Initialize the registers, data variables, and oem 
// functions after kernel init. function.
//----------------------------------------------------------------------------
void Oem_Initialization(void)
{
    Init_EC_Indirect_Selection(SPI_selection_internal);
    //SPI_Read_ID();
    //Check_Mirror_Occurs();

    Init_GPIO();

    #ifdef PECI_Support
    Init_PECI();
    #endif

    Init_OEMVariable();
}

//----------------------------------------------------------------------------
// The function of clearing external ram for OEM code
// Clear external ram (0x100~0xFFF)
//----------------------------------------------------------------------------
void Init_ClearRam(void)
{
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x100;
    while(byte_register_pntr<0x1000)// Clear external ram (0x100~0xFFF)
    {
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }							
}

//----------------------------------------------------------------------------
// Hook_ECExitFollowMode 
//----------------------------------------------------------------------------
void Hook_ECExitFollowMode(void)
{
    
}

//----------------------------------------------------------------------------
// Check_Mirror_Occurs
//----------------------------------------------------------------------------
void Check_Mirror_Occurs(void)
{
	if(IS_MASK_SET(FLHCTRL3R,BIT7))
	{
		SET_MASK(FLHCTRL3R,BIT7); // Clear mirror bit
    }
	
	SET_MASK(FLHCTRL3R,BIT0); // FSCK/FSCE#/FMISO/FMOSI are tri-state.

    #if HW_Mirror_Only_Once
    if(Read_Eflash_Byte(0x00, 0x00, 0x4D) != 00)
    {
       Do_Eflash_Write_1Byte(0x00, 0x00, 0x00, 0x4D); // Disable mirror , mirror Size -> 0
    }
    #endif
   	
    SET_MASK(HINSTC1,BIT6);   //Rescan 16 byte signature
}

//----------------------------------------------------------------------------
// Function Name : Init_OEMVariable
// Purpose : setup default variable when EC reset
//----------------------------------------------------------------------------
void Init_OEMVariable(void)
{
//    Init_Brightness();
	LED_FLASH_CNT = 0x0001;	// for LED control
    
	SysPowState=SYSTEM_S5;		
	if(BRAM[63]==0x55&&ShutDnCause == SC_IntWatchDog)
	{
		BRAM[63]=0x00;
		CLEAR_MASK(KBHISR,SYSF);	
                Ccb42_SYS_FLAG=0;
		DelayDoPowerSeq=250;
		Oem_TriggerS5S0();
	}
}


//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      1. Before jump to main function if want to keep EC setting [return(0x33);] is necessary.
//      2. If you don't understand the use of Hook_ECRetunrMainFuncKeepCondition function, 
//          don't change anything.
//      3. Always at bank0 (0x9000)
//----------------------------------------------------------------------------
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if(WinFlashMark==0x33)
    {
        return(0x33);
    }
    else
    {
        return(0x00);
    }
}