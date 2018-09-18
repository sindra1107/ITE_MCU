/*-----------------------------------------------------------------------------
 * TITLE: CORE_CHIPREGS.H
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
 
#ifndef CORE_CHIPREGS_H
#define CORE_CHIPREGS_H

//-----------------------------------------------------------------------------
// (10XXh) Shared Memory Flash Interface Bridge (SMFI) 
//-----------------------------------------------------------------------------
extern ECReg 	FBCFG			;// 0x1000	 FBIU Configuration
extern ECReg 	FPCFG			;// 0x1001	 Flash Programming Configuration Register
extern ECReg 	FECBSR			;// 0x1005	 Flash EC Code Banking Select Register
extern ECReg 	FMSSR			;// 0x1007	 Flash Memory Size Select Registe
extern ECReg 	SMECCS			;// 0x1020	 Shared Memory EC Control and Status
extern ECReg 	SMHSR			;// 0x1022	 Shared Memory Host Semaphore
extern ECReg	FLHCTRL1R		;// 0x1031	 Flash Control Register 1	
//#define --		    BIT(7)  // Reserved
//#define --		    BIT(6)  // Reserved
#define SPIFR1		    BIT(5)  // SPI Flash Read Mode
#define SPIFR0		    BIT(4)  // SPI Flash Read Mode
                                //11b: Uses ¡§Fast Read Dual Input/Output (DIOFR)¡¨ cycle (instruction = BBh)
                                //10b: Uses ¡§Fast Read Dual Output (DOFR)¡¨ cycle (instruction = 3Bh)
                                //01b: Uses ¡§Fast Read (FREAD)¡¨ cycle (instruction = 0Bh)
                                //00b: Uses ¡§Read¡¨ cycle (instruction = 03h)
#define LFSW1T		    BIT(3)  // Serial Wait 1T
//#define --		    BIT(2)  // Reserved
//#define --		    BIT(1)  // Reserved
//#define --		    BIT(0)  // Reserved

extern ECReg	FLHCTRL2R		;// 0x1032	 Flash Control Register 2
extern ECReg	DCache			;// 0x1033   256 bytes cache
extern ECReg	UCCTRLR			;// 0x1034	 uC Control Register
extern ECReg	HCTRL2R			;// 0x1036	 Host Control 2 Register
extern ECReg    HSPICTRL2R      ;// 0x1039   HSPI Control 2 Register
extern ECReg	HSPICTRL3R      ;// 0x103A	 HSPI Control Register 3
extern ECReg 	ECINDAR0		;// 0x103B	 EC-Indirect Memory Address Register 0
extern ECReg 	ECINDAR1		;// 0x103C	 EC-Indirect Memory Address Register 1
extern ECReg 	ECINDAR2		;// 0x103D	 EC-Indirect Memory Address Register 2
extern ECReg 	ECINDAR3		;// 0x103E	 EC-Indirect Memory Address Register 3
extern ECReg 	ECINDDR			;// 0x103F	 EC-Indirect Memory Data Register
extern ECReg	SCRA0L			;// 0x1040	 Scratch SRAM 0 Address Low Byte Register
extern ECReg	SCRA0M			;// 0x1041	 Scratch SRAM 0 Address Middle Byte Register
extern ECReg	SCRA0H			;// 0x1042	 Scratch SRAM 0 Address High Byte Register
extern ECReg	SCRA1L			;// 0x1043	 Scratch SRAM 1 Address Low Byte Register
extern ECReg	SCRA1M			;// 0x1044	 Scratch SRAM 1 Address Middle Byte Register
extern ECReg	SCRA1H			;// 0x1045	 Scratch SRAM 1 Address High Byte Register
extern ECReg	SCRA2L			;// 0x1046	 Scratch SRAM 2 Address Low Byte Register
extern ECReg	SCRA2M			;// 0x1047	 Scratch SRAM 2 Address Middle Byte Register
extern ECReg	SCRA2H			;// 0x1048	 Scratch SRAM 2 Address High Byte Register
extern ECReg	SCRA3L			;// 0x1049	 Scratch SRAM 3 Address Low Byte Register
extern ECReg	SCRA3M			;// 0x104A	 Scratch SRAM 3 Address Middle Byte Register
extern ECReg	SCRA3H			;// 0x104B	 Scratch SRAM 3 Address High Byte Register
extern ECReg	SCRA4L			;// 0x104C	 Scratch SRAM 4 Address Low Byte Register
extern ECReg	SCRA4M			;// 0x104D	 Scratch SRAM 4 Address Middle Byte Register
extern ECReg	SCRA4H			;// 0x104E	 Scratch SRAM 4 Address High Byte Register

/*      FBCFG       */
#define SSMC    BIT(7)
/*      SMECCS      */
#define HOSTWA  BIT(5)
#define LKPRR   BIT(2)

extern ECReg	P0BA0R			;// 0x104F;	// Protect 0 Base Addr Register 0
extern ECReg	P0BA1R			;// 0x1050;	// Protect 0 Base Addr Register 1
extern ECReg	P0ZR			;// 0x1051;	// Protect 0 Size Register
extern ECReg	P1BA0R			;// 0x1052;	// Protect 1 Base Addr Register 0
extern ECReg	P1BA1R			;// 0x1053;	// Protect 1 Base Addr Register 1
extern ECReg	P1ZR			;// 0x1054;	// Protect 1 Size Register
extern ECReg	DSINST			;// 0x1055;	// Deferred SPI Instruction
extern ECReg	DSADR1			;// 0x1056;	// Deferred SPI Address	Deferred SPI Address 15-12 (DSA15-12)
extern ECReg	DSADR2			;// 0x1057;	// Deferred SPI Address Deferred SPI Address 23-16 (DSA23-16)
extern ECReg	HINSTC1			;// 0x1058;	// Host Instruction Control 1
#define DISSV		BIT(3)
#define DISS		BIT(2)
#define ENDPI		BIT(1)
#define ENDEI		BIT(0)

extern ECReg	HINSTC2			;// 0x1059;	// Host Instruction Control 2
#define DISEID8		BIT(3)
#define DISEID7		BIT(2)
#define DISEI52		BIT(1)
#define DISEI20		BIT(0)

extern ECReg	HRAMWC			;// 0x105A;	// Host RAM Window Control
#define Window0En	BIT(0)		 // Window 0 enabled
#define Window1En	BIT(1)		 // Window 1 enabled
#define H2RAMS		BIT(4)		 // 0 : H2RAM-HLPC selected, 1 : H2RAM-HSPI selected

extern ECReg	HRAMW0BA		;// 0x105B;	// Host RAM Winodw 0 Base Address external ram 0x800 ~ 0xFFF
extern ECReg	HRAMW1BA		;// 0x105C;	// Host RAM Window 1 Base Address external ram 0x000 ~ 0x7FF
extern ECReg	HRAMW0AAS		;// 0x105D;	// Host RAM Window 0 Access Allow Size
extern ECReg	HRAMW1AAS		;// 0x105E;	// Host RAM Window 1 Access Allow Size
#define HostRamSize16Byte 		0x00
#define HostRamSize32Byte 		0x01
#define HostRamSize64Byte 		0x02
#define HostRamSize128Byte 		0x03
#define HostRamSize256Byte 		0x04
#define HostRamSize512Byte 		0x05
#define HostRamSize1024Byte 	0x06
#define HostRamSize2048Byte 	0x07

extern ECReg	SCAR5H			;// 0x105F;
extern ECReg	FLHCTRL3R		;// 0x1063;
extern ECReg    FLHCTRL4R       ;// 0x1064; // Flash Control 4 Register
extern ECReg    HSPICTRL        ;// 0x1068; // HSPI Control Register 4
extern ECReg    P2BA0R          ;// 0x1070; // Protect 2 Base Addr Register 0
extern ECReg    P2BA1R          ;// 0x1071; // Protect 2 Base Addr Register 1
extern ECReg    P2ZR            ;// 0x1072; // Protect 2 Size Register
extern ECReg    P3BA0R          ;// 0x1073; // Protect 3 Base Addr Register 0
extern ECReg    P3BA1R          ;// 0x1074; // Protect 3 Base Addr Register 1
extern ECReg    P3ZR            ;// 0x1075; // Protect 3 Size Register
extern ECReg    HRAMW2BA        ;// 0x1076; // Host RAM Windows 2 Base Address
extern ECReg    HRAMW3BA        ;// 0x1077; // Host RAM Windows 3 Base Address
extern ECReg    HRAMW2AAS       ;// 0x1078; // Host RAM Windows 2 Access Allow Size
extern ECReg    HRAMW3AAS       ;// 0x1079; // Host RAM Windows 3 Access Allow Size
extern ECReg    H2RAMECSIE      ;// 0x107A; // H2RAM EC Semaphore Interrupt Enable
extern ECReg    H2RAMECSA       ;// 0x107B; // H2RAM EC Semaphore Address
extern ECReg    H2RAMHSS        ;// 0x107C; // H2RAM Host Semphore Status
extern ECReg    HPADR           ;// 0x107E; // Host Protect Authentication Data Register
//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC) 
//-----------------------------------------------------------------------------
extern ECReg 	ISR0      		;// 0x1100	 Interrupt Status Register 0
extern ECReg 	ISR1       		;// 0x1101	 Interrupt Status Register 1
extern ECReg 	ISR2       		;// 0x1102	 Interrupt Status Register 2
extern ECReg 	ISR3       		;// 0x1103	 Interrupt Status Register 3
extern ECReg 	ISR4    		;// 0x1114	 Interrupt Status Register 4
extern ECReg 	ISR5    		;// 0x1118   Interrupt Status Register 5
extern ECReg 	ISR6    		;// 0x111C	 Interrupt Status Register 6
extern ECReg 	ISR7    		;// 0x1120	 Interrupt Status Register 7
extern ECReg 	ISR8    		;// 0x1124	 Interrupt Status Register 8
extern ECReg 	ISR9            ;// 0x1128   Interrupt Status Register 9
extern ECReg    ISR10           ;// 0x112C Interrupt Status Register 10
extern ECReg    ISR11           ;// 0x1130 Interrupt Status Register 11
extern ECReg    ISR12           ;// 0x1134 Interrupt Status Register 12
extern ECReg    ISR13           ;// 0x1138 Interrupt Status Register 13
extern ECReg    ISR14           ;// 0x113C Interrupt Status Register 14
extern ECReg    ISR15           ;// 0x1140 Interrupt Status Register 15
extern ECReg    ISR16           ;// 0x1144 Interrupt Status Register 16
extern ECReg    ISR17           ;// 0x1148 Interrupt Status Register 17
extern ECReg    ISR18           ;// 0x114C Interrupt Status Register 18
extern ECReg    ISR19           ;// 0x1150 Interrupt Status Register 19

extern ECReg 	IER0      		;// 0x1104	 Interrupt Enable Register 0
extern ECReg 	IER1       		;// 0x1105	 Interrupt Enable Register 1
extern ECReg 	IER2      		;// 0x1106	 Interrupt Enable Register 2
extern ECReg 	IER3       		;// 0x1107	 Interrupt Enable Register 3
extern ECReg 	IER4    		;// 0x1115	 Interrupt Enable Register 4
extern ECReg 	IER5    		;// 0x1119   Interrupt Enable Register 5
extern ECReg 	IER6    		;// 0x111D	 Interrupt Enable Register 6
extern ECReg 	IER7    		;// 0x1121	 Interrupt Enable Register 7
extern ECReg 	IER8    		;// 0x1125   Interrupt Enable Register 8
extern ECReg 	IER9    		;// 0x1129   Interrupt Enable Register 9
extern ECReg    IER10           ;// 0x112D Interrupt Enable Register 10
extern ECReg    IER11           ;// 0x1131 Interrupt Enable Register 11
extern ECReg    IER12           ;// 0x1135 Interrupt Enable Register 12
extern ECReg    IER13           ;// 0x1139 Interrupt Enable Register 13
extern ECReg    IER14           ;// 0x113D Interrupt Enable Register 14
extern ECReg    IER15           ;// 0x1141 Interrupt Enable Register 15
extern ECReg    IER16           ;// 0x1145 Interrupt Enable Register 16
extern ECReg    IER17           ;// 0x1149 Interrupt Enable Register 17
extern ECReg    IER18           ;// 0x114D Interrupt Enable Register 18
extern ECReg    IER19           ;// 0x1151 Interrupt Enable Register 19

