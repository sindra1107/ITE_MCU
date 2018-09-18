/*-----------------------------------------------------------------
 * TITLE: OEM_SCANTABS.C - RC Table(s) for Scan Matix
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *----------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

const unsigned char code Rc_ROM_Tables[] =   
{
    // Scanner Table 1  
	0x29,0x5a,0x7b,0x00,0x00,0xe7,0x7c,0x00,0xed,0x31,0x32,0xE1,0x2c,0x73,0x8a,0xe3,
	0x00,0x1e,0x4a,0x00,0x00,0x7d,0x41,0x00,0x49,0x3a,0x2a,0xe5,0x22,0x34,0x8b,0x75,
	0x00,0x5d,0x16,0x00,0x00,0xe6,0x42,0x88,0x4b,0x3b,0x2b,0x7a,0x1b,0xaf,0x00,0x58,
	0x00,0x5b,0x54,0x00,0x00,0xb4,0x43,0x89,0x44,0x3c,0x2d,0xe4,0x1d,0x4c,0x00,0x0d,
	0x00,0x66,0x4d,0x00,0x8c,0x00,0x3e,0x00,0x46,0x3d,0x25,0x72,0x52,0x26,0x00,0x24,
	0xe2,0x55,0x45,0x82,0x00,0x00,0xb1,0x00,0xb6,0x36,0x2e,0x69,0xec,0x1c,0x00,0x0e,
	0x91,0x00,0xb8,0x81,0x00,0xb5,0xb2,0x79,0xb7,0x35,0x21,0x70,0xad,0xb0,0x71,0x15,
	0xe0,0x74,0x4e,0x00,0x8d,0x6b,0xb3,0x00,0x6c,0x33,0x1a,0x8e,0xae,0x23,0x00,0x84,
  	
};

const unsigned char code EtKey_ROM_Tables[] =
{	//16   17   18		// 19X8 Scan Table 
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00,
};

const unsigned char code KB_S3WakeUP_Tables[] =
{
    // Scanner Table 1 
	//00   01   02   03   04   05   06   07   08   09   10   11   12   13   14   15
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
 	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
   	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
 	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55  //
};

const unsigned char code EtKey_S3WakeUP_Tables[] =
{	//16   17   18		// 19X8 Scan Table 
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
	0x55,0x55,0x55,
};

//----------------------------------------------------------------------------
// The function of hotkey Fn + F1
//----------------------------------------------------------------------------
void HotKey_Fn_F1(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F2
//----------------------------------------------------------------------------
void HotKey_Fn_F2(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F3
//----------------------------------------------------------------------------
void HotKey_Fn_F3(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F4
//----------------------------------------------------------------------------
void HotKey_Fn_F4(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F5
//----------------------------------------------------------------------------
void HotKey_Fn_F5(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F6
//----------------------------------------------------------------------------
void HotKey_Fn_F6(BYTE event)
{	

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F7
//----------------------------------------------------------------------------
void HotKey_Fn_F7(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F8
//----------------------------------------------------------------------------
void HotKey_Fn_F8(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F9
//----------------------------------------------------------------------------
void HotKey_Fn_F9(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F10
//----------------------------------------------------------------------------
void HotKey_Fn_F10(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F11
//----------------------------------------------------------------------------
void HotKey_Fn_F11(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F12
//----------------------------------------------------------------------------
void HotKey_Fn_F12(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + ESC
//----------------------------------------------------------------------------
void HotKey_Fn_ESC(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + up arrow
//----------------------------------------------------------------------------
void HotKey_Fn_UP(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + down arrow
//----------------------------------------------------------------------------
void HotKey_Fn_DOWN(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + left arrow
//----------------------------------------------------------------------------
void HotKey_Fn_LEFT(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + right arrow
//----------------------------------------------------------------------------
void HotKey_Fn_RIGHT(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + Ins (Scr Lk)
//---------------------------------------------------------------------------
void HotKey_Fn_Ins(BYTE event)
{

}

//----------------------------------------------------------------------------
// The function of hotkey Fn + Del (NumLk)
//---------------------------------------------------------------------------
void HotKey_Fn_Del(BYTE event)
{

}


const FUNCT_PTR_V_B code HotKey_Fn_Fx[] =
{
	HotKey_Fn_F1,    	// Fn + F1
	HotKey_Fn_F2, 		// Fn + F2
	HotKey_Fn_F3, 		// Fn + F3
	HotKey_Fn_F4,       // Fn + F4
	HotKey_Fn_F5,    	// Fn + F5
	HotKey_Fn_F6, 		// Fn + F6
	HotKey_Fn_F7, 		// Fn + F7
	HotKey_Fn_F8,       // Fn + F8
	HotKey_Fn_F9,    	// Fn + F9
	HotKey_Fn_F10, 		// Fn + F10
	HotKey_Fn_F11, 		// Fn + F11
	HotKey_Fn_F12,    	// Fn + F12	
	HotKey_Fn_ESC,    	// Fn + ESC	
	HotKey_Fn_UP,    	// Fn + up arrow	
	HotKey_Fn_DOWN,    	// Fn + down arrow	
	HotKey_Fn_LEFT,    	// Fn + left arrow	
	HotKey_Fn_RIGHT,  	// Fn + right arrow	
	//HotKey_Fn_Ins,	// Fn + Ins (Scr Lk)
	//HotKey_Fn_Del,	// Fn + Del (NumLk)
};

//---------------------------------------------------------------------------
//	Numpad 7 Home	[B0h]
//	Numpad 8 UP  	[B1h]
//	Numpad 9 PGUp	[B2h]
//	Numpad *   		[B3h]
//	Numpad 4 Left	[B4h]
//	Numpad 5 		[B5h]
//	Numpad 6 Right	[B6h]
//	Numpad -  		[B7h]
//	Numpad 1 End	[B8h]
// 	Numpad 2 Down	[B9h]
//	Numpad 3 PGDn	[BAh]
//	Numpad + 		[BBh]
//	Numpad 0 Ins	[BCh]
// 	Numpad . Del	[BDh]
//	Numpad /      	[BEh]
//---------------------------------------------------------------------------

const BYTE code ss2_9C[] =	// Numpad 7 
{
    0x3D,   // Normal 		// 7
    0xB0,   // Numlock 
    0xB0,   // Fn 
    0xB0    // Fn+Numlock 
};

const BYTE code ss2_9D[] =	// Numpad 8   
{
    0x3E,   // Normal 		// 8
    0xB1,   // Numlock 
    0xB1,   // Fn 
    0xB1    // Fn+Numlock 
};

const BYTE code ss2_9E[] = 	// Numpad 9  
{
    0x46,   // Normal 		// 9
    0xB2,   // Numlock 
    0xB2,   // Fn 
    0xB2    // Fn+Numlock 
};

const BYTE code ss2_9F[] = 	// Numpad 0  
{
    0x45,   // Normal 		// 0
    0xBE,   // Numlock 
    0xBE,   // Fn 
    0xBE    // Fn+Numlock 
};

const BYTE code ss2_A0[] = 	// Numpad U  
{
    0x3C,   // Normal 		// U
    0xB4,   // Numlock 
    0xB4,   // Fn 
    0xB4    // Fn+Numlock 
};

const BYTE code ss2_A1[] = 	// Numpad I  
{
    0x43,   // Normal 		// I
    0xB5,   // Numlock 
    0xB5,   // Fn 
    0xB5    // Fn+Numlock 
};

const BYTE code ss2_A2[] =	// Numpad O 
{
    0x44,   // Normal 		// O
    0xB6,   // Numlock 
    0xB6,   // Fn 
    0xB6    // Fn+Numlock 
};

const BYTE code ss2_A3[] =	// Numpad P 
{
    0x4D,   // Normal 		// P
    0xB3,   // Numlock 
    0xB3,   // Fn 
    0xB3    // Fn+Numlock 
};

const BYTE code ss2_A4[] = 	// Numpad J 
{
    0x3B,   // Normal 		// J
    0xB8,   // Numlock 
    0xB8,   // Fn 
    0xB8    // Fn+Numlock 
};

const BYTE code ss2_A5[] = 	// Numpad K 
{
    0x42,   // Normal 		// K
    0xB9,   // Numlock 
    0xB9,   // Fn 
    0xB9    // Fn+Numlock 
};

const BYTE code ss2_A6[] =	// Numpad L 
{
    0x4B,   // Normal 		// L
    0xBA,   // Numlock 
    0xBA,   // Fn 
    0xBA    // Fn+Numlock 
};

const BYTE code ss2_A7[] = 	// Numpad ;:  
{
    0x4C,   // Normal 		// ;:
    0xB7,   // Numlock 
    0xB7,   // Fn 
    0xB7    // Fn+Numlock 
};

const BYTE code ss2_A8[] =	// Numpad M  
{
    0x3A,   // Normal 		// M
    0xBC,   // Numlock 
    0xBC,   // Fn 
    0xBC    // Fn+Numlock 
};

const BYTE code ss2_A9[] = 	// Numpad ,<  
{
    0x41,   // Normal 		// ,< 
    0x41,   // Numlock 
    0x41,   // Fn 
    0x41    // Fn+Numlock 
};

const BYTE code ss2_AA[] = 	// Numpad .>   
{
    0x49,   // Normal 		// .> 
    0xBD,   // Numlock 
    0xBD,   // Fn 
    0xBD    // Fn+Numlock 
};

const BYTE code ss2_AB[] = 	// Numpad /?      
{
    0x4A,   // Normal 		// /? 
    0xBB,   // Numlock 
    0xBB,   // Fn 
    0xBB    // Fn+Numlock 
};

const BYTE code ss2_AC[] =   
{
    0x5A,   // Normal 
    0x81,   // Fn 
};
//----------------------------------------------------------------
// Function key F1 ~ F12
//----------------------------------------------------------------
const BYTE code ss2_AD[] = 	// F1
{
    0x05,   // Normal 
    0xD0,   // Fn 
};

const BYTE code ss2_AE[] = 	// F2 	 
{
    0x06,   // Normal 
    0xD1,   // Fn 
};

const BYTE code ss2_AF[] = 	// F3  
{
    0x04,   // Normal 
    0xD2,   // Fn 
};

const BYTE code ss2_B0[] =	// F4   
{
    0x0C,   // Normal 
    0xD3,   // Fn 
};

const BYTE code ss2_B1[] = 	// F5  
{
    0x03,   // Normal 
    0xD4,   // Fn 
};

const BYTE code ss2_B2[] = 	// F6  
{
    0x0B,   // Normal 
    0xD5,   // Fn 
};

const BYTE code ss2_B3[] = 	// F7  
{
    0x80,   // Normal 
    0xD6,   // Fn 
};

const BYTE code ss2_B4[] = 	// F8  
{
    0x0A,   // Normal 
    0xD7,   // Fn 
};

const BYTE code ss2_B5[] = 	// F9  
{
    0x01,   // Normal 
    0xD8,   // Fn 
    //0x01,   // Normal 
};

const BYTE code ss2_B6[] = 	// F10  
{
    0x09,   // Normal 
	//0x09,   // Fn 
    0xD9,   // Fn 
    //0x09,   // Normal 
};

const BYTE code ss2_B7[] = 	// F11  
{
    0x78,   // Normal 
    0xDA,   // Fn 
    //0x78,   // Normal 
};

const BYTE code ss2_B8[] = 	// F12  
{
    0x07,   // Normal 
    0xDB,   // Fn 
    //0x07,
};

/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_A2_table
 *
 * The A2_TABLE structure contains the following.
 *
 * BYTE comb;  Bit   Setting Combination Key
 *            ---   -----------------------
 *             7    Hook_calc_index_comb_BIT7
 *             6    Hook_calc_index_comb_BIT6
 *             5    Fn
 *             4    Numlock
 *             3    Ctrl
 *             2    Alt
 *             1    Shift
 *             0    reserved
 *
 * BYTE *pntr; Pointer to array for key.
 * ------------------------------------------------------------------------- */
