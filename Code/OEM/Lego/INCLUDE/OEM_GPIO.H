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


#define KSI_GPIO_Control  0xFF               // GPIO Mode
#define KSI_GPIO_OutputEn 0x00               // KSI Disable Output
#define KSI_Data    0x00

#define KSO_GPIO_Control_7_0  0xFF           // GPIO Mode
#define KSO_GPIO_OutputEn_7_0 0x00           // KSO Disable Output
#define KSO_Data_7_0   0x00

#define KSO_GPIO_Control_15_8  0xFF          // GPIO Mode
#define KSO_GPIO_OutputEn_15_8 0x00          // KSO  Output   // 2014-10-28: Peter Modify for Audio
#define KSO_Data_15_8   0x08                                  // 2014-10-28: Peter Modify for Audio

//-----------------------------------------------------------------
// GPIO Port A Registers define
//-----------------------------------------------------------------
#define PortA_Init		0x00            // PORT Data

#define PortA0_Ctrl		ALT	//OUTPUT	    // ME_FLASH_EN   
#define PortA1_Ctrl		ALT //OUTPUT			// FAN_CTL_DGPU
#define PortA2_Ctrl		INPUT			//         
#define PortA3_Ctrl		INPUT			//
#define PortA4_Ctrl		INPUT      	    // 
#define PortA5_Ctrl		INPUT       	//       
#define PortA6_Ctrl		INPUT      	    //
#define PortA7_Ctrl		INPUT       	// 

#define FANCTL1_ON()		SET_MASK(GPDRA,BIT(0))
#define FANCTL1_OFF()		CLEAR_MASK(GPDRA,BIT(0))
#define Read_FANCTL1()		IS_MASK_CLEAR(GPDRA, BIT(0))
#define FAN_CTL_DGPU_ON()		SET_MASK(GPDRA,BIT(1))
#define FAN_CTL_DGPU_OFF()		CLEAR_MASK(GPDRA,BIT(1))

//-----------------------------------------------------------------
// GPIO Port B Registers define
//-----------------------------------------------------------------
#define PortB_Init		0x00            // PORT Data

#define PortB0_Ctrl		OUTPUT			// EC_SCI#
#define PortB1_Ctrl		OUTPUT			// EC_SMI#
#define PortB2_Ctrl		INPUT			//          
#define PortB3_Ctrl		ALT		    // THM_CLK
#define PortB4_Ctrl		ALT			// THM_DAT
#define PortB5_Ctrl		OUTPUT			// A20GATE
#define PortB6_Ctrl		OUTPUT			// EC_PCH_PWROK 
#define PortB7_Ctrl		INPUT			// 

//-----------------------------------------------------------------
// GPIO Port C Registers define
//-----------------------------------------------------------------
#define PortC_Init		0x00            // PORT Data

#define PortC0_Ctrl		INPUT + PULL_UP			// DGPU_PRSNT#
#define PortC1_Ctrl		INPUT		    // PCH_SMCLK_THM
#define PortC2_Ctrl		INPUT		    // PCH_SMDATA_THM
#define PortC3_Ctrl		INPUT           // 
#define PortC4_Ctrl		INPUT	        //
#define PortC5_Ctrl		INPUT		    // 
#define PortC6_Ctrl		INPUT			// 
#define PortC7_Ctrl		INPUT			//

// 2014-08-28: Peter add for VGA, start
#define Read_DGPU_IN()		IS_MASK_CLEAR(GPDRC, BIT(0))
// 2014-08-28: Peter add for VGA, end

//-----------------------------------------------------------------
// GPIO Port D Registers define
//-----------------------------------------------------------------
#define PortD_Init		0x00            // PORT Data

#define PortD0_Ctrl		OUTPUT			// PWR_B_LED#
#define PortD1_Ctrl		INPUT			// 
#define PortD2_Ctrl		INPUT			// BUF_PLT_RST#
#define PortD3_Ctrl		INPUT			//
#define PortD4_Ctrl		INPUT			// 
#define PortD5_Ctrl		OUTPUT			// RSMRST#
#define PortD6_Ctrl		ALT 			// FAN_TACH1
#define PortD7_Ctrl		INPUT	        //