extern ECReg 	IELMR0    		;// 0x1108	 Interrupt Edge/Level-Triggered Mode Register 0
extern ECReg 	IELMR1     		;// 0x1109	 Interrupt Edge/Level-Triggered Mode Register 1
extern ECReg 	IELMR2   		;// 0x110A	 Interrupt Edge/Level-Triggered Mode Register 2
extern ECReg 	IELMR3     		;// 0x110B	 Interrupt Edge/Level-Triggered Mode Register 3
extern ECReg 	IELMR4    		;// 0x1116	 Interrupt Edge/Level-Triggered Mode Register 4
extern ECReg 	IELMR5    		;// 0x111A   Interrupt Edge/Level-Triggered Mode Register 5
extern ECReg 	IELMR6    		;// 0x111E   Interrupt Edge/Level-Triggered Mode Register 6
extern ECReg 	IELMR7    		;// 0x1122   Interrupt Edge/Level-Triggered Mode Register 7
extern ECReg 	IELMR8    		;// 0x1126   Interrupt Edge/Level-Triggered Mode Register 8
extern ECReg 	IELMR9    		;// 0x112A   Interrupt Edge/Level-Triggered Mode Register 9
extern ECReg    IELMR10         ;// 0x112E Interrupt Edge/Level-Triggered Mode Register 10
extern ECReg    IELMR11         ;// 0x1132 Interrupt Edge/Level-Triggered Mode Register 11
extern ECReg    IELMR12         ;// 0x1136 Interrupt Edge/Level-Triggered Mode Register 12
extern ECReg    IELMR13         ;// 0x113A Interrupt Edge/Level-Triggered Mode Register 13
extern ECReg    IELMR14         ;// 0x113E Interrupt Edge/Level-Triggered Mode Register 14
extern ECReg    IELMR15         ;// 0x1142 Interrupt Edge/Level-Triggered Mode Register 15
extern ECReg    IELMR16         ;// 0x1146 Interrupt Edge/Level-Triggered Mode Register 16
extern ECReg    IELMR17         ;// 0x114A Interrupt Edge/Level-Triggered Mode Register 17
extern ECReg    IELMR18         ;// 0x114E Interrupt Edge/Level-Triggered Mode Register 18
extern ECReg    IELMR19         ;// 0x1152 Interrupt Edge/Level-Triggered Mode Register 19

extern ECReg 	IPOLR0     		;// 0x110C	 Interrupt Polarity Register 0
extern ECReg 	IPOLR1    		;// 0x110D	 Interrupt Polarity Register 1
extern ECReg 	IPOLR2    		;// 0x110E	 Interrupt Polarity Register 2
extern ECReg 	IPOLR3    		;// 0x110F	 Interrupt Polarity Register 3
extern ECReg 	IPOLR4    		;// 0x1117	 Interrupt Polarity Register 4
extern ECReg 	IPOLR5    		;// 0x111B   Interrupt Polarity Register 5
extern ECReg 	IPOLR6    		;// 0x111F   Interrupt Polarity Register 6
extern ECReg 	IPOLR7    		;// 0x1123   Interrupt Polarity Register 7
extern ECReg 	IPOLR8    		;// 0x1127   Interrupt Polarity Register 8
extern ECReg 	IPOLR9    		;// 0x112B   Interrupt Polarity Register 9
extern ECReg    IPOLR10         ;// 0x112F Interrupt Polarity Register 10
extern ECReg    IPOLR11         ;// 0x1133 Interrupt Polarity Register 11
extern ECReg    IPOLR12         ;// 0x1137 Interrupt Polarity Register 12
extern ECReg    IPOLR13         ;// 0x113B Interrupt Polarity Register 13
extern ECReg    IPOLR14         ;// 0x113F Interrupt Polarity Register 14
extern ECReg    IPOLR15         ;// 0x1143 Interrupt Polarity Register 15
extern ECReg    IPOLR16         ;// 0x1147 Interrupt Polarity Register 16
extern ECReg    IPOLR17         ;// 0x114B Interrupt Polarity Register 17
extern ECReg    IPOLR18         ;// 0x114F Interrupt Polarity Register 18
extern ECReg    IPOLR19         ;// 0x1153 Interrupt Polarity Register 19

extern ECReg 	IVECT    		;// 0x1110	 Interrupt Vector Register
extern ECReg 	INT0ST    		;// 0x1111	 INT0# status
extern ECReg 	PFAILR    		;// 0x1112	 Power Fail Register

//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge) 
//-----------------------------------------------------------------------------
extern ECReg 	IHIOA     		;// 0x1200	 Indirect Host I/O Address
extern ECReg 	IHD      		;// 0x1201	 Indirect Host Data
extern ECReg 	LSIOHA    		;// 0x1202	 Lock Super I/O Host Access
extern ECReg 	SIOLV     		;// 0x1203	 Super I/O Access Lock Violation
extern ECReg 	IBMAE			;// 0x1204	 EC to I-Bus Modules Access Enable
extern ECReg 	IBCTL   		;// 0x1205	 I-Bus Control
//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC) 
//-----------------------------------------------------------------------------
extern ECReg 	KBHICR   		;// 0x1300	 KBC Host Interface Control Register
extern ECReg 	KBIRQR     		;// 0x1302	 KBC Interrupt Control Register
extern ECReg 	KBHISR   		;// 0x1304	 KBC Host Interface Keyboard/Mouse Status Register
extern ECReg 	KBHIKDOR 		;// 0x1306	 KBC Host Interface Keyboard Data Output Register
extern ECReg 	KBHIMDOR  		;// 0x1308	 KBC Host Interface Mouse Data Output Register
extern ECReg 	KBHIDIR   		;// 0x130A	 KBC Host Interface Keyboard/Mouse Data Input Register
//-----------------------------------------------------------------------------
// (14xxh) System Wake-Up Control (SWUC) 
//-----------------------------------------------------------------------------
extern ECReg 	SWCTL1			;// 0x1400	 SWUC Control Status 1 Register
extern ECReg 	SWCTL2			;// 0x1402	 SWUC Control Status 2 Register
extern ECReg 	SWCTL3			;// 0x1404	 SWUC Control Status 3 Register
extern ECReg 	SWCBALR			;// 0x1408	 SWUC Host Configuration Base Address Low Byte Register
extern ECReg 	SWCBAHR			;// 0x140A	 SWUC Host Configuration Base Address High Byte Register
extern ECReg 	SWCIER     		;// 0x140C	 SWUC Interrupt Enable Register
extern ECReg 	SWCHSTR    		;// 0x140E	 SWUC Host Event Status Register
extern ECReg 	SWCHIER  		;// 0x1410	 SWUC Host Event Interrupt Enable Register

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC) 
//-----------------------------------------------------------------------------
								 //		 	 PM1
extern ECReg 	PM1STS   		;// 0x1500	 Host Interface PM Channel 1 Status
extern ECReg 	PM1DO      		;// 0x1501	 Host Interface PM Channel 1 Data Out Port
extern ECReg 	PM1DOSCI  		;// 0x1502	 Host Interface PM Channel 1 Data Out Port with SCI
extern ECReg 	PM1DOSMI  		;// 0x1503	 Host Interface PM Channel 1 Data Out Port with SMI
extern ECReg 	PM1DI			;// 0x1504	 Host Interface PM Channel 1 Data In Port
extern ECReg 	PM1DISCI   		;// 0x1505	 Host Interface PM Channel 1 Data In Port with SCI
extern ECReg 	PM1CTL     		;// 0x1506	 Host Interface PM Channel 1 Control
extern ECReg 	PM1IC     		;// 0x1507	 Host Interface PM Channel 1 Interrupt Control
extern ECReg 	PM1IE    		;// 0x1508	 Host Interface PM Channel 1 Interrupt Enable
								 //			 PM2
extern ECReg 	PM2STS    		;// 0x1510	 Host Interface PM Channel 2 Status
extern ECReg 	PM2DO     		;// 0x1511	 Host Interface PM Channel 2 Data Out Port
extern ECReg 	PM2DOSCI   		;// 0x1512	 Host Interface PM Channel 2 Data Out Port with SCI
extern ECReg 	PM2DOSMI  		;// 0x1513	 Host Interface PM Channel 2 Data Out Port with SMI
extern ECReg 	PM2DI     		;// 0x1514	 Host Interface PM Channel 2 Data In Port
extern ECReg 	PM2DISCI   		;// 0x1515	 Host Interface PM Channel 2 Data In Port with SCI
extern ECReg 	PM2CTL     		;// 0x1516	 Host Interface PM Channel 2 Control
extern ECReg 	PM2IC     		;// 0x1517	 Host Interface PM Channel 2 Interrupt Control
extern ECReg 	PM2IE     		;// 0x1518	 Host Interface PM Channel 2 Interrupt Enable
								 //			 Mailbox
extern ECReg	MBXCTRL			;// 0x1519	 Mailbox Control
extern ECReg	MBXEC[]			;// 0x15F0 16-byte PMC2EX Mailbox 0 ~ Mailbox 15

extern ECReg 	PM3STS    		;// 0x1520  Host Interface PM Channel 3 Status
extern ECReg 	PM3DO     		;// 0x1521  Host Interface PM Channel 3 Data Out Port
extern ECReg 	PM3DI     		;// 0x1522  Host Interface PM Channel 3 Data In Port
extern ECReg 	PM3CTL     		;// 0x1523  Host Interface PM Channel 3 Control
extern ECReg 	PM3IC     		;// 0x1524  Host Interface PM Channel 3 Interrupt Control
extern ECReg 	PM3IE     		;// 0x1525  Host Interface PM Channel 3 Interrupt Enable

extern ECReg 	PM4STS    		;// 0x1530  Host Interface PM Channel 4 Status
extern ECReg 	PM4DO     		;// 0x1531  Host Interface PM Channel 4 Data Out Port
extern ECReg 	PM4DI     		;// 0x1532  Host Interface PM Channel 4 Data In Port
extern ECReg 	PM4CTL     		;// 0x1533  Host Interface PM Channel 4 Control
extern ECReg 	PM4IC     		;// 0x1534  Host Interface PM Channel 4 Interrupt Control
extern ECReg 	PM4IE     		;// 0x1535  Host Interface PM Channel 4 Interrupt Enable

extern ECReg    PM5STS          ;// 0x1540  Host Interface PM Channel 5 Status
extern ECReg    PM5DO           ;// 0x1541  Host Interface PM Channel 5 Data Out Port
extern ECReg    PM5DI           ;// 0x1542  Host Interface PM Channel 5 Data In Port
extern ECReg    PM5CTL          ;// 0x1543  Host Interface PM Channel 5 Control
extern ECReg    PM5IC           ;// 0x1544  Host Interface PM Channel 5 Interrupt Control
extern ECReg    PM5IE           ;// 0x1545  Host Interface PM Channel 5 Interrupt Enable
//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control Register                           
//-----------------------------------------------------------------------------
								 //			 GPIO data register
extern ECReg	GCR     		;// 0x1600	 General Control Register
extern ECReg	GCR1     		;// 0x16F0	 General Control 1 Register
#define         SPICTRL_0 BIT(4)
#define         SPICTRL_1 BIT(5) // SPI interface control
#define         SSSPIBP BIT(6)  // Support SSPI BUSY Pin

extern ECReg	GCR2     		;// 0x16F1   General Control 2 Register
#define 		CK32OE	BIT(6)	// CK32K Out Enable
#define			SMB4E	BIT(5)	// SMBus Channel 4 Enable
#define 		PECIE	BIT(4)	// PECI Enable

extern ECReg	GCR3     		;// 0x16F2  General Control 3 Register
extern ECReg	GCR4     		;// 0x16F3  General Control 4 Register
extern ECReg	GCR5     		;// 0x16F4  General Control 5 Register
extern ECReg	GCR6     		;// 0x16F5  General Control 6 Register
extern ECReg	GCR7     		;// 0x16F6  General Control 7 Register
extern ECReg    GCR8            ;// 0x16F7  General Control 8 Register
extern ECReg    GCR9            ;// 0x16F8  General Control 9 Register
extern ECReg    GCR10           ;// 0x16F9  General Control 10 Register
extern ECReg    GCR11           ;// 0x16FA  General Control 11 Register
extern ECReg    GCR12           ;// 0x16FB  General Control 12 Register
extern ECReg    GCR13           ;// 0x16FC  General Control 13 Register
extern ECReg    GCR14           ;// 0x16FD  General Control 14 Register
extern ECReg    GCR15           ;// 0x16FE  General Control 15 Register
extern ECReg    GCR16           ;// 0x16E0  General Control 16 Register
extern ECReg    GCR17           ;// 0x16E1  General Control 17 Register
extern ECReg    GCR18           ;// 0x16E2  General Control 18 Register
extern ECReg    GCR19           ;// 0x16E4  General Control 19 Register
extern ECReg    GCR20           ;// 0x16E5  General Control 20 Register
extern ECReg    GCR21           ;// 0x16E6  General Control 21 Register
extern ECReg    GCR22           ;// 0x16E7  General Control 22 Register

extern ECReg	GPDRA 			;// 0x1601	 Port A Data Register
extern ECReg	GPDRB 			;// 0x1602	 Port B Data Register
extern ECReg	GPDRC 			;// 0x1603	 Port C Data Register
extern ECReg	GPDRD 			;// 0x1604	 Port D Data Register
extern ECReg	GPDRE 			;// 0x1605	 Port E Data Register
extern ECReg	GPDRF 			;// 0x1606	 Port F Data Register
extern ECReg	GPDRG 			;// 0x1607	 Port G Data Register
extern ECReg	GPDRH 			;// 0x1608	 Port H Data Register
extern ECReg	GPDRI 			;// 0x1609	 Port I Data Register
extern ECReg	GPDRJ 			;// 0x160A	 Port J Data Register
extern ECReg	GPDRM 			;// 0x160D   Port M Data Register
								 //		 	 GPIO control register
