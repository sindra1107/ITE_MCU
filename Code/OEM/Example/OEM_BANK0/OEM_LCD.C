
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

const BYTE BrightnessTBL[PANEL_COUNT][MAX_LEVEL+1]= 
{
	{0x03,0x14,0x28,0x3C,0x50,0x64,0x78,0x8C,0xA0,0xB4,0xC8   },
	{0x03,0x14,0x28,0x3C,0x50,0x64,0x78,0x8C,0xA0,0xB4,0xC8   },
};

//-----------------------------------------------------------------------------
// Setup Brightness value
//-----------------------------------------------------------------------------
void Setup_Brightness(BYTE brg_level)
{
    // check setup value is under range
	if(brg_level > MAX_LEVEL)       brg_level = MAX_LEVEL;	    
    if(PanelId > (PANEL_COUNT-1))   PanelId = (PANEL_COUNT-1);  
    PWM_VADJ = BrightnessTBL[PanelId][brg_level];
}

//-----------------------------------------------------------------------------
// Initialize Brightness variable
//-----------------------------------------------------------------------------
void Init_Brightness(void)
{
    BrgLevel = 0x04 ;	
}

//-----------------------------------------------------------------------------
// Check Brightness level change
//-----------------------------------------------------------------------------
void Check_Brightness(void)
{
    if(bBrightness != BrgLevel) 
    {    
        bBrightness = BrgLevel;
        Setup_Brightness(bBrightness);    
    }
}
              