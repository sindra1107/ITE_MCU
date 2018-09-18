/*-----------------------------------------------------------------------------
 * TITLE: CORE_SCAN.H
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

#ifndef CORE_SCAN_H
#define CORE_SCAN_H

#include <OEM_Project.H>

#define KSO16CtrlReg	GPCRC3
#define KSO17CtrlReg	GPCRC5

union KEY
{
   BYTE byte;
   struct
   {
      FIELD input:            3; /* Bit 0 - 2. Bit address of the KI bit. */
      FIELD debounce_status:  1; /* Bit 3.     Debounce status. */
      FIELD output:           4; /* Bit 4 - 7. Bit address of the KO bit. */
   } field;
};

struct Sscan
{
    FIELD kbf_head:  4; /* Keyboard buffer head (0-15). */
    FIELD kbf_tail:  4; /* Keyboard buffer tail (0-15). */
    FIELD kbf_mark:  4; /* Keyboard buffer overflow marker (0-15). */
    FIELD TMscale:   4; /* Typematic scale. */
    FIELD scan_line: 4;
    FIELD saf_make:  1; /* Scan activity flag - make. */
    FIELD saf_break: 1; /* Scan activity flag - break. */
    FIELD saf_keys:  1; /* Scan activity flag - keys active. */
};

union Unew_keyl
{
    BYTE byte;
    struct
    {
        FIELD state: 1; /* Bit[0]   1 means debounce counted out. */
        FIELD trans: 1; /* Bit[1]   1 for BREAK. 0 for MAKE. */
        FIELD intm:  1; /* Bit[2] 	*/
        FIELD ghost: 1; /* Bit[3]   Ghost key indicator. */
        FIELD same:  1; /* Bit[4]   1 = key activity last time was SAME as this time. */
        FIELD count: 3; /* Bit[5:7] Debounce counter. */
    }field;
};

//extern const unsigned char code EtKey_ROM_Tables[];
extern data union KEY new_keyh;
extern data union KEY typematic;
extern data struct Sscan scan;
extern data union Unew_keyl new_keyl;
// For extend keys
extern data union KEY new_extendkey;
extern data struct Sscan extendscan;
extern data union Unew_keyl extendstatus;
extern data union KEY etkeytypematic;

//*******************************************************
#ifndef KB_HW_KeyScan   // Firmware scan keyboard
//*******************************************************
static void check_tm(union KEY key);
static void debounce_key(void);
static void change_valid(void);
static void check_scan(BYTE changes, BYTE scan_address);
static void cscfnd(BYTE bit_num, BYTE scan_address);
static void setup_debounce(BYTE bit_num, BYTE scan_address, BYTE event);
static FLAG find_paths(BYTE change_make_key, BYTE scan_address);

void Lock_Scan(void);
void Unlock_Scan(void); 
void Start_Scan_Transmission(void);
FLAG Check_Scan_Transmission(void);
void Init_Kbd(void);
void Setup_Diode_Key(void);
void Clear_Key(void);
void Clear_Typematic(void);
void Set_Typematic(WORD type_rate);
extern void service_scan(void);
BYTE Get_Buffer(void);
void Buffer_Mark(void);
FLAG Buffer_Key(BYTE row_column);
BYTE Buffer_String(const BYTE *pntr);
extern BYTE scan_keys(void);

void Enable_Any_Key_Irq(void);
void Write_Strobe(BYTE scan_line_num);
BYTE Read_Scan_Lines(void);
void Scan_Init(void);
FLAG Get_Kbd_Type(void);
void Setup_Ext_Hotkey_Pntr(void);

// For extend keys
static BYTE bScanExtendKeys(void);
static void SetExtendScanLines(BYTE scan_line);
static void CheckExtendKeys(bit_num, scan_address);
static void ExtendKeyDebounce(BYTE KSI_bit_num, BYTE scan_address, BYTE event);
static void DebounceExtendkey(void);
static void CheckExtendKeyValid(void);
static void Send_EtScan2(union KEY key, BYTE event);
static void ClearExtendKeys(void);
static void CheckEtKeystm(union KEY key);
extern void CheckKSO1617Support(void);

//*******************************************************
#else   // Hardware scan keyboard
//*******************************************************
extern BYTE Get_Buffer(void);
extern void Buffer_Mark(void);
extern FLAG Buffer_Key(BYTE row_column);
extern BYTE Buffer_String(const BYTE *pntr);
extern FLAG Get_Kbd_Type(void);
extern void service_scan(void);
extern void Unlock_Scan(void); 
extern void Lock_Scan(void);
extern void Set_Typematic(WORD type_rate);
extern void Clear_Key(void);
extern void Clear_Typematic(void);
extern void Init_Kbd(void);
extern void CheckKSO1617Support(void);
extern void Scan_Init(void);
extern void Enable_Any_Key_Irq(void);
extern void check_tm(union KEY key);
extern void HW_KB_Check_TM(void);
extern void Clear_AllKeysBreak(void);

//*******************************************************
#endif  // #ifndef KB_HW_KeyScan  
//*******************************************************

#endif  
