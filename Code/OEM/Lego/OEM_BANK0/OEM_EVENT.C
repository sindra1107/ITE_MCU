/*-----------------------------------------------------------------------------
 * TITLE: OEM_EVENT.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// no change function

//-----------------------------------------------------------------------------
void NullEvent(void)
{

}

//-----------------------------------------------------------------------------
//power button was pressed
//-----------------------------------------------------------------------------
void PSWPressed(void)
{
    PSW_COUNTER = T_PSWOFF;		        // initialize counter
     
    switch (SysPowState)    
    {   
        case SYSTEM_S5 :
			//PSW_COUNTER = T_PSWOFF;		    // initialize counter
			Oem_TriggerS5S0();
            break;
            
        case SYSTEM_S3 :
		case SYSTEM_S0 :
            DNBSWON_ON();
	        //PSW_COUNTER = T_PSWOFF;			// initialize counter
	        //PulseSBPowerButton();
			break;
			
        default :
            break;
    }
}

//-----------------------------------------------------------------------------
//power button was released
//-----------------------------------------------------------------------------
void PSWReleased(void)
{
    PSW_COUNTER = 0;				        // reset counter
	DNBSWON_OFF();
}

//-----------------------------------------------------------------------------
//power button was overrided
//-----------------------------------------------------------------------------
void PSWOverrided(void)
{
	if(IS_MASK_SET(POWER_FLAG1,wait_PSW_off))	// power button was pressed	
	{	
		if(PSW_COUNTER != 0 )	
		{									 
			PSW_COUNTER -= 1;		        // PSW_COUNTER count down
			if(PSW_COUNTER == 0)		    // time out
			{								
				Oem_TriggerS0S5(SC_4SEC);
			} 								   
		} 									   
	} 	
}



// ----------------------------------------------------------------------------
// Device insert/remove debounce routine.
// input:   device_id
// ----------------------------------------------------------------------------
const struct sDebounce code Debounce_TBL[] = 
{
  	{&POWER_FLAG1	,wait_PSW_off	,&DEBOUNCE_CONT1	,T_PSW_DEBOUNCE	    ,PSWPressed	    ,PSWReleased	,PSWOverrided	    },
    {&EVT_STATUS1	,DummyFlag 	    ,&DEBOUNCE_CONT2 	,T_EXTEVT_DEBOUNCE	,NullEvent	    ,NullEvent		,NullEvent	        },      
	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT3 	,T_EXTEVT_DEBOUNCE	,NullEvent	    ,NullEvent	    ,NullEvent		    }, 
	{&EVT_STATUS1	,DummyFlag 		,&DEBOUNCE_CONT4 	,T_EXTEVT_DEBOUNCE  ,NullEvent	    ,NullEvent	    ,NullEvent		    }, 
	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT5 	,T_EXTEVT_DEBOUNCE	,NullEvent	    ,NullEvent      ,NullEvent		    }, 
	{&EVT_STATUS1	,DummyFlag	    ,&DEBOUNCE_CONT6 	,T_EXTEVT_DEBOUNCE	,NullEvent	    ,NullEvent		,NullEvent		    }, 
	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT7 	,T_EXTEVT_DEBOUNCE	,NullEvent	    ,NullEvent	    ,NullEvent			}, 
	{&EVT_STATUS1	,DummyFlag 		,&DEBOUNCE_CONT8 	,T_EXTEVT_DEBOUNCE  ,NullEvent	    ,NullEvent		,NullEvent			}, 
	{&EVT_STATUS1	,DummyFlag	    ,&DEBOUNCE_CONT9 	,T_EXTEVT_DEBOUNCE  ,NullEvent	    ,NullEvent		,NullEvent		    }, 
	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT10 	,T_EXTEVT_DEBOUNCE	,NullEvent	    ,NullEvent		,NullEvent		    }, 
};

// ----------------------------------------------------------------------------
// EventManager function
//
// Note : 
//	If want to call the function of status not change, please set nochange_func = 1
// ----------------------------------------------------------------------------
#pragma OT(8, SPEED)
void EventManager(BYTE device_id) 
{
	BYTE new_state,old_state;
	BYTE device_flag;
	//BYTE do_nochange_func = 0x00;
	switch(device_id)	
	{
		case 0 :     							
			new_state = Read_NBSW();
			break;
			
		case 1 :     							
			new_state = 0x00;
			break;

		case 2 :
			new_state = 0x00;
			break;

		case 3 :
			new_state = 0x00;
			break;
			
		case 4 :
			new_state = 0x00;
			break;
			
		case 5 :
			new_state = 0x00;
			break;
			
		case 6 :
			new_state = 0x00;
			break;
				
		case 7:	
            new_state = 0x00;
			break;

		case 8:	 
			new_state = 0x00;
			break;	

		case 9:	
            new_state = 0x00;
			break;
	
		default :
			new_state = 0x00;
			break;
	}

	Tmp_XPntr = Debounce_TBL[device_id].REG;
	Tmp_XPntr1 = Debounce_TBL[device_id].Cunter;
	device_flag = Debounce_TBL[device_id].Flag;

	old_state = ((*Tmp_XPntr & device_flag) != 0x00);
	if(new_state != old_state)	
	{		 
		if((*Tmp_XPntr1) == 0x00)	
		{	
			(*Tmp_XPntr1) = Debounce_TBL[device_id].Time;	
		}	 
		else 
		{	
			(*Tmp_XPntr1) --;	
			if((*Tmp_XPntr1) == 0)	
			{	 
				if(new_state)	
				{	
					(Debounce_TBL[device_id].press)();
					*Tmp_XPntr |= device_flag;
				}
				else 
				{	
					(Debounce_TBL[device_id].release)();
					*Tmp_XPntr  &= (~device_flag);
				}
			}  
		}  
	}
	else
	{ 	
		*Tmp_XPntr1 = 0x00;	
	}
	
	(Debounce_TBL[device_id].nochange)();
}