extern ECReg 	GPCRA0			;// 0x1610	 Port Control A0 Registers
extern ECReg 	GPCRA1			;// 0x1611	 Port Control A1 Registers
extern ECReg 	GPCRA2			;// 0x1612	 Port Control A2 Registers
extern ECReg 	GPCRA3			;// 0x1613	 Port Control A3 Registers
extern ECReg 	GPCRA4			;// 0x1614	 Port Control A4 Registers
extern ECReg 	GPCRA5			;// 0x1615	 Port Control A5 Registers
extern ECReg 	GPCRA6			;// 0x1616	 Port Control A6 Registers
extern ECReg 	GPCRA7			;// 0x1617	 Port Control A7 Registers

extern ECReg 	GPCRB0			;// 0x1618	 Port Control B0 Registers
extern ECReg 	GPCRB1			;// 0x1619	 Port Control B1 Registers
extern ECReg 	GPCRB2			;// 0x161A	 Port Control B2 Registers
extern ECReg 	GPCRB3			;// 0x161B	 Port Control B3 Registers
extern ECReg 	GPCRB4			;// 0x161C	 Port Control B4 Registers
extern ECReg 	GPCRB5			;// 0x161D	 Port Control B5 Registers
extern ECReg 	GPCRB6			;// 0x161E	 Port Control B6 Registers
extern ECReg 	GPCRB7			;// 0x161F	 Port Control B7 Registers

extern ECReg 	GPCRC0			;// 0x1620	 Port Control C0 Registers
extern ECReg 	GPCRC1			;// 0x1621	 Port Control C1 Registers
extern ECReg 	GPCRC2			;// 0x1622	 Port Control C2 Registers
extern ECReg 	GPCRC3			;// 0x1623	 Port Control C3 Registers
extern ECReg 	GPCRC4			;// 0x1624	 Port Control C4 Registers
extern ECReg 	GPCRC5			;// 0x1625	 Port Control C5 Registers
extern ECReg 	GPCRC6			;// 0x1626	 Port Control C6 Registers
extern ECReg 	GPCRC7			;// 0x1627	 Port Control C7 Registers

extern ECReg 	GPCRD0			;// 0x1628	 Port Control D0 Registers
extern ECReg 	GPCRD1			;// 0x1629	 Port Control D1 Registers
extern ECReg 	GPCRD2			;// 0x162A	 Port Control D2 Registers
extern ECReg 	GPCRD3			;// 0x162B	 Port Control D3 Registers
extern ECReg 	GPCRD4			;// 0x162C	 Port Control D4 Registers
extern ECReg 	GPCRD5			;// 0x162D	 Port Control D5 Registers
extern ECReg 	GPCRD6			;// 0x162E	 Port Control D6 Registers
extern ECReg 	GPCRD7			;// 0x162F	 Port Control D7 Registers

extern ECReg 	GPCRE0			;// 0x1630	 Port Control E0 Registers
extern ECReg 	GPCRE1			;// 0x1631	 Port Control E1 Registers
extern ECReg 	GPCRE2			;// 0x1632	 Port Control E2 Registers
extern ECReg 	GPCRE3			;// 0x1633	 Port Control E3 Registers
extern ECReg 	GPCRE4			;// 0x1634	 Port Control E4 Registers
extern ECReg 	GPCRE5			;// 0x1635	 Port Control E5 Registers
extern ECReg 	GPCRE6			;// 0x1636	 Port Control E6 Registers
extern ECReg 	GPCRE7			;// 0x1637	 Port Control E7 Registers

extern ECReg 	GPCRF0			;// 0x1638	 Port Control F0 Registers
extern ECReg 	GPCRF1			;// 0x1639	 Port Control F1 Registers
extern ECReg 	GPCRF2			;// 0x163A	 Port Control F2 Registers
extern ECReg 	GPCRF3			;// 0x163B	 Port Control F3 Registers
extern ECReg 	GPCRF4			;// 0x163C	 Port Control F4 Registers
extern ECReg 	GPCRF5			;// 0x163D	 Port Control F5 Registers
extern ECReg 	GPCRF6			;// 0x163E	 Port Control F6 Registers
extern ECReg 	GPCRF7			;// 0x163F	 Port Control F7 Registers

extern ECReg 	GPCRG0			;// 0x1640	 Port Control G0 Registers
extern ECReg 	GPCRG1			;// 0x1641	 Port Control G1 Registers
extern ECReg 	GPCRG2			;// 0x1642	 Port Control G2 Registers
extern ECReg 	GPCRG3			;// 0x1643	 Port Control G3 Registers
extern ECReg 	GPCRG4			;// 0x1644	 Port Control G4 Registers
extern ECReg 	GPCRG5			;// 0x1645	 Port Control G5 Registers
extern ECReg 	GPCRG6			;// 0x1646	 Port Control G6 Registers
extern ECReg 	GPCRG7			;// 0x1647	 Port Control G7 Registers

extern ECReg 	GPCRH0			;// 0x1648	 Port Control H0 Registers
extern ECReg 	GPCRH1			;// 0x1649	 Port Control H1 Registers
extern ECReg 	GPCRH2			;// 0x164A	 Port Control H2 Registers
extern ECReg 	GPCRH3			;// 0x164B	 Port Control H3 Registers
extern ECReg 	GPCRH4			;// 0x164C	 Port Control H4 Registers
extern ECReg 	GPCRH5			;// 0x164D	 Port Control H5 Registers
extern ECReg 	GPCRH6			;// 0x164E	 Port Control H6 Registers

extern ECReg 	GPCRI0			;// 0x1650	 Port Control I0 Registers
extern ECReg 	GPCRI1			;// 0x1651	 Port Control I1 Registers
extern ECReg 	GPCRI2			;// 0x1652	 Port Control I2 Registers
extern ECReg 	GPCRI3			;// 0x1653	 Port Control I3 Registers
extern ECReg 	GPCRI4			;// 0x1654	 Port Control I4 Registers
extern ECReg 	GPCRI5			;// 0x1655	 Port Control I5 Registers
extern ECReg 	GPCRI6			;// 0x1656	 Port Control I6 Registers
extern ECReg 	GPCRI7			;// 0x1657	 Port Control I7 Registers

extern ECReg 	GPCRJ0			;// 0x1658	 Port Control J0 Registers
extern ECReg 	GPCRJ1			;// 0x1659	 Port Control J1 Registers
extern ECReg 	GPCRJ2			;// 0x165A	 Port Control J2 Registers
extern ECReg 	GPCRJ3			;// 0x165B	 Port Control J3 Registers
extern ECReg 	GPCRJ4			;// 0x165C	 Port Control J4 Registers
extern ECReg 	GPCRJ5			;// 0x165D	 Port Control J5 Registers
extern ECReg 	GPCRJ6			;// 0x165E   Port Control J6 Registers
extern ECReg 	GPCRJ7			;// 0x165F   Port Control J7 Registers

extern ECReg 	GPCRM0			;// 0x16A0   Port Control M0 Registers
extern ECReg 	GPCRM1			;// 0x16A1   Port Control M1 Registers
extern ECReg 	GPCRM2			;// 0x16A2   Port Control M2 Registers
extern ECReg 	GPCRM3			;// 0x16A3   Port Control M3 Registers
extern ECReg 	GPCRM4			;// 0x16A4   Port Control M4 Registers
extern ECReg 	GPCRM5			;// 0x16A5   Port Control M5 Registers
extern ECReg 	GPCRM6			;// 0x16A6   Port Control M6 Registers
								 //		 	 Port Data Mirror Register
extern ECReg 	GPDMRA			;// 0x1661	 Port A Data Mirror Register
extern ECReg 	GPDMRB			;// 0x1662	 Port B Data Mirror Register
extern ECReg 	GPDMRC			;// 0x1663	 Port C Data Mirror Register
extern ECReg 	GPDMRD			;// 0x1664	 Port D Data Mirror Register
extern ECReg 	GPDMRE			;// 0x1665	 Port E Data Mirror Register
extern ECReg 	GPDMRF			;// 0x1666	 Port F Data Mirror Register
extern ECReg 	GPDMRG			;// 0x1667	 Port G Data Mirror Register
extern ECReg 	GPDMRH			;// 0x1668	 Port H Data Mirror Register
extern ECReg 	GPDMRI			;// 0x1669	 Port I Data Mirror Register
extern ECReg 	GPDMRJ			;// 0x166A	 Port J Data Mirror Register
extern ECReg 	GPDMRM			;// 0x166D   Port M Data Mirror Register

extern ECReg 	GPOTA			;// 0x1671   Output Type Register

extern ECReg 	GPOTB			;// 0x1672	 Output Type Register
extern ECReg 	GPOTD			;// 0x1674	 Output Type Register
extern ECReg 	GPOTE			;// 0x1675   Output Type Register
extern ECReg    GPOTF           ;// 0x1676   Output Type Register
extern ECReg    GPOTH           ;// 0x1678   Output Type Register
extern ECReg    GPOTJ           ;// 0x167A   Output Type Register

//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface Register                            			  
//-----------------------------------------------------------------------------
extern ECReg 	PSCTL1    		;// 0x1700	 PS/2 Control Register 1
extern ECReg 	PSCTL2			;// 0x1701	 PS/2 Control Register 2
extern ECReg 	PSCTL3     		;// 0x1702	 PS/2 Control Register 3
extern ECReg 	PSINT1   		;// 0x1704	 PS/2 Interrupt Control Register 1
extern ECReg 	PSINT2    		;// 0x1705	 PS/2 Interrupt Control Register 2
extern ECReg 	PSINT3    		;// 0x1706	 PS/2 Interrupt Control Register 3
extern ECReg 	PSSTS1    		;// 0x1708	 PS/2 Status Register 1
extern ECReg 	PSSTS2    		;// 0x1709	 PS/2 Status Register 2
extern ECReg 	PSSTS3    		;// 0x170A	 PS/2 Status Register 3
extern ECReg 	PSDAT1    		;// 0x170C	 PS/2 Data Register 1
extern ECReg 	PSDAT2     		;// 0x170D	 PS/2 Data Register 2
extern ECReg	PSDAT3 			;// 0x170E	 PS/2 Data Register 3

//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM) 
//-----------------------------------------------------------------------------
extern ECReg	C0CPRS  		;// 0x1800	 Channel 0 Clock Prescaler Register
extern ECReg	CTR       		;// 0x1801	 Cycle Time 0
extern ECReg	DCR0     		;// 0x1802	 Channel 0 PWM Duty Cycle		
extern ECReg	DCR1      		;// 0x1803	 Channel 0 PWM Duty Cycle	
extern ECReg	DCR2     		;// 0x1804	 Channel 0 PWM Duty Cycle	
extern ECReg	DCR3       		;// 0x1805	 Channel 0 PWM Duty Cycle	
extern ECReg	DCR4      		;// 0x1806	 Channel 0 PWM Duty Cycle	
extern ECReg	DCR5      		;// 0x1807	 Channel 0 PWM Duty Cycle	
extern ECReg	DCR6       		;// 0x1808	 Channel 0 PWM Duty Cycle	
extern ECReg	DCR7     		;// 0x1809	 Channel 0 PWM Duty Cycle	
extern ECReg	PWMPOL        	;// 0x180A	 PWM Polarity
extern ECReg	PCFSR      		;// 0x180B	 Prescaler Clock Frequency Select Register
extern ECReg	PCSSGL   		;// 0x180C	 Prescaler Clock Source Select Group Low
extern ECReg	PCSSGH    		;// 0x180D	 Prescaler Clock Source Select Group High
extern ECReg	CR256PCSSG		;// 0x180E	 CR256 Prescaler Clock Source Select Group
extern ECReg	PCSGR			;// 0x180F	 Prescaler Clock Source Gating Register
extern ECReg	F1TLRR     		;// 0x181E	 Fan 1 Tachometer LSB Reading
extern ECReg	F1TMRR    		;// 0x181F	 Fan 1 Tachometer MSB Reading
extern ECReg	F2TLRR    		;// 0x1820	 Fan 2 Tachometer LSB Reading
extern ECReg	F2TMRR     		;// 0x1821	 Fan 2 Tachometer MSB Reading
extern ECReg	ZINTSCR   		;// 0x1822	 Zone Interrupt Status Control
extern ECReg	ZTIER      		;// 0x1823	 PWM Clock Control Register
extern ECReg	TSWCTLR    		;// 0x1824   Tachometer Switch Control Register
extern ECReg	C4CPRS    		;// 0x1827	 Channel 4 Clock Prescaler Register
extern ECReg	C4MCPRS    		;// 0x1828	 Channel 4 Clock Prescaler MSB Register
extern ECReg	C6CPRS    		;// 0x182B	 Channel 6 Clock Prescaler Register
extern ECReg	C6MCPRS    		;// 0x182C	 Channel 6 Clock Prescaler MSB Register
extern ECReg	C7CPRS     		;// 0x182D	 Channel 7 Clock Prescaler Register
extern ECReg	C7MCPRS    		;// 0x182E	 Channel 7 Clock Prescaler MSB Register
extern ECReg	CLK6MSEL   		;// 0x1840   Clock 6MHz Select Register
extern ECReg	CTR1    		;// 0x1841   Cycle Time 1
extern ECReg	CTR2    		;// 0x1842   Cycle Time 2
extern ECReg	CTR3    		;// 0x1843   Cycle Time 3
extern ECReg	PWM5TOCTRL		;// 0x1844   PWM5 Timeout Control Register
extern ECReg	CFLRR    		;// 0x1845   Color Frequency LSB Register
extern ECReg	CFMRR    		;// 0x1846   Color Frequency MSB Register
extern ECReg	CFINTCTRL		;// 0x1847   Color Frequency Interrupt Control Register