#define PWR_LED_OFF()		SET_MASK(GPDRD, BIT(0))
#define PWR_LED_ON()		CLEAR_MASK(GPDRD, BIT(0))
#define Read_PWR_LED()		IS_MASK_CLEAR(GPDRD, BIT(0))
#define PWRLED1_ON()	        CLEAR_MASK(GPDRD,BIT(0))
#define PWRLED1_OFF()	        SET_MASK(GPDRD,BIT(0))
#define FAN_ATTACH()		IS_MASK_SET(GPDRD, BIT(6))
//-----------------------------------------------------------------
// GPIO Port E Registers define
//-----------------------------------------------------------------
#define PortE_Init		0x00            // PORT Data

#define PortE0_Ctrl		OUTPUT			// FANCTL1
#define PortE1_Ctrl		INPUT			// 
#define PortE2_Ctrl		INPUT			// 
#define PortE3_Ctrl		INPUT			// 
#define PortE4_Ctrl		INPUT	        // PWR_SWIN#
#define PortE5_Ctrl		INPUT			// 
#define PortE6_Ctrl		INPUT			// 
#define PortE7_Ctrl		OUTPUT			// H_PROCHOT_EC


//-----------------------------------------------------------------
// GPIO Port F Registers define
//-----------------------------------------------------------------
#define PortF_Init		0x08            // PORT Data

#define PortF0_Ctrl		INPUT		    // 
#define PortF1_Ctrl		INPUT		    //
#define PortF2_Ctrl		INPUT			//
#define PortF3_Ctrl		OUTPUT			// WLAN_PWR_ON#
#define PortF4_Ctrl		INPUT           // 
#define PortF5_Ctrl		INPUT 			//
#define PortF6_Ctrl		INPUT	        // H_PECI
#define PortF7_Ctrl		OUTPUT	        // USB_PWREN

//-----------------------------------------------------------------
// GPIO Port G Registers define
//-----------------------------------------------------------------
#define PortG_Init		0x02            // PORT Data

#define PortG0_Ctrl		INPUT			//
#define PortG1_Ctrl		OUTPUT       	// PWR_BTN#
#define PortG2_Ctrl		INPUT           // 3V3DS_PG
#define PortG3_Ctrl		INPUT           //
#define PortG4_Ctrl		INPUT           //
#define PortG5_Ctrl		INPUT           //
#define PortG6_Ctrl		OUTPUT			// DOCK_AC19V_ON
#define PortG7_Ctrl		INPUT           //

// 2014-08-28: Peter add for VGA, start
#define DOCK_AC19V_ON()			SET_MASK(GPDRG, BIT(6))
#define DOCK_AC19V_OFF()		CLEAR_MASK(GPDRG, BIT(6))
// 2014-08-28: Peter add for VGA,end


//-----------------------------------------------------------------
// GPIO Port H Registers define
//-----------------------------------------------------------------
#define PortH_Init		0x00            // PORT Data

#define PortH0_Ctrl		ALT		        // PCI_CLKRUN#
#define PortH1_Ctrl		INPUT			// DGPU_PWROK
#define PortH2_Ctrl		OUTPUT			// EC_PWR_ON
#define PortH3_Ctrl		INPUT		    //
#define PortH4_Ctrl		INPUT		    //
#define PortH5_Ctrl		INPUT		    //
#define PortH6_Ctrl		INPUT		    //

#define IS_DGPU_PWR_OK()		IS_MASK_SET(GPDRH, BIT(1))
//-----------------------------------------------------------------
// GPIO Port I Registers define
//-----------------------------------------------------------------
#define PortI_Init		0x00            // PORT Data

#define PortI0_Ctrl		INPUT           // ALL_SYS_PWRGD
#define PortI1_Ctrl		INPUT			//
#define PortI2_Ctrl		INPUT			// SLP_S3#_3R
#define PortI3_Ctrl		INPUT	        // SUS_PWR_DN_ACK
#define PortI4_Ctrl		INPUT		    //
#define PortI5_Ctrl		INPUT		    //
#define PortI6_Ctrl		INPUT		    //
#define PortI7_Ctrl		INPUT       	//

//-----------------------------------------------------------------
// GPIO Port J Registers define
//-----------------------------------------------------------------
#define PortJ_Init		0x00            // PORT Data

#define PortJ0_Ctrl		INPUT			//
#define PortJ1_Ctrl		INPUT			//
#define PortJ2_Ctrl		INPUT			//
#define PortJ3_Ctrl		ALT			// FAN_TACH_DGPU
#define PortJ4_Ctrl		INPUT			//          
#define PortJ5_Ctrl		INPUT			//


