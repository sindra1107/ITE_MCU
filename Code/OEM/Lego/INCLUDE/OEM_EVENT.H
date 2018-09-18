/*-----------------------------------------------------------------------------
 * TITLE: OEM_EVENT.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_INPUT_H
#define OEM_INPUT_H

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void EventManager(BYTE device_id);

struct sDebounce
{
	XBYTE	*REG;
	BYTE	Flag;
	XBYTE	*Cunter;
	BYTE	Time;
	FUNCT_PTR_V_V	press;
	FUNCT_PTR_V_V	release;
	FUNCT_PTR_V_V	nochange;	
};

#endif