extern ECReg	TSWCTRL    		;// 0x1848   Tachometer Switch Control Register
extern ECReg	PWMODENR		;// 0x1849   PWM Output Open-Drain Enable Register
//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC) 
//-----------------------------------------------------------------------------
extern ECReg	ADCSTS			;// 0x1900	 ADC Status
extern ECReg	ADCCFG			;// 0x1901	 ADC Configuration
extern ECReg	ADCCTL			;// 0x1902	 ADC Clock Control
extern ECReg	ADCGCR			;// 0x1903   ADC General Control Register
extern ECReg	VCH0CTL			;// 0x1904	 Voltage Channel 0 Channel Control
extern ECReg	KDCTL			;// 0x1905	 Calibration Data Control Register
extern ECReg	VCH1CTL      	;// 0x1906	 Voltage Channel 1 Control
extern ECReg	VCH1DATL     	;// 0x1907	 Voltage Channel 1 Data Buffer LSB
extern ECReg	VCH1DATM       	;// 0x1908	 Voltage Channel 1 Data Buffer MSB
extern ECReg	VCH2CTL        	;// 0x1909	 Voltage Channel 2 Control
extern ECReg	VCH2DATL      	;// 0x190A	 Voltage Channel 2 Data Buffer LSB
extern ECReg	VCH2DATM     	;// 0x190B	 Voltage Channel 2 Data Buffer MSB
extern ECReg	VCH3CTL       	;// 0x190C	 Voltage Channel 3 Control
extern ECReg	VCH3DATL      	;// 0x190D	 Voltage Channel 3 Data Buffer LSB
extern ECReg	VCH3DATM      	;// 0x190E	 Voltage Channel 3 Data Buffer MSB
extern ECReg	VHSCDBL      	;// 0x1914	 Voltage High Scale Calibration Data Buffer LSB
extern ECReg	VHSCDBM       	;// 0x1915	 Voltage High Scale Calibration Data Buffer MSB
extern ECReg	VCH0DATL		;// 0x1918	 Voltage Channel 0 Data Buffer LSB
extern ECReg	VCH0DATM		;// 0x1919	 Voltage Channel 0 Data Buffer MSB
extern ECReg	VHSGCDBL      	;// 0x191C	 Voltage High Scale Gain-error Calibration Data Buffer LSB
extern ECReg	VHSGCDBM     	;// 0x191d	 Voltage High Scale Gain-error Calibration Data Buffer MSB

extern ECReg    VCMPSCP         ;// 0x1937 Voltage Compare Scan Period
extern ECReg    VCH4CTL         ;// 0x1938 Voltage Channel 4 Control Register
extern ECReg    VCH4DATM        ;// 0x1939 Volt Channel 4 Data Buffer MSB
extern ECReg    VCH4DATL        ;// 0x193A Volt Channel 4 Data Buffer LSB
extern ECReg    VCH5CTL         ;// 0x193B Voltage Channel 5 Control Register
extern ECReg    VCH5DATM        ;// 0x193C Volt Channel 5 Data Buffer MSB
extern ECReg    VCH5DATL        ;// 0x193D Volt Channel 5 Data Buffer LSB
extern ECReg    VCH6CTL         ;// 0x193E Voltage Channel 6 Control Register
extern ECReg    VCH6DATM        ;// 0x193F Volt Channel 6 Data Buffer MSB
extern ECReg    VCH6DATL        ;// 0x1940 Volt Channel 6 Data Buffer LSB
extern ECReg    VCH7CTL         ;// 0x1941 Voltage Channel 7 Control Register
extern ECReg    VCH7DATM        ;// 0x1942 Volt Channel 7 Data Buffer MSB
extern ECReg    VCH7DATL        ;// 0x1943 Volt Channel 7 Data Buffer LSB
extern ECReg    ADCDVSTS        ;// 0x1944 ADC Data Vaild Status
extern ECReg    VCMPSTS         ;// 0x1945 Voltage Compare Status
extern ECReg    VCMP0CTL        ;// 0x1946 Voltage Compare Channel 0 Control Register
extern ECReg    CMP0THRDATM     ;// 0x1947 Voltage Compare 0 Threshold Data Buffer MSB
extern ECReg    CMP0THRDATL     ;// 0x1948 Voltage Compare 0 Threshold Data Buffer LSB
extern ECReg    VCMP1CTL        ;// 0x1949 Voltage Compare Channel 1 Control Register
extern ECReg    CMP1THRDATM     ;// 0x194A Voltage Compare 1 Threshold Data Buffer MSB
extern ECReg    CMP1THRDATL     ;// 0x194B Voltage Compare 1 Threshold Data Buffer LSB
extern ECReg    VCMP2CTL        ;// 0x194C Voltage Compare Channel 2 Control Register
extern ECReg    CMP2THRDATM     ;// 0x194D Voltage Compare 2 Threshold Data Buffer MSB
extern ECReg    CMP2THRDATL     ;// 0x194E Voltage Compare 2 Threshold Data Buffer LSB
extern ECReg    VCMPOTR			;// Voltage Comparator Output Type Register
extern ECReg    VCMPLR			;// Voltage Comparator Lock Register

//-----------------------------------------------------------------------------
// (1Axxh) Digital to Analog Converter (DAC) 
//-----------------------------------------------------------------------------
extern ECReg	DACPWRDN      	;// 0x1A01	 DAC Power Down Register
extern ECReg	DACDAT0      	;// 0x1A02	 DAC Data Channel 0
extern ECReg	DACDAT1       	;// 0x1A03	 DAC Data Channel 1
extern ECReg	DACDAT2        	;// 0x1A04	 DAC Data Channel 2
extern ECReg	DACDAT3       	;// 0x1A05	 DAC Data Channel 3
extern ECReg	DACDAT4       	;// 0x1A06	 DAC Data Channel 4
extern ECReg	DACDAT5       	;// 0x1A07	 DAC Data Channel 5

//-----------------------------------------------------------------------------
// (1Bxxh) Wack-Up control (WUC) 
//-----------------------------------------------------------------------------
extern ECReg	WUEMR1			;// 0x1B00	 Wake-Up Edge Mode Register 1
extern ECReg	WUEMR2      	;// 0x1B01	 Wake-Up Edge Mode Register 2
extern ECReg	WUEMR3       	;// 0x1B02	 Wake-Up Edge Mode Register 3
extern ECReg	WUEMR4       	;// 0x1B03	 Wake-Up Edge Mode Register 4
extern ECReg	WUEMR6       	;// 0x1B10	 Wake-Up Edge Mode Register 6
extern ECReg	WUEMR7       	;// 0x1B14   Wake-Up Edge Mode Register 7
extern ECReg    WUEMR8          ;// 0x1B18   Wake-Up Edge Mode Register 8
extern ECReg    WUEMR9          ;// 0x1B1C   Wake-Up Edge Mode Register 9
extern ECReg    WUEMR10         ;// 0x1B20   Wake-Up Edge Mode Register 10
extern ECReg    WUEMR11         ;// 0x1B24   Wake-Up Edge Mode Register 11
extern ECReg    WUEMR12         ;// 0x1B28   Wake-Up Edge Mode Register 12
extern ECReg    WUEMR13         ;// 0x1B2C   Wake-Up Edge Mode Register 13
extern ECReg    WUEMR14         ;// 0x1B30   Wake-Up Edge Mode Register 14
extern ECReg	WUESR1       	;// 0x1B04	 Wake-Up Edge Sense Register 1
extern ECReg	WUESR2       	;// 0x1B05	 Wake-Up Edge Sense Register 2
extern ECReg	WUESR3       	;// 0x1B06	 Wake-Up Edge Sense Register 3
extern ECReg	WUESR4        	;// 0x1B07	 Wake-Up Edge Sense Register 4
extern ECReg	WUESR6        	;// 0x1B11	 Wake-Up Edge Sense Register 6
extern ECReg	WUESR7        	;// 0x1B15   Wake-Up Edge Sense Register 7
extern ECReg    WUESR8          ;// 0x1B19   Wake-Up Edge Sense Register 8
extern ECReg    WUESR9          ;// 0x1B1D   Wake-Up Edge Sense Register 9
extern ECReg    WUESR10         ;// 0x1B21   Wake-Up Edge Sense Register 10
extern ECReg    WUESR11         ;// 0x1B25   Wake-Up Edge Sense Register 11
extern ECReg    WUESR12         ;// 0x1B29   Wake-Up Edge Sense Register 12
extern ECReg    WUESR13         ;// 0x1B2D   Wake-Up Edge Sense Register 13
extern ECReg    WUESR14         ;// 0x1B31   Wake-Up Edge Sense Register 14
extern ECReg	WUENR1        	;// 0x1B08	 Wake-Up Enable Register 1
extern ECReg	WUENR2       	;// 0x1B09	 Wake-Up Enable Register 2
extern ECReg	WUENR3       	;// 0x1B0A	 Wake-Up Enable Register 3
extern ECReg	WUENR4			;// 0x1B0B	 Wake-Up Enable Register 4
extern ECReg	WUENR6			;// 0x1B12	 Wake-Up Enable Register 6
extern ECReg	WUENR7			;// 0x1B16   Wake-Up Enable Register 7
extern ECReg    WUENR8          ;// 0x1B1A   Wake-Up Enable Register 8
extern ECReg    WUENR9          ;// 0x1B1E   Wake-Up Enable Register 9

//-----------------------------------------------------------------------------
// (1Cxxh) SMBus Interface (SMB) 
//-----------------------------------------------------------------------------
extern ECReg	HOSTA_A      	;// 0x1C00	 Host Status A
extern ECReg	HOSTA_B      	;// 0x1C11	 Host Status B
extern ECReg	HOSTA_C      	;// 0x1C29	 Host Status C
extern ECReg	HOSTA_D      	;// 0x1C35	 Host Status D
#define HOSTA_BDS           BIT(7)  // Byte Done Status
#define HOSTA_TMOE    	    BIT(6)  // Time-out Error
#define HOSTA_NACK   	    BIT(5)  // Not Response ACK
#define HOSTA_FAIL  	    BIT(4)  // Fail
#define HOSTA_BSER    	    BIT(3)  // Bus Error
#define HOSTA_DVER    	    BIT(2)  // Device Error
#define HOSTA_FINTR   	    BIT(1)  // Finish Interrupt
#define HOSTA_HOBY  	    BIT(0)  // Host Busy

extern ECReg	HOCTL_A       	;// 0x1C01	 Host Control A
extern ECReg	HOCTL_B       	;// 0x1C12	 Host Control B
extern ECReg	HOCTL_C       	;// 0x1C2A	 Host Control C
extern ECReg	HOCTL_D         ;// 0x1C36   Host Control D
#define HOCTL_PEC_EN        BIT(7)  // PEC Enable
#define HOCTL_SRT    	    BIT(6)  // Start
#define HOCTL_LABY   	    BIT(5)  // Last Byte
#define HOCTL_SMCD2  	    BIT(4)  // SMBus Command
#define HOCTL_SMCD1    	    BIT(3)  // SMBus Command
#define HOCTL_SMCD0    	    BIT(2)  // SMBus Command
#define HOCTL_KILL   	    BIT(1)  // Kill
#define HOCTL_INTREN  	    BIT(0)  // Host Interrupt Enable