const A2_TABLE sskey2_A2_table[] =
{											// Keyboard matrix index
	// Keypad -->
	{0x30, ss2_9C },    /* index = 00h */ 	// 0x9C	
    {0x30, ss2_9D },    /* index = 01h */	// 0x9D
    {0x30, ss2_9E },    /* index = 02h */	// 0x9E	
    {0x30, ss2_9F },    /* index = 03h */	// 0x9F	
    {0x30, ss2_A0 },    /* index = 04h */	// 0xA0
    {0x30, ss2_A1 },    /* index = 05h */	// 0xA1
    {0x30, ss2_A2 },    /* index = 06h */	// 0xA2
    {0x30, ss2_A3 },    /* index = 07h */	// 0xA3
    {0x30, ss2_A4 },    /* index = 08h */	// 0xA4
    {0x30, ss2_A5 },    /* index = 09h */	// 0xA5
    {0x30, ss2_A6 },    /* index = 0Ah */	// 0xA6
    {0x30, ss2_A7 },    /* index = 0Bh */	// 0xA7
    {0x30, ss2_A8 },    /* index = 0Ch */	// 0xA8
    {0x30, ss2_A9 },  	/* index = 0Dh */	// 0xA9
    {0x30, ss2_AA },  	/* index = 0Eh */	// 0xAA
    {0x30, ss2_AB },   	/* index = 0Fh */	// 0xAB
    {0x20, ss2_AC },  	/* index = 10h */	// 0xAC
	// Keypad <--
	
	// F1~F12 hotkeys -->
    {0x20, ss2_AD },    /* index = 11h */	// 0xAD
    {0x20, ss2_AE },    /* index = 12h */	// 0xAE
    {0x20, ss2_AF },    /* index = 13h */	// 0xAF
    {0x20, ss2_B0 },    /* index = 14h */	// 0xB0
    {0x20, ss2_B1 },    /* index = 15h */	// 0xB1
    {0x20, ss2_B2 },    /* index = 16h */	// 0xB2
    {0x20, ss2_B3 },    /* index = 17h */	// 0xB3
    {0x20, ss2_B4 },    /* index = 18h */	// 0xB4
    {0x20, ss2_B5 },  	/* index = 19h */	// 0xB5
    {0x20, ss2_B6 },  	/* index = 1Ah */	// 0xB6
    {0x20, ss2_B7 },   	/* index = 1Bh */	// 0xB7
    {0x20, ss2_B8 }     /* index = 1Ch */	// 0xB8	
    // F1~F12 hotkeys <--
};
											// Reserved 0xB9 ~ 0xDF
 
