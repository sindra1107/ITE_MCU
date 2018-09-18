/*-----------------------------------------------------------------------------
 * TITLE: CORE_CHIPREGS.C
 *
 * Copyright (c) ITE INC. All Rights Reserved.
 *
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//-----------------------------------------------------------------------------
// (10XXh) Shared Memory Flash Interface Bridge (SMFI) 
//-----------------------------------------------------------------------------
ECReg 	FBCFG			_at_ 0x1000;	// FBIU Configuration
ECReg 	FPCFG			_at_ 0x1001;	// Flash Programming Configuration Register
ECReg 	FECBSR			_at_ 0x1005;	// Flash EC Code Banking Select Register
ECReg 	FMSSR			_at_ 0x1007;	// Flash Memory Size Select Registe
ECReg 	SMECCS			_at_ 0x1020;	// Shared Memory EC Control and Status
ECReg 	SMHSR			_at_ 0x1022;	// Shared Memory Host Semaphore
ECReg	FLHCTRL1R		_at_ 0x1031;	// Flash Control Register 1	
ECReg	FLHCTRL2R		_at_ 0x1032;	// Flash Control Register 2
ECReg	DCache			_at_ 0x1033;	// 256 bytes cache
ECReg	UCCTRLR			_at_ 0x1034;	// uC Control Register
ECReg	HCTRL2R			_at_ 0x1036;	// Host Control 2 Register
ECReg   HSPICTRL2R      _at_ 0x1039;	// HSPI Control 2 Register
ECReg	HSPICTRL3R	    _at_ 0x103A;	// HSPI
ECReg 	ECINDAR0		_at_ 0x103B;	// EC-Indirect Memory Address Register 0
ECReg 	ECINDAR1		_at_ 0x103C;	// EC-Indirect Memory Address Register 1
ECReg 	ECINDAR2		_at_ 0x103D;	// EC-Indirect Memory Address Register 2
ECReg 	ECINDAR3		_at_ 0x103E;	// EC-Indirect Memory Address Register 3
ECReg 	ECINDDR			_at_ 0x103F;	// EC-Indirect Memory Data Register
ECReg	SCRA0L			_at_ 0x1040;	// Scratch SRAM 0 Address Low Byte Register
ECReg	SCRA0M			_at_ 0x1041;	// Scratch SRAM 0 Address Middle Byte Register
ECReg	SCRA0H			_at_ 0x1042;	// Scratch SRAM 0 Address High Byte Register
ECReg	SCRA1L			_at_ 0x1043;	// Scratch SRAM 1 Address Low Byte Register
ECReg	SCRA1M			_at_ 0x1044;	// Scratch SRAM 1 Address Middle Byte Register
ECReg	SCRA1H			_at_ 0x1045;	// Scratch SRAM 1 Address High Byte Register
ECReg	SCRA2L			_at_ 0x1046;	// Scratch SRAM 2 Address Low Byte Register
ECReg	SCRA2M			_at_ 0x1047;	// Scratch SRAM 2 Address Middle Byte Register
ECReg	SCRA2H			_at_ 0x1048;	// Scratch SRAM 2 Address High Byte Register
ECReg	SCRA3L			_at_ 0x1049;	// Scratch SRAM 3 Address Low Byte Register
ECReg	SCRA3M			_at_ 0x104A;	// Scratch SRAM 3 Address Middle Byte Register
ECReg	SCRA3H			_at_ 0x104B;	// Scratch SRAM 3 Address High Byte Register
ECReg	SCRA4L			_at_ 0x104C;	// Scratch SRAM 4 Address Low Byte Register
ECReg	SCRA4M			_at_ 0x104D;	// Scratch SRAM 4 Address Middle Byte Register
ECReg	SCRA4H			_at_ 0x104E;	// Scratch SRAM 4 Address High Byte Register

ECReg	P0BA0R			_at_ 0x104F;	// Protect 0 Base Addr Register 0
ECReg	P0BA1R			_at_ 0x1050;	// Protect 0 Base Addr Register 1
ECReg	P0ZR			_at_ 0x1051;	// Protect 0 Size Register
ECReg	P1BA0R			_at_ 0x1052;	// Protect 1 Base Addr Register 0
ECReg	P1BA1R			_at_ 0x1053;	// Protect 1 Base Addr Register 1
ECReg	P1ZR			_at_ 0x1054;	// Protect 1 Size Register
ECReg	DSINST			_at_ 0x1055;	// Deferred SPI Instruction
ECReg	DSADR1			_at_ 0x1056;	// Deferred SPI Address
ECReg	DSADR2			_at_ 0x1057;	// Deferred SPI Address
ECReg	HINSTC1			_at_ 0x1058;	// Host Instruction Control 1
ECReg	HINSTC2			_at_ 0x1059;	// Host Instruction Control 2
ECReg	HRAMWC			_at_ 0x105A;	// Host RAM Window Control
ECReg	HRAMW0BA		_at_ 0x105B;	// Host RAM Winodw 0 Base Address
ECReg	HRAMW1BA		_at_ 0x105C;	// Host RAM Window 1 Base Address
ECReg	HRAMW0AAS		_at_ 0x105D;	// Host RAM Window 0 Access Allow Size
ECReg	HRAMW1AAS		_at_ 0x105E;	// Host RAM Window 1 Access Allow Size
ECReg	SCAR5H			_at_ 0x105F;
ECReg	FLHCTRL3R		_at_ 0x1063;
ECReg   FLHCTRL4R       _at_ 0x1064;    // Flash Control 4 Register
ECReg   HSPICTRL        _at_ 0x1068;    // HSPI Control Register 4
ECReg   P2BA0R          _at_ 0x1070;    // Protect 2 Base Addr Register 0
ECReg   P2BA1R          _at_ 0x1071;    // Protect 2 Base Addr Register 1
ECReg   P2ZR            _at_ 0x1072;    // Protect 2 Size Register
ECReg   P3BA0R          _at_ 0x1073;    // Protect 3 Base Addr Register 0
ECReg   P3BA1R          _at_ 0x1074;    // Protect 3 Base Addr Register 1
ECReg   P3ZR            _at_ 0x1075;    // Protect 3 Size Register
ECReg   HRAMW2BA        _at_ 0x1076;    // Host RAM Windows 2 Base Address
ECReg   HRAMW3BA        _at_ 0x1077;    // Host RAM Windows 3 Base Address
ECReg   HRAMW2AAS       _at_ 0x1078;    // Host RAM Windows 2 Access Allow Size
ECReg   HRAMW3AAS       _at_ 0x1079;    // Host RAM Windows 3 Access Allow Size
ECReg   H2RAMECSIE      _at_ 0x107A;    // H2RAM EC Semaphore Interrupt Enable
ECReg   H2RAMECSA       _at_ 0x107B;    // H2RAM EC Semaphore Address
ECReg   H2RAMHSS        _at_ 0x107C;    // H2RAM Host Semphore Status
ECReg   HPADR           _at_ 0x107E;    // Host Protect Authentication Data Register
//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC) 
//-----------------------------------------------------------------------------
ECReg 	ISR0      		_at_ 0x1100;	// Interrupt Status Register 0
ECReg 	ISR1       		_at_ 0x1101;	// Interrupt Status Register 1
ECReg 	ISR2       		_at_ 0x1102;	// Interrupt Status Register 2
ECReg 	ISR3       		_at_ 0x1103;	// Interrupt Status Register 3
ECReg 	ISR4    		_at_ 0x1114;	// Interrupt Status Register 4
ECReg 	ISR5    		_at_ 0x1118;	// Interrupt Status Register 5
ECReg 	ISR6    		_at_ 0x111C;	// Interrupt Status Register 6
ECReg 	ISR7    		_at_ 0x1120;	// Interrupt Status Register 7
ECReg 	ISR8            _at_ 0x1124;	// Interrupt Status Register 8
ECReg 	ISR9            _at_ 0x1128;	// Interrupt Status Register 9
ECReg   ISR10           _at_ 0x112C;    // Interrupt Status Register 10
ECReg   ISR11           _at_ 0x1130;    // Interrupt Status Register 11
ECReg   ISR12           _at_ 0x1134;    // Interrupt Status Register 12
ECReg   ISR13           _at_ 0x1138;    // Interrupt Status Register 13
ECReg   ISR14           _at_ 0x113C;    // Interrupt Status Register 14
ECReg   ISR15           _at_ 0x1140;    // Interrupt Status Register 15
ECReg   ISR16           _at_ 0x1144;    // Interrupt Status Register 16
ECReg   ISR17           _at_ 0x1148;    // Interrupt Status Register 17
ECReg   ISR18           _at_ 0x114C;    // Interrupt Status Register 18
ECReg   ISR19           _at_ 0x1150;	// Interrupt Status Register 19

ECReg 	IER0      		_at_ 0x1104;	// Interrupt Enable Register 0
ECReg 	IER1       		_at_ 0x1105;	// Interrupt Enable Register 1
ECReg 	IER2      		_at_ 0x1106;	// Interrupt Enable Register 2
ECReg 	IER3       		_at_ 0x1107;	// Interrupt Enable Register 3
ECReg 	IER4    		_at_ 0x1115;	// Interrupt Enable Register 4
ECReg 	IER5    		_at_ 0x1119;	// Interrupt Enable Register 5
ECReg 	IER6    		_at_ 0x111D;	// Interrupt Enable Register 6
ECReg 	IER7    		_at_ 0x1121;	// Interrupt Enable Register 7
ECReg 	IER8    		_at_ 0x1125;	// Interrupt Enable Register 8
ECReg 	IER9    		_at_ 0x1129;	// Interrupt Enable Register 9
ECReg   IER10           _at_ 0x112D;    // Interrupt Enable Register 10
ECReg   IER11           _at_ 0x1131;    // Interrupt Enable Register 11
ECReg   IER12           _at_ 0x1135;    // Interrupt Enable Register 12
ECReg   IER13           _at_ 0x1139;    // Interrupt Enable Register 13
ECReg   IER14           _at_ 0x113D;    // Interrupt Enable Register 14
ECReg   IER15           _at_ 0x1141;    // Interrupt Enable Register 15
ECReg   IER16           _at_ 0x1145;    // Interrupt Enable Register 16
ECReg   IER17           _at_ 0x1149;    // Interrupt Enable Register 17
ECReg   IER18           _at_ 0x114D;    // Interrupt Enable Register 18
ECReg   IER19           _at_ 0x1151;    // Interrupt Enable Register 19

ECReg 	IELMR0    		_at_ 0x1108;	// Interrupt Edge/Level-Triggered Mode Register 0
ECReg 	IELMR1     		_at_ 0x1109;	// Interrupt Edge/Level-Triggered Mode Register 1
ECReg 	IELMR2   		_at_ 0x110A;	// Interrupt Edge/Level-Triggered Mode Register 2
ECReg 	IELMR3     		_at_ 0x110B;	// Interrupt Edge/Level-Triggered Mode Register 3
ECReg 	IELMR4    		_at_ 0x1116;	// Interrupt Edge/Level-Triggered Mode Register 4
ECReg 	IELMR5    		_at_ 0x111A;	// Interrupt Edge/Level-Triggered Mode Register 5
ECReg 	IELMR6    		_at_ 0x111E;	// Interrupt Edge/Level-Triggered Mode Register 6
ECReg 	IELMR7    		_at_ 0x1122;	// Interrupt Edge/Level-Triggered Mode Register 7
ECReg 	IELMR8    		_at_ 0x1126;	// Interrupt Edge/Level-Triggered Mode Register 8
ECReg 	IELMR9    		_at_ 0x112A;	// Interrupt Edge/Level-Triggered Mode Register 9
ECReg   IELMR10         _at_ 0x112E;    // Interrupt Edge/Level-Triggered Mode Register 10
ECReg   IELMR11         _at_ 0x1132;    // Interrupt Edge/Level-Triggered Mode Register 11
ECReg   IELMR12         _at_ 0x1136;    // Interrupt Edge/Level-Triggered Mode Register 12
ECReg   IELMR13         _at_ 0x113A;    // Interrupt Edge/Level-Triggered Mode Register 13
ECReg   IELMR14         _at_ 0x113E;    // Interrupt Edge/Level-Triggered Mode Register 14
ECReg   IELMR15         _at_ 0x1142;    // Interrupt Edge/Level-Triggered Mode Register 15
ECReg   IELMR16         _at_ 0x1146;    // Interrupt Edge/Level-Triggered Mode Register 16
ECReg   IELMR17         _at_ 0x114A;    // Interrupt Edge/Level-Triggered Mode Register 17
ECReg   IELMR18         _at_ 0x114E;    // Interrupt Edge/Level-Triggered Mode Register 18
ECReg   IELMR19         _at_ 0x1152;    // Interrupt Edge/Level-Triggered Mode Register 19

ECReg 	IPOLR0     		_at_ 0x110C;	// Interrupt Polarity Register 0
ECReg 	IPOLR1    		_at_ 0x110D;	// Interrupt Polarity Register 1
ECReg 	IPOLR2    		_at_ 0x110E;	// Interrupt Polarity Register 2
ECReg 	IPOLR3    		_at_ 0x110F;	// Interrupt Polarity Register 3
ECReg 	IPOLR4    		_at_ 0x1117;	// Interrupt Polarity Register 4
ECReg 	IPOLR5    		_at_ 0x111B;	// Interrupt Polarity Register 5
ECReg 	IPOLR6    		_at_ 0x111F;	// Interrupt Polarity Register 6
ECReg 	IPOLR7    		_at_ 0x1123;	// Interrupt Polarity Register 7
ECReg 	IPOLR8    		_at_ 0x1127;	// Interrupt Polarity Register 8
ECReg 	IPOLR9    		_at_ 0x112B;	// Interrupt Polarity Register 9
ECReg   IPOLR10         _at_ 0x112F;    // Interrupt Polarity Register 10
ECReg   IPOLR11         _at_ 0x1133;    // Interrupt Polarity Register 11
ECReg   IPOLR12         _at_ 0x1137;    // Interrupt Polarity Register 12
ECReg   IPOLR13         _at_ 0x113B;    // Interrupt Polarity Register 13
ECReg   IPOLR14         _at_ 0x113F;    // Interrupt Polarity Register 14
ECReg   IPOLR15         _at_ 0x1143;    // Interrupt Polarity Register 15
ECReg   IPOLR16         _at_ 0x1147;    // Interrupt Polarity Register 16
ECReg   IPOLR17         _at_ 0x114B;    // Interrupt Polarity Register 17
ECReg   IPOLR18         _at_ 0x114F;    // Interrupt Polarity Register 18
ECReg   IPOLR19         _at_ 0x1153;    // Interrupt Polarity Register 19

ECReg 	IVECT    		_at_ 0x1110;	// Interrupt Vector Register
ECReg 	INT0ST    		_at_ 0x1111;	// INT0# status
ECReg 	PFAILR    		_at_ 0x1112;	// Power Fail Register

//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge) 
//-----------------------------------------------------------------------------
ECReg 	IHIOA     		_at_ 0x1200;	// Indirect Host I/O Address
ECReg 	IHD      		_at_ 0x1201;	// Indirect Host Data
ECReg 	LSIOHA    		_at_ 0x1202;	// Lock Super I/O Host Access
ECReg 	SIOLV     		_at_ 0x1203;	// Super I/O Access Lock Violation
ECReg 	IBMAE			_at_ 0x1204;	// EC to I-Bus Modules Access Enable
ECReg 	IBCTL   		_at_ 0x1205;	// I-Bus Control

//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC) 
//-----------------------------------------------------------------------------
ECReg 	KBHICR   		_at_ 0x1300;	// KBC Host Interface Control Register
ECReg 	KBIRQR     		_at_ 0x1302;	// KBC Interrupt Control Register
ECReg 	KBHISR   		_at_ 0x1304;	// KBC Host Interface Keyboard/Mouse Status Register
ECReg 	KBHIKDOR 		_at_ 0x1306;	// KBC Host Interface Keyboard Data Output Register
ECReg 	KBHIMDOR  		_at_ 0x1308;	// KBC Host Interface Mouse Data Output Register
ECReg 	KBHIDIR   		_at_ 0x130A;	// KBC Host Interface Keyboard/Mouse Data Input Register

//-----------------------------------------------------------------------------
// (14xxh) System Wake-Up Control (SWUC) 
//-----------------------------------------------------------------------------
ECReg 	SWCTL1			_at_ 0x1400;	// SWUC Control Status 1 Register
ECReg 	SWCTL2			_at_ 0x1402;	// SWUC Control Status 2 Register
ECReg 	SWCTL3			_at_ 0x1404;	// SWUC Control Status 3 Register
ECReg 	SWCBALR			_at_ 0x1408;	// SWUC Host Configuration Base Address Low Byte Register
ECReg 	SWCBAHR			_at_ 0x140A;	// SWUC Host Configuration Base Address High Byte Register
ECReg 	SWCIER     		_at_ 0x140C;	// SWUC Interrupt Enable Register
ECReg 	SWCHSTR    		_at_ 0x140E;	// SWUC Host Event Status Register
ECReg 	SWCHIER  		_at_ 0x1410;	// SWUC Host Event Interrupt Enable Register

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC) 
//-----------------------------------------------------------------------------
										// PM1
ECReg 	PM1STS   		_at_ 0x1500;	// Host Interface PM Channel 1 Status
ECReg 	PM1DO      		_at_ 0x1501;	// Host Interface PM Channel 1 Data Out Port
ECReg 	PM1DOSCI  		_at_ 0x1502;	// Host Interface PM Channel 1 Data Out Port with SCI
ECReg 	PM1DOSMI  		_at_ 0x1503;	// Host Interface PM Channel 1 Data Out Port with SMI
ECReg 	PM1DI			_at_ 0x1504;	// Host Interface PM Channel 1 Data In Port
ECReg 	PM1DISCI   		_at_ 0x1505;	// Host Interface PM Channel 1 Data In Port with SCI
ECReg 	PM1CTL     		_at_ 0x1506;	// Host Interface PM Channel 1 Control
ECReg 	PM1IC     		_at_ 0x1507;	// Host Interface PM Channel 1 Interrupt Control
ECReg 	PM1IE    		_at_ 0x1508;	// Host Interface PM Channel 1 Interrupt Enable
										// PM2
ECReg 	PM2STS    		_at_ 0x1510;	// Host Interface PM Channel 2 Status
ECReg 	PM2DO     		_at_ 0x1511;	// Host Interface PM Channel 2 Data Out Port
ECReg 	PM2DOSCI   		_at_ 0x1512;	// Host Interface PM Channel 2 Data Out Port with SCI
ECReg 	PM2DOSMI  		_at_ 0x1513;	// Host Interface PM Channel 2 Data Out Port with SMI
ECReg 	PM2DI     		_at_ 0x1514;	// Host Interface PM Channel 2 Data In Port
ECReg 	PM2DISCI   		_at_ 0x1515;	// Host Interface PM Channel 2 Data In Port with SCI
ECReg 	PM2CTL     		_at_ 0x1516;	// Host Interface PM Channel 2 Control
ECReg 	PM2IC     		_at_ 0x1517;	// Host Interface PM Channel 2 Interrupt Control
ECReg 	PM2IE     		_at_ 0x1518;	// Host Interface PM Channel 2 Interrupt Enable
										// Mailbox
ECReg	MBXCTRL			_at_ 0x1519;	// Mailbox Control
ECReg   MBXEC[16]       _at_ 0x15F0;    // 16-byte PMC2EX Mailbox 0 ~ Mailbox 15

ECReg 	PM3STS    		_at_ 0x1520;	// Host Interface PM Channel 3 Status
ECReg 	PM3DO     		_at_ 0x1521;	// Host Interface PM Channel 3 Data Out Port
ECReg 	PM3DI     		_at_ 0x1522;	// Host Interface PM Channel 3 Data In Port
ECReg 	PM3CTL     		_at_ 0x1523;	// Host Interface PM Channel 3 Control
ECReg 	PM3IC     		_at_ 0x1524;	// Host Interface PM Channel 3 Interrupt Control
ECReg 	PM3IE     		_at_ 0x1525;	// Host Interface PM Channel 3 Interrupt Enable

ECReg 	PM4STS    		_at_ 0x1530;	// Host Interface PM Channel 4 Status
ECReg 	PM4DO     		_at_ 0x1531;	// Host Interface PM Channel 4 Data Out Port
ECReg 	PM4DI     		_at_ 0x1532;	// Host Interface PM Channel 4 Data In Port
ECReg 	PM4CTL     		_at_ 0x1533;	// Host Interface PM Channel 4 Control
ECReg 	PM4IC     		_at_ 0x1534;	// Host Interface PM Channel 4 Interrupt Control
ECReg 	PM4IE     		_at_ 0x1535;	// Host Interface PM Channel 4 Interrupt Enable

ECReg   PM5STS          _at_ 0x1540;    // Host Interface PM Channel 5 Status
ECReg   PM5DO           _at_ 0x1541;    // Host Interface PM Channel 5 Data Out Port
ECReg   PM5DI           _at_ 0x1542;    // Host Interface PM Channel 5 Data In Port
ECReg   PM5CTL          _at_ 0x1543;    // Host Interface PM Channel 5 Control
ECReg   PM5IC           _at_ 0x1544;    // Host Interface PM Channel 5 Interrupt Control
ECReg   PM5IE           _at_ 0x1545;    // Host Interface PM Channel 5 Interrupt Enable

//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control Register                           
//-----------------------------------------------------------------------------
										// GPIO data register
ECReg	GCR     		_at_ 0x1600;	// General Control Register
ECReg	GCR1     		_at_ 0x16F0;	// General Control 1 Register
ECReg	GCR2     		_at_ 0x16F1;	// General Control 2 Register
ECReg	GCR3     		_at_ 0x16F2;	// General Control 3 Register
ECReg	GCR4     		_at_ 0x16F3;	// General Control 4 Register
ECReg	GCR5     		_at_ 0x16F4;	// General Control 5 Register
ECReg	GCR6     		_at_ 0x16F5;	// General Control 6 Register
ECReg	GCR7     		_at_ 0x16F6;	// General Control 7 Register
ECReg   GCR8            _at_ 0x16F7;    // General Control 8 Register
ECReg   GCR9            _at_ 0x16F8;    // General Control 9 Register
ECReg   GCR10           _at_ 0x16F9;    // General Control 10 Register
ECReg   GCR11           _at_ 0x16FA;    // General Control 11 Register
ECReg   GCR12           _at_ 0x16FB;    // General Control 12 Register
ECReg   GCR13           _at_ 0x16FC;    // General Control 13 Register
ECReg   GCR14           _at_ 0x16FD;    // General Control 14 Register
ECReg   GCR15           _at_ 0x16FE;    // General Control 15 Register
ECReg   GCR16           _at_ 0x16E0;    // General Control 16 Register
ECReg   GCR17           _at_ 0x16E1;    // General Control 17 Register
ECReg   GCR18           _at_ 0x16E2;    // General Control 18 Register

ECReg   GCR19           _at_ 0x16E4;    // General Control 19 Register
ECReg   GCR20           _at_ 0x16E5;    // General Control 20 Register
ECReg   GCR21           _at_ 0x16E6;    // General Control 21 Register
ECReg   GCR22           _at_ 0x16E7;    // General Control 22 Register

ECReg	GPDRA 			_at_ 0x1601;	// Port A Data Register
ECReg	GPDRB 			_at_ 0x1602;	// Port B Data Register
ECReg	GPDRC 			_at_ 0x1603;	// Port C Data Register
ECReg	GPDRD 			_at_ 0x1604;	// Port D Data Register
ECReg	GPDRE 			_at_ 0x1605;	// Port E Data Register
ECReg	GPDRF 			_at_ 0x1606;	// Port F Data Register
ECReg	GPDRG 			_at_ 0x1607;	// Port G Data Register
ECReg	GPDRH 			_at_ 0x1608;	// Port H Data Register
ECReg	GPDRI 			_at_ 0x1609;	// Port I Data Register
ECReg	GPDRJ 			_at_ 0x160A;	// Port J Data Register
ECReg	GPDRM 			_at_ 0x160D;	// Port M Data Register
										// GPIO control register
ECReg 	GPCRA0			_at_ 0x1610;	// Port Control A0 Registers
ECReg 	GPCRA1			_at_ 0x1611;	// Port Control A1 Registers
ECReg 	GPCRA2			_at_ 0x1612;	// Port Control A2 Registers
ECReg 	GPCRA3			_at_ 0x1613;	// Port Control A3 Registers
ECReg 	GPCRA4			_at_ 0x1614;	// Port Control A4 Registers
ECReg 	GPCRA5			_at_ 0x1615;	// Port Control A5 Registers
ECReg 	GPCRA6			_at_ 0x1616;	// Port Control A6 Registers
ECReg 	GPCRA7			_at_ 0x1617;	// Port Control A7 Registers

ECReg 	GPCRB0			_at_ 0x1618;	// Port Control B0 Registers
ECReg 	GPCRB1			_at_ 0x1619;	// Port Control B1 Registers
ECReg 	GPCRB2			_at_ 0x161A;	// Port Control B2 Registers
ECReg 	GPCRB3			_at_ 0x161B;	// Port Control B3 Registers
ECReg 	GPCRB4			_at_ 0x161C;	// Port Control B4 Registers
ECReg 	GPCRB5			_at_ 0x161D;	// Port Control B5 Registers
ECReg 	GPCRB6			_at_ 0x161E;	// Port Control B6 Registers
ECReg 	GPCRB7			_at_ 0x161F;	// Port Control B7 Registers

ECReg 	GPCRC0			_at_ 0x1620;	// Port Control C0 Registers
ECReg 	GPCRC1			_at_ 0x1621;	// Port Control C1 Registers
ECReg 	GPCRC2			_at_ 0x1622;	// Port Control C2 Registers
ECReg 	GPCRC3			_at_ 0x1623;	// Port Control C3 Registers
ECReg 	GPCRC4			_at_ 0x1624;	// Port Control C4 Registers
ECReg 	GPCRC5			_at_ 0x1625;	// Port Control C5 Registers
ECReg 	GPCRC6			_at_ 0x1626;	// Port Control C6 Registers
ECReg 	GPCRC7			_at_ 0x1627;	// Port Control C7 Registers

ECReg 	GPCRD0			_at_ 0x1628;	// Port Control D0 Registers
ECReg 	GPCRD1			_at_ 0x1629;	// Port Control D1 Registers
ECReg 	GPCRD2			_at_ 0x162A;	// Port Control D2 Registers
ECReg 	GPCRD3			_at_ 0x162B;	// Port Control D3 Registers
ECReg 	GPCRD4			_at_ 0x162C;	// Port Control D4 Registers
ECReg 	GPCRD5			_at_ 0x162D;	// Port Control D5 Registers
ECReg 	GPCRD6			_at_ 0x162E;	// Port Control D6 Registers
ECReg 	GPCRD7			_at_ 0x162F;	// Port Control D7 Registers

ECReg 	GPCRE0			_at_ 0x1630;	// Port Control E0 Registers
ECReg 	GPCRE1			_at_ 0x1631;	// Port Control E1 Registers
ECReg 	GPCRE2			_at_ 0x1632;	// Port Control E2 Registers
ECReg 	GPCRE3			_at_ 0x1633;	// Port Control E3 Registers
ECReg 	GPCRE4			_at_ 0x1634;	// Port Control E4 Registers
ECReg 	GPCRE5			_at_ 0x1635;	// Port Control E5 Registers
ECReg 	GPCRE6			_at_ 0x1636;	// Port Control E6 Registers
ECReg 	GPCRE7			_at_ 0x1637;	// Port Control E7 Registers

ECReg 	GPCRF0			_at_ 0x1638;	// Port Control F0 Registers
ECReg 	GPCRF1			_at_ 0x1639;	// Port Control F1 Registers
ECReg 	GPCRF2			_at_ 0x163A;	// Port Control F2 Registers
ECReg 	GPCRF3			_at_ 0x163B;	// Port Control F3 Registers
ECReg 	GPCRF4			_at_ 0x163C;	// Port Control F4 Registers
ECReg 	GPCRF5			_at_ 0x163D;	// Port Control F5 Registers
ECReg 	GPCRF6			_at_ 0x163E;	// Port Control F6 Registers
ECReg 	GPCRF7			_at_ 0x163F;	// Port Control F7 Registers

ECReg 	GPCRG0			_at_ 0x1640;	// Port Control G0 Registers
ECReg 	GPCRG1			_at_ 0x1641;	// Port Control G1 Registers
ECReg 	GPCRG2			_at_ 0x1642;	// Port Control G2 Registers
ECReg 	GPCRG3			_at_ 0x1643;	// Port Control G3 Registers
ECReg 	GPCRG4			_at_ 0x1644;	// Port Control G4 Registers
ECReg 	GPCRG5			_at_ 0x1645;	// Port Control G5 Registers
ECReg 	GPCRG6			_at_ 0x1646;	// Port Control G6 Registers
ECReg 	GPCRG7			_at_ 0x1647;	// Port Control G7 Registers

ECReg 	GPCRH0			_at_ 0x1648;	// Port Control H0 Registers
ECReg 	GPCRH1			_at_ 0x1649;	// Port Control H1 Registers
ECReg 	GPCRH2			_at_ 0x164A;	// Port Control H2 Registers
ECReg 	GPCRH3			_at_ 0x164B;	// Port Control H3 Registers
ECReg 	GPCRH4			_at_ 0x164C;	// Port Control H4 Registers
ECReg 	GPCRH5			_at_ 0x164D;	// Port Control H5 Registers
ECReg 	GPCRH6			_at_ 0x164E;	// Port Control H6 Registers

ECReg 	GPCRI0			_at_ 0x1650;	// Port Control I0 Registers
ECReg 	GPCRI1			_at_ 0x1651;	// Port Control I1 Registers
ECReg 	GPCRI2			_at_ 0x1652;	// Port Control I2 Registers
ECReg 	GPCRI3			_at_ 0x1653;	// Port Control I3 Registers
ECReg 	GPCRI4			_at_ 0x1654;	// Port Control I4 Registers
ECReg 	GPCRI5			_at_ 0x1655;	// Port Control I5 Registers
ECReg 	GPCRI6			_at_ 0x1656;	// Port Control I6 Registers
ECReg 	GPCRI7			_at_ 0x1657;	// Port Control I7 Registers

ECReg 	GPCRJ0			_at_ 0x1658;	// Port Control J0 Registers
ECReg 	GPCRJ1			_at_ 0x1659;	// Port Control J1 Registers
ECReg 	GPCRJ2			_at_ 0x165A;	// Port Control J2 Registers
ECReg 	GPCRJ3			_at_ 0x165B;	// Port Control J3 Registers
ECReg 	GPCRJ4			_at_ 0x165C;	// Port Control J4 Registers
ECReg 	GPCRJ5			_at_ 0x165D;	// Port Control J5 Registers
ECReg 	GPCRJ6			_at_ 0x165E;	// Port Control J6 Registers
ECReg 	GPCRJ7			_at_ 0x165F;	// Port Control J7 Registers

ECReg 	GPCRM0			_at_ 0x16A0;	// Port Control M0 Registers
ECReg 	GPCRM1			_at_ 0x16A1;	// Port Control M1 Registers
ECReg 	GPCRM2			_at_ 0x16A2;	// Port Control M2 Registers
ECReg 	GPCRM3			_at_ 0x16A3;	// Port Control M3 Registers
ECReg 	GPCRM4			_at_ 0x16A4;	// Port Control M4 Registers
ECReg 	GPCRM5			_at_ 0x16A5;	// Port Control M5 Registers
ECReg 	GPCRM6			_at_ 0x16A6;	// Port Control M6 Registers

										// Port Data Mirror Register
ECReg 	GPDMRA			_at_ 0x1661;	// Port A Data Mirror Register
ECReg 	GPDMRB			_at_ 0x1662;	// Port B Data Mirror Register
ECReg 	GPDMRC			_at_ 0x1663;	// Port C Data Mirror Register
ECReg 	GPDMRD			_at_ 0x1664;	// Port D Data Mirror Register
ECReg 	GPDMRE			_at_ 0x1665;	// Port E Data Mirror Register
ECReg 	GPDMRF			_at_ 0x1666;	// Port F Data Mirror Register
ECReg 	GPDMRG			_at_ 0x1667;	// Port G Data Mirror Register
ECReg 	GPDMRH			_at_ 0x1668;	// Port H Data Mirror Register
ECReg 	GPDMRI			_at_ 0x1669;	// Port I Data Mirror Register
ECReg 	GPDMRJ			_at_ 0x166A;	// Port J Data Mirror Register
ECReg 	GPDMRM			_at_ 0x166D;	// Port M Data Mirror Register

ECReg 	GPOTA			_at_ 0x1671;	// Output Type Register
ECReg 	GPOTB			_at_ 0x1672;	// Output Type Register
ECReg 	GPOTD			_at_ 0x1674;	// Output Type Register
ECReg 	GPOTE			_at_ 0x1675;	// Output Type Register
ECReg   GPOTF           _at_ 0x1676;    // Output Type Register
ECReg   GPOTH           _at_ 0x1678;    // Output Type Register
ECReg   GPOTJ           _at_ 0x167A;    // Output Type Register

//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface Register                            			  
//-----------------------------------------------------------------------------
ECReg 	PSCTL1    		_at_ 0x1700;	// PS/2 Control Register 1
ECReg 	PSCTL2			_at_ 0x1701;	// PS/2 Control Register 2
ECReg 	PSCTL3     		_at_ 0x1702;	// PS/2 Control Register 3
ECReg 	PSINT1   		_at_ 0x1704;	// PS/2 Interrupt Control Register 1
ECReg 	PSINT2    		_at_ 0x1705;	// PS/2 Interrupt Control Register 2
ECReg 	PSINT3    		_at_ 0x1706;	// PS/2 Interrupt Control Register 3
ECReg 	PSSTS1    		_at_ 0x1708;	// PS/2 Status Register 1
ECReg 	PSSTS2    		_at_ 0x1709;	// PS/2 Status Register 2
ECReg 	PSSTS3    		_at_ 0x170A;	// PS/2 Status Register 3
ECReg 	PSDAT1    		_at_ 0x170C;	// PS/2 Data Register 1
ECReg 	PSDAT2     		_at_ 0x170D;	// PS/2 Data Register 2
ECReg	PSDAT3 			_at_ 0x170E;	// PS/2 Data Register 3

//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM) 
//-----------------------------------------------------------------------------
ECReg	C0CPRS  		_at_ 0x1800;	// Channel 0 Clock Prescaler Register
ECReg	CTR       		_at_ 0x1801;	// Cycle Time 0
ECReg	DCR0     		_at_ 0x1802;	// Channel 0 PWM Duty Cycle		
ECReg	DCR1      		_at_ 0x1803;	// Channel 0 PWM Duty Cycle	
ECReg	DCR2     		_at_ 0x1804;	// Channel 0 PWM Duty Cycle	
ECReg	DCR3       		_at_ 0x1805;	// Channel 0 PWM Duty Cycle	
ECReg	DCR4      		_at_ 0x1806;	// Channel 0 PWM Duty Cycle	
ECReg	DCR5      		_at_ 0x1807;	// Channel 0 PWM Duty Cycle	
ECReg	DCR6       		_at_ 0x1808;	// Channel 0 PWM Duty Cycle	
ECReg	DCR7     		_at_ 0x1809;	// Channel 0 PWM Duty Cycle	
ECReg	PWMPOL        	_at_ 0x180A;	// PWM Polarity
ECReg	PCFSR      		_at_ 0x180B;	// Prescaler Clock Frequency Select Register
ECReg	PCSSGL   		_at_ 0x180C;	// Prescaler Clock Source Select Group Low
ECReg	PCSSGH    		_at_ 0x180D;	// Prescaler Clock Source Select Group High
ECReg	CR256PCSSG		_at_ 0x180E;	// CR256 Prescaler Clock Source Select Group
ECReg	PCSGR			_at_ 0x180F;	// Prescaler Clock Source Gating Register
ECReg	F1TLRR     		_at_ 0x181E;	// Fan 1 Tachometer LSB Reading
ECReg	F1TMRR    		_at_ 0x181F;	// Fan 1 Tachometer MSB Reading
ECReg	F2TLRR    		_at_ 0x1820;	// Fan 2 Tachometer LSB Reading
ECReg	F2TMRR     		_at_ 0x1821;	// Fan 2 Tachometer MSB Reading
ECReg	ZINTSCR   		_at_ 0x1822;	// Zone Interrupt Status Control
ECReg	ZTIER      		_at_ 0x1823;	// PWM Clock Control Register
ECReg	TSWCTLR    		_at_ 0x1824;	// Tachometer Switch Control Register
ECReg	C4CPRS    		_at_ 0x1827;	// Channel 4 Clock Prescaler Register
ECReg	C4MCPRS    		_at_ 0x1828;	// Channel 4 Clock Prescaler MSB Register
ECReg	C6CPRS    		_at_ 0x182B;	// Channel 6 Clock Prescaler Register
ECReg	C6MCPRS    		_at_ 0x182C;	// Channel 6 Clock Prescaler MSB Register
ECReg	C7CPRS     		_at_ 0x182D;	// Channel 7 Clock Prescaler Register
ECReg	C7MCPRS    		_at_ 0x182E;	// Channel 7 Clock Prescaler MSB Register
ECReg	CLK6MSEL   		_at_ 0x1840;	// PWM Clock 6MHz Select Register
ECReg	CTR1    		_at_ 0x1841;	// Cycle Time 1
ECReg	CTR2    		_at_ 0x1842;	// Cycle Time 2
ECReg	CTR3    		_at_ 0x1843;	// Cycle Time 3
ECReg	PWM5TOCTRL		_at_ 0x1844;	// PWM5 Timeout Control Register
ECReg	CFLRR    		_at_ 0x1845;	// Color Frequency LSB Register
ECReg	CFMRR    		_at_ 0x1846;	// Color Frequency MSB Register
ECReg	CFINTCTRL		_at_ 0x1847;	// Color Frequency Interrupt Control Register

ECReg	TSWCTRL    		_at_ 0x1848;	// Tachometer Switch Control Register
ECReg	PWMODENR		_at_ 0x1849;	// PWM Output Open-Drain Enable Register

ECReg	PWM0LHE 		_at_ 0x1850;	// PWM0 LED DIMMING ENABLE REGISTER
ECReg	PWM0LCR1		_at_ 0x1851;	// PWM0 LED DIMMING CONTROL REGISTER 1
ECReg	PWM0LCR2		_at_ 0x1852;	// PWM0 LED DIMMING CONTROL REGISTER 2
ECReg	PWM1LHE 		_at_ 0x1853;	// PWM1 LED DIMMING ENABLE REGISTER
ECReg	PWM1LCR1		_at_ 0x1854;	// PWM1 LED DIMMING CONTROL REGISTER 1
ECReg	PWM1LCR2		_at_ 0x1855;	// PWM1 LED DIMMING CONTROL REGISTER 2

//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC) 
//-----------------------------------------------------------------------------
ECReg	ADCSTS			_at_ 0x1900;	// ADC Status
ECReg	ADCCFG			_at_ 0x1901;	// ADC Configuration
ECReg	ADCCTL			_at_ 0x1902;	// ADC Clock Control
ECReg   ADCGCR          _at_ 0x1903;    // ADC General Control Register
ECReg	VCH0CTL			_at_ 0x1904;	// Voltage Channel 0 Channel Control
ECReg	KDCTL			_at_ 0x1905;	// Calibration Data Control Register
ECReg	VCH1CTL      	_at_ 0x1906;	// Voltage Channel 1 Control
ECReg	VCH1DATL     	_at_ 0x1907;	// Voltage Channel 1 Data Buffer LSB
ECReg	VCH1DATM       	_at_ 0x1908;	// Voltage Channel 1 Data Buffer MSB
ECReg	VCH2CTL        	_at_ 0x1909;	// Voltage Channel 2 Control
ECReg	VCH2DATL      	_at_ 0x190A;	// Voltage Channel 2 Data Buffer LSB
ECReg	VCH2DATM     	_at_ 0x190B;	// Voltage Channel 2 Data Buffer MSB
ECReg	VCH3CTL       	_at_ 0x190C;	// Voltage Channel 3 Control
ECReg	VCH3DATL      	_at_ 0x190D;	// Voltage Channel 3 Data Buffer LSB
ECReg	VCH3DATM      	_at_ 0x190E;	// Voltage Channel 3 Data Buffer MSB
ECReg	VHSCDBL      	_at_ 0x1914;	// Voltage High Scale Calibration Data Buffer LSB
ECReg	VHSCDBM       	_at_ 0x1915;	// Voltage High Scale Calibration Data Buffer MSB
ECReg	VCH0DATL		_at_ 0x1918;	// Voltage Channel 0 Data Buffer LSB
ECReg	VCH0DATM		_at_ 0x1919;	// Voltage Channel 0 Data Buffer MSB
ECReg	VHSGCDBL      	_at_ 0x191C;	// Voltage High Scale Gain-error Calibration Data Buffer LSB
ECReg   VHSGCDBM        _at_ 0x191D;    // Voltage High Scale Gain-error Calibration Data Buffer MSB

ECReg   VCMPSCP         _at_ 0x1937;    // Voltage Compare Scan Period
ECReg   VCH4CTL         _at_ 0x1938;    // Voltage Channel 4 Control Register
ECReg   VCH4DATM        _at_ 0x1939;    // Volt Channel 4 Data Buffer MSB
ECReg   VCH4DATL        _at_ 0x193A;    // Volt Channel 4 Data Buffer LSB
ECReg   VCH5CTL         _at_ 0x193B;    // Voltage Channel 5 Control Register
ECReg   VCH5DATM        _at_ 0x193C;    // Volt Channel 5 Data Buffer MSB
ECReg   VCH5DATL        _at_ 0x193D;    // Volt Channel 5 Data Buffer LSB
ECReg   VCH6CTL         _at_ 0x193E;    // Voltage Channel 6 Control Register
ECReg   VCH6DATM        _at_ 0x193F;    // Volt Channel 6 Data Buffer MSB
ECReg   VCH6DATL        _at_ 0x1940;    // Volt Channel 6 Data Buffer LSB
ECReg   VCH7CTL         _at_ 0x1941;    // Voltage Channel 7 Control Register
ECReg   VCH7DATM        _at_ 0x1942;    // Volt Channel 7 Data Buffer MSB
ECReg   VCH7DATL        _at_ 0x1943;    // Volt Channel 7 Data Buffer LSB
ECReg   ADCDVSTS        _at_ 0x1944;    // ADC Data Vaild Status
ECReg   VCMPSTS         _at_ 0x1945;    // Voltage Compare Status
ECReg   VCMP0CTL        _at_ 0x1946;    // Voltage Compare Channel 0 Control Register
ECReg   CMP0THRDATM     _at_ 0x1947;    // Voltage Compare 0 Threshold Data Buffer MSB
ECReg   CMP0THRDATL     _at_ 0x1948;    // Voltage Compare 0 Threshold Data Buffer LSB
ECReg   VCMP1CTL        _at_ 0x1949;    // Voltage Compare Channel 1 Control Register
ECReg   CMP1THRDATM     _at_ 0x194A;    // Voltage Compare 1 Threshold Data Buffer MSB
ECReg   CMP1THRDATL     _at_ 0x194B;    // Voltage Compare 1 Threshold Data Buffer LSB
ECReg   VCMP2CTL        _at_ 0x194C;    // Voltage Compare Channel 2 Control Register
ECReg   CMP2THRDATM     _at_ 0x194D;    // Voltage Compare 2 Threshold Data Buffer MSB
ECReg   CMP2THRDATL     _at_ 0x194E;    // Voltage Compare 2 Threshold Data Buffer LSB
ECReg   VCMPOTR			_at_ 0x194F;    // Voltage Comparator Output Type Register
ECReg   VCMPLR			_at_ 0x1952;    // Voltage Comparator Lock Register

//-----------------------------------------------------------------------------
// (1Axxh) Digital to Analog Converter (DAC) 
//-----------------------------------------------------------------------------
ECReg	DACPWRDN      	_at_ 0x1A01;	// DAC Power Down Register
ECReg	DACDAT0      	_at_ 0x1A02;	// DAC Data Channel 0
ECReg	DACDAT1       	_at_ 0x1A03;	// DAC Data Channel 1
ECReg	DACDAT2        	_at_ 0x1A04;	// DAC Data Channel 2
ECReg	DACDAT3       	_at_ 0x1A05;	// DAC Data Channel 3
ECReg	DACDAT4       	_at_ 0x1A06;	// DAC Data Channel 4
ECReg	DACDAT5       	_at_ 0x1A07;	// DAC Data Channel 5

//-----------------------------------------------------------------------------
// (1Bxxh) Wack-Up control (WUC) 
//-----------------------------------------------------------------------------
ECReg	WUEMR1			_at_ 0x1B00;	// Wake-Up Edge Mode Register 1
ECReg	WUEMR2      	_at_ 0x1B01;	// Wake-Up Edge Mode Register 2
ECReg	WUEMR3       	_at_ 0x1B02;	// Wake-Up Edge Mode Register 3
ECReg	WUEMR4       	_at_ 0x1B03;	// Wake-Up Edge Mode Register 4
ECReg	WUEMR6       	_at_ 0x1B10;	// Wake-Up Edge Mode Register 6
ECReg	WUEMR7       	_at_ 0x1B14;	// Wake-Up Edge Mode Register 7
ECReg   WUEMR8          _at_ 0x1B18;    // Wake-Up Edge Mode Register 8
ECReg   WUEMR9          _at_ 0x1B1C;    // Wake-Up Edge Mode Register 9
ECReg   WUEMR10         _at_ 0x1B20;    // Wake-Up Edge Mode Register 10
ECReg   WUEMR11         _at_ 0x1B24;    // Wake-Up Edge Mode Register 11
ECReg   WUEMR12         _at_ 0x1B28;    // Wake-Up Edge Mode Register 12
ECReg   WUEMR13         _at_ 0x1B2C;    // Wake-Up Edge Mode Register 13
ECReg   WUEMR14         _at_ 0x1B30;    // Wake-Up Edge Mode Register 14
ECReg	WUESR1       	_at_ 0x1B04;	// Wake-Up Edge Sense Register 1
ECReg	WUESR2       	_at_ 0x1B05;	// Wake-Up Edge Sense Register 2
ECReg	WUESR3       	_at_ 0x1B06;	// Wake-Up Edge Sense Register 3
ECReg	WUESR4        	_at_ 0x1B07;	// Wake-Up Edge Sense Register 4
ECReg	WUESR6        	_at_ 0x1B11;	// Wake-Up Edge Sense Register 6
ECReg	WUESR7        	_at_ 0x1B15;	// Wake-Up Edge Sense Register 7
ECReg   WUESR8          _at_ 0x1B19;    // Wake-Up Edge Sense Register 8
ECReg   WUESR9          _at_ 0x1B1D;    // Wake-Up Edge Sense Register 9
ECReg   WUESR10         _at_ 0x1B21;    // Wake-Up Edge Sense Register 10
ECReg   WUESR11         _at_ 0x1B25;    // Wake-Up Edge Sense Register 11
ECReg   WUESR12         _at_ 0x1B29;    // Wake-Up Edge Sense Register 12
ECReg   WUESR13         _at_ 0x1B2D;    // Wake-Up Edge Sense Register 13
ECReg   WUESR14         _at_ 0x1B31;    // Wake-Up Edge Sense Register 14
ECReg	WUENR1        	_at_ 0x1B08;	// Wake-Up Enable Register 1
ECReg	WUENR2       	_at_ 0x1B09;	// Wake-Up Enable Register 2
ECReg	WUENR3       	_at_ 0x1B0A;	// Wake-Up Enable Register 3
ECReg	WUENR4			_at_ 0x1B0B;	// Wake-Up Enable Register 4
ECReg	WUENR6			_at_ 0x1B12;	// Wake-Up Enable Register 6
ECReg	WUENR7			_at_ 0x1B16;	// Wake-Up Enable Register 7
ECReg   WUENR8          _at_ 0x1B1A;    // Wake-Up Enable Register 8
ECReg   WUENR9          _at_ 0x1B1E;    // Wake-Up Enable Register 9

//-----------------------------------------------------------------------------
// (1Cxxh) SMBus Interface (SMB) 
//-----------------------------------------------------------------------------
ECReg	HOSTA_A      	_at_ 0x1C00;	// Host Status A
ECReg	HOSTA_B      	_at_ 0x1C11;	// Host Status B
ECReg	HOSTA_C      	_at_ 0x1C29;	// Host Status C
ECReg	HOSTA_D      	_at_ 0x1C35;	// Host Status D
ECReg	HOCTL_A       	_at_ 0x1C01;	// Host Control A
ECReg	HOCTL_B       	_at_ 0x1C12;	// Host Control B
ECReg	HOCTL_C       	_at_ 0x1C2A;	// Host Control C
ECReg	HOCTL_D       	_at_ 0x1C36;	// Host Control D
ECReg	HOCMD_A       	_at_ 0x1C02;	// Host Command A
ECReg	HOCMD_B       	_at_ 0x1C13;	// Host Command B
ECReg	HOCMD_C       	_at_ 0x1C2B;	// Host Command C
ECReg	HOCMD_D       	_at_ 0x1C37;	// Host Command D
ECReg	TRASLA_A      	_at_ 0x1C03;	// Transmit Slave Address A
ECReg	TRASLA_B      	_at_ 0x1C14;	// Transmit Slave Address B
ECReg	TRASLA_C      	_at_ 0x1C2C;	// Transmit Slave Address C
ECReg	TRASLA_D      	_at_ 0x1C38;	// Transmit Slave Address D
ECReg	D0REG_A       	_at_ 0x1C04;	// Host Data 0 A
ECReg	D0REG_B       	_at_ 0x1C15;	// Host Data 0 B
ECReg	D0REG_C       	_at_ 0x1C2D;	// Host Data 0 C
ECReg	D0REG_D       	_at_ 0x1C39;	// Host Data 0 D
ECReg	D1REG_A       	_at_ 0x1C05;	// Host Data 1 A
ECReg	D1REG_B      	_at_ 0x1C16;	// Host Data 1 B
ECReg	D1REG_C      	_at_ 0x1C2E;	// Host Data 1 C
ECReg	D1REG_D      	_at_ 0x1C3A;	// Host Data 1 D
ECReg	HOBDB_A       	_at_ 0x1C06;	// Host Block Data Byte A
ECReg	HOBDB_B        	_at_ 0x1C17;	// Host Block Data Byte B
ECReg	HOBDB_C        	_at_ 0x1C2F;	// Host Block Data Byte C
ECReg	HOBDB_D        	_at_ 0x1C3B;	// Host Block Data Byte D
ECReg	PECERC_A      	_at_ 0x1C07;	// Packet Error Check A
ECReg	PECERC_B    	_at_ 0x1C18;	// Packet Error Check B
ECReg	PECERC_C    	_at_ 0x1C30;	// Packet Error Check C
ECReg	PECERC_D    	_at_ 0x1C3C;	// Packet Error Check D

ECReg	RESLADR_A		_at_ 0x1C08;	// Receive Slave Adress A
ECReg	RESLADR_B		_at_ 0x1C19;	// Receive Slave Adress B
ECReg	RESLADR_2_A		_at_ 0x1C3F;	// Receive Slave Adress_2 A
ECReg	RESLADR_2_B		_at_ 0x1C44;	// Receive Slave Adress_2 B
ECReg	SLDA_A			_at_ 0x1C09;	// Slave Data A
ECReg	SLDA_B			_at_ 0x1C1A;	// Slave Data B

ECReg	SMBPCTL_A      	_at_ 0x1C0A;	// SMBUS Pin Control A
ECReg	SMBPCTL_B      	_at_ 0x1C1B;	// SMBUS Pin Control B
ECReg	SMBPCTL_C      	_at_ 0x1C31;	// SMBUS Pin Control C
ECReg	SMBPCTL_D      	_at_ 0x1C3D;	// SMBUS Pin Control D

ECReg	SLSTA_A			_at_ 0x1C0B;	// Slave Status A
ECReg	SLSTA_B			_at_ 0x1C1C;	// Slave Status B
ECReg	SICR_A			_at_ 0x1C0C;	// Slave Interrupt Control A
ECReg	SICR_B			_at_ 0x1C1D;	// Slave Interrupt Control B
ECReg	NDADR_A			_at_ 0x1C0D;	// Notify Device Adress A
ECReg	NDADR_B			_at_ 0x1C1E;	// Notify Device Adress B
ECReg	NDLB_A			_at_ 0x1C0E;	// Notify Data Low Byte A
ECReg	NDLB_B			_at_ 0x1C1F;	// Notify Data Low Byte B
ECReg	NDHB_A			_at_ 0x1C0F;	// Notify Data High Byte A
ECReg	NDHB_B			_at_ 0x1C20;	// Notify Data High Byte B

ECReg	HOCTL2_A      	_at_ 0x1C10;	// Host Control2 A
ECReg	HOCTL2_B      	_at_ 0x1C21;	// Host Control2 B
ECReg	HOCTL2_C      	_at_ 0x1C32;	// Host Control2 C
ECReg	HOCTL2_D      	_at_ 0x1C3E;	// Host Control2 D
ECReg	SMB4P7USL   	_at_ 0x1C22;	// 4.7 £gs Low Register
ECReg	SMB4P0USH   	_at_ 0x1C23;	// 4.7 £gs High Register
ECReg	SMB300NS  		_at_ 0x1C24;	// 300 ns Register
ECReg	SMB250NS  		_at_ 0x1C25;	// 250 ns Register
ECReg	SMB25MS   		_at_ 0x1C26;	// 25 ms Register
ECReg	SMB45P3USL 		_at_ 0x1C27;	// 45.3 £gs Low Register
ECReg	SMBS4P3USH 		_at_ 0x1C28;	// 45.3 £gs High Register
ECReg	SMB4P7A4P0H		_at_ 0x1C33;	// 4.7 £gs and 4.0 £gs High Register

ECReg	SLVISEL			_at_ 0x1C34;	// Slave Interface Select
ECReg	SCLKTS_A		_at_ 0x1C40;	// SMCLK Timing Setting Register A
ECReg	SCLKTS_B		_at_ 0x1C41;	// SMCLK Timing Setting Register B
ECReg	SCLKTS_C		_at_ 0x1C42;	// SMCLK Timing Setting Register C
ECReg	SCLKTS_D		_at_ 0x1C43;	// SMCLK Timing Setting Register D
ECReg   SMBFFCTRL1      _at_ 0x1C45;    // SMbus FIFO Control 1 Register
ECReg   SMBFFSTS1       _at_ 0x1C46;    // SMBus FIFO Status 1 Register
ECReg   SMBFFCTRL2      _at_ 0x1C47;    // SMBus FIFO Control 2 Register
ECReg   SMBFFSTS2       _at_ 0x1C48;    // SMBus FIFO Status 2 Register

ECReg   HONACKSRC_A     _at_ 0x1C49;    // HOST Nack Source A
ECReg   HONACKSRC_B     _at_ 0x1C4A;    // HOST Nack Source	B
ECReg   HONACKSRC_C     _at_ 0x1C4B;    // HOST Nack Source	C
ECReg   HONACKSRC_D     _at_ 0x1C4C;    // HOST Nack Source	D
ECReg   SLVFTH          _at_ 0x1C4D;    // Slave FIFO Threshold
ECReg   MSTHTH          _at_ 0x1C4F;    // Master FIFO Threshold
ECReg   MFTHEN          _at_ 0x1C50;    // Master FIFO Threshold Enable
ECReg   MFTISTA         _at_ 0x1C51;    // Master FIFO Threshold Interrupt Status
ECReg   SFTHEN          _at_ 0x1C58;    // Slave FIFO Threshold Enable
ECReg   SFTISTA         _at_ 0x1C59;    // Slave FIFO Threshold Interrupt Status
ECReg   SFFCTL          _at_ 0x1C5E;    // Slave FIFO Control Register
ECReg   SFFSTA          _at_ 0x1C5F;    // Slave FIFO Status
ECReg   I2CW2RF         _at_ 0x1C69;    // I2C Wr to Rd FIFO Register
ECReg   IWRFISTA        _at_ 0x1C6A;    // I2C Wr to Rd FIFO Interrupt Status

//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS) 
//-----------------------------------------------------------------------------
ECReg	KSOL          	_at_ 0x1D00;	// Keyboard Scan Out
ECReg	KSOH1          	_at_ 0x1D01;	// Keyboard Scan Out
ECReg	KSOCTRL      	_at_ 0x1D02;	// Keyboard Scan Out Control
ECReg	KSOH2			_at_ 0x1D03;	// Keyboard Scan Out
ECReg	KSI           	_at_ 0x1D04;	// Keyboard Scan In
ECReg	KSICTRL       	_at_ 0x1D05;	// Keyboard Scan In Control
ECReg	KSIGCTRL       	_at_ 0x1D06;	// Keyboard Scan In [7:0] GPIO Control
ECReg	KSIGOEN       	_at_ 0x1D07;	// Keyboard Scan In [7:0] GPIO Output Enable
ECReg	KSIGDAT       	_at_ 0x1D08;	// Keyboard Scan In [7:0] GPIO DATA
ECReg	KSIGDMRR       	_at_ 0x1D09;	// Keyboard Scan In [7:0] GPIO DATA Mirror
ECReg	KSOHGCTRL       _at_ 0x1D0A;	// Keyboard Scan Out [15:8] GPIO Control
ECReg	KSOHGOEN       	_at_ 0x1D0B;	// Keyboard Scan Out [15:8] GPIO Output Enable
ECReg	KSOHGDMRR       _at_ 0x1D0C;	// Keyboard Scan Out [15:8] GPIO DATA Mirror
ECReg	KSOLGCTRL       _at_ 0x1D0D;	// Keyboard Scan Out [7:0] GPIO Control
ECReg	KSOLGOEN       	_at_ 0x1D0E;	// Keyboard Scan Out [7:0] GPIO Output Enable
ECReg	KSOLGDMRR       _at_ 0x1D0F;	// Keyboard Scan Out [7:0] GPIO DATA Mirror
ECReg   KSO0LSDR        _at_ 0x1D10;    // KSO 0 Low Scan Data Register
ECReg   KSO1LSDR        _at_ 0x1D11;    // KSO 1 Low Scan Data Register
ECReg   KSO2LSDR        _at_ 0x1D12;    // KSO 2 Low Scan Data Register
ECReg   KSO3LSDR        _at_ 0x1D13;    // KSO 3 Low Scan Data Register
ECReg   KSO4LSDR        _at_ 0x1D14;    // KSO 4 Low Scan Data Register
ECReg   KSO5LSDR        _at_ 0x1D15;    // KSO 5 Low Scan Data Register
ECReg   KSO6LSDR        _at_ 0x1D16;    // KSO 6 Low Scan Data Register
ECReg   KSO7LSDR        _at_ 0x1D17;    // KSO 7 Low Scan Data Register
ECReg   KSO8LSDR        _at_ 0x1D18;    // KSO 8 Low Scan Data Register
ECReg   KSO9LSDR        _at_ 0x1D19;    // KSO 9 Low Scan Data Register
ECReg   KSO10LSDR       _at_ 0x1D1A;    // KSO 10 Low Scan Data Register
ECReg   KSO11LSDR       _at_ 0x1D1B;    // KSO 11 Low Scan Data Register
ECReg   KSO12LSDR       _at_ 0x1D1C;    // KSO 12 Low Scan Data Register
ECReg   KSO13LSDR       _at_ 0x1D1D;    // KSO 13 Low Scan Data Register
ECReg   KSO14LSDR       _at_ 0x1D1E;    // KSO 14 Low Scan Data Register
ECReg   KSO15LSDR       _at_ 0x1D1F;    // KSO 15 Low Scan Data Register
ECReg   KSO16LSDR       _at_ 0x1D20;    // KSO 16 Low Scan Data Register
ECReg   KSO17LSDR       _at_ 0x1D21;    // KSO 17 Low Scan Data Register
ECReg   SDC1R           _at_ 0x1D22;    // Scan Data Control 1 Register
ECReg   SDC2R           _at_ 0x1D23;    // Scan Data Control 2 Register
ECReg   SDC3R           _at_ 0x1D24;    // Scan Data Control 3 Register
ECReg   SDSR            _at_ 0x1D25;    // Scan Data Control 4 Register
//-----------------------------------------------------------------------------
// (1Exxh) EC Clock and Power Management controller (ECPM) 
//-----------------------------------------------------------------------------
ECReg	CGCTRL1R    	_at_ 0x1E01;	// Clock Gating Control 1
ECReg	CGCTRL2R      	_at_ 0x1E02;	// Clock Gating Control 2
ECReg	CGCTRL3R		_at_ 0x1E05;	// Clock Gating Control 3
ECReg	PLLCTRL        	_at_ 0x1E03;	// PLL Control
ECReg	AUTOCG			_at_ 0x1E04;	// Auto Clock Gating
ECReg	PLLFREQR		_at_ 0x1E06;	// PLL Frequency
ECReg	PLLSSCR			_at_ 0x1E07;	// PLL Frequency
ECReg   PLLCSS          _at_ 0x1E08;    // PLL Clock Source Status
ECReg   CGCTRL4R        _at_ 0x1E09;    // Clock Gating Control 4 Register
//-----------------------------------------------------------------------------
// (1Fxxh) External Timer & External Watchdog (ETWD) 
//-----------------------------------------------------------------------------
ECReg	ETWCFG        	_at_ 0x1F01;	// External Timer/WDT Configuration Register
ECReg	ETPSR         	_at_ 0x1F02;	// External Timer Prescaler Register
ECReg	ETCNTLHR     	_at_ 0x1F03;	// External Timer Counter High Byte
ECReg	ETCNTLLR      	_at_ 0x1F04;	// External Timer Counter Low Byte
ECReg	ETWCTRL      	_at_ 0x1F05;	// External Timer/WDT Control Register
ECReg	EWDCNTLR      	_at_ 0x1F06;	// External WDT Counter Low Byte
ECReg	EWDKEYR      	_at_ 0x1F07;	// External WDT Key Register
ECReg	EWDCNTHR		_at_ 0x1F09;	// External WDT Counter High Byte

ECReg	ET2PSR      	_at_ 0x1F0A;	// External Timer 2 Prescaler Register
ECReg	ET2CNTLHR      	_at_ 0x1F0B;	// External Timer 2 Counter High Byte
ECReg	ET2CNTLLR      	_at_ 0x1F0C;	// External Timer 2 Counter Low Byte
ECReg	ET2CNTLH2R		_at_ 0x1F0E;	// External Timer 2 Counter High Byte 

//-----------------------------------------------------------------------------
// General Control (GCTRL) (20xxh)
//-----------------------------------------------------------------------------
ECReg	ECHIPID1		_at_ 0x2000;	// Chip ID Byte 1
ECReg	ECHIPID2		_at_ 0x2001;	// Chip ID Byte 2
ECReg	ECHIPVER		_at_ 0x2002;	// Chip Version
ECReg	IDR				_at_ 0x2004;	// Identify Input Register
ECReg	RSTS			_at_ 0x2006;	// Reset Status
ECReg	RSTC1			_at_ 0x2007;	// Reset Control 1
ECReg	RSTC2			_at_ 0x2008;	// Reset Control 2
ECReg	RSTC3			_at_ 0x2009;	// Reset Control 3
ECReg	RSTC4			_at_ 0x2011;	// Reset Control 4
ECReg	RSTDMMC			_at_ 0x2010;	// Reset Control DMMC
ECReg	BADRSEL			_at_ 0x200A;	// Base Address Select
ECReg	WNCKR			_at_ 0x200B;	// Wait Next Clock Rising
ECReg	OSCTRL			_at_ 0x200C;	// Oscillator Control Register
ECReg	SPCTRL1			_at_ 0x200D;	// Special Control 1
ECReg	RSTCH			_at_ 0x200E;	// Reset Control Host Side
ECReg	GENIRQ			_at_ 0x200F;	// Generate IRQ
ECReg	SPECTRL2		_at_ 0x2012;	// Special Control 2
ECReg	SPECTRL3		_at_ 0x2016;	// Special Control 3

ECReg	PI2ECH			_at_ 0x2014;	// Port I2EC High-Byte Register
ECReg	PI2ECL			_at_ 0x2015;	// Port I2EC Low-Byte Register
ECReg	BINTADDR0R		_at_ 0x2019;	// BRAM Interrupt Address 0 Register
ECReg	BINTADDR1R		_at_ 0x201A;	// BRAM Interrupt Address 1 Register
ECReg	BINTCTRLR		_at_ 0x201B;	// BRAM Interrupt Control Register
ECReg   SPCTRL4         _at_ 0x201C;    // Special Control 4

ECReg   SHA1HASHCTRLR   _at_ 0x202D;    // SHA1 Hash Control Register
ECReg   SHA1HBADDR      _at_ 0x202E;    // SHA1 Hash Base Address Register
//-----------------------------------------------------------------------------
// (21xxh) External GPIO Controller (EGPC) 
//-----------------------------------------------------------------------------
ECReg	EADDR			_at_ 0x2100;	// External GPIO Address Register
ECReg	EDAT			_at_ 0x2101;	// External GPIO Data Register
ECReg	ECNT			_at_ 0x2102;	// External GPIO Control Register
ECReg	ESTS			_at_ 0x2103;	// External GPIO Status Register

//-----------------------------------------------------------------------------
// (22xxh) Battery-Backed SRAM (BRAM) 
//-----------------------------------------------------------------------------
ECReg	BRAM[64]		_at_ 0x2280;	// 64 bytes bram

//-----------------------------------------------------------------------------
// (23xxh) Consumer IR (CIR) 
//-----------------------------------------------------------------------------
ECReg	C0DR			_at_ 0x2300;	// CIR Data Register
ECReg	C0MSTCR			_at_ 0x2301; 	// CIR Master Control Register
ECReg	C0IER			_at_ 0x2302; 	// CIR Interrupt Enable Register
ECReg	C0IIR			_at_ 0x2303;	// CIR Interrupt Identification Register
ECReg	C0CFR			_at_ 0x2304;	// CIR Carrier Frequency Register
ECReg	C0RCR			_at_ 0x2305;	// CIR Receive Control Register
ECReg	C0TCR			_at_ 0x2306;	// CIR Transmitter Register
ECReg	C0SCK			_at_ 0x2307;	// CIR for sleep mode
ECReg	C0BDLR			_at_ 0x2308;	// CIR Baud Rate Divisor Low Byte Register
ECReg	C0BDHR			_at_ 0x2309;	// CIR Baud Rate Divisor High Byte Register
ECReg	C0TFSR			_at_ 0x230A;	// CIR Transmitter FIFO Status Register
ECReg	C0RFSR			_at_ 0x230B;	// CIR Receiver FIFO Status Register
ECReg	C0WCSSR			_at_ 0x230C;	// CIR Wakeup Code Set Select Register
ECReg	C0WCL			_at_ 0x230D;	// CIR Wakeup Code Length Register
ECReg	C0WCR			_at_ 0x230E;	// CIR Wakeup Code Read/Write Register
ECReg	C0WPS			_at_ 0x230F;	// CIR Wakeup Code Power Control/Status Register
ECReg	CSCRR			_at_ 0x2310;	// CIR Scratch Register

//-----------------------------------------------------------------------------
// (25xxh) Debugger (DBGR) 
//-----------------------------------------------------------------------------
ECReg 	BKA1L           _at_ 0x2510;	// Trigger 1 Address Low Byte Register
ECReg 	BKA1M           _at_ 0x2511;	// Trigger 1 Address Middle Byte Register
ECReg 	BKA1H           _at_ 0x2512;	// Trigger 1 Address High Byte Register
ECReg 	BKA2L           _at_ 0x2513;	// Trigger 2 Address Low Byte Register
ECReg 	BKA2M           _at_ 0x2514;	// Trigger 2 Address Middle Byte Register
ECReg 	BKA2H           _at_ 0x2515;	// Trigger 2 Address High Byte Register
ECReg 	BKA3L           _at_ 0x2516;	// Trigger 3 Address Low Byte Register
ECReg 	BKA3M           _at_ 0x2517;	// Trigger 3 Address Middle Byte Register
ECReg 	BKA3H           _at_ 0x2518;	// Trigger 3 Address High Byte Register

//-----------------------------------------------------------------------------
// (26xxh) Serial Peripheral Interface (SSPI) 
//-----------------------------------------------------------------------------
ECReg 	SPIDATA			_at_ 0x2600;	// SPI Data Register
ECReg 	SPICTRL1		_at_ 0x2601;	// SPI Control 1 Register
ECReg 	SPICTRL2		_at_ 0x2602;	// SPI Control 2 Register
ECReg 	SPICTRL3		_at_ 0x2604;	// SPI Control 3 Register
ECReg 	SPISTS			_at_ 0x2603;	// SPI Status Register

//-----------------------------------------------------------------------------
// (27xxh) Extern Serial Port (UART1) 
//-----------------------------------------------------------------------------
ECReg 	UART1_RBR		_at_ 0x2700;	// Receiver Buffer Register
ECReg 	UART1_IER		_at_ 0x2701;	// Interrupt Enable Register
ECReg 	UART1_IIR		_at_ 0x2702;	// Interrupt Identification Register
ECReg 	UART1_LCR		_at_ 0x2703;	// Line Control Register
ECReg 	UART1_MCR		_at_ 0x2704;	// Modem Control Register
ECReg 	UART1_LSR		_at_ 0x2705;	// Line Status Register
ECReg 	UART1_MSR		_at_ 0x2706;	// Modem Status Register
ECReg 	UART1_SCR		_at_ 0x2707;	// Scratch Pad Register
ECReg 	UART1_ECSPMR	_at_ 0x2708;	// EC Serial Port Mode Register

//-----------------------------------------------------------------------------
// (28xxh) Extern Serial Port (UART2) 
//-----------------------------------------------------------------------------
ECReg 	UART2_RBR		_at_ 0x2800;	// Receiver Buffer Register
ECReg 	UART2_IER		_at_ 0x2801;	// Interrupt Enable Register
ECReg 	UART2_IIR		_at_ 0x2802;	// Interrupt Identification Register
ECReg 	UART2_LCR		_at_ 0x2803;	// Line Control Register
ECReg 	UART2_MCR		_at_ 0x2804;	// Modem Control Register
ECReg 	UART2_LSR		_at_ 0x2805;	// Line Status Register
ECReg 	UART2_MSR		_at_ 0x2806;	// Modem Status Register
ECReg 	UART2_SCR		_at_ 0x2807;	// Scratch Pad Register
ECReg 	UART2_ECSPMR	_at_ 0x2808;	// EC Serial Port Mode Register

//-----------------------------------------------------------------------------
// (29xxh) 8 Bit Timer (TMR)
//-----------------------------------------------------------------------------
ECReg	PRSC			_at_ 0x2900;	// TMR Prescaler Register
ECReg	GCSMS			_at_ 0x2901;	// Group Clock Source and Mode Select Register
ECReg	CTR_A0			_at_ 0x2902;	// A0 Cycle Time Register
ECReg	CTR_A1			_at_ 0x2903;	// A1 Cycle Time Register
ECReg	CTR_B0			_at_ 0x2904;	// B0 Cycle Time Register
ECReg	CTR_B1			_at_ 0x2905;	// B1 Cycle Time Register
ECReg	DCR_A0			_at_ 0x2906;	// A0 Duty Time Register
ECReg	DCR_A1			_at_ 0x2907;	// A1 Duty Time Register
ECReg	DCR_B0			_at_ 0x2908;	// B0 Duty Time Register
ECReg	DCR_B1			_at_ 0x2909;	// B1 Duty Time Register
ECReg	CCGSR			_at_ 0x290A;	// Channel Clock Group Select Register
ECReg	TMRCE			_at_ 0x290B;	// TMR Clock Enable Register
ECReg	TMEIE			_at_ 0x290C;	// TMR Interrupt Enable Register

//-----------------------------------------------------------------------------
// (2Exxh) Consumer Electronics Control (CEC)
//-----------------------------------------------------------------------------
ECReg   CECDR          _at_ 0x2E00;    // CEC Data Register
ECReg   CECFSTS        _at_ 0x2E01;    // CEC FIFO Status Register
ECReg   CECDLA         _at_ 0x2E02;    // CEC Device Logical Address Register
ECReg   CECCTRL        _at_ 0x2E03;    // CEC Control Register
ECReg   CECSTS         _at_ 0x2E04;    // CEC Status Register
ECReg   CECIE          _at_ 0x2E05;    // CEC Interrupt Enable Register
ECReg   CECOPSTS       _at_ 0x2E06;    // CEC Operation Status Register
ECReg   CECCRH         _at_ 0x2E07;    // CEC Received Header Register

//-----------------------------------------------------------------------------
// (30xxh) Platform Environment Control Interface (PECI)
//-----------------------------------------------------------------------------
ECReg   HOSTAR          _at_ 0x3000;    // Host Status Register
ECReg   HOCTLR          _at_ 0x3001;    // Host Control Register
ECReg   HOCMDR          _at_ 0x3002;    // Host Command Register
ECReg   HOTRADDR        _at_ 0x3003;    // Host Target Address Register
ECReg   HOWRLR          _at_ 0x3004;    // Host Write Length Register
ECReg   HORDLR          _at_ 0x3005;    // Host Read Length Register
ECReg   HOWRDR          _at_ 0x3006;    // Host Write Data Register
ECReg   HORDDR          _at_ 0x3007;    // Host Read Data Register

ECReg   HOCTL2R         _at_ 0x3008;    // Host Control 2 Register
ECReg   RWFCSV          _at_ 0x3009;    // Received Write FCS Value
ECReg   RRFCSV          _at_ 0x300A;    // Received Read FCS Value
ECReg   WFCSV           _at_ 0x300B;    // Write FCS Value
ECReg   RFCSV           _at_ 0x300C;    // Read FCS Falue
ECReg   AWFCSV          _at_ 0x300D;    // Assured Write FCS Value
ECReg   PADCTLR         _at_ 0x300E;    // Pad Control Register