extern ECReg	HOCMD_A       	;// 0x1C02	 Host Command A
extern ECReg	HOCMD_B       	;// 0x1C13	 Host Command B
extern ECReg	HOCMD_C       	;// 0x1C2B	 Host Command C
extern ECReg	HOCMD_D       	;// 0x1C37   Host Command D
extern ECReg	TRASLA_A      	;// 0x1C03	 Transmit Slave Address A
extern ECReg	TRASLA_B      	;// 0x1C14	 Transmit Slave Address B
extern ECReg	TRASLA_C      	;// 0x1C2C	 Transmit Slave Address C
extern ECReg	TRASLA_D      	;// 0x1C38   Transmit Slave Address D
extern ECReg	D0REG_A       	;// 0x1C04	 Host Data 0 A
extern ECReg	D0REG_B       	;// 0x1C15	 Host Data 0 B
extern ECReg	D0REG_C       	;// 0x1C2D	 Host Data 0 C
extern ECReg	D0REG_D       	;// 0x1C39   Host Data 0 D
extern ECReg	D1REG_A       	;// 0x1C05	 Host Data 1 A
extern ECReg	D1REG_B      	;// 0x1C16	 Host Data 1 B
extern ECReg	D1REG_C      	;// 0x1C2E	 Host Data 1 C
extern ECReg	D1REG_D      	;// 0x1C3A	 Host Data 1 D
extern ECReg	HOBDB_A       	;// 0x1C06	 Host Block Data Byte A
extern ECReg	HOBDB_B        	;// 0x1C17	 Host Block Data Byte B
extern ECReg	HOBDB_C        	;// 0x1C2F	 Host Block Data Byte C
extern ECReg	HOBDB_D        	;// 0x1C3B	 Host Block Data Byte D
extern ECReg	PECERC_A      	;// 0x1C07	 Packet Error Check A
extern ECReg	PECERC_B    	;// 0x1C18	 Packet Error Check B
extern ECReg	PECERC_C    	;// 0x1C30	 Packet Error Check C
extern ECReg	PECERC_D    	;// 0x1C3C	 Packet Error Check D

extern ECReg	RESLADR_A		;// 0x1C08   Receive Slave Adress A
extern ECReg	RESLADR_B		;// 0x1C19   Receive Slave Adress B
extern ECReg	RESLADR_2_A		;// 0x1C3F   Receive Slave Adress_2 A
extern ECReg	RESLADR_2_B		;// 0x1C44   Receive Slave Adress_2 B
extern ECReg	SLDA_A			;// 0x1C09   Slave Data A
extern ECReg	SLDA_B			;// 0x1C1A   Slave Data B

extern ECReg	SMBPCTL_A      	;// 0x1C0A	 SMBUS Pin Control A
extern ECReg	SMBPCTL_B      	;// 0x1C1B	 SMBUS Pin Control B
extern ECReg	SMBPCTL_C      	;// 0x1C31	 SMBUS Pin Control C
extern ECReg	SMBPCTL_D      	;// 0x1C3D   SMBUS Pin Control D

extern ECReg	SLSTA_A			;// 0x1C0B   Slave Status A
extern ECReg	SLSTA_B			;// 0x1C1C   Slave Status B
extern ECReg	SICR_A			;// 0x1C0C   Slave Interrupt Control A
extern ECReg	SICR_B			;// 0x1C1D   Slave Interrupt Control B
extern ECReg	NDADR_A			;// 0x1C0D   Notify Device Adress A
extern ECReg	NDADR_B			;// 0x1C1E   Notify Device Adress B
extern ECReg	NDLB_A			;// 0x1C0E   Notify Data Low Byte A
extern ECReg	NDLB_B			;// 0x1C1F   Notify Data Low Byte B
extern ECReg	NDHB_A			;// 0x1C0F   Notify Data High Byte A
extern ECReg	NDHB_B			;// 0x1C20   Notify Data High Byte B

extern ECReg	HOCTL2_A      	;// 0x1C10	 Host Control2 A
extern ECReg	HOCTL2_B      	;// 0x1C21	 Host Control2 B
extern ECReg	HOCTL2_C      	;// 0x1C32	 Host Control2 C
extern ECReg	HOCTL2_D      	;// 0x1C3E	 Host Control2 D
extern ECReg	SMB4P7USL   	;// 0x1C22	 4.7 £gs Low Register
extern ECReg	SMB4P0USH   	;// 0x1C23	 4.7 £gs High Register
extern ECReg	SMB300NS  		;// 0x1C24	 300 ns Register
extern ECReg	SMB250NS  		;// 0x1C25	 250 ns Register
extern ECReg	SMB25MS   		;// 0x1C26	 25 ms Register
extern ECReg	SMB45P3USL 		;// 0x1C27	 45.3 £gs Low Register
extern ECReg	SMBS4P3USH 		;// 0x1C28	 45.3 £gs High Register
extern ECReg	SMB4P7A4P0H		;// 0x1C33	 4.7 £gs and 4.0 £gs High Register

extern ECReg	SLVISEL			;// 0x1C34   Slave Interface Select
extern ECReg	SCLKTS_A		;// 0x1C40   SMCLK Timing Setting Register A
extern ECReg	SCLKTS_B		;// 0x1C41   SMCLK Timing Setting Register B
extern ECReg	SCLKTS_C		;// 0x1C42   SMCLK Timing Setting Register C
extern ECReg	SCLKTS_D		;// 0x1C43   SMCLK Timing Setting Register D

extern ECReg    SMBFFCTRL1      ;// 0x1C45   SMbus FIFO Control 1 Register
extern ECReg    SMBFFSTS1       ;// 0x1C46   SMBus FIFO Status 1 Register
extern ECReg    SMBFFCTRL2      ;// 0x1C47   SMBus FIFO Control 2 Register
extern ECReg    SMBFFSTS2       ;// 0x1C48   SMBus FIFO Status 2 Register

extern ECReg   HONACKSRC_A      ;// 0x1C49;  HOST Nack Source A
extern ECReg   HONACKSRC_B      ;// 0x1C4A;  HOST Nack Source	B
extern ECReg   HONACKSRC_C      ;// 0x1C4B;  HOST Nack Source	C
extern ECReg   HONACKSRC_D      ;// 0x1C4C;  HOST Nack Source	D
extern ECReg   SLVFTH           ;// 0x1C4D;  Slave FIFO Threshold
extern ECReg   MSTHTH           ;// 0x1C4F;  Master FIFO Threshold
extern ECReg   MFTHEN           ;// 0x1C50;  Master FIFO Threshold Enable
extern ECReg   MFTISTA          ;// 0x1C51;  Master FIFO Threshold Interrupt Status
extern ECReg   SFTHEN           ;// 0x1C58;  Slave FIFO Threshold Enable
extern ECReg   SFTISTA          ;// 0x1C59;  Slave FIFO Threshold Interrupt Status
extern ECReg   SFFCTL           ;// 0x1C5E;  Slave FIFO Control Register
extern ECReg   SFFSTA           ;// 0x1C5F;  Slave FIFO Status
extern ECReg   I2CW2RF          ;// 0x1C69;  I2C Wr to Rd FIFO Register
extern ECReg   IWRFISTA         ;// 0x1C6A;  I2C Wr to Rd FIFO Interrupt Status
//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS) 
//-----------------------------------------------------------------------------
extern ECReg	KSOL          	;// 0x1D00	 Keyboard Scan Out
extern ECReg	KSOH1          	;// 0x1D01	 Keyboard Scan Out
extern ECReg	KSOCTRL      	;// 0x1D02	 Keyboard Scan Out Control
extern ECReg	KSOH2			;// 0x1D03	 Keyboard Scan Out
extern ECReg	KSI           	;// 0x1D04	 Keyboard Scan In
extern ECReg	KSICTRL       	;// 0x1D05	 Keyboard Scan In Control
extern ECReg	KSIGCTRL       	;// 0x1D06   Keyboard Scan In [7:0] GPIO Control
extern ECReg	KSIGOEN       	;// 0x1D07   Keyboard Scan In [7:0] GPIO Output Enable
extern ECReg	KSIGDAT       	;// 0x1D08   Keyboard Scan In [7:0] GPIO DATA
extern ECReg	KSIGDMRR       	;// 0x1D09   Keyboard Scan In [7:0] GPIO DATA Mirror
extern ECReg	KSOHGCTRL       ;// 0x1D0A   Keyboard Scan Out [15:8] GPIO Control
extern ECReg	KSOHGOEN       	;// 0x1D0B   Keyboard Scan Out [15:8] GPIO Output Enable
extern ECReg	KSOHGDMRR       ;// 0x1D0C   Keyboard Scan Out [15:8] GPIO DATA Mirror
extern ECReg	KSOLGCTRL       ;// 0x1D0D   Keyboard Scan Out [7:0] GPIO Control
extern ECReg	KSOLGOEN       	;// 0x1D0E   Keyboard Scan Out [7:0] GPIO Output Enable
extern ECReg	KSOLGDMRR       ;// 0x1D0F   Keyboard Scan Out [7:0] GPIO DATA Mirror
extern ECReg    KSO0LSDR        ;// 0x1D10   KSO 0 Low Scan Data Register
extern ECReg    KSO1LSDR        ;// 0x1D11   KSO 1 Low Scan Data Register
extern ECReg    KSO2LSDR        ;// 0x1D12   KSO 2 Low Scan Data Register
extern ECReg    KSO3LSDR        ;// 0x1D13   KSO 3 Low Scan Data Register
extern ECReg    KSO4LSDR        ;// 0x1D14   KSO 4 Low Scan Data Register
extern ECReg    KSO5LSDR        ;// 0x1D15   KSO 5 Low Scan Data Register
extern ECReg    KSO6LSDR        ;// 0x1D16   KSO 6 Low Scan Data Register
extern ECReg    KSO7LSDR        ;// 0x1D17   KSO 7 Low Scan Data Register
extern ECReg    KSO8LSDR        ;// 0x1D18   KSO 8 Low Scan Data Register
extern ECReg    KSO9LSDR        ;// 0x1D19   KSO 9 Low Scan Data Register
extern ECReg    KSO10LSDR       ;// 0x1D1A   KSO 10 Low Scan Data Register
extern ECReg    KSO11LSDR       ;// 0x1D1B   KSO 11 Low Scan Data Register
extern ECReg    KSO12LSDR       ;// 0x1D1C   KSO 12 Low Scan Data Register
extern ECReg    KSO13LSDR       ;// 0x1D1D   KSO 13 Low Scan Data Register
extern ECReg    KSO14LSDR       ;// 0x1D1E   KSO 14 Low Scan Data Register
extern ECReg    KSO15LSDR       ;// 0x1D1F   KSO 15 Low Scan Data Register
extern ECReg    KSO16LSDR       ;// 0x1D20   KSO 16 Low Scan Data Register
extern ECReg    KSO17LSDR       ;// 0x1D21   KSO 17 Low Scan Data Register
extern ECReg    SDC1R           ;// 0x1D22   Scan Data Control 1 Register
#define SDEN        BIT7        // Scan data enable
//#define --        BIT6        // Reserved
#define INTSDVEN    BIT5        // Interrupt from scan data valid enable
//#define --        BIT4        // Reserved
//#define --        BIT3        // Reserved
//---------------------------------
// BIT2 ~ BIT0  Scan loop select
#define SLS_00_Round    0x00
#define SLS_02_Round    0x01
#define SLS_03_Round    0x02
#define SLS_04_Round    0x03
#define SLS_05_Round    0x04
#define SLS_06_Round    0x05
#define SLS_07_Round    0x06
#define SLS_08_Round    0x07

extern ECReg    SDC2R           ;// 0x1D23   Scan Data Control 2 Register
#define KSOPCS1     BIT7        // KSO pin count select
#define KSOPCS0     BIT6        // KSO pin count select
//#define --        BIT5        // Reserved
//#define --        BIT4        // Reserved
//---------------------------------
// BIT3 ~ BIT0  Wait KSO high delay
#define WKSOHDLY_23us   0x00
#define WKSOHDLY_31us   0x01
#define WKSOHDLY_39us   0x02
#define WKSOHDLY_47us   0x03
#define WKSOHDLY_55us   0x04
#define WKSOHDLY_63us   0x05
#define WKSOHDLY_71us   0x06
#define WKSOHDLY_79us   0x07
#define WKSOHDLY_87us   0x08
#define WKSOHDLY_95us   0x09


extern ECReg    SDC3R           ;// 0x1D24   Scan Data Control 3 Register
//---------------------------------
// BIT7 ~ BIT4  Wait KSO low delay
#define WKSOLDLY_11us   (0x00 << 4)
#define WKSOLDLY_13us   (0x01 << 4)
#define WKSOLDLY_15us   (0x02 << 4)
#define WKSOLDLY_17us   (0x03 << 4)
#define WKSOLDLY_19us   (0x04 << 4)
#define WKSOLDLY_21us   (0x05 << 4)
#define WKSOLDLY_23us   (0x06 << 4)
#define WKSOLDLY_25us   (0x07 << 4)
#define WKSOLDLY_27us   (0x08 << 4)
#define WKSOLDLY_29us   (0x09 << 4)
//---------------------------------
// BIT3 ~ BIT0  Spacing delay between rounds
#define SDLYBR_00ms     0x00
#define SDLYBR_01ms     0x01
#define SDLYBR_02ms     0x02
#define SDLYBR_03ms     0x03
#define SDLYBR_04ms     0x04
#define SDLYBR_05ms     0x05
#define SDLYBR_06ms     0x06
#define SDLYBR_07ms     0x07
#define SDLYBR_08ms     0x08
#define SDLYBR_09ms     0x09
#define SDLYBR_10ms     0x0A
#define SDLYBR_11ms     0x0B
#define SDLYBR_12ms     0x0C
#define SDLYBR_13ms     0x0D
#define SDLYBR_14ms     0x0E
#define SDLYBR_15ms     0x0F