/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_overlay_table
 * ------------------------------------------------------------------------- */
const BYTE code sskey2_overlay_table[] =
{               //	Normal   	Fn   			// Keyboard matrix index
    0xC3, 0xC1, // 	Print Scr 	SysRq 			// 0xE0
	0x77, 0x7E, //	Num Lk     	Scr LK  		// 0xE1
	0xC0, 0xC0, //	Del   		Del    	    	// 0xE2
	0xC2, 0xC2, //	Insert   	Insert    		// 0xE3

	0x98, 0xDD, // 	Up arrow 	Function key up arrow  (HotKey_Fn_Up) 		// 0xE4
	0x99, 0xDE, //	Down arrow 	Function key down arrow  (HotKey_Fn_Down) 	// 0xE5
	0x9A, 0xDF, //	Left arrow	Function key Left arrow  (HotKey_Fn_LEFT)  	// 0xE6
	0x9B, 0xE0,	//	Right arrow	Function key Right arrow (HotKey_Fn_RIGHT)	// 0xE7
	
	0x94, 0x9F, // 	Home 		Play/Pause event// 0xE8
	0x96, 0x9E, //	PgUp 		Stop event 		// 0xE9
	0x97, 0x9D, //	PgDn		Prev Track event// 0xEA
	0x95, 0x9C,	//	End			Next Track event// 0xEB

	0x76, 0xDC,	//	ESC			ESC				// 0xEC
	0xBE, 0xBE,	//	KeyPad_/	KeyPad_/		// 0xED

	0xC4, 0xC4,	// Euro Sign	// Euro Sign	// 0xEE
	0xC5, 0xC5,	// Dollar Sign	// Dollar Sign	// 0xEF
};

												// Reserved 0xEE ~ 0xFF								