#define KSI0_Ctrl       INPUT           // SLP_S4#_3R

#define KSO11_Ctrl      INPUT           // AMP_MUTE#



//------------------------------------------------------------------------------
// S.B.
//------------------------------------------------------------------------------
#define SCI_ON()		CLEAR_MASK(GPDRB,BIT(0))
#define SCI_OFF()		SET_MASK(GPDRB,BIT(0))

#define SMI_ON()		CLEAR_MASK(GPDRB,BIT(1))
#define SMI_OFF()		SET_MASK(GPDRB,BIT(1))

#define GATEA20_ON()	SET_MASK(GPDRB,BIT(5))
#define GATEA20_OFF()	CLEAR_MASK(GPDRB,BIT(5))

//------------------------------------------------------------------------------
// Power sequnce
//------------------------------------------------------------------------------
#define DNBSWON_ON()	CLEAR_MASK(GPDRG,BIT(1))
#define DNBSWON_OFF()	SET_MASK(GPDRG,BIT(1))

#define RSMRST_ON()		CLEAR_MASK(GPDRD,BIT(5))
#define RSMRST_OFF()	SET_MASK(GPDRD,BIT(5))

#define S5_ON()			SET_MASK(GPDRH,BIT(2))
#define S5_OFF()		CLEAR_MASK(GPDRH,BIT(2))
#define Read_S5_ON()    IS_MASK_SET(GPDRH,BIT(2))


#define PCH_PROCHOT_ON()    CLEAR_MASK(GPDRE,BIT(7))
#define PCH_PROCHOT_OFF()   SET_MASK(GPDRE,BIT(7))


#define ECPWROK_ON()	SET_MASK(GPDRB,BIT(6))
#define ECPWROK_OFF()	CLEAR_MASK(GPDRB,BIT(6))

#define WLAN_PWR_EN_ON()    CLEAR_MASK(GPDRF,BIT(3))
#define WLAN_PWR_EN_OFF()   SET_MASK(GPDRF,BIT(3))

#define USB_On_ON()	    SET_MASK(GPDRF,BIT(7))
#define USB_On_OFF()	CLEAR_MASK(GPDRF,BIT(7))


#define Read_SLPS3()	IS_MASK_SET(GPDRI,BIT(2))
#define Read_SLPS4()	IS_MASK_SET(KSIGDMRR,BIT(0))
#define Read_SLPS5()	IS_MASK_SET(KSIGDMRR,BIT(0))

#define Read_LPCRST()	IS_MASK_SET(GPDRD,BIT(2))

#define Read_NBSW()		IS_MASK_CLEAR(GPDRE,BIT(4))

#define Read_ALL_SYS_PWRGD()  IS_MASK_SET(GPDRI, BIT(0))

#define VOLMUTE_ON()	    KSOH1 |= 0x00;		// 2014-10-28: Peter add for Audio
#define VOLMUTE_OFF()	    KSOH1 |= 0x08;		// 2014-10-28: Peter add for Audio


//#define SUSON_ON()		SET_MASK(GPDRE,BIT(0))
//#define SUSON_OFF()		CLEAR_MASK(GPDRE,BIT(0))

//#define MAINON_ON()		SET_MASK(GPDRH,BIT(2))
//#define MAINON_OFF()	CLEAR_MASK(GPDRH,BIT(2))

//#define VRON_ON()		SET_MASK(GPDRE,BIT(2))
//#define VRON_OFF()		CLEAR_MASK(GPDRE,BIT(2))


//#define BT_EN_ON()    SET_MASK(GPDRG,BIT(1))
//#define BT_EN_OFF()   CLEAR_MASK(GPDRG,BIT(1))


//#define Read_SLPA()	    IS_MASK_SET(GPDRE,BIT(1))
//#define Read_SUSACK()   IS_MASK_SET(GPDRA,BIT(5))
//#define Read_SLP_SUS()  IS_MASK_SET(GPDRF,BIT(7))

//#define Read_HWPG()		IS_MASK_SET(GPDRC,BIT(6))
//#define Read_DTSALERT() IS_MASK_CLEAR(GPDRI,BIT(3))

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

extern void Init_GPIO(void);

#define Fan_volt		DCR0

typedef struct InitGPIOReg
{
    XBYTE 	*reg;	
	BYTE	value;
} sInitGPIOReg;


#endif