extern ECReg    SDSR           ;// 0x1D25   Scan Data Control 4 Register
//#define --        BIT7        // Reserved
//#define --        BIT6        // Reserved
//#define --        BIT5        // Reserved
//#define --        BIT4        // Reserved
//#define --        BIT3        // Reserved
//#define --        BIT2        // Reserved
//#define --        BIT1        // Reserved
#define SDV         BIT0        // Scan data valid     

//-----------------------------------------------------------------------------
// (1Exxh) EC Clock and Power Management controller (ECPM) 
//-----------------------------------------------------------------------------
extern ECReg	CGCTRL1R    	;// 0x1E01	 Clock Gating Control 1
extern ECReg	CGCTRL2R      	;// 0x1E02	 Clock Gating Control 2
extern ECReg	CGCTRL3R		;// 0x1E05	 Clock Gating Control 3
extern ECReg	PLLCTRL        	;// 0x1E03	 PLL Control
extern ECReg	AUTOCG			;// 0x1E04	 Auto Clock Gating
extern ECReg	PLLFREQR		;// 0x1E06	 PLL Frequency
extern ECReg	PLLSSCR			;// 0x1E07   PLL Frequency
extern ECReg    PLLCSS          ;// 0x1E08   PLL Clock Source Status
extern ECReg    CGCTRL4R        ;// 0x1E09   Clock Gating Control 4 Register
//-----------------------------------------------------------------------------
// (1Fxxh) External Timer & External Watchdog (ETWD) 
//-----------------------------------------------------------------------------
extern ECReg	ETWCFG        	;// 0x1F01	 External Timer/WDT Configuration Register
extern ECReg	ETPSR         	;// 0x1F02	 External Timer Prescaler Register
extern ECReg	ETCNTLHR     	;// 0x1F03	 External Timer Counter High Byte
extern ECReg	ETCNTLLR      	;// 0x1F04	 External Timer Counter Low Byte
extern ECReg	ETWCTRL      	;// 0x1F05	 External Timer/WDT Control Register
extern ECReg	EWDCNTLR      	;// 0x1F06	 External WDT Counter Low Byte
extern ECReg	EWDCNTHR		;// 0x1F09	 External WDT Counter High Byte
extern ECReg	EWDKEYR      	;// 0x1F07	 External WDT Key Register

extern ECReg	ET2PSR      	;// 0x1F0A   External Timer 2 Prescaler Register
extern ECReg	ET2CNTLHR      	;// 0x1F0B   External Timer 2 Counter High Byte
extern ECReg	ET2CNTLLR      	;// 0x1F0C   External Timer 2 Counter Low Byte
extern ECReg	ET2CNTLH2R		;// 0x1F0E   External Timer 2 Counter High Byte 

//-----------------------------------------------------------------------------
// General Control (GCTRL) (20xxh)
//-----------------------------------------------------------------------------
extern ECReg	ECHIPID1		;// 0x2000	 Chip ID Byte 1
extern ECReg	ECHIPID2		;// 0x2001	 Chip ID Byte 2
extern ECReg	ECHIPVER		;// 0x2002	 Chip Version
extern ECReg	IDR				;// 0x2004	 Identify Input Register
extern ECReg	RSTS			;// 0x2006	 Reset Status
extern ECReg	RSTC1			;// 0x2007	 Reset Control 1
#define RSMFI               BIT(7)	// Reset SMFI
#define RINTC               BIT(6)	// Reset INTC
#define REC2I               BIT(5)	// Reset EC2I
#define RKBC                BIT(4)	// Reset KBC
#define RSWUC               BIT(3)	// Reset SWUC
#define RPMC                BIT(2)	// Reset PMC
#define RGPIO               BIT(1)	// Reset GPIO
#define RPWM                BIT(0)	// Reset PWM

extern ECReg	RSTC2			;// 0x2008	 Reset Control 2
#define RADC                BIT(7)	// Reset ADC
#define RDAC                BIT(6)	// Reset DAC
#define RWUC                BIT(5)	// Reset WUC
#define RKBS                BIT(4)	// Reset KBS
//#define --                BIT(3)	// Reserved
#define REGPC               BIT(2)	// Reset EGPC
#define RCIR                BIT(1)	// Reset CIR
//#define --                BIT(0)	// Reserved

extern ECReg	RSTC3			;// 0x2009	 Reset Control 3
//#define --                BIT(7)	// Reserved
#define RPS23               BIT(6)	// Reset PS/2 Channel 3
#define RPS22               BIT(5)	// Reset PS/2 Channel 2
#define RPS21               BIT(4)	// Reset PS/2 Channel 1     //To reset the logic of PS/2 shared with all channels, write 1111b to bit 7-4 at the
                                                                // same time and writing 0111b is reserved.
#define RSMBD               BIT(3)	// Reset SMBus Channel D
#define RSMBC               BIT(2)	// Reset SMBus Channel C
#define RSMBB               BIT(1)	// Reset SMBus Channel B
#define RSMBA               BIT(0)	// Reset SMBus Channel A    //To reset the logic of SMBus shared with all channels, write 1111b to bit 3-0 at
                                                                //the same time and writing 0111b is reserved.

extern ECReg	RSTC4			;// 0x2011   Reset Control 4
//#define --                BIT(7)	// Reserved
//#define --                BIT(6)	// Reserved
//#define --                BIT(5)	// Reserved
#define RPECI               BIT(4)	// Reset PECI
#define RTMR                BIT(3)	// Reset TMR
#define RUART2              BIT(2)	// Reset UART2
#define RUART1              BIT(1)	// Reset UART1
#define RSPI                BIT(0)	// Reset SPI
extern ECReg	RSTDMMC			;// 0x2010   Reset Control DMMC
extern ECReg	BADRSEL			;// 0x200A	 Base Address Select
extern ECReg	WNCKR			;// 0x200B	 Wait Next Clock Rising
extern ECReg	OSCTRL			;// 0x200C	 Oscillator Control Register
extern ECReg	SPCTRL1			;// 0x200D	 Special Control 1
extern ECReg	RSTCH			;// 0x200E	 Reset Control Host Side
extern ECReg	GENIRQ			;// 0x200F	 Generate IRQ
extern ECReg	SPECTRL2		;// 0x2012   Special Control 2
extern ECReg	SPECTRL3		;// 0x2016   Special Control 3

extern ECReg	PI2ECH			;// 0x2014   Port I2EC High-Byte Register
extern ECReg	PI2ECL			;// 0x2015   Port I2EC Low-Byte Register
extern ECReg	BINTADDR0R		;// 0x2019   BRAM Interrupt Address 0 Register
extern ECReg	BINTADDR1R		;// 0x201A   BRAM Interrupt Address 1 Register
extern ECReg	BINTCTRLR		;// 0x201B   BRAM Interrupt Control Register
extern ECReg    SPCTRL4         ;// 0x201C   Special Control 4

extern ECReg    SHA1HASHCTRLR   ;// 0x202D   SHA1 Hash Control Register
extern ECReg    SHA1HBADDR      ;// 0x202E   SHA1 Hash Base Address Register
//-----------------------------------------------------------------------------
// (21xxh) External GPIO Controller (EGPC) 
//-----------------------------------------------------------------------------
extern ECReg	EADDR			;// 0x2100	 External GPIO Address Register
extern ECReg	EDAT			;// 0x2101	 External GPIO Data Register
extern ECReg	ECNT			;// 0x2102	 External GPIO Control Register
extern ECReg	ESTS			;// 0x2103	 External GPIO Status Register

//-----------------------------------------------------------------------------
// (22xxh) Battery-Backed SRAM (BRAM) 
//-----------------------------------------------------------------------------
extern ECReg	BRAM[]			;// 0x2280	 64 bytes bram

//-----------------------------------------------------------------------------
// (23xxh) Consumer IR (CIR) 
//-----------------------------------------------------------------------------
extern ECReg	C0DR			;// 0x2300	 CIR Data Register
extern ECReg	C0MSTCR			;// 0x2301 	 CIR Master Control Register
#define	CIR_CTXSEL		    BIT(7)	// CTX Channel Select
#define	CIR_CRXSEL		    BIT(6)	// CRX Channel Select
#define	CIR_ILSEL		    BIT(5)	// Internal Loopback Select
#define	CIR_ILE			    BIT(4)	// Internal Loopback Enable
#define	CIR_FIFOTL1		    BIT(3)	// FIFO Threshold Level
#define	CIR_FIFOTL0		    BIT(2)	// FIFO Threshold Level
#define	CIR_FIFOCLR		    BIT(1)	// FIFO Clear
#define	CIR_RESET		    BIT(0)	// RESET

extern ECReg	C0IER			;// 0x2302 	 CIR Interrupt Enable Register
extern ECReg	C0IIR			;// 0x2303	 CIR Interrupt Identification Register
extern ECReg	C0CFR			;// 0x2304	 CIR Carrier Frequency Register
extern ECReg	C0RCR			;// 0x2305	 CIR Receive Control Register
#define	CIR_RXEN		    BIT(7)	// Receiver Enable
//#define	CIR_		    BIT(6)	// Reserved
#define	CIR_RDWOS		    BIT(5)	// Receiver Data Without Sync.
#define	CIR_RXEND		    BIT(4)	// Receiver Demodulation Enable
#define	CIR_RXACT		    BIT(3)	// Receiver Active
#define	CIR_RXDCR2		    BIT(2)	// Receiver Demodulation Carrier Range
#define	CIR_RXDCR1		    BIT(1)	// Receiver Demodulation Carrier Range
#define	CIR_RXDCR0		    BIT(0)	// Receiver Demodulation Carrier Range

extern ECReg	C0TCR			;// 0x2306	 CIR Transmitter Register
extern ECReg	C0SCK			;// 0x2307	 CIR for sleep mode
#define	DLLOCK				BIT(7)	// DLL Lock
#define	BRCM2				BIT(6)	// Baud Rate Count Mode
#define	BRCM1				BIT(5)	// Baud Rate Count Mode
#define	BRCM0				BIT(4)	// Baud Rate Count Mode
#define	DLLTE				BIT(3)	// DLL Test Enable
#define	DLL1P8E				BIT(2)	// DLL 1.8432M Enable
#define	TXDCKG				BIT(1)	// TXD Clock Gating
#define	SCKS				BIT(0)	// Slow Clock Select

extern ECReg	C0BDLR			;// 0x2308	 CIR Baud Rate Divisor Low Byte Register
extern ECReg	C0BDHR			;// 0x2309	 CIR Baud Rate Divisor High Byte Register
extern ECReg	C0TFSR			;// 0x230A	 CIR Transmitter FIFO Status Register
extern ECReg	C0RFSR			;// 0x230B	 CIR Receiver FIFO Status Register
extern ECReg	C0WCSSR			;// 0x230C	 CIR Wakeup Code Set Select Register
extern ECReg	C0WCL			;// 0x230D	 CIR Wakeup Code Length Register
extern ECReg	C0WCR			;// 0x230E	 CIR Wakeup Code Read/Write Register
extern ECReg	C0WPS			;// 0x230F	 CIR Wakeup Code Power Control/Status Register
extern ECReg	CSCRR			;// 0x2310	 CIR Scratch Register

//-----------------------------------------------------------------------------
// (25xxh) Debugger (DBGR) 
//-----------------------------------------------------------------------------
extern ECReg 	BKA1L           ;// 0x2510   Trigger 1 Address Low Byte Register
extern ECReg 	BKA1M           ;// 0x2511   Trigger 1 Address Middle Byte Register
extern ECReg 	BKA1H           ;// 0x2512   Trigger 1 Address High Byte Register
extern ECReg 	BKA2L           ;// 0x2513   Trigger 2 Address Low Byte Register
extern ECReg 	BKA2M           ;// 0x2514   Trigger 2 Address Middle Byte Register
extern ECReg 	BKA2H           ;// 0x2515   Trigger 2 Address High Byte Register
extern ECReg 	BKA3L           ;// 0x2516   Trigger 3 Address Low Byte Register
extern ECReg 	BKA3M           ;// 0x2517   Trigger 3 Address Middle Byte Register
extern ECReg 	BKA3H           ;// 0x2518   Trigger 3 Address High Byte Register