/* ----------------------------------------------------------------------------
 * Insyde Software Key Number 2
 *
 * 00h         Null
 * 01h - 7Fh   Same as IBM Scan Code, Set2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * C0h - DFh   Pre-Index for PPK function
 * C0h - DFh   Pre-Index for SMI function
 * ------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 * FUNCTION: sskey3_80_table - Insyde Software Key Number 2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * ------------------------------------------------------------------------- */
const BYTE code sskey3_80_table[] =
{
//-----------------------------------------------------------------
// Index from keyboard matrix
//-----------------------------------------------------------------	
									// Keyboard matrix index
	0x83, 	DO_SIMPLE_CODE,       	// [80h] F7 (118) 
	0x5A, 	DO_E0_PREFIX_CODE,    	// [81h] Numpad Enter (108) 
    0x1F, 	DO_E0_PREFIX_CODE,    	// [82h] Windows Left 
    0x27, 	DO_E0_PREFIX_CODE,    	// [83h] Windows Right 
    0x2F, 	DO_E0_PREFIX_CODE,    	// [84h] Application 
    0x37, 	DO_E0_PREFIX_CODE,    	// [85h] Power event 
    0x3F, 	DO_E0_PREFIX_CODE,    	// [86h] Sleep event 
    0x5E, 	DO_E0_PREFIX_CODE,		// [87h] Wake event 
    LShift, DO_CONTROL_EFFECT,		// [88h] 12 Shift(L) 
    RShift, DO_CONTROL_EFFECT,		// [89h] 59 Shift(R) 
    LAlt, 	DO_CONTROL_EFFECT,    	// [8Ah] 11 Alt(L) 
    RAlt, 	DO_CONTROL_EFFECT_E0,	// [8Bh] E0 11 Alt(R) 
    LCtrl, 	DO_CONTROL_EFFECT, 		// [8Ch] 14 Crtl(L) 
    RCtrl, 	DO_CONTROL_EFFECT_E0,	// [8Dh] E0 14 Ctrl(R) 
    FN, 	DO_CONTROL_EFFECT,    	// [8Eh] Fn 
    OVLAY,	DO_CONTROL_EFFECT,		// [8Fh] Overlay 
    0x00, 	DO_SIMPLE_CODE,       	// [90h] Reserved 
    0x00, 	DO_SPECIAL_CODE,      	// [91h] Pause (126) 
    0x01, 	DO_SPECIAL_CODE,      	// [92h] Break 
    0x84, 	DO_SIMPLE_CODE,       	// [93h] (124) Alt-Case (SysRq) 
	0x6C, 	DO_E0_PREFIX_CODE,    	// [94h] Home 
    0x69, 	DO_E0_PREFIX_CODE,    	// [95h] End 
    0x7D, 	DO_E0_PREFIX_CODE,  	// [96h] Page up 
    0x7A, 	DO_E0_PREFIX_CODE,    	// [97h] Page down 
	0x75, 	DO_E0_PREFIX_CODE,    	// [98h] UP arrow 
    0x72, 	DO_E0_PREFIX_CODE,    	// [99h] Down arrow 
    0x6B, 	DO_E0_PREFIX_CODE,  	// [9Ah] Left arrow 
    0x74, 	DO_E0_PREFIX_CODE,   	// [9Bh] Right arrow 
    
//-----------------------------------------------------------------
// For MicroSoft enhance keyboard feature.
//-----------------------------------------------------------------
 	0x4D, DO_E0_PREFIX_CODE,    	// [9Ch] Next Track event 
    0x15, DO_E0_PREFIX_CODE,    	// [9Dh] Prev Track event 
    0x3B, DO_E0_PREFIX_CODE,    	// [9Eh] Stop event 
    0x34, DO_E0_PREFIX_CODE,    	// [9Fh] Play/Pause event 
    0x23, DO_E0_PREFIX_CODE,    	// [A0h] Mute event 
    0x32, DO_E0_PREFIX_CODE,    	// [A1h] Volume Up event 
    0x21, DO_E0_PREFIX_CODE,    	// [A2h] Volume Down event 
    0x48, DO_E0_PREFIX_CODE,    	// [A3h] Mail event 
    0x10, DO_E0_PREFIX_CODE,    	// [A4h] Search event 
    0x3A, DO_E0_PREFIX_CODE,    	// [A5h] Web/Home event 
    0x38, DO_E0_PREFIX_CODE,    	// [A6h] Back event 
    0x30, DO_E0_PREFIX_CODE,    	// [A7h] Forward event 
    0x28, DO_E0_PREFIX_CODE,    	// [A8h] Stop event 
    0x20, DO_E0_PREFIX_CODE,    	// [A9h] Refresh event 
    0x18, DO_E0_PREFIX_CODE,    	// [AAh] Favorites event 
    0x2B, DO_E0_PREFIX_CODE,    	// [ABh] Caluator event 
    0x40, DO_E0_PREFIX_CODE,    	// [ACh] My Computer event 
    0x50, DO_E0_PREFIX_CODE,    	// [ADh] Media event 
    0x00, DO_SIMPLE_CODE,       	// [AEh] Reserved 
    0x00, DO_SIMPLE_CODE,      		// [AFh] Reserved 
    
//-----------------------------------------------------------------
// Index from sskey2_A2_table
//-----------------------------------------------------------------
	0x6C, DO_SIMPLE_CODE,     		// Numpad 7 Home	[B0h]
  	0x75, DO_SIMPLE_CODE,      		// Numpad 8 UP  	[B1h]
 	0x7D, DO_SIMPLE_CODE,       	// Numpad 9 PGUp	[B2h]
  	0x7C, DO_SIMPLE_CODE,       	// Numpad *   		[B3h]
	0x6B, DO_SIMPLE_CODE,       	// Numpad 4 Left	[B4h]
 	0x73, DO_SIMPLE_CODE,       	// Numpad 5 		[B5h]
	0x74, DO_SIMPLE_CODE,       	// Numpad 6 Right	[B6h]
	0x7B, DO_SIMPLE_CODE,       	// Numpad -  		[B7h]
	0x69, DO_SIMPLE_CODE,       	// Numpad 1 End		[B8h]
 	0x72, DO_SIMPLE_CODE,       	// Numpad 2 Down	[B9h]
	0x7A, DO_SIMPLE_CODE,       	// Numpad 3 PGDn	[BAh]
	0x79, DO_SIMPLE_CODE,       	// Numpad + 		[BBh]
	0x70, DO_SIMPLE_CODE,       	// Numpad 0 Ins		[BCh]
	0x71, DO_SIMPLE_CODE,      	 	// Numpad . Del		[BDh]
	0x4A, DO_E0_PREFIX_CODE, 		// Numpad /      	[BEh]
	
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[BFh]
	
    0x71, DO_E0_PREFIX_CODE,  		// Delete 			[C0h]  
    0x84, DO_SIMPLE_CODE,    		// SysRq			[C1h]  
    0x70, DO_E0_PREFIX_CODE,    	// Insert			[C2h]  
    0x7C, DO_E0_PREFIX_CODE,  		// Print Screen		[C3h] 
	0x41, DO_E0_PREFIX_CODE,     	// Euro Sign 		[C4h]
	0x49, DO_E0_PREFIX_CODE,    	// Dollar Sign 		[C5h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C6h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C7h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C8h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C9h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CAh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CBh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CCh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CDh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CEh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CFh]
	
// Function key F1 ~ F12     
    0	, DO_COSTOMER_FUNCTION,		// Function key F1	[D0h]  
    1	, DO_COSTOMER_FUNCTION,		// Function key F2	[D1h]  
    2	, DO_COSTOMER_FUNCTION,		// Function key F3	[D2h] 
    3	, DO_COSTOMER_FUNCTION,		// Function key F4	[D3h] 
    4	, DO_COSTOMER_FUNCTION,		// Function key F5	[D4h] 
    5	, DO_COSTOMER_FUNCTION,		// Function key F6	[D5h] 
    6	, DO_COSTOMER_FUNCTION,		// Function key F7	[D6h] 
    7	, DO_COSTOMER_FUNCTION,		// Function key F8	[D7h] 
    8	, DO_COSTOMER_FUNCTION,		// Function key F9	[D8h] 
    9	, DO_COSTOMER_FUNCTION,		// Function key F10	[D9h] 
    10	, DO_COSTOMER_FUNCTION,		// Function key F11	[DAh]  
    11	, DO_COSTOMER_FUNCTION,		// Function key F12	[DBh] 
	12	, DO_COSTOMER_FUNCTION,   	// Function key Esc	[DCh]
	13	, DO_COSTOMER_FUNCTION,   	// Function key Up arrow	[DDh]
	14	, DO_COSTOMER_FUNCTION,   	// Function key Down arrow	[DEh]
	15	, DO_COSTOMER_FUNCTION,  	// Function key Left arrow	[DFh]
	16	, DO_COSTOMER_FUNCTION,  	// Function key Right arrow	[E0h]	
};

									// Reserved 0xE0 ~ 0xFF		

