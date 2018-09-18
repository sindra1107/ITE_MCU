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
    #ifdef ITE_EVBoard
    DCache=0x03;
    BADRSEL=0x00;

    Init_EC_Indirect_Selection(SPI_selection_external);

    GPCRA0 = OUTPUT;
    GPCRA1 = OUTPUT;
    GPCRA2 = OUTPUT;
    GPCRA3 = OUTPUT;
    GPCRA4 = OUTPUT;
    GPCRA5 = OUTPUT;
    GPCRA6 = OUTPUT;
    GPCRA7 = OUTPUT;

    CLEAR_MASK(KBHISR,BIT2);
    
    GPCRD3 = OUTPUT;
    GPCRD4 = OUTPUT;
    GPCRB5 = OUTPUT;
    GPCRB6 = OUTPUT;
    
    Hook_KBRSTOFF();
    Hook_SCIOFF();
    Hook_SMIOFF();
    Hook_A20ON();

    RSTS = 0x44;
    InitSio();

    GPCRF0 = ALT+PULL_UP;
    GPCRF1 = ALT+PULL_UP;
    GPCRF2 = ALT+PULL_UP;
    GPCRF3 = ALT+PULL_UP;
    GPCRF4 = ALT+PULL_UP;
    GPCRF5 = ALT+PULL_UP;               // Enable all ps2 interface

    KSO16CtrlReg = ALT+PULL_UP;
    KSO17CtrlReg = ALT+PULL_UP;

    CheckKSO1617Support(); 
    
    //ChangePLLFrequency(0x04);
    //ChangePLLFrequency(0x07);
    //ChangeSPIFlashReadMode(SPIReadMode_3);

    #endif
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