//-----------------------------------------------------------------------------
// (26xxh) Serial Peripheral Interface (SSPI)
//-----------------------------------------------------------------------------
extern ECReg   SPIDATA          ;   // 0x2600  SPI Data Register
extern ECReg   SPICTRL1         ;   // 0x2601  SPI Control Register 1
#define CHPOL				BIT(7)	// Chip Select Polarity
#define CLPOL               BIT(6)  // Clock Polarity
#define CLPHS               BIT(5)  // Clock Phase
#define SCKFREQ2            BIT(4)
#define SCKFREQ1            BIT(3)
#define SCKFREQ0            BIT(2)  // SSCK Frequency
#define NTREN               BIT(1)  // Interrupt Enable
#define WIRECH0             BIT(0)  // Device0 3-Wire Mode, 0: Disable (4-wire), 1: Enable (3-wire)

extern ECReg   SPICTRL2        ;    // 0x2602  SPI Control Register 2
#define HBANK               BIT(7)	// Host Side Bank
#define DEVBUSYPOL          BIT(6)	// Device Busy Polarity
#define BYTEWIDTH2          BIT(5)  // Byte Width
#define BYTEWIDTH1          BIT(4)  // Byte Width
#define BYTEWIDTH0          BIT(3)  // Byte Width
#define CHRW                BIT(2)  // Channel Read/Write Cycle
#define BLKSEL              BIT(1)  // Block Select
#define WIRECH1             BIT(0)  // Device1 3-Wire Mode, 0: Disable (4-wire), 1: Enable (3-wire)

extern ECReg   SPICTRL3        ;    // 0x2604  SPI Control Register 3
#define DEVBUSYMODE         BIT(3)  // Device Busy Mode
#define CSPOLSEL            BIT(2)  // Chip Select Polarity Select
#define CHPOL1              BIT(1)  // Chip Select Polarity 1
#define BUSYNOCLK           BIT(0)  // No BUSY Clock

extern ECReg   SPISTS           ;   // 0x2603  SPI Start and End Status Register
#define WAITBUSYSTART       BIT(7)  // Wait Busy Start Signal
#define DEVBUSY             BIT(6)  // Device Busy Signal
#define TRANEND             BIT(5)  // SPI Transmission End
#define CH0START            BIT(4)  // Channel 0 Start Signal
#define CH1START            BIT(3)  // Channel 1 Start Signal
#define TRANIP              BIT(2)  // Transfer In Progress
#define TRANENDIF           BIT(1)  // Transfer End Flag
#define SPIBUSY             BIT(0)  // SPI Busy

//-----------------------------------------------------------------------------
// (27xxh) Extern Serial Port (UART1) 
//-----------------------------------------------------------------------------
extern ECReg 	UART1_RBR		;// 0x2700  Receiver Buffer Register
extern ECReg 	UART1_IER		;// 0x2701  Interrupt Enable Register
extern ECReg 	UART1_IIR		;// 0x2702  Interrupt Identification Register
extern ECReg 	UART1_LCR		;// 0x2703  Line Control Register
extern ECReg 	UART1_MCR		;// 0x2704  Modem Control Register
extern ECReg 	UART1_LSR		;// 0x2705  Line Status Register
extern ECReg 	UART1_MSR		;// 0x2706  Modem Status Register
extern ECReg 	UART1_SCR		;// 0x2707  Scratch Pad Register
extern ECReg 	UART1_ECSPMR	;// 0x2708  EC Serial Port Mode Register

//-----------------------------------------------------------------------------
// (28xxh) Extern Serial Port (UART2) 
//-----------------------------------------------------------------------------
extern ECReg 	UART2_RBR		;// 0x2800  Receiver Buffer Register
extern ECReg 	UART2_IER		;// 0x2801  Interrupt Enable Register
extern ECReg 	UART2_IIR		;// 0x2802  Interrupt Identification Register
extern ECReg 	UART2_LCR		;// 0x2803  Line Control Register
extern ECReg 	UART2_MCR		;// 0x2804  Modem Control Register
extern ECReg 	UART2_LSR		;// 0x2805  Line Status Register
extern ECReg 	UART2_MSR		;// 0x2806  Modem Status Register
extern ECReg 	UART2_SCR		;// 0x2807  Scratch Pad Register
extern ECReg 	UART2_ECSPMR	;// 0x2808  EC Serial Port Mode Register

//-----------------------------------------------------------------------------
// (29xxh) 8 Bit Timer (TMR)
//-----------------------------------------------------------------------------
extern ECReg	PRSC			;// 0x2900  TMR Prescaler Register
extern ECReg	GCSMS			;// 0x2901  Group Clock Source and Mode Select Register
extern ECReg	CTR_A0			;// 0x2902  A0 Cycle Time Register
extern ECReg	CTR_A1			;// 0x2903  A1 Cycle Time Register
extern ECReg	CTR_B0			;// 0x2904  B0 Cycle Time Register
extern ECReg	CTR_B1			;// 0x2905  B1 Cycle Time Register
extern ECReg	DCR_A0			;// 0x2906  A0 Duty Time Register
extern ECReg	DCR_A1			;// 0x2907  A1 Duty Time Register
extern ECReg	DCR_B0			;// 0x2908  B0 Duty Time Register
extern ECReg	DCR_B1			;// 0x2909  B1 Duty Time Register
extern ECReg	CCGSR			;// 0x290A  Channel Clock Group Select Register
extern ECReg	TMRCE			;// 0x290B  TMR Clock Enable Register
extern ECReg	TMEIE			;// 0x290C  TMR Interrupt Enable Register

//-----------------------------------------------------------------------------
// (2Exxh) Consumer Electronics Control (CEC)
//-----------------------------------------------------------------------------
extern ECReg   CECDR            ;// 0x2E00  CEC Data Register
extern ECReg   CECFSTS          ;// 0x2E01  CEC FIFO Status Register
extern ECReg   CECDLA           ;// 0x2E02  CEC Device Logical Address Register
extern ECReg   CECCTRL          ;// 0x2E03  CEC Control Register
extern ECReg   CECSTS           ;// 0x2E04  CEC Status Register
extern ECReg   CECIE            ;// 0x2E05  CEC Interrupt Enable Register
extern ECReg   CECOPSTS         ;// 0x2E06  CEC Operation Status Register
extern ECReg   CECCRH           ;// 0x2E07  CEC Received Header Register

//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC)
//-----------------------------------------------------------------------------
// IR0
//		-					BIT(0)	// -
#define	Int_WKO20			BIT(1)	// WKO[20]
#define	Int_KBCOBFE			BIT(2)	// KBC Output Buffer Empty Interrupt
#define	Int_PMCOBFE			BIT(3)	// PMC Output Buffer Empty Interrupt
#define	Int_SMBUS3			BIT(4)	// SMBUS3 Interrupt	
#define Int_WKINTAD			BIT(5)	// WKINTAD (WKINTA or WKINTD)
#define Int_WKO23			BIT(6)	// WKO[23]
#define Int_PWM				BIT(7)	// PWM Interrupt

// IR1
#define	Int_ADC				BIT(0)	// ADC Interrupt
#define	Int_SMBUS0			BIT(1)	// SMBUS0 Interrupt
#define	Int_SMBUS1			BIT(2)	// SMBUS0 Interrupt
#define	Int_KB				BIT(3)	// KB Matrix Scan Interrupt
#define	Int_WKO26			BIT(4)	// WKO[26]
#define Int_WKINTC			BIT(5)	// WKINTC
#define Int_WKO25			BIT(6)	// WKO[25]
#define Int_CIR				BIT(7)	// CIR Interrupt

// IR2
#define	Int_SMBUS2			BIT(0)	// SMBUS2 Interrupt
#define Int_WKO24			BIT(1)	// WKO[24]
#define	Int_PS2_2			BIT(2)	// PS/2 Interrupt 2
#define	Int_PS2_1			BIT(3)	// PS/2 Interrupt 1
#define	Int_PS2_0			BIT(4)	// PS/2 Interrupt 0
#define	Int_WKO22			BIT(5)	// WKO[22]
#define	SMFIS				BIT(6)	// SMFI Semaphore Interrupt
#define	SMFIL				BIT(7)	// SMFI Lock Error Interrupt

// IR3
#define	Int_KBCIBF			BIT(0)	// KBC Input Buffer Full Interrupt
#define Int_PMCIBF			BIT(1)	// PMC Input Buffer Full Interrupt
#define Int_PMC2OBE         BIT(2)	// PMC2 Output Buffer Empty Intr.
#define Int_PMC2IBF		    BIT(3)	// PMC2 Input Buffer Full Intr.
#define	Int_GINT			BIT(4)	// GINT from function 1 of GPD5
#define	Int_EGPC			BIT(5)	// EGPC Interrupt
#define	Int_EXTimer			BIT(6)	// External Timer Interrupt
#define	Int_WKO21			BIT(7)	// WKO[21]

// IR4
#define	Int_GPINT0			BIT(0)	// GPINT0
#define	Int_GPINT1			BIT(1)	// GPINT1
#define	Int_GPINT2			BIT(2)	// GPINT2
#define	Int_GPINT3			BIT(3)	// GPINT3
#define	Int_CIRGPINT	    BIT(4)	// CIR GPINT
#define	Int_SSPI		    BIT(5)	// SSPI Interrupt
#define	Int_UART1		    BIT(6)	// UART1 Interrupt
#define Int_UART2		    BIT(7)	// UART2 Interrupt

// IR5
//#define   Int_		    BIT(0)	//
//#define	Int_		    BIT(1)	//
//#define	Int_		    BIT(2)	//
//#define	Int_		    BIT(3)	//
//#define	Int_		    BIT(4)	//
//#define	Int_		    BIT(5)	//
//#define	Int_		    BIT(6)	//
//#define	Int_		    BIT(7)	//

// IR6
#define	Int_WKO60			BIT(0)	// WKO[60]
#define	Int_WKO61			BIT(1)	// WKO[61]
#define	Int_WKO62			BIT(2)	// WKO[62]
#define	Int_WKO63			BIT(3)	// WKO[63]
#define	Int_WKO64			BIT(4)	// WKO[64]
#define	Int_WKO65			BIT(5)	// WKO[65]
#define	Int_WKO66			BIT(6)	// WKO[66]
#define	Int_WKO67			BIT(7)	// WKO[67]

// IR7
//#define   Int_		    BIT(0)	//
//#define	Int_		    BIT(1)	//
#define Int_ET2Intr		    BIT(2)	// External Timer 2 Interrupt
#define Int_DeferredSPI     BIT(3)  // Deferred SPI Instruction Interrupt
#define Int_TMRINTA0	    BIT(4)	// TMRINTA0
#define Int_TMRINTA1	    BIT(5)	// TMRINTA1
#define Int_TMRINTB0	    BIT(6)	// TMRINTB0
#define	Int_TMRINTB1	    BIT(7)	// TMRINTB1

// IR8
#define Int_PMC2EXOBE	    BIT(0)	// PMC2EX Output Buffer Empty Intr.
#define	Int_PMC2EXIBF	    BIT(1)	// PMC2EX Input Buffer Full Intr.
#define	Int_PMC3OBE		    BIT(2)	// PMC3 Output Buffer Empty Intr.
#define Int_PMC3IBF			BIT(3)	// PMC3 Input Buffer Full Interrupt
#define Int_PMC4OBE		    BIT(4)	// PMC4 Output Buffer Empty Intr.
#define	Int_PMC4IBF		    BIT(5)	// PMC4 Input Buffer Full Intr.
//#define	Int_		    BIT(6)	//
#define	Int_I2BRAM		    BIT(7)	// I2BRAM Interrupt

// IR9
#define	Int_WKO70			BIT(0)	// WKO[70]
#define	Int_WKO71			BIT(1)	// WKO[71]
#define	Int_WKO72			BIT(2)	// WKO[72]
#define	Int_WKO73			BIT(3)	// WKO[73]
#define	Int_WKO74			BIT(4)	// WKO[74]
#define	Int_WKO75			BIT(5)	// WKO[75]
#define	Int_WKO76			BIT(6)	// WKO[76]
#define	Int_WKO77			BIT(7)	// WKO[77]

// IR10
//#define   Int_            BIT(0)
//#define   Int_            BIT(1)
#define Int_CEC             BIT(2)  // CEC Interrupt
#define Int_H2RAMLPC        BIT(3)  // H2RAM LPC Trigger
//#define   Int_            BIT(4)
#define Int_WKO88           BIT(5)  // WKO[88]
#define Int_WKO89           BIT(6)  // WKO[89]
#define Int_WKO90           BIT(7)  // WKO[90]

// IR11
#define Int_WKO80           BIT(0)  // WKO[80]
#define Int_WKO81           BIT(1)  // WKO[81]
#define Int_WKO82           BIT(2)  // WKO[82]
#define Int_WKO83           BIT(3)  // WKO[83]
#define Int_WKO84           BIT(4)  // WKO[84]
#define Int_WKO85           BIT(5)  // WKO[85]
#define Int_WKO86           BIT(6)  // WKO[86]
#define Int_WKO87           BIT(7)  // WKO[87]