//-----------------------------------------------------------------
// The function of checking boot hotkey Dino 1024    
//-----------------------------------------------------------------
#define Crisiskey01        0x8E   	// Fn
#define Crisiskey02        0xEC  	// ESC

void CrisisHotkey01(BYTE event)
{
    if(event == BREAK_EVENT)
    {
        CrisisKeyStatus=0x00;
    }
    else if(event == MAKE_EVENT)
    {
        CrisisKeyStatus++;
    }
}

void CrisisHotkey02(BYTE event)
{
    if(event == BREAK_EVENT)
    {
        CrisisKeyStatus=0x00;
    }
    else if(event == MAKE_EVENT)
    {
        CrisisKeyStatus++;
    }
}


const sBootHotKeyStruct code asBootHotKeyStruct[]=
{
	{ Crisiskey01, CrisisHotkey01	},
	{ Crisiskey02, CrisisHotkey02	},
};

void CheckBootHotKey(matrix, event)
{
	BYTE index;
    for(index=0x00; index<(sizeof(asBootHotKeyStruct)/sizeof(sBootHotKeyStruct)); index++)
    {
		if(matrix==asBootHotKeyStruct[index].matrix)
	    {
	        (asBootHotKeyStruct[index].pfunction)(event);
            return;
        }
    }
    CrisisKeyStatus=0x00;
}

