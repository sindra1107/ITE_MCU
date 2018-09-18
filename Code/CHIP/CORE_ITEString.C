/*-----------------------------------------------------------------------------
 * TITLE: CORE_ITESTRING.C
 *
 * Author : Dino
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 * To occupy code space 0x40 - 0x6F
 * 0x40 - 0x4F is 16B-Signature
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

const unsigned char code ITEString[] =
{
    0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,EC_Signature_Flag,
    0x85,0x12,0x5A,0x5A,0xAA,EC_Signature_Addr,0x55,0x55,
};

const unsigned char code VersionString[] =  "ITE EC-V14.5  ";