// IR12
#define Int_WKO91           BIT(0)  // WKO[91]
#define Int_WKO92           BIT(1)  // WKO[92]
#define Int_WKO93           BIT(2)  // WKO[93]
#define Int_WKO94           BIT(3)  // WKO[94]
#define Int_WKO95           BIT(4)  // WKO[95]
#define Int_WKO96           BIT(5)  // WKO[96]
#define Int_WKO97           BIT(6)  // WKO[97]
#define Int_WKO98           BIT(7)  // WKO[98]

// IR13
#define Int_WKO99           BIT(0)  // WKO[99]
#define Int_WKO100          BIT(1)  // WKO[100]
#define Int_WKO101          BIT(2)  // WKO[101]
#define Int_WKO102          BIT(3)  // WKO[102]
#define Int_WKO103          BIT(4)  // WKO[103]
#define Int_WKO104          BIT(5)  // WKO[104]
#define Int_WKO105          BIT(6)  // WKO[105]
#define Int_WKO106          BIT(7)  // WKO[106]

// IR14
#define Int_WKO107          BIT(0)  // WKO[107]
#define Int_WKO108          BIT(1)  // WKO[108]
#define Int_WKO109          BIT(2)  // WKO[109]
#define Int_WKO110          BIT(3)  // WKO[110]
#define Int_WKO111          BIT(4)  // WKO[111]
#define Int_WKO112          BIT(5)  // WKO[112]
#define Int_WKO113          BIT(6)  // WKO[113]
#define Int_WKO114          BIT(7)  // WKO[114]

// IR15
#define Int_WKO115          BIT(0)  // WKO[115]
#define Int_WKO116          BIT(1)  // WKO[116]
#define Int_WKO117          BIT(2)  // WKO[117]
#define Int_WKO118          BIT(3)  // WKO[118]
#define Int_WKO119          BIT(4)  // WKO[119]
#define Int_WKO120          BIT(5)  // WKO[120]
#define Int_WKO121          BIT(6)  // WKO[121]
#define Int_WKO122          BIT(7)  // WKO[122]

// IR16
#define Int_WKO128          BIT(0)  // WKO[128]
#define Int_WKO129          BIT(1)  // WKO[129]
#define Int_WKO130          BIT(2)  // WKO[130]
#define Int_WKO131          BIT(3)  // WKO[131]
#define Int_WKO132          BIT(4)  // WKO[132]
#define Int_WKO133          BIT(5)  // WKO[133]
#define Int_WKO134          BIT(6)  // WKO[134]
//#define Int_              BIT(7)

// IR18
//#define Int_              BIT(0)
//#define Int_              BIT(1)
//#define Int_              BIT(2)
//#define Int_              BIT(3)
//#define Int_              BIT(4)
#define Int_PMC5OBE         BIT(5)  // PMC5 Output Buffer Empty Intr.
#define Int_PMC5IBE         BIT(6)  // PMC5 Input Buffer Full Intr.
#define Int_VCI             BIT(7)  // Voltage Compare Interrupt
//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge) 
//-----------------------------------------------------------------------------
// Lock Super I/O Host Access Register
#define	LKCFG				BIT(0)	// Lock PNPCFG Registers Host Access

// Super I/O Access Lock Violation Register
#define	CFGLV				BIT(0)	// PNPCFG Register Lock Violation

// EC to I-Bus Modules Access Enable Register
#define	SWUCAE				BIT(2)	// Mobile System Wake-Up Control Access Enable
#define	CFGAE				BIT(0)	// PNPCFG Register EC Access Enable

// I-Bus Control Register
#define	CWIB				BIT(2)	// EC Write to I-Bus
#define	CRIB				BIT(1)	// EC Read from I-Bus
#define CSAE				BIT(0)	// EC to I-Bus Access Enabled

//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC) 
//-----------------------------------------------------------------------------
// KBC Host Interface Control Register
#define	PM1ICIE				BIT(6)	// PM Channel 1 Input Buffer Full 8032 Interrupt Enable
#define	PM1OCIE				BIT(5)	// PM Channel 1 Output Buffer Empty 8032 Interrupt Enable
#define	PM1HIE				BIT(4)	// PM Channel 1 Host Interface Interrupt Enable
#define	IBFCIE				BIT(3)	// Input Buffer Full 8032 Interrupt Enable
#define OBECIE				BIT(2)	// Output Buffer Empty 8032 Interrupt Enable
#define	OBFMIE				BIT(1)	// Output Buffer Full Mouse Interrupt Enable
#define	OBFKIE 				BIT(0)	// Output Buffer Full Keyboard Interrupt Enable

// KBC Interrupt Control Register
#define	IRQNP				BIT(6)	// Interrupt Negative Polarity
#define	IRQ11B				BIT(2)	// IRQ11 Control Bit
#define	IRQ12B				BIT(1)	// IRQ12 Control Bit
#define	IRQ1B				BIT(0)	// IRQ1 Control Bit

// KBC Host Interface Keyboard/Mouse Status Register
#define PARE    			BIT(7)	// Programming Data
#define GTIM    			BIT(6)	// Programming Data
#define AOBF    			BIT(5)	// Programming Data
#define KEYL    			BIT(4)	// Programming Data
#define C_D     			BIT(3)	// Command or data port
#define SYSF    			BIT(2)	// Programming Data (System flag)
#define	IBF					BIT(1)	// Input Buffer Full
#define	OBF					BIT(0)	// Output Buffer Full

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC) 
//-----------------------------------------------------------------------------
// PM Status Register
#define SMIEVT    			BIT(6)
#define SCIEVT   			BIT(5)
#define BURST  				BIT(4)
#define	P_C_D				BIT(3)	// Command or data port
#define	P_IBF				BIT(1)	// Input Buffer Full
#define	P_OBF				BIT(0)	// Output Buffer Full

// PM Control
#define	APM					BIT(7)	// Enhance PM Mode
#define SCINP				BIT(6)	// SCI Negative Polarity
#define	OBEIE				BIT(1)	// Output Buffer Empty Interrupt Enable
#define	IBFIE				BIT(0)	// Input Buffer Full Interrupt Enable

// PM Interrupt Control
#define	SMINP				BIT(6)	// SMI Negative Polarity
#define SCIB				BIT(2)	// Host SCI Control Bit
#define	SMIB				BIT(1)	// Host SMI Control Bit
#define	IRQB				BIT(0)	// Host IRQ Control Bit

// PM Interrupt Enable
#define HWSMIEN				BIT(5)	// Hardware SMI Enable
#define	HWSCIEN				BIT(4)	// Hardware SCI Enable
#define	HWIRQEN				BIT(3)	// Hardware IRQ Enable
#define SMIEN				BIT(2)	// SMI Enable
#define SCIEN				BIT(1)	// SCI Enable
#define IRQEN				BIT(0)	// IRQ Enable

// PM Interrupt Enable
#define	MBXEN				BIT(7)	// Mailbox Enable


//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control Register                           
//-----------------------------------------------------------------------------
// General Control Register
#define	GFLE				BIT(7)	// GPB5 Follow LPCRST# Enable
#define	WUI7EN				BIT(6)	// WUI7 Enabled
#define	WUI6EN				BIT(5)	// WUI6 Enabled
//		-					BIT(4)	// -
//		-					BIT(3)	// -
#define	LPCRSTEN_GPB7		BIT(2)	// LPC Reset is enabled on GPB7
#define	LPCRSTEN_GPD2		BIT(1)	// LPC Reset is enabled on GPD2
//		-					BIT(0)	// -

// Port Control n Registers
#define PM_Input			BIT(7)	// Input
#define PM_Output			BIT(6)	// Outpur
#define PM_ALT				0x00	// Alternate Function
#define PM_PullUp			BIT(2)	// Port Pin Pull Up
#define PM_PullDown			BIT(1)	// Port Pin Pull Down
#define	PM_8mA				0x10	// sourcing/sinking 8mA/8mA
#define	PM_12mA				0x18	// sourcing/sinking 12mA/12mA
#define	PM_16mA				0x38	// sourcing/sinking 16mA/16mA

//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface Register                            			  
//-----------------------------------------------------------------------------
// PS/2 Control Register
#define	DCEN				BIT(4)	// Debounce Circuit Enable
#define	TRMS				BIT(3)	// Transmit,Receive Mode Selection
#define	PSHE				BIT(2)	// PS/2 Hardware Enable
#define	CCLK				BIT(1)	// Control CLK Line
#define	CDAT				BIT(0)	// Control DATA Line

// PS/2 Interrupt Control Register
#define	TDIE				BIT(2)	// Transaction Done Interrupt Enable
#define	SIE					BIT(1)	// Start Interrupt Enable
#define	SMIE				BIT(0)	// Software Mode Interrupt Enable

// PS/2 Status Register
#define	FER					BIT(5)	// Frame Error
#define	PER					BIT(4)	// Parity Error
#define	TDS					BIT(3)	// Transaction Done Status
#define	SS					BIT(2)	// Start Status
#define	CLS					BIT(1)	// CLK Line Status
#define	DLS					BIT(0)	// DATA Line Status	 

//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM) 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC) 
//-----------------------------------------------------------------------------
// ADC Status Register
#define	FIRHIACC			BIT(7)	// Filter High Accuracy
#define AINITB				BIT(3)	// Analog Accuracy Initialization Bit
#define	ADCPS				BIT(2)	// ADC Power Statement
#define	DOVE				BIT(1)	// Data Overflow Event
#define	EOCE				BIT(0)	// End-of-Cycle Event

// ADC Configuration Register
#define	DFILEN				BIT(5)	// Digital Filter Enable
#define	INTECEN				BIT(2)	// Interrupt from End-of-Cycle Event Enable
#define	ADCEN				BIT(0)	// ADC Module Enable

// Voltage Channel Control Register
#define	DATVAL				BIT(7)	// Data Valid
#define	INTDVEN				BIT(5)	// Interrupt from Data Valid Enable

// Calibration Data Control Register
#define	AHCE				BIT(7)	// Automatic Hardware Calibration Enable
#define	HCDATVAL			BIT(5)	// High-Scaler Calibration Data Valid
#define	GCDATVAL			BIT(4)	// Gain_Error Calibration Data Valid
#define	VHSCKE				BIT(1)	// Volt High Scale Calibration Enable
#define	GECKE				BIT(0)	// Gain_Error Calibration Enable

//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS) 
//-----------------------------------------------------------------------------
// Keyboard Scan Out Control Register
#define	KSOPU				BIT(2)	// KSO Pull Up
#define	KSOOD				BIT(0)	// KSO Open Drain

// Keyboard Scan In Control Register
#define	KSIPU				BIT(2)	// KSI Pull Up

//-----------------------------------------------------------------------------
// (20xxh) General Control (GCTRL) 
//-----------------------------------------------------------------------------
// Reset Status


//-----------------------------------------------------------------------------
// (30xxh) Platform Environment Control Interface (PECI)
//-----------------------------------------------------------------------------
extern ECReg   HOSTAR;              // 0x3000;    // Host Status Register
#define TEMPERR             BIT(7)  // PECI Get Temperature Error
#define BUSERR              BIT(6)  // PECI Bus Abnormal/Contention Error
#define EXTERR              BIT(5)  // PECI Slave Message Phase t-bit Extend over Error
#define WR_FCS_ERR          BIT(3)  // Write_FCS Error
#define RD_FCS_ERR          BIT(2)  // Read_FCS Error
#define FINISH              BIT(1)  // Finish
#define HOBY                BIT(0)  // Host Busy

extern ECReg   HOCTLR;              // 0x3001;    // Host Control Register
#define FIFOCLR             BIT(5)  // Data FIFO Pointer Clear
#define FCSERR_ABT          BIT(4)  // PECI Host Auto-abort at FCS_Error
#define PECIHEN             BIT(3)  // PECI Host Enable
#define CONCTRL             BIT(2)  // PECI Contention Control
#define AWFCS_EN            BIT(1)  // Assured Write FCS Enable
#define START               BIT(0)  // Start

extern ECReg   HOCMDR;              // 0x3002;    // Host Command Register
extern ECReg   HOTRADDR;            // 0x3003;    // Host Target Address Register
extern ECReg   HOWRLR;              // 0x3004;    // Host Write Length Register
extern ECReg   HORDLR;              // 0x3005;    // Host Read Length Register
extern ECReg   HOWRDR;              // 0x3006;    // Host Write Data Register
extern ECReg   HORDDR;              // 0x3007;    // Host Read Data Register

extern ECReg   HOCTL2R;             // 0x3008;    // Host Control 2 Register
extern ECReg   RWFCSV               ;// 0x3009  Received Write FCS Value
extern ECReg   RRFCSV               ;// 0x300A  Received Read FCS Value
extern ECReg   WFCSV                ;// 0x300B  Write FCS Value
extern ECReg   RFCSV                ;// 0x300C  Read FCS Falue
extern ECReg   AWFCSV               ;// 0x300D  Assured Write FCS Value
extern ECReg   PADCTLR              ;// 0x300E  Pad Control Register

#endif  
