/*-----------------------------------------------------------------------------
 * TITLE: CORE_CHIPSFR.H
 *
 * STD Special Function Registers (SFR) Declaration and Bit Definition.
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 * ------------------------------------------------------------------------- */
 
#ifndef CORE_CHIPSFR_H
#define CORE_CHIPSFR_H

//-----------------------------------------------------------------
// Standard 8051 SFR 
//-----------------------------------------------------------------
sfr P0   = 0x80;
sfr P1   = 0x90;
sfr P2   = 0xA0;
sfr P3   = 0xB0;
sfr PSW  = 0xD0;
sfr ACC  = 0xE0;
sfr B    = 0xF0;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr CKCON = 0x8E;
sfr IE   = 0xA8;
sfr IP   = 0xB8;
sfr SCON = 0x98;
sfr SBUF = 0x99;

sfr T2CON  = 0xC8;
sfr T2MOD  = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2	   = 0xCC;
sfr TH2	   = 0xCD;
sfr WDTCON = 0xD8;

sfr MPRECF = 0xF7;

sbit WDTEB	= 0xD9;		// Watch dog register
sbit WDTRST = 0xD8;

//-----------------------------------------------------------------
// Bit register
//-----------------------------------------------------------------	
sbit CY   = 0xD7;
sbit AC   = 0xD6;
sbit F0   = 0xD5;
sbit RS1  = 0xD4;
sbit RS0  = 0xD3;
sbit OV   = 0xD2;
sbit P    = 0xD0;		// PSW  

sbit TF1  = 0x8F;
sbit TR1  = 0x8E;
sbit TF0  = 0x8D;
sbit TR0  = 0x8C;
sbit IE1  = 0x8B;
sbit IT1  = 0x8A;
sbit IE0  = 0x89;
sbit IT0  = 0x88;		// TCON 

sbit EA   = 0xAF;
sbit ET2  = 0xAD;
sbit ES   = 0xAC;
sbit ET1  = 0xAB;
sbit EX1  = 0xAA;
sbit ET0  = 0xA9;
sbit EX0  = 0xA8;		// IE  

sbit PS   = 0xBC;
sbit PT1  = 0xBB;
sbit PX1  = 0xBA;
sbit PT0  = 0xB9;
sbit PX0  = 0xB8;		// IP 

sbit RD   = 0xB7;
sbit WR   = 0xB6;
sbit T1   = 0xB5;
sbit T0   = 0xB4;
sbit INT1 = 0xB3;
sbit INT0 = 0xB2;
//sbit TXD  = 0xB1;
//sbit RXD  = 0xB0;

sbit SM0  = 0x9F;
sbit SM1  = 0x9E;
sbit SM2  = 0x9D;
sbit REN  = 0x9C;
sbit TB8  = 0x9B;
sbit RB8  = 0x9A;
sbit TI   = 0x99;
sbit RI   = 0x98;		// SCON 

sbit TF2  	= 0xCF;
sbit EXF2  	= 0xCE;
sbit RCLK  	= 0xCD;
sbit TCLK  	= 0xCC;
sbit EXEN2  = 0xCB;
sbit TR2  	= 0xCA;
sbit CT2 	= 0xC9;
sbit CPRL2  = 0xC8;		// T2CON 

#endif  
