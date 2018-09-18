/*-----------------------------------------------------------------------------
 * TITLE: CORE_SCN.C - code to handle local keyboard scanning.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//*******************************************************
#ifndef KB_HW_KeyScan   // Firmware scan keyboard
//******************************************************* 
void CapDelay(void)
{
    WNCKR = 0x00;               // Delay 15.26 us
    WNCKR = 0x00;               // Delay 15.26 us	
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   scan_keys
 *
 * Scan key matrix once.
 *
 * Return: value != 0, scan activity detected, scan again later.
 *         value  = 0, no scan activity detected.
 * ------------------------------------------------------------------------- */
BYTE scan_keys(void)
{
	BYTE result;
	result = FALSE;
	
    scan.saf_make = 0;
    scan.saf_break = 0;
    scan.saf_keys = 0;

 	if (typematic.byte) 
	{
     	check_tm(typematic);  	// Check typematic. 
 	}

	if (new_keyh.byte)   		// Exist Debounce key? 
 	{   						// Yes, bounding. 
     	scan.saf_make = 1;   	// Set debounce make bit. 
      	debounce_key();
      	result = TRUE;
 	}
    
    if (!result)				// Otherwise, scan all. 
    {  
        for (ITempB03=0;ITempB03<16;ITempB03++)
        {
        	Write_Strobe(ITempB03);
			CapDelay();								
         	ITempB02 = KSI; 	// Read in KI 0 - 7 sense line data. */
            ITempB02 = (~ITempB02) ^ bscan_matrix[ITempB03];
            if (ITempB02 != 0) 
           	{
            	check_scan(ITempB02, ITempB03); 
          	}

            if (bscan_matrix[ITempB03]) 
          	{  							// Here, if current still active. 
                scan.saf_keys = 1;   	// Set keys active bits. Check all key release. 
            }   
			KSOL=0xFF;	
			KSOH1=0xFF;
        }
        								// If ghost exist, make key clear.
        if (new_keyl.field.ghost == 1)
        {  
            new_keyl.field.ghost = 0;	// Ghost flag is set. Clear it.
            ITempB01 = new_keyl.byte & 7;
            if (ITempB01 == 0)
            {  
                ITempB01 = Byte_Mask((BYTE) (new_keyh.field.input));
                ITempB01 = ITempB01 & diode_key; 
            }

            if (ITempB01 == 0)
            {   
                new_keyh.byte = 0;	// Clear new key. 
                new_keyl.byte = 0;
            }
        } 
    }

	return((BYTE) (scan.saf_make + scan.saf_break + scan.saf_keys));
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Write_Strobe
 *
 * Writes the scan matrix KSO[15:0] lines based on Scan Line bit number.
 *
 * KSO[15:0] will be all floats or open except for the bit corresponding to
 * the Scan Line number.  This bit will be low to be detected by the sense
 * line input port later.
 *
 * Config.Msk_Strobe_H and Config.Msk_Strobe_L specify which of the 16 bits on
 * the port are used for the scanner.  (1 = Scanner, 0 = Other OEM function).
 * This allows port pins which are not used for the scanner output lines to be
 * used for something else.
 *
 * Input: Scan line number.
 * ------------------------------------------------------------------------- */
void Write_Strobe(BYTE scan_line_num)
{
	if (scan_line_num<8)
   	{
     	KSOL=~(0x01<<scan_line_num);
      	KSOH1=0xFF;
  	}
 	else
  	{
     	KSOL=0xFF;
   		KSOH1=~(0x01<<(scan_line_num-0x08));
   	} 

	if(ExtendMatrix)
	{
		KSOH2 = 0xFF;
		Hook_SetGPIOScanPinH();
	}
}

/* ----------------------------------------------------------------------------
 * FUNCTION: check_scan
 *
 * Input:
 *     changes = Any bit set indicates there is a difference in state from
 *         last KSI to this KSI.
 *     scan_address = Address of strobe line that was low when changes was
 *         computed.
 *
 * NOTE:  For the shift and bit test of "changes" to work, "changes" MUST be
 * unsigned.  (Right shifting an unsigned quantity fills vacated bits with
 * zeros.  Right shifting a signed quantity will fill vacated bits with sign
 * bits on some machines and zero bits on others.)
 * ------------------------------------------------------------------------- */
static void check_scan(BYTE changes, BYTE scan_address)
{
    BYTE flag;
    BYTE change_make_key;
    BYTE bit_num; 
     
	flag = FALSE;					// Simple Matrix. 
	if (new_keyl.field.ghost == 1)
 	{
    	flag = TRUE;
	}
	else
	{   /* Find 0 -> 1 's. */
		change_make_key = changes & ~bscan_matrix[scan_address];
     	if (change_make_key == 0) 
		{
           	flag = FALSE;
    	}
   		else if (find_paths(change_make_key, scan_address)) 
		{
         	flag = TRUE;    /* TRUE if ghost keys. */
       	}
	}

	if (flag)
 	{   /* Ghost exists. */
  		new_keyl.field.ghost = 1;  /* Set ghost flag. */
    	/* Only look at 1 -> 0 transition & diode key always no ghost. */
     	changes &= bscan_matrix[scan_address] | diode_key;
	}

    bit_num = 0;
    while (changes != 0)
    {   
        if (changes & 0x01) 	/* Look at changes 1 bit at a time. */
		{
            cscfnd(bit_num, scan_address);
        }
        bit_num++;
        changes = changes >> 1; /* Shift bit out (and a zero bit in) to check next bit. */
    }
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   cscfnd
 *
 * Find changed bit.  This subroutine is called for each bit in this KSI that
 * is different from last KSI.
 * ------------------------------------------------------------------------- */
static void cscfnd(BYTE bit_num, BYTE scan_address)
{
    if (bscan_matrix[scan_address] & Byte_Mask(bit_num))
    {  
        if (scan.saf_break == 0) 
		{
            scan.saf_break = 1;
            setup_debounce(bit_num, scan_address, BREAK_EVENT);
        }
    }
    else
    {   
        if (scan.saf_make == 0) 
		{
            scan.saf_make = 1;
            setup_debounce(bit_num, scan_address, MAKE_EVENT);
        }
    } 
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   setup_debounce
 *
 * Input:
 *     scan_address = number of bit of KO.
 *     bit_num = number of bit that changed from last KI to this KI for KO.
 *     event = contact event (MAKE_EVENT or BREAK_EVENT).
 * ------------------------------------------------------------------------- */
static void setup_debounce(BYTE bit_num, BYTE scan_address, BYTE event)
{
    new_keyh.field.output = scan_address;
    new_keyh.field.input = bit_num;
    new_keyh.field.debounce_status = 1;
    new_keyl.field.state = 0;  /* Debounce has not counted out. */
    new_keyl.field.same = 0;   /* Key activity indication. */

    if (event == MAKE_EVENT)
    {   /* For MAKE key (key pressed). */
        new_keyl.field.trans = 0;
        new_keyl.field.count = Ext_Cb2.field.Break_Count; /* Shouldn't this be Make_Count? */
    }
    else
    {   /* For BREAK key (key released). */
        new_keyl.field.trans = 1;
        new_keyl.field.count = Ext_Cb2.field.Make_Count; /* Shouldn't this be Break_Count? */
    }
}

/* ----------------------------------------------------------------------------
 * FUNCTION: find_paths
 *
 * Input:  DOWN_STATE  scan_address
 *         change_make_key
 *
 * Return: FALSE if no paths found, Otherwise returns TRUE.
 * ------------------------------------------------------------------------- */
static FLAG find_paths(BYTE change_make_key, BYTE scan_address)
{
    FLAG paths_found, done;
    BYTE paths, temp, bits;
    BYTE first_address;

    /* For the shift and bit test to work, "bits" MUST be unsigned.  (Right
       shifting an unsigned quantity fills vacated bits with zeros.  Right
       shifting a signed quantity will fill vacated bits with sign bits on some
       machines and zero bits on others.) */
    done = FALSE;
    paths_found = FALSE;
    first_address = scan_address;

    change_make_key &= ~(diode_key); /* Ignore diode key. */
    /* change_make_key = bKO_BITS. */

    if (change_make_key == 0) 
	{
        done = TRUE; /* paths_found == FALSE */
    }

    if (!done)
    {
        paths = bscan_matrix[scan_address] | change_make_key;
        paths &= ~(diode_key);  /* Ignore diode key. */
        /* paths = bKO_PATHS. */
        if (paths == 0) 
		{
            done = TRUE;  /* paths_found == FALSE */
        }
    }

    while (!done)
    {
        scan_address++;

        if (scan_address >= MAX_SCAN_LINES) 	
        //if(scan_address >= STANDARD_SCAN_LINES)
		{
            scan_address = 0;   /* Wrap around */
        }

        if (scan_address == first_address) 
		{
            done = TRUE;        /* No scan lines left.  paths_found == FALSE */
        }

        if (!done)
        {   /* Check Path */
            temp  = bscan_matrix[scan_address]; /* Any paths? */
            temp &= ~(diode_key);               /* Ignore diode key */

            if (temp != 0) 
			{    /* Paths found */
                temp &= paths;  /* Do paths line up? */
            }

            if (temp != 0)
            {   /* Paths line up */
                if (change_make_key != temp)  /* Only 1 bit set? */
                {   /* No, ghost exists. */
                    paths_found = TRUE;
                    done = TRUE;
                }

                if (!done)
                {   /* The following checks if more than one bit is set to 1.
                       Because "bits" is unsigned, each shift moves the bit
                       under test out and a 0 bit in.  When the first 1 bit is
                       found, if "bits" == 0, this indicates that there is only
                       one bit set. */
                    bits = paths;  /* Only 1 bit set? */
                    temp = FALSE;

                    do
                    {
                        if (bits & 0x01) 
						{
                            temp = TRUE;
                        }

                        /* Shift bit out (and a zero bit in) to check next bit. */
                        bits = bits >> 1;
                    } while (temp == FALSE);

                    if (bits != 0)
                    {   /* No, more than 1 bit set. */
                        paths_found = TRUE;
                        done = TRUE;
                    }
                } /* if (!done) */
            } /* if (temp != 0) */
        } /* if (!done) */
    } /* while (!done) */

   return (paths_found);
}

/* ----------------------------------------------------------------------------
 * FUNCTION: debounce_key
 * ------------------------------------------------------------------------- */
static void debounce_key(void)
{							
    scan.scan_line = new_keyh.field.output;	
    Write_Strobe(scan.scan_line); 
	CapDelay();	
    ITempB01 = Read_Scan_Lines(); 
    ITempB01 = ~ITempB01;            

    ITempB02 = Byte_Mask((BYTE) (new_keyh.field.input));	
    ITempB02 = ITempB02 & ITempB01;                       			

    if (ITempB02 != 0)
    {  
        if (new_keyl.field.trans == 0) 
		{
            new_keyl.field.same = 1;    // last key detected as a MAKE,  same = 1.
        }
        else 
		{
            new_keyl.field.same = 0;    // last key detected as a BREAK, same = 0.
        }
    }
    else
    { 
        if (new_keyl.field.trans == 0) 
		{
            new_keyl.field.same = 0;    // last key detected as a MAKE,  same = 0. 
        }
        else 
		{
            new_keyl.field.same = 1;    // last key detected as a BREAK, same = 1. 
        }
    } 
#if 0		// Dino 0201 change keyboard debounce time to 5ms
    if (new_keyl.field.state == 0)
    {  
        if (new_keyl.field.count != 0)
        {   
            new_keyl.field.count--;
        }
        else
        {
            if (new_keyl.field.same == 0)
            {   
                new_keyh.byte = 0;	// Debounce failed, so claer all data
                new_keyl.byte = 0;
            }
            else
            {   
                new_keyl.field.state = 1;
            } 
        }
    }
    else
#endif		
    { 
        if (new_keyl.field.same == 0)
        {   
            new_keyh.byte = 0;	// Debounce failed. 
            new_keyl.byte = 0;
        }
        else
        { 
      		change_valid(); 	// Debounce OK 
        } 
    }
}

/* ----------------------------------------------------------------
 * FUNCTION: Read_Scan_Lines - Read KSI[7:0] of the scan matrix
 *
 * Return: Data from sense lines that are enabled.
 *         The lines that are disabled return 1s.
 *
 * C prototype: BYTE Read_Scan_Lines();
 * ---------------------------------------------------------------- */
BYTE Read_Scan_Lines(void)
{
  	return (KSI);                  
}

/* ---------------------------------------------------------------
 * FUNCTION: change_valid
 * --------------------------------------------------------------- */
static void change_valid(void)
{
    ITempB04 = Byte_Mask((BYTE) (new_keyh.field.input)); 
    ITempB03 = bscan_matrix[new_keyh.field.output]; 
    ITempB03 = ITempB03 ^ ITempB04;                         
    bscan_matrix[new_keyh.field.output] = ITempB03; 

	ITempB05 = BREAK_EVENT;           	// Ready for BREAK indication. 
    if ((ITempB04 & ITempB03) != 0)
    {   						
        ITempB05 = MAKE_EVENT;  				
        typematic.byte = new_keyh.byte;	// Set New Typematic Key.
        scan.TMscale = TM_SCALE;
        bTMcount = bTMdelay;

		etkeytypematic.byte = 0x00;
    }
	
    Send_Scan2(new_keyh, ITempB05);
    new_keyh.byte = 0;
    new_keyl.byte = 0; 
}

/* ----------------------------------------------------------------------------
 * FUNCTION: check_tm - Handle typematic function.
 *
 * Input: Typematic key
 * ------------------------------------------------------------------------- */
static void check_tm(union KEY key)
{
 	ITempB02 = FALSE;										
    ITempB01 = Byte_Mask((BYTE) (key.field.input)); 
    ITempB01 = ITempB01 & bscan_matrix[key.field.output];

    if (ITempB01 == 0)		 	// Release Typematic key? 
    {   
        typematic.byte = 0;	// Clear Typematic. 
        ITempB02 = TRUE;
    }

    if (!ITempB02)
    {  
        scan.TMscale--;		 // Count down Prescale.
        if (scan.TMscale != 0) 
		{
            ITempB02 = TRUE;
        }
    }

    if (!ITempB02)
    {
        scan.TMscale = TM_SCALE;// Reload prescale counter. 
        bTMcount--;             // Count down TMcount. 
        if (bTMcount != 0) 
		{
            ITempB02 = TRUE;
        }
    }

    if (!ITempB02)
    {
        bTMcount = bTMrepeat;   // Reload TMcount. 
        Send_Scan2(key, REPEAT_EVENT);   
    }
}

/* ----------------------------------------------------------------
 * FUNCTION: Scan_Init - Initialize internal keyboard (scanner)
 * ---------------------------------------------------------------- */
void Scan_Init(void)					// Lower all KSO lines for scan matrix
{
 	KSOL=0x00;  
  	KSOH1=0x00;
	
	if(ExtendMatrix)				// The function of extend keys
	{
		KSOH2=0x00;
		
		Hook_SetGPIOScanPinCtrl();
		Hook_SetGPIOScanPinL();
	}
}

/* ----------------------------------------------------------------
 * FUNCTION: Enable_Any_Key_Irq
 *
 * Setup for any key from scanner to generate an interrupt.
 *
 * Lower the "strobe" lines so that when any key is pressed at least one input
 * line will go low.  Any bits (out of the possible 16) that are not used for
 * the internal keyboard (scanner) are left alone.  This is done using
 * Config.Msk_Strobe_H and Config.Msk_Strobe_L.
 *
 * Then, if the internal keyboard (scanner) is enabled, allow the interrupt to
 * occur when a key is pressed on the scanner.
 * -------------------------------------------------------------- */
void Enable_Any_Key_Irq(void)	// Lower all KSO lines for scan matrix
{
	KSOL=0x00;             
  	KSOH1=0x00;
	
	if (ExtendMatrix)
	{
		KSOH2=0x00;
		Hook_SetGPIOScanPinL();
	}	
	SET_MASK(IER1,Int_KB);      // enable KSI interrupt					
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Start_Scan_Transmission
 *
 * Lock out other devices so scanner can transmit data to Host, and start
 * Timer B with event "SEND_ENABLE".  When the "RESPONSE_TIME" has expired,
 * the Timer B interrupt handler will post a "SEND" service request to be
 * dispatched by the main service loop.  At that time the data will be sent to
 * the Host via the "SEND" service handler.
 * ------------------------------------------------------------------------- */
void Start_Scan_Transmission(void)
{
    //Load_Timer_B();
    //Timer_B.fbit.SEND_ENABLE = 1;
    SetServiceSendFlag();
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Check_Scan_Transmission
 *
 * See if the scanner keyboard data transmission (to Host) should be allowed.
 *
 * Return: Transmission status indication.  TRUE if ok to transmit.
 * ------------------------------------------------------------------------- */
FLAG Check_Scan_Transmission(void)
{
    FLAG allow_transmission = FALSE;

    if ((Int_Var.Scan_Lock == 0) && (Flag.SCAN_INH == 0)) 
    {   	/* Scanner transmission is locked and inhibited. */ 
    
        if (scan.kbf_head != scan.kbf_tail) 
		{
            allow_transmission = TRUE;  /* Allow transmission */
        }
    }    

    return (allow_transmission);
}

/* ----------------------------------------------------------------
 * FUNCTION: Get_Kbd_Type
 *
 * Returns the type of the internal keyboard.
 *
 * Returns: 0 = U.S. keyboard, 1 = Japanese keyboard.
 * -------------------------------------------------------------- */
FLAG Get_Kbd_Type(void)
{						// Check keyboard type here
						// Returns: 0 = U.S. keyboard, 1 = Japanese keyboard.
	if(1)				// check type here
	{
		return(0);  	// U.S. keyboard. 
	}
	else
	{
		return(1);		// Japanese keyboard
	}
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Lock_Scan
 *
 * Lock out the scanner via "Scan_Lock" and clear pending scanner "SEND"
 * events.
 * ------------------------------------------------------------------------- */
void Lock_Scan(void)
{
    Int_Var.Scan_Lock = 1;
    //Timer_B.fbit.SEND_ENABLE = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Init_Kbd - Scanner Keyboard Initialization.
 * ------------------------------------------------------------------------- */
void Unlock_Scan(void) 
{
	Int_Var.Scan_Lock = 0;
}

void CheckKSO1617Support(void)
{
	ExtendScanPin = 0x00;

	if((KSO16CtrlReg&0xFB)==0x00)
	{
		ExtendScanPin++;
	}

	if((KSO17CtrlReg&0xFB)==0x00)
	{
		ExtendScanPin++;
	}
	
	if(ExtendScanPin!=0x00)
	{
		ExtendMatrix = 1; 
	} 
	else
	{
		ExtendMatrix = 0;
	}
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Init_Kbd - Scanner Keyboard Initialization.
 * ------------------------------------------------------------------------- */
void Init_Kbd(void)
{
	CheckKSO1617Support();

	Scan_Init();  

	Hook_Setup_Scanner_Pntr();
    Setup_Diode_Key();

    new_keyh.byte = 0;
    new_keyl.byte = 0;

 	ClearExtendKeys();	// for extend keys

    Clear_Fn_Keys();
    Clear_Key();        /* Clear key matrix/buffer */
    Clear_Typematic();

	Enable_Any_Key_Irq();

    FN_Key_Break = 0x00;        // Clear FN_Key_Break
    FN_Key_Break_HS = 0x00;

    ClearFnKeyBundledFalg();
    
    #if KB_FnStickKey
    FnStickKey = 0;
    #endif
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Setup_Diode_Key
 * ------------------------------------------------------------------------- */
void Setup_Diode_Key(void)
{
 	if(1)
	{   
        //if (Ext_Cb3_DISABLE_NKEY) { /* Simple matrix (NO diodes) */
        diode_key = 0x00;
    }
    else 
	{                      /* N-key (diodes in keyboard) */
        diode_key = 0xFF;
    }
}


/* ----------------------------------------------------------------------------
 * FUNCTION: Clear_Key - Clear local keyboard buffer and related variables.
 * ------------------------------------------------------------------------- */
void Clear_Key(void)
{
    BYTE i;
    //WORD msk_strobe;

    for(i = 0; i < MAX_SCAN_LINES; i++)	// Clear scan matrix.
	{
        bscan_matrix[i] = 0;
    }

    for(i = 0; i < KBF_SIZE; i++)		// Clear key buffer.
	{
        bKEY_BUFF[i] = 0;
    }

    scan.kbf_head = 0;
    scan.kbf_tail = 0;
    typematic.byte = 0;
    scan.saf_make = 0;
    scan.saf_break = 0;
    scan.saf_keys = 0;
	scan.scan_line = 0;
}


/* ----------------------------------------------------------------------------
 * FUNCTION: Clear_Typematic - Set default typematic delay and clear type-matic action.
 * ------------------------------------------------------------------------- */
void Clear_Typematic(void)
{
    typematic.byte = 0;
    bTMdelay = TM_DELAY;
    bTMrepeat = TM_REPEAT;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Set_Typematic - Set the typematic rate.
 *
 * Input: typematic rate
 *        Bit[4:0] Typematic repeat interval
 *        Bit[6:5] Delay time
 * ------------------------------------------------------------------------- */
//const BYTE code repeat_tbl[] =
//{
//     3,  4,  4,  5,  5,  6,  6,  7,  7,  8,  9, 10, 11, 12, 13, 14,
//    15, 16, 18, 20, 22, 24, 25, 27, 30, 33, 37, 41, 44, 48, 52, 55
//};
//const BYTE code delay_tbl[] = {27, 55, 83, 111};

const BYTE code repeat_tbl[] =
{
     3,  4,  4,  5,  5,  5,  6,  6,  7,  7,  8, 9, 10, 11, 11, 12,
    13, 15, 16, 18, 20, 21, 23, 25, 27, 30, 33, 37, 40, 43, 47, 50
};
const BYTE code delay_tbl[] = {25, 50, 75, 100};

void Set_Typematic(WORD type_rate)
{
    Save_Typematic = type_rate;   /* Save for suspend/resume. */

    /* Bit 4 - 0 typematic repeat interval index. */
    bTMrepeat = repeat_tbl[type_rate & 0x1F];

    /* Bit 6 - 5 delay time index. */
    bTMdelay = delay_tbl[(type_rate >> 5) & 0x03];
}


/* ----------------------------------------------------------------------------
 * FUNCTION: Handle_Scan - Service the local keyboard in response to a key press.
 * ------------------------------------------------------------------------- */
void service_scan(void)
{
 	BYTE scan_activity;

    if (Timer_A.fbit.TMR_SCAN == 0)
    {
        Timer_A.fbit.TMR_SCAN = 1;	// Activate scan timer.
    }
	
	if(ExtendMatrix)				// extend keys	
	{
		scan_activity = scan_keys()|bScanExtendKeys();	 
	}
	else 
	{
		scan_activity = scan_keys();// Scan keyboard matrix one time.
	}

  	if (scan_activity)				// There is scan activity.
    {   	
    	;
	}
    else							// No scan activity 
    {   
        Timer_A.fbit.TMR_SCAN = 0;  // Disable the scan timer. 
        F_Service_KEY = 0;     		// Clear any pending service request.  
        Enable_Any_Key_Irq();       // Enable Any Key interrupt.
        FN_Key_Break = 0x00;        // Clear FN_Key_Break
        FN_Key_Break_HS = 0x00;

        ClearFnKeyBundledFalg();
  	}

    if (Timer_B.fbit.SEND_ENABLE == 0) 	// 1 = Device send request (Request already set)
    {
   		if (Check_Scan_Transmission())	// Data available
		{   
     		Start_Scan_Transmission();	// Start new transmission
     	}
    }
}


/*****************************************************************************/
/********** SCANNER KEY BUFFER ROUTINES **************************************/
/*****************************************************************************/

/* ----------------------------------------------------------------------------
 * FUNCTION:   Get_Buffer
 *
 * Get data byte from keyboard buffer (if not empty) and update "scan.kbf_head"
 * with new index into keyboard buffer.
 *
 * Return: Data from buffer (WORD of all 1's if buffer is empty).
 * ------------------------------------------------------------------------- */
//WORD Get_Buffer(void)
BYTE Get_Buffer(void)
{
    //WORD buffer_data;
    BYTE buffer_data;

    if (scan.kbf_head != scan.kbf_tail)
    {
        //buffer_data = (WORD) bKEY_BUFF[scan.kbf_head++];
		buffer_data = bKEY_BUFF[scan.kbf_head++];
        if (scan.kbf_head >= KBF_SIZE) 
		{
            scan.kbf_head = 0;
        }
    }
    else
    {   /* Buffer is empty. */
        buffer_data = 0xFF;
    }
    return (buffer_data);
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_Mark - Mark local keyboard buffer tail.
 * ------------------------------------------------------------------------- */
void Buffer_Mark(void)
{
    scan.kbf_mark = scan.kbf_tail;   /* Copy scan.kbf_tail to scan.kbf_mark. */
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_Key
 *
 * Input:  Row/Column (0iii,oooo) to put in buffer.
 * Return: TRUE operation successful, FALSE unsuccessful.
 * ------------------------------------------------------------------------- */
FLAG Buffer_Key(BYTE row_column)
{
    FLAG ready = TRUE;  /* Ready for successful operation */

    bKEY_BUFF[scan.kbf_tail] = row_column;  /* Store Data to Buffer Tail */
    scan.kbf_tail++;                        /* Increment Buffer Tail (pointer) */

    if (scan.kbf_tail >= KBF_SIZE) 
	{
        scan.kbf_tail = 0;  /* Wrap pointer if too large. */
    }

    /* Check Overflow */
    if (scan.kbf_tail == scan.kbf_head)
    {   /* Overflow */
        scan.kbf_tail = scan.kbf_mark;  /* Restore buffer marker. */
        bKEY_BUFF[scan.kbf_tail] = 0;   /* Set OverFlow Mark. */
        ready = FALSE;                  /* Overflow Indication !!! */
    }

    return (ready);
}


/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_String
 *
 * Places a string in the local keyboard buffer (without a terminating NULL).
 * Call Buffer_Key to place data in key buffer.
 *
 * Input:  Pointer to null terminated string.
 * Return: 0x80 if buffer overflow error, else 0.
 * ------------------------------------------------------------------------- */
BYTE Buffer_String(const BYTE *pntr)
{
    register BYTE error = 0;

    while ((*pntr != 0) && (error == 0))
    {
        if (Buffer_Key(*pntr++) == 0) {
            error = 0x80;   /* Indicate Overflow */
        }
    }

    return (error);
}

//*****************************************************************
// The functions of extend keys
//*****************************************************************
//-----------------------------------------------------------------
// The function of Scaning extend keys
//-----------------------------------------------------------------
BYTE bScanExtendKeys(void)
{
	ITempB06 = FALSE;
	extendscan.saf_break = 0;
	extendscan.saf_make= 0;
	extendscan.saf_keys= 0;

 	if (etkeytypematic.byte) 
	{
     	CheckEtKeystm(etkeytypematic);	// Check typematic. 
 	}

	if (new_extendkey.byte)   		
 	{   								// Yes, bounding.
     	extendscan.saf_make = 1;  
      	DebounceExtendkey();
      	ITempB06 = TRUE;
 	}

	if(ITempB06 == FALSE)
	{
        for (ITempB01=0;ITempB01<ExtendScanPin;ITempB01++)
        {
			SetExtendScanLines(ITempB01);
			ITempB02 = KSI;
			ITempB02 = (~ITempB02)^bscan_matrix[ITempB01+STANDARD_SCAN_LINES];
            if (ITempB02 != 0) 
           	{
				CheckExtendKeys(ITempB02,(ITempB01+STANDARD_SCAN_LINES));
          	}

            if (bscan_matrix[ITempB01+STANDARD_SCAN_LINES]) 
          	{  								// Here, if current still active.
                extendscan.saf_keys = 1;   	// Set keys active bits. Check all key release.
            }   
            
            KSOH2 = 0xFF;
		    Hook_SetGPIOScanPinH();
        }
	}

	if (extendstatus.field.ghost == 1)
 	{  
     	extendstatus.field.ghost = 0;	// Ghost flag is set.
     	ITempB01 = extendstatus.byte & 7;
   		if (ITempB01 == 0)
     	{  
        	ITempB01 = Byte_Mask((BYTE)(new_extendkey.field.input));
        	ITempB01 = ITempB01 & diode_key; 
  		}
    	if (ITempB01 == 0)
      	{   
        	new_extendkey.byte = 0;		// Clear new key. 
        	extendstatus.byte = 0;
      	}
	} 
	
	return((BYTE) (extendscan.saf_make + extendscan.saf_break + extendscan.saf_keys));
}

//-----------------------------------------------------------------
// The function of Setting extend scan lines
//-----------------------------------------------------------------
void SetExtendScanLines(BYTE scan_line)
{
	if(scan_line<0x02)
	{
		KSOL = 0xFF;
		KSOH1 = 0xFF;
		KSOH2 = ~(0x01<<scan_line);
		Hook_SetGPIOScanPinH();
	}
	else 
	{
		KSOL = 0xFF;
		KSOH1 = 0xFF;
		KSOH2 = 0xFF;
		Hook_SetGPIOScanPinL();
	}
    CapDelay();
}

//-----------------------------------------------------------------
// The function of Setting extend scan lines
//-----------------------------------------------------------------
void CheckExtendKeys(KSI_bit_num, scan_address)
{
    BYTE flag;
    BYTE change_make_key;
       
	flag = FALSE;				
	if (extendstatus.field.ghost == 1)
 	{
    	flag = TRUE;
   	}
	else
  	{   							// Find 0 -> 1 's.
 		change_make_key = KSI_bit_num & ~bscan_matrix[scan_address];
     	if (change_make_key == 0) 
		{
        	flag = FALSE;
     	}
     	else if (find_paths(change_make_key, scan_address)) 
		{
          	flag = TRUE;    			// TRUE if ghost keys.
      	}
	}

	if (flag)
 	{   								// Ghost exists. 
     	extendstatus.field.ghost = 1;	// Set ghost flag.
      	KSI_bit_num &= bscan_matrix[scan_address] | diode_key;
	}

	ITempB03 = 0x00;
    while (KSI_bit_num != 0)
    {   
        if (KSI_bit_num & 0x01) 	
		{
    		if (bscan_matrix[scan_address] & Byte_Mask(ITempB03))
   		 	{  
        		if (extendscan.saf_break == 0) 
				{
            		extendscan.saf_break = 1;
					ExtendKeyDebounce(ITempB03, scan_address, BREAK_EVENT);
        		}
    		}
    		else
    		{
        		if (extendscan.saf_make == 0) 
				{
            		extendscan.saf_make = 1;
					ExtendKeyDebounce(ITempB03, scan_address, MAKE_EVENT);
        		}
    		} 
        }
        ITempB03++;
        KSI_bit_num = KSI_bit_num >> 1; /* Shift bit out (and a zero bit in) to check next bit. */
    }
}

//-----------------------------------------------------------------
// The function of extend keys debounce
//-----------------------------------------------------------------
void ExtendKeyDebounce(BYTE KSI_bit_num, BYTE scan_address, BYTE event)
{
    new_extendkey.field.output = scan_address-STANDARD_SCAN_LINES;
    new_extendkey.field.input = KSI_bit_num;
    new_extendkey.field.debounce_status = 1;
    extendstatus.field.state = 0;  // Debounce has not counted out. */
    extendstatus.field.same = 0;   // Key activity indication. */

    if (event == MAKE_EVENT)
    { 
        extendstatus.field.trans = 0;
        extendstatus.field.count = 1;//Ext_Cb2.field.Break_Count; 
    }
    else
    {  
        extendstatus.field.trans = 1;
        extendstatus.field.count = 1;//Ext_Cb2.field.Make_Count; 
    }
}


void DebounceExtendkey(void)
{
	SetExtendScanLines(new_extendkey.field.output);
	ITempB04 = Read_Scan_Lines();
	ITempB04 = ~ITempB04;
 	ITempB05 = Byte_Mask((BYTE)(new_extendkey.field.input)); 
	ITempB05 = ITempB05 & ITempB04;

	if (ITempB05 != 0)
    {  
        if (extendstatus.field.trans == 0) 	// key make
		{
            extendstatus.field.same = 1;   	// last key detected as a MAKE, same = 1.
        }
        else 
		{
            extendstatus.field.same = 0;    // last key detected as a BREAK, same = 0.
        }
    }
    else
    { 
        if (extendstatus.field.trans == 0) 
		{
            extendstatus.field.same = 0;    // last key detected as a MAKE, same = 0. 
        }
        else 
		{
            extendstatus.field.same = 1;    // last key detected as a BREAK, same = 1. 
        }
    } 

    if (extendstatus.field.state == 0)	// 1 means debounce counted out.
    {  
        if (extendstatus.field.count != 0)
        {  
            extendstatus.field.count--;
        }
        else
        {
            if (extendstatus.field.same == 0)
            {   
                new_extendkey.byte = 0;	// Debounce failed, so claer all data
                extendstatus.byte = 0;
            }
            else
            {  
                extendstatus.field.state = 1;
            } 
        } 
    }
    else
    { 
        if (extendstatus.field.same == 0)
        {   
            new_extendkey.byte = 0;	/* Debounce failed. */
            extendstatus.byte = 0;
        }
        else
        {   
          	CheckExtendKeyValid();
        } 
    }
}


//-----------------------------------------------------------------
// The function of checking extend key valid
//-----------------------------------------------------------------
void CheckExtendKeyValid(void)
{
    ITempB02 = Byte_Mask((BYTE) (new_extendkey.field.input)); 
    ITempB01 = bscan_matrix[(new_extendkey.field.output + STANDARD_SCAN_LINES)];
    ITempB01 = ITempB01 ^ ITempB02;                        
    bscan_matrix[(new_extendkey.field.output + STANDARD_SCAN_LINES)] = ITempB01; 

	ITempB03 = BREAK_EVENT;                       
    if ((ITempB02 & ITempB01) != 0)
    {   						
        ITempB03 = MAKE_EVENT;  							
        etkeytypematic.byte = new_extendkey.byte;
        extendscan.TMscale = TM_SCALE;
        bTMcount = bTMdelay;
		
		typematic.byte = 0x00;
    }
	
    Send_EtScan2(new_extendkey, ITempB03);
    new_extendkey.byte = 0;
    extendstatus.byte = 0;
}

//-----------------------------------------------------------------
// The function of
//-----------------------------------------------------------------
void Send_EtScan2(union KEY key, BYTE event)
{	
	if(IS_MASK_SET(UtilityFlag,KBDebug))
	{
		if(KeyScanACK==KU_ACK_Start)
		{
			if(event==MAKE_EVENT)
			{
				KeyScanKSI = key.field.input;
				KeyScanKSO = key.field.output;
				KeyScanACK = KU_ACK_FullKeyboard;
			}
		}
	}
	else
	{
    	ITempB02 = (key.field.input * 3) + key.field.output; 
		ITempB01 = *(Extendkey_Table_Pntr + ITempB02);

		Et_Hook_keyboard(key.field.input, key.field.output);
    	Send_Key(ITempB01, event);
	}
}

//-----------------------------------------------------------------
// The function of clearing extend keys
//-----------------------------------------------------------------
void ClearExtendKeys(void)
{
	new_extendkey.byte = 0;		
	extendstatus.byte = 0;
	etkeytypematic.byte = 0;
}

//-----------------------------------------------------------------
// The function of checking extend keys Typematic
//-----------------------------------------------------------------
void CheckEtKeystm(union KEY key)
{
	ITempB02 = FALSE;
    ITempB01 = Byte_Mask((BYTE) (key.field.input)); 
    ITempB01 = ITempB01 & bscan_matrix[key.field.output+STANDARD_SCAN_LINES];

    if (ITempB01 == 0) 
    {
        etkeytypematic.byte = 0;
        ITempB02 = TRUE;
    }

    if (!ITempB02)
    {
        extendscan.TMscale--;
        if (extendscan.TMscale != 0) 
		{
            ITempB02 = TRUE;
        }
    }

    if (!ITempB02)
    {
        extendscan.TMscale = TM_SCALE;
        bTMcount--;            
        if (bTMcount != 0) 
		{
            ITempB02 = TRUE;
        }
    }

    if (!ITempB02)
    {
        bTMcount = bTMrepeat;   
        Send_EtScan2(key,REPEAT_EVENT);  
    }
}

//*******************************************************
//*******************************************************
//*******************************************************
#else   // Hardware scan keyboard
//*******************************************************
//*******************************************************
//*******************************************************

/* ----------------------------------------------------------------------------
 * FUNCTION:   Get_Buffer
 *
 * Get data byte from keyboard buffer (if not empty) and update "scan.kbf_head"
 * with new index into keyboard buffer.
 *
 * Return: Data from buffer (WORD of all 1's if buffer is empty).
 * ------------------------------------------------------------------------- */
BYTE Get_Buffer(void)
{
    BYTE buffer_data;

    if (scan.kbf_head != scan.kbf_tail)
    {
		buffer_data = bKEY_BUFF[scan.kbf_head++];
        if (scan.kbf_head >= KBF_SIZE) 
		{
            scan.kbf_head = 0;
        }
    }
    else
    {   /* Buffer is empty. */
        buffer_data = 0xFF;
    }
    return (buffer_data);
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_Mark - Mark local keyboard buffer tail.
 * ------------------------------------------------------------------------- */
void Buffer_Mark(void)
{
    scan.kbf_mark = scan.kbf_tail;   /* Copy scan.kbf_tail to scan.kbf_mark. */
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_Key
 *
 * Input:  Row/Column (0iii,oooo) to put in buffer.
 * Return: TRUE operation successful, FALSE unsuccessful.
 * ------------------------------------------------------------------------- */
FLAG Buffer_Key(BYTE row_column)
{
    FLAG ready = TRUE;  /* Ready for successful operation */

    bKEY_BUFF[scan.kbf_tail] = row_column;  /* Store Data to Buffer Tail */
    scan.kbf_tail++;                        /* Increment Buffer Tail (pointer) */

    if (scan.kbf_tail >= KBF_SIZE) 
	{
        scan.kbf_tail = 0;  /* Wrap pointer if too large. */
    }

    /* Check Overflow */
    if (scan.kbf_tail == scan.kbf_head)
    {   /* Overflow */
        scan.kbf_tail = scan.kbf_mark;  /* Restore buffer marker. */
        bKEY_BUFF[scan.kbf_tail] = 0;   /* Set OverFlow Mark. */
        ready = FALSE;                  /* Overflow Indication !!! */
    }

    return (ready);
}

/* ----------------------------------------------------------------------------
 * FUNCTION:   Buffer_String
 *
 * Places a string in the local keyboard buffer (without a terminating NULL).
 * Call Buffer_Key to place data in key buffer.
 *
 * Input:  Pointer to null terminated string.
 * Return: 0x80 if buffer overflow error, else 0.
 * ------------------------------------------------------------------------- */
BYTE Buffer_String(const BYTE *pntr)
{
    register BYTE error = 0;

    while ((*pntr != 0) && (error == 0))
    {
        if (Buffer_Key(*pntr++) == 0) {
            error = 0x80;   /* Indicate Overflow */
        }
    }

    return (error);
}

/* ----------------------------------------------------------------
 * FUNCTION: Get_Kbd_Type
 *
 * Returns the type of the internal keyboard.
 *
 * Returns: 0 = U.S. keyboard, 1 = Japanese keyboard.
 * -------------------------------------------------------------- */
FLAG Get_Kbd_Type(void)
{						// Check keyboard type here
						// Returns: 0 = U.S. keyboard, 1 = Japanese keyboard.
	if(1)				// check type here
	{
		return(0);  	// U.S. keyboard. 
	}
	else
	{
		return(1);		// Japanese keyboard
	}
}

/* ----------------------------------------------------------------------------
 * FUNCTION: find_paths
 *
 * Input:  DOWN_STATE  scan_address
 *         change_make_key
 *
 * Return: FALSE if no paths found, Otherwise returns TRUE.
 * ------------------------------------------------------------------------- */
static FLAG find_paths(BYTE change_make_key, BYTE scan_address)
{
    FLAG paths_found, done;
    BYTE paths, temp, bits;
    BYTE first_address;

    /* For the shift and bit test to work, "bits" MUST be unsigned.  (Right
       shifting an unsigned quantity fills vacated bits with zeros.  Right
       shifting a signed quantity will fill vacated bits with sign bits on some
       machines and zero bits on others.) */
    done = FALSE;
    paths_found = FALSE;
    first_address = scan_address;

    //change_make_key &= ~(diode_key); /* Ignore diode key. */
    /* change_make_key = bKO_BITS. */

    if (change_make_key == 0) 
	{
        done = TRUE; /* paths_found == FALSE */
    }

    if (!done)
    {
        paths = bscan_matrix[scan_address] | change_make_key;
        //paths &= ~(diode_key);  /* Ignore diode key. */
        /* paths = bKO_PATHS. */
        if (paths == 0) 
		{
            done = TRUE;  /* paths_found == FALSE */
        }
    }

    while (!done)
    {
        scan_address++;

        if (scan_address >= 18) 	
        //if(scan_address >= STANDARD_SCAN_LINES)
		{
            scan_address = 0;   /* Wrap around */
        }

        if (scan_address == first_address) 
		{
            done = TRUE;        /* No scan lines left.  paths_found == FALSE */
        }

        if (!done)
        {   /* Check Path */
            temp  = bscan_matrix[scan_address]; /* Any paths? */
            //temp &= ~(diode_key);               /* Ignore diode key */

            if (temp != 0) 
			{    /* Paths found */
                temp &= paths;  /* Do paths line up? */
            }

            if (temp != 0)
            {   /* Paths line up */
                if (change_make_key != temp)  /* Only 1 bit set? */
                {   /* No, ghost exists. */
                    paths_found = TRUE;
                    done = TRUE;
                }

                if (!done)
                {   /* The following checks if more than one bit is set to 1.
                       Because "bits" is unsigned, each shift moves the bit
                       under test out and a 0 bit in.  When the first 1 bit is
                       found, if "bits" == 0, this indicates that there is only
                       one bit set. */
                    bits = paths;  /* Only 1 bit set? */
                    temp = FALSE;

                    do
                    {
                        if (bits & 0x01) 
						{
                            temp = TRUE;
                        }

                        /* Shift bit out (and a zero bit in) to check next bit. */
                        bits = bits >> 1;
                    } while (temp == FALSE);

                    if (bits != 0)
                    {   /* No, more than 1 bit set. */
                        paths_found = TRUE;
                        done = TRUE;
                    }
                } /* if (!done) */
            } /* if (temp != 0) */
        } /* if (!done) */
    } /* while (!done) */

   return (paths_found);
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Handle_Scan - Service the local keyboard in response to a key press.
 * ------------------------------------------------------------------------- */
void service_scan(void)
{
    BYTE kso_index, ksi_index;
    BYTE ksitemp;
    BYTE extend_key;
    ECReg *SDRPointer;

    //-----------------------------------------------------
    // All key is pressed
    //
    if (Timer_A.fbit.TMR_SCAN == 0)
    {
        Timer_A.fbit.TMR_SCAN = 1;	// Activate scan timer.
    }

    //-----------------------------------------------------
    // Pre-clear variables
    //
    scan.saf_keys = 0;
    ksitemp = 0x00;
    SDRPointer = &KSO0LSDR;

    //-----------------------------------------------------
    // Scan KSO0 ~ 15, 16, or 17
    //
    for(kso_index=0x00; kso_index<(16+ExtendScanPin); kso_index++)
    {
        ksitemp = ~(SDRPointer[kso_index]);                     // Read KSI and inverse
        ksitemp = ksitemp ^ bscan_matrix[kso_index];
        
        if(ksitemp!=0x00)                                       // Status change (make-->brak, or break-->make)
        {
            if(kso_index>15)                                    // KSO16, KSO17
            {
                KB_HW_ExtendKeyIndex=0x01;
            }
            else                                                // KSO0 ~ KSO15
            {
                KB_HW_ExtendKeyIndex=0x00;
            }

            //-----------------------------------------------------
            // Check KSI0 ~ 7
            //
            for(ksi_index=0x00; ksi_index<8; ksi_index++)
            {
                if(IS_MASK_SET(ksitemp, BIT(ksi_index)))
                {
                    if(KB_HW_ExtendKeyIndex==0x01)              // KSO16, KSO17
                    {
                        new_keyh.field.output = (kso_index-16); // Save KSO for type union KEY
                    }
                    else                                        // KSO0 ~ KSO15
                    {
                        new_keyh.field.output = kso_index;      // Save KSO for type union KEY
                    }
                    new_keyh.field.input = ksi_index;           // Save KSI for type union KEY
 
                    if(IS_MASK_CLEAR(bscan_matrix[kso_index], BIT(ksi_index)))  // Make
                    {
                        if(find_paths(ksitemp, kso_index)==FALSE)   // No ghost key 
                        {
                            Send_Scan2(new_keyh, MAKE_EVENT);   // Key make         
                            typematic.byte = new_keyh.byte;     // Set typematic key
                            scan.TMscale = TM_SCALE;            // Repeat time
                            bTMcount = bTMdelay;                // Delay time

                            if(KB_HW_ExtendKeyIndex==0x01)      // KSO16, KSO17
                            {
                                KB_HW_ExtendKeyTypematic=0x01;  // Set key typematic of KSO16, KSO17 
                            }
                            else
                            {
                                KB_HW_ExtendKeyTypematic=0x00;  // Set key typematic of KSO0 ~ KSO15
                            }
                            SET_MASK(bscan_matrix[kso_index], BIT(ksi_index));
                        }
                        else                                    // ghost key found
                        {
                            typematic.byte = 0;	                // Clear Typematic. 
                        }
                    }
                    else                                        // Break
                    {
                        Send_Scan2(new_keyh, BREAK_EVENT);      // Key break;
                        CLEAR_MASK(bscan_matrix[kso_index], BIT(ksi_index));
                    }
                }
            }
        }
        
        //-----------------------------------------------------
        // Any key still active.
        //
        if(bscan_matrix[kso_index]) 
        {  					    // Here, if current still active. 
            scan.saf_keys = 1;  // Set keys active bits. Check all key release. 
        }  
    }

    //-----------------------------------------------------
    // All key break
    //
    if((scan.saf_keys)==0x00)       // all key break
    {
        Clear_AllKeysBreak();
    }

    //-----------------------------------------------------
    // Start sending keyboard data
    //
	if (scan.kbf_head != scan.kbf_tail)
	{
        F_Service_SEND = 1;         // Post service request
        SetServiceSendFlag();
	}

    //-----------------------------------------------------
    // Write to clear data valid bit and enabling interrupt 
    //
    SET_MASK(SDSR, SDV);            // Scan data valid W/C
    SET_MASK(IER10, BIT4);          // Enable interrupt 
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Init_Kbd - Scanner Keyboard Initialization.
 * ------------------------------------------------------------------------- */
void Unlock_Scan(void) 
{
	Int_Var.Scan_Lock = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Lock_Scan
 *
 * Lock out the scanner via "Scan_Lock" and clear pending scanner "SEND"
 * events.
 * ------------------------------------------------------------------------- */
void Lock_Scan(void)
{
    Int_Var.Scan_Lock = 1;
    //Timer_B.fbit.SEND_ENABLE = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Set_Typematic - Set the typematic rate.
 *
 * Input: typematic rate
 *        Bit[4:0] Typematic repeat interval
 *        Bit[6:5] Delay time
 * ------------------------------------------------------------------------- */
const BYTE code repeat_tbl[] =
{
     3,  4,  4,  5,  5,  5,  6,  6,  7,  7,  8, 9, 10, 11, 11, 12,
    13, 15, 16, 18, 20, 21, 23, 25, 27, 30, 33, 37, 40, 43, 47, 50
};
const BYTE code delay_tbl[] = {25, 50, 75, 100};

void Set_Typematic(WORD type_rate)
{
    Save_Typematic = type_rate;   /* Save for suspend/resume. */

    /* Bit 4 - 0 typematic repeat interval index. */
    bTMrepeat = repeat_tbl[type_rate & 0x1F];

    /* Bit 6 - 5 delay time index. */
    bTMdelay = delay_tbl[(type_rate >> 5) & 0x03];
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Clear_Key - Clear local keyboard buffer and related variables.
 * ------------------------------------------------------------------------- */
void Clear_Key(void)
{
    BYTE i;

    for(i = 0; i < MAX_SCAN_LINES; i++)	// Clear scan matrix.
	{
        bscan_matrix[i] = 0;
    }

    for(i = 0; i < KBF_SIZE; i++)   // Clear key buffer.
	{
        bKEY_BUFF[i] = 0;
    }

    scan.kbf_head = 0;              // Clear keyboard buffer head
    scan.kbf_tail = 0;              // Clear keyboard buffer tail
    scan.saf_keys = 0;              // Clear Scan activity flag - keys active.
    new_keyh.byte = 0;              // Clear KSO KSI

    Clear_AllKeysBreak();
    
    #if KB_FnStickKey
    FnStickKey = 0;
    #endif
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Clear_Typematic - Set default typematic delay and clear type-matic action.
 * ------------------------------------------------------------------------- */
void Clear_Typematic(void)
{
    typematic.byte = 0;
    bTMdelay = TM_DELAY;
    bTMrepeat = TM_REPEAT;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: Init_Kbd - Scanner Keyboard Initialization.
 * ------------------------------------------------------------------------- */
void Init_Kbd(void)
{
	CheckKSO1617Support();      // Check KSO16 and KSO17
	Hook_Setup_Scanner_Pntr();  // to define the possible scanner tables
    Clear_Key();                // Clear key matrix/buffer
    Clear_Typematic();          // Clear Typematic 
	Enable_Any_Key_Irq();       // Enable any key interrupt (HW mode)
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void CheckKSO1617Support(void)
{
	ExtendScanPin = 0x00;

	if((KSO16CtrlReg&0xFB)==0x00)
	{
		ExtendScanPin++;
	}

	if((KSO17CtrlReg&0xFB)==0x00)
	{
		ExtendScanPin++;
	}

    if(ExtendScanPin>2)
    {
        ExtendScanPin=2;
    }

    Scan_Init();                // Initialize internal keyboard (HW scanner)
}

/* ----------------------------------------------------------------
 * FUNCTION: Scan_Init - Initialize internal keyboard (scanner)
 * ---------------------------------------------------------------- */
void Scan_Init(void)
{
    SDC1R = SDEN+INTSDVEN+SLS_03_Round;     // Scan data enable, interrupt from scan data valid enable, 3 round

    if(ExtendScanPin==0x02)                 // 18 x 8
    {
        SDC2R = KSOPCS1+WKSOHDLY_55us;      // 18 x 8, Wait KSO high delay 55us
    }
    else if(ExtendScanPin==0x01)            // 17 x 8
    {
        SDC2R = KSOPCS0+WKSOHDLY_55us;      // 17 x 8, Wait KSO high delay 55us
    }
    else                                    // 16 x 8
    {
        SDC2R = WKSOHDLY_55us;              // 16 x 8, Wait KSO high delay 55us
    }
    
    SDC3R = WKSOLDLY_29us+SDLYBR_00ms;      // Wait KSO low delay 29us, spacing delay between rounds 0ms.
}

/* ----------------------------------------------------------------
 * FUNCTION: Enable_Any_Key_Irq
 *
 * Setup for any key from scanner to generate an interrupt.
 *
 * Lower the "strobe" lines so that when any key is pressed at least one input
 * line will go low.  Any bits (out of the possible 16) that are not used for
 * the internal keyboard (scanner) are left alone.  This is done using
 * Config.Msk_Strobe_H and Config.Msk_Strobe_L.
 *
 * Then, if the internal keyboard (scanner) is enabled, allow the interrupt to
 * occur when a key is pressed on the scanner.
 * -------------------------------------------------------------- */
void Enable_Any_Key_Irq(void)
{
	ISR10 = BIT4;
    SET_MASK(IER10, BIT4);  
}

/* ----------------------------------------------------------------------------
 * FUNCTION: check_tm - Handle typematic function.
 *
 * Input: Typematic key
 * ------------------------------------------------------------------------- */
void check_tm(union KEY key)
{
    BYTE sendit;
    BYTE check;
    
 	sendit = FALSE;										
    check = Byte_Mask((BYTE) (key.field.input)); 
    if(KB_HW_ExtendKeyTypematic==0x00)
    {
        check = check & bscan_matrix[key.field.output];
    }
    else
    {
        check = check & bscan_matrix[(key.field.output + 16)];
    }

    if (check == 0)	            // Release Typematic key? 
    {   
        typematic.byte = 0;	    // Clear Typematic. 
        sendit = TRUE;
    }

    if (!sendit)
    {  
        scan.TMscale--;		    // Count down Prescale.
        if (scan.TMscale != 0) 
		{
            sendit = TRUE;
        }
    }

    if (!sendit)
    {
        scan.TMscale = TM_SCALE;// Reload prescale counter. 
        bTMcount--;             // Count down TMcount. 
        if (bTMcount != 0) 
		{
            sendit = TRUE;
        }
    }

    if (!sendit)
    {
        if(KB_HW_ExtendKeyTypematic==0x00)
        {
            KB_HW_ExtendKeyIndex=0x00;
        }
        else
        {
            KB_HW_ExtendKeyIndex=0x01;
        }
        bTMcount = bTMrepeat;   // Reload TMcount. 
        Send_Scan2(key, REPEAT_EVENT);   
    }
}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
void HW_KB_Check_TM(void)
{
    BYTE kso_index;
 	if(typematic.byte) 
	{
     	check_tm(typematic);  	    // Check typematic. 
 	}

    if(IS_MASK_SET(SDSR, BIT1))     // All FFh
    {
        for(kso_index=0x00; kso_index<(16+ExtendScanPin); kso_index++)
        {
            if(bscan_matrix[kso_index]!=0x00)
            {
                F_Service_KEY = 1;  // Request scanner service. 
                break;
            }
        }
    }
}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
void Clear_AllKeysBreak(void)
{
    Timer_A.fbit.TMR_SCAN = 0;  // Disable the scan timer. 
    typematic.byte = 0;         // Clear typematic
    FN_Key_Break = 0x00;        // Clear FN_Key_Break
    FN_Key_Break_HS = 0x00;

    ClearFnKeyBundledFalg();
    KB_HW_ExtendKeyIndex = 0x00;
    KB_HW_ExtendKeyTypematic = 0x00;
}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
void FindGhostKey(void)
{



}

//*******************************************************
#endif  // #ifndef KB_HW_KeyScan  
//*******************************************************
