/*-----------------------------------------------------------------------------
 * TITLE: OEM_GPIO.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/
 
#ifndef OEM_GPIO_H
#define OEM_GPIO_H

//-----------------------------------------------------------------
// 
//-----------------------------------------------------------------
#define HighActive  	1
#define LowActive     	0

//-----------------------------------------------------------------
// GPIO Registers define
//-----------------------------------------------------------------
/*  General Control Register (GCR)  */
// BIT 7     -  GPIOB5 HIGH Follow LPCRST# HIGH-to-LOW
// BIT 6     -  WUI7 Enabled
// BIT 5     -  WUI6 Enabled
// BIT [2:1] -  [01] LPCRST# in GPIOB7
//              [10] LPCRST# in GPIOD2
//              [11] LPCRST# is dsiabled 
#define GCR_Init		0x06            // 
#define GCR2_Init		0x00			//

//-----------------------------------------------------------------
// GPIO Port A Registers define
//-----------------------------------------------------------------
#define PortA_Init		0x43            // PORT Data

#define PortA0_Ctrl		OUTPUT		    //    
#define PortA1_Ctrl		OUTPUT			// 
#define PortA2_Ctrl		OUTPUT			//         
#define PortA3_Ctrl		ALT			    //
#define PortA4_Ctrl		OUTPUT      	// 
#define PortA5_Ctrl		INPUT       	//       
#define PortA6_Ctrl		OUTPUT      	//
#define PortA7_Ctrl		INPUT       	// 

//-----------------------------------------------------------------
// GPIO Port B Registers define
//-----------------------------------------------------------------
#define PortB_Init		0x04            // PORT Data

#define PortB0_Ctrl		INPUT			// 
#define PortB1_Ctrl		INPUT			// 
#define PortB2_Ctrl		OUTPUT			//          
#define PortB3_Ctrl		ALT				// 
#define PortB4_Ctrl		ALT				// 
#define PortB5_Ctrl		OUTPUT			// 
#define PortB6_Ctrl		OUTPUT			// 
#define PortB7_Ctrl		OUTPUT			// 

//-----------------------------------------------------------------
// GPIO Port C Registers define
//-----------------------------------------------------------------
#define PortC_Init		0x80            // PORT Data

#define PortC0_Ctrl		OUTPUT			// 
#define PortC1_Ctrl		ALT+PULL_UP		// 
#define PortC2_Ctrl		ALT+PULL_UP		// 
#define PortC3_Ctrl		OUTPUT          // 
#define PortC4_Ctrl		INPUT	        //
#define PortC5_Ctrl		INPUT		    // 
#define PortC6_Ctrl		INPUT			// 
#define PortC7_Ctrl		OUTPUT			//

//-----------------------------------------------------------------
// GPIO Port D Registers define
//-----------------------------------------------------------------
#define PortD_Init		0x18            // PORT Data

#define PortD0_Ctrl		INPUT			// 
#define PortD1_Ctrl		INPUT			// 
#define PortD2_Ctrl		INPUT			// 
#define PortD3_Ctrl		OUTPUT			//
#define PortD4_Ctrl		OUTPUT			// 
#define PortD5_Ctrl		INPUT			// 
#define PortD6_Ctrl		ALT 			//
#define PortD7_Ctrl		INPUT+PULL_DW	//

//-----------------------------------------------------------------
// GPIO Port E Registers define
//-----------------------------------------------------------------
#define PortE_Init		0x00            // PORT Data

#define PortE0_Ctrl		OUTPUT			// 
#define PortE1_Ctrl		INPUT			// 
#define PortE2_Ctrl		OUTPUT			// 
#define PortE3_Ctrl		INPUT			// 
#define PortE4_Ctrl		INPUT+PULL_UP	// 
#define PortE5_Ctrl		INPUT			// 
#define PortE6_Ctrl		INPUT			// 
#define PortE7_Ctrl		INPUT			//

//-----------------------------------------------------------------
// GPIO Port F Registers define
//-----------------------------------------------------------------
#define PortF_Init		0x00            // PORT Data

#define PortF0_Ctrl		INPUT		    // 
#define PortF1_Ctrl		INPUT		    //
#define PortF2_Ctrl		INPUT			//
#define PortF3_Ctrl		INPUT			// 
#define PortF4_Ctrl		ALT             // 
#define PortF5_Ctrl		ALT 			//
#define PortF6_Ctrl		INPUT	        //
#define PortF7_Ctrl		INPUT	        //

//-----------------------------------------------------------------
// GPIO Port G Registers define
//-----------------------------------------------------------------
#define PortG_Init		0x01            // PORT Data

#define PortG0_Ctrl		OUTPUT			//
#define PortG1_Ctrl		OUTPUT       	//
#define PortG2_Ctrl		INPUT           //
#define PortG3_Ctrl		INPUT           //
#define PortG4_Ctrl		INPUT           //
#define PortG5_Ctrl		INPUT           //
#define PortG6_Ctrl		OUTPUT			//
#define PortG7_Ctrl		INPUT           //

