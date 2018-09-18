/*-----------------------------------------------------------------------------
* TITLE: API_OW.H
*
* Author : Dino
*
* History : 
* ------------------------------
* Version : 1.00
* ------------------------------
*
* Note : To link [api_xxx.o] if related api function be used.
*
*---------------------------------------------------------------------------*/

#ifndef API_OW_H
#define API_OW_H

#define API_OW_SUPPORT 		1
#if API_OW_SUPPORT
//*****************************************************************************
//*****************************************************************************
// Software OW
// Pin 87 - GPCRF2
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
// F.W. OW pin definition [example]
//*****************************************************************************
#define OneWireInput 	        GPCRF2 = INPUT;
#define OneWireOutput 	        GPCRF2 = OUTPUT;
#define OneWireHigh		        SET_MASK(GPDRF, BIT2);
#define OneWireLow		        CLEAR_MASK(GPDRF, BIT2);
#define OneWireStatusLow        IS_MASK_CLEAR(GPDRF, BIT2)
#define OneWireStatusHigh       IS_MASK_SET(GPDRF, BIT2)

//*****************************************************************************
//*****************************************************************************
// H.W. OW
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
// (0x00F0_2Axxh) H.W. OW Registers
//*****************************************************************************
extern ECReg   OW_DATA;					// One Wire Data Register
extern ECReg   OW_CTRL;					// One Wire Control Register
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OW_RD           BIT(2)          // One-Wire Read
#define OW_WR           BIT(1)          // One-Wire Write
#define OW_RST          BIT(0)          // One-Wire Reset
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~				 
extern ECReg   OW_MOD;					// One Wire Mode Register
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OBMOD           BIT(1)          // One Bit Mode
#define OD              BIT(0)          // OverDrive
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern ECReg   OW_STS;					// One Wire Status Register
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PDR             BIT(3)          // Presence Detect Result
#define OWHIGH_ERR      BIT(2)          // One-Wire High Error
#define OWLOW_ERR       BIT(1)          // One-Wire Low Error
#define OW_DONE         BIT(0)          // One-Wire Done
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern ECReg   OW_INTEN;				// One Wire Interrupt Enable Register
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OWHIGH_EN       BIT(2)          // One-Wire High Error Interrupt Enable
#define OWLOW_EN        BIT(1)          // One-Wire Low Error Interrupt Enable
#define OW_DONE_EN      BIT(0)          // One-Wire Done Interrupt Enable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern ECReg   OW_RSTL_RSTH_H;			// One Wire High bit of Reset Low and Reset High Register
extern ECReg   OW_RST_LOW;				// One Wire Reset Low Register
extern ECReg   OW_MSP;					// One Wire Master Sample Present Register
extern ECReg   OW_RSTH;					// One Wire Reset High Register
extern ECReg   OW_SLOT; 				// One Wire Time Slot Register
extern ECReg   OW_W1L; 					// One Wire Write 1 Low Register
extern ECReg   OW_W0L; 					// One Wire Write 0 Low Register
extern ECReg   OW_MSR; 					// One Wire Master Sample Read Bit Register
//*****************************************************************************
// Function prototype
//*****************************************************************************
extern BYTE SW_OW_Device_Reset(void);
extern void SW_OW_Device_WriteByte(BYTE PsidByte);
extern BYTE SW_OW_Device_ReadByte(void);

extern BYTE HW_OW_Device_Reset(void);
extern BYTE HW_OW_Device_WriteByte(BYTE writedata);
extern BYTE HW_OW_Device_ReadByte(void);
extern void Enable_ETimer_T(BYTE Tomeout);
#endif
#endif