//-----------------------------------------------------------------------------
// Keyboard wake up system from S3
//-----------------------------------------------------------------------------
void CheckKBS3Wake(BYTE BKSI,BYTE BKSO)
{
	BYTE wuv;

    wuv = ((BKSI << 4)|BKSO);
    Tmp_code_pointer = &KB_S3WakeUP_Tables;
    if(*(Tmp_code_pointer + wuv)==0x55)
    {
        PulseSBPowerButton();
    }
}

void Et_CheckKBS3Wake(BYTE BKSI,BYTE BKSO)
{
	BYTE wuv;

    wuv = ((BKSI*3)+BKSO);
    Tmp_code_pointer = &EtKey_S3WakeUP_Tables;
    if(*(Tmp_code_pointer + wuv)==0x55)
    {
        PulseSBPowerButton();
    }
}

//----------------------------------------------------------------------------
// table_entry : value of keyboard matrix table. for example Rc_ROM_Tables[]
// event : key MAKE_EVENT or BREAK_EVENT or REPEAT_EVENT
//----------------------------------------------------------------------------
void OEM_Hook_Send_Key(BYTE table_entry, BYTE event)
{
    if(SystemNotS0)
    {  	
        CheckBootHotKey(table_entry,event);
    }
}

//----------------------------------------------------------------------------
// Return : 0xFF --> Send_Key function will be break; (no any scan code to host)
//----------------------------------------------------------------------------
BYTE OEM_Hook_Skip_Send_Key(void)
{
    return(0x00);
}
								