//-----------------------------------------------------------------
// GPIO Port H Registers define
//-----------------------------------------------------------------
#define PortH_Init		0x00            // PORT Data

#define PortH0_Ctrl		ALT				// CLKRUN#
#define PortH1_Ctrl		OUTPUT			//
#define PortH2_Ctrl		OUTPUT			//
#define PortH3_Ctrl		INPUT		    //
#define PortH4_Ctrl		INPUT		    //
#define PortH5_Ctrl		INPUT		    //
#define PortH6_Ctrl		INPUT		    //

//-----------------------------------------------------------------
// GPIO Port I Registers define
//-----------------------------------------------------------------
#define PortI_Init		0x00            // PORT Data

#define PortI0_Ctrl		ALT             //
#define PortI1_Ctrl		INPUT			//
#define PortI2_Ctrl		ALT			    //
#define PortI3_Ctrl		INPUT	        //
#define PortI4_Ctrl		ALT		        //
#define PortI5_Ctrl		ALT		        //
#define PortI6_Ctrl		ALT		        //
#define PortI7_Ctrl		ALT       	    //

//-----------------------------------------------------------------
// GPIO Port J Registers define
//-----------------------------------------------------------------
#define PortJ_Init		0x1E            // PORT Data

#define PortJ0_Ctrl		OUTPUT			//
#define PortJ1_Ctrl		OUTPUT			//
#define PortJ2_Ctrl		OUTPUT			//
#define PortJ3_Ctrl		OUTPUT			//
#define PortJ4_Ctrl		OUTPUT			//          
#define PortJ5_Ctrl		OUTPUT			//


//------------------------------------------------------------------------------
// S.B.
//------------------------------------------------------------------------------
#define SCI_ON()		CLEAR_MASK(GPDRD,BIT(3))
#define SCI_OFF()		SET_MASK(GPDRD,BIT(3))

#define SMI_ON()		CLEAR_MASK(GPDRD,BIT(4))
#define SMI_OFF()		SET_MASK(GPDRD,BIT(4))

#define GATEA20_ON()	SET_MASK(GPDRB,BIT(5))
#define GATEA20_OFF()	CLEAR_MASK(GPDRB,BIT(5))

#define KBRST_ON()		CLEAR_MASK(GPDRB,BIT(6))
#define KBRST_OFF()		SET_MASK(GPDRB,BIT(6))

//------------------------------------------------------------------------------
// Power sequnce
//------------------------------------------------------------------------------
#define DNBSWON_ON()	CLEAR_MASK(GPDRJ,BIT(3))
#define DNBSWON_OFF()	SET_MASK(GPDRJ,BIT(3))

#define RSMRST_ON()		CLEAR_MASK(GPDRB,BIT(2))
#define RSMRST_OFF()	SET_MASK(GPDRB,BIT(2))

#define S5_ON()			SET_MASK(GPDRH,BIT(1))
#define S5_OFF()		CLEAR_MASK(GPDRH,BIT(1))

#define ACPRESENT_ON()	SET_MASK(GPDRG,BIT(6))	
#define ACPRESENT_OFF()	CLEAR_MASK(GPDRG,BIT(6))

#define PCH_PROCHOT_ON()    CLEAR_MASK(GPDRA,BIT(1))
#define PCH_PROCHOT_OFF()   SET_MASK(GPDRA,BIT(1))

#define SUSON_ON()		SET_MASK(GPDRE,BIT(0))
#define SUSON_OFF()		CLEAR_MASK(GPDRE,BIT(0))

#define MAINON_ON()		SET_MASK(GPDRH,BIT(2))
#define MAINON_OFF()	CLEAR_MASK(GPDRH,BIT(2))

#define VRON_ON()		SET_MASK(GPDRE,BIT(2))
#define VRON_OFF()		CLEAR_MASK(GPDRE,BIT(2))

#define ECPWROK_ON()	SET_MASK(GPDRC,BIT(3))
#define ECPWROK_OFF()	CLEAR_MASK(GPDRC,BIT(3))

#define WLAN_PWR_EN_ON()    SET_MASK(GPDRB,BIT(7))
#define WLAN_PWR_EN_OFF()   CLEAR_MASK(GPDRB,BIT(7))

#define BT_EN_ON()    SET_MASK(GPDRG,BIT(1))
#define BT_EN_OFF()   CLEAR_MASK(GPDRG,BIT(1))

#define USB_On_ON()	    CLEAR_MASK(GPDRG,BIT(0))
#define USB_On_OFF()	SET_MASK(GPDRG,BIT(0))