//-----------------------------------------------------------------------------
// Keyboard hook function (KSO0 - KSO15)
// KSIValus : keyboard KSI
// KSOValus : keyboard KSO
//-----------------------------------------------------------------------------
void Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{
#if S3KeyboardWakeUp 
	if(SystemIsS3)
	{
		CheckKBS3Wake(KSIValus,KSOValus);
	}
#endif	
}		

//-----------------------------------------------------------------------------
// Keyboard hook function (KSO16 - KSO17 and GPIO KSO)
// KSIValus : keyboard KSI
// KSOValus : keyboard KSO
//-----------------------------------------------------------------------------
void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{
#if S3KeyboardWakeUp 
	if(SystemIsS3)
	{
		Et_CheckKBS3Wake(KSIValus,KSOValus);
	}
#endif	
}

/* ---------------------------------------------------------------------------
 * FUNCTION: Hook_Setup_Scanner_Pntr - to define the possible scanner tables
 *
 *     0   Rc_RAM_Table
 *     1   ROM Table 1
 *     ...
 * ------------------------------------------------------------------------ */
void Hook_Setup_Scanner_Pntr(void)
{                                        	
	Scanner_Table_Pntr = &Rc_ROM_Tables;
	Extendkey_Table_Pntr = &EtKey_ROM_Tables;
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to high
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinH(void)
{
	if(ExternMatrixGPO)
	{
		GPOKeyPin1H;
	}
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to low
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinL(void)
{
	if(ExternMatrixGPO)
	{
		GPOKeyPin1L;
	}
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin output
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinCtrl(void)
{
	if(ExternMatrixGPO)
	{
		GPOKeyPin1Ctl = 0x40;		// output
	}
}

//-----------------------------------------------------------------------------
// Fn key make
//-----------------------------------------------------------------------------
void Hook_Fn_Key_Make(void)
{

}

//-----------------------------------------------------------------------------
// Fn key break
//-----------------------------------------------------------------------------
void Hook_Fn_Key_Break(void)
{

}

//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit6
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT6(void)
{
    return(0x00);
}

//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit7
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT7(void)
{
    return(0x00);
}