#define Read_SLPS3()	IS_MASK_SET(GPDRE,BIT(5))
#define Read_SLPS4()	IS_MASK_SET(GPDRC,BIT(4))
#define Read_SLPS5()	IS_MASK_SET(GPDRB,BIT(1))
#define Read_SLPA()	    IS_MASK_SET(GPDRE,BIT(1))
#define Read_SUSACK()   IS_MASK_SET(GPDRA,BIT(5))
#define Read_SLP_SUS()  IS_MASK_SET(GPDRF,BIT(7))

#define Read_LPCRST()	//IS_MASK_SET(GPDRD,BIT(2))   //?
#define Read_HWPG()		IS_MASK_SET(GPDRC,BIT(6))
#define Read_NBSW()		IS_MASK_CLEAR(GPDRE,BIT(4))
#define Read_DTSALERT() IS_MASK_CLEAR(GPDRI,BIT(3))

#define Read_S5_ON()    IS_MASK_SET(GPDRH,BIT(1))

//-----------------------------------------------------------------------------
// Define LED control
//-----------------------------------------------------------------------------
#define NUMLED_ON()		CLEAR_MASK(GPDRA,BIT(6))
#define NUMLED_OFF()	SET_MASK(GPDRA,BIT(6))

#define CAPLED_ON()		CLEAR_MASK(GPDRC,BIT(7))
#define CAPLED_OFF()	SET_MASK(GPDRC,BIT(7))

#define PWRLED1_ON()	CLEAR_MASK(GPDRA,BIT(0))
#define PWRLED1_OFF()	SET_MASK(GPDRA,BIT(0))

#define PWRLED2_ON()
#define PWRLED2_OFF()

#define BATLED1_ON()	SET_MASK(GPDRA,BIT(2))      //OK
#define BATLED1_OFF()	CLEAR_MASK(GPDRA,BIT(2))    //OK

#define BATLED2_ON()	//SET_MASK(GPDRB,BIT(1))      //?
#define BATLED2_OFF()	//CLEAR_MASK(GPDRB,BIT(1))    //?

#define TP_LED_ON()		//CLEAR_MASK(GPDRJ,BIT(2))    //?
#define TP_LED_OFF()	//SET_MASK(GPDRJ,BIT(2))      //?

//-----------------------------------------------------------------------------
// Define IO control
//-----------------------------------------------------------------------------
#define VOLMUTE_ON()	SET_MASK(GPDRA,BIT(4))      //OK
#define VOLMUTE_OFF()	CLEAR_MASK(GPDRA,BIT(4))    //OK

#define EC_ODD_EN_ON()  SET_MASK(GPDRJ,BIT(0))      //OK
#define EC_ODD_EN_OFF() CLEAR_MASK(GPDRJ,BIT(0))    //OK

#define BackLight_ON()	CLEAR_MASK(GPDRJ,BIT(4))    //OK EC_FPBACK 
#define BackLight_OFF()	SET_MASK(GPDRJ,BIT(4))      //OK EC_FPBACK

#define PWM_VADJ		DCR3
#define Charge_CC		;       //DACDAT0	
#define Charge_CV		;       //DACDAT2
#define Fan_volt		DCR2 

//-----------------------------------------------------------------------------
// H.W. input
//-----------------------------------------------------------------------------
#define Read_ACIN()		IS_MASK_SET(GPDRD,BIT(1))   //OK

#define Read_LID()		IS_MASK_CLEAR(GPDRD,BIT(0)) //OK

#define Read_ABat()		    Fix_ADCAvg0
#define Read_SYS_I()	    Fix_ADCAvg1
#define Read_CPU_VCC()      ADCAvg0    
#define Read_CPU_ICC()      ADCAvg1
#define Read_GFX_VR_VCC()   ADCAvg3
#define Read_GFX_VR_ICC()   ADCAvg4

#define Read_WLAN()		//IS_MASK_CLEAR(GPDRJ,BIT(1)) //?
#define Read_WWAN()		//IS_MASK_CLEAR(GPDRJ,BIT(2)) //?

#define Read_Docking()	0
#define Read_MMBInt()	0 

#define DC_ON()			SET_MASK(GPDRC,BIT(0))      //OK
#define DC_OFF()		CLEAR_MASK(GPDRC,BIT(0))    //OK

extern void Init_GPIO(void);
extern void Hook_SCION(void);
extern void Hook_SCIOFF(void);
extern void Hook_SMION(void);
extern void Hook_SMIOFF(void);
extern void Hook_A20ON(void);
extern void Hook_A20OFF(void);
extern void Hook_KBRSTON(void);
extern void Hook_KBRSTOFF(void);
extern void Hook_NUMLED_ON(void);
extern void Hook_NUMLED_OFF(void);
extern void Hook_CAPLED_ON(void);
extern void Hook_CAPLED_OFF(void);

typedef struct InitGPIOReg
{
    XBYTE 	*reg;	
	BYTE	value;
} sInitGPIOReg;

#endif
