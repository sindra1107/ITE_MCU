/*-----------------------------------------------------------------------------
 * TITLE: OEM_INIT.C
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Oem_StartUp
//----------------------------------------------------------------------------
void Oem_StartUp(void)
{

}

//----------------------------------------------------------------------------
// Oem_Initialization - Initialize the registers, data variables, and oem 
// functions after kernel init. function.
//----------------------------------------------------------------------------
void Oem_Initialization(void)
{
	Init_GPIO();
    
    #ifdef HSPI
	GPIO_HSPI_INIT();
    #endif

    #ifdef SPIReadMode
    ChangeSPIFlashReadMode(SPIReadMode);
    #endif

    #ifdef HSRSMode
    ChangeHSRSMode(HSRSMode);
    #endif

    #ifdef PLLFrequency
    ChangePLLFrequency(PLLFrequency);
    #endif

    #ifdef PECI_Support
    Init_PECI();
    #endif

	Init_Regs();

    #ifdef SMBusChannel4Support
    InitSMBusChannel4();
    #endif
	Init_SMBus_Regs();
    
    #if ADCFuncSupport    
	Init_ADC();
    #endif

    #if CIRFuncSupport	
	Init_CIR();
    #endif

	Init_Cache();
	Init_PS2Port();
    
    #ifdef SysMemory2ECRam	
	InitSysMemory2ECRam();
    #endif
    
    InitSMBus();
    ResetSCIEvent();
	Init_OEMVariable();
    
	if(ExtendScanPin==0x02)		// KSO16 and KSO17 are used.
	{  
		if(ExternMatrixGPO)
		{
			ExtendScanPin++;
		}
	}
}

//----------------------------------------------------------------------------
// The function of init. registers 
//----------------------------------------------------------------------------
//const struct REG_INIT_DEF code reg_init_table[] = 
const sREG_INIT_DEF code reg_init_table[] = 
{
        { &FMSSR 		,Init_FMSSR         }, 	// share rom size
// HOST interface
    	{ &SPCTRL1      ,Init_I2EC          },  // Enable I2EC R/W
    	{ &BADRSEL      ,Init_BADR          },  // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define
    	{ &SWCBALR      ,Init_SWCBALR       },
    	{ &SWCBAHR      ,Init_SWCBAHR       },
		{ &RSTS			,0x84				},	

// KBC and PM interface
		{ &KBIRQR 		,0x00              	}, 	// Disable KBC IRQ
        { &KBHICR 		,IBFCIE+PM1ICIE     }, 	// KBC port control IBFCIE+PMICIE
        { &PM1CTL		,IBFIE+SCINP        }, 	// EC port control  IBFCIE+SCI low active
        { &PM2CTL 		,IBFIE+SCINP        }, 	// EC port2 control IBFCIE+SCI low active  
// KBC and PM3 interface
        #ifdef PMC3_Support
        { &PM3CTL 		,IBFIE         	    }, 	// PMC3 input buffer full interrupt enable
        #endif	

// PS2
        { &PSCTL1 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL2 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
        { &PSCTL3 		,PS2_InhibitMode    }, 	// Enable Debounce,Receive mode, Inhibit CLK
		//{ &PSINT1		,0x06				}, 	// Transation Done,Start Clock Interrupt
        //{ &PSINT2		,0x06				},	// Transation Done,Start Clock Interrupt 
        //{ &PSINT3		,0x06				},	// Transation Done,Start Clock Interrupt 

// Key Scan
        { &KSOCTRL   	,KSOOD + KSOPU      },	//
  		{ &KSICTRL   	,KSIPU       		},	//
	
// ADC								
  		{ &ADCSTS    	,AINITB             }, 	// Enable Analog accuracy initialization
        //{ &ADCSTS    	,0                 	}, 	// Stop adc accuracy initialization
        { &ADCSTS    	,0x80          		}, 	// Stop adc accuracy initialization
		{ &ADCCFG    	,0         			}, 	//
        { &KDCTL     	,AHCE              	}, 	// Enable Hardware Callibration
		{ &ADCCFG    	,DFILEN  		    },	// Enable Digital Filter enable,
		{ &ADCCTL		,0x15				},

// DAC
        { &DACPWRDN  	,0x00              	}, 	//
    
//PWM
		{ &ZTIER        ,0x00       		},   // Disable
        { &CTR      	,0xC8      		    },   //	Set CTR = 200 Duty Cycle output = (DCRi)/(CTR+1)
       	//{ &C0CPRS 	,0x2D      		    },   // Beep F =1KHz
		{ &C4CPRS    	,0xE3				},	 // 
		{ &C4MCPRS	    ,0x00				},   //
		{ &C6CPRS    	,0x01				},	 // F =23KHz
		{ &C6MCPRS		,0x00				},	 //
		{ &C7CPRS    	,0xE3				},	 // brightness = 200 HZ
		{ &C7MCPRS		,0x00				},   //
		{ &PCFSR        ,0x8A      		    },   // bit7=1: Disable CR256 channel 1 output. bit0-bit3: 0 => select 32.768 kHz, 1=> select EC clock frequency
        { &PCSSGL       ,0x50      		    },   // Select channel 0-3 Group
		{ &PCSSGH       ,0xC0				},	 // Select channel 4-7 Group
		{ &ZTIER        ,0x02       		},   // Enable
        { &DCR2         ,0x00      		    },   //	Default 
        { &DCR3         ,0x00      		    },   // Default 
        //{ &DCR7         ,0x00      		},   // Default 
};

void Init_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(reg_init_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = reg_init_table[index].address;
		*Tmp_XPntr = reg_init_table[index].initdata;
        index ++;
    }
}

//const struct REG_INIT_DEF code Init_SMBus_table[] = 
const sREG_INIT_DEF code Init_SMBus_table[] = 
{
// SMBus          
	    { &SMB4P7USL	, 0x28				},	// 100K	
	    { &SMB4P0USH  	, 0x25      		},  
        { &SMB300NS     , 0x03      		},  
        { &SMB250NS     , 0x02      		},   
        { &SMB25MS      , 0x19      		},   
        { &SMB45P3USL   , 0xA5      		},  
        { &SMBS4P3USH   , 0x01      		},   
        { &SMB4P7A4P0H	, 0x00      		},  
     
        { &HOCTL2_A 	, 0x01      		},  
        { &HOCTL_A   	, 0x03      		},  
        { &HOCTL_A  	, 0x01      		},  
        { &HOSTA_A    	, 0xFF      		},  
        
        { &HOCTL2_B   	, 0x01      		},  
        { &HOCTL_B    	, 0x03      		},	
        { &HOCTL_B    	, 0x01      		},	
        { &HOSTA_B    	, 0xFF      		},	
        
    	{ &HOCTL2_C		, 0x01				},	 
   	 	{ &HOCTL_C		, 0x03				},	 
   		{ &HOCTL_C		, 0x01				},	 
    	{ &HOSTA_C		, 0xFF				},
            
        #ifdef SMBusChannel4Support
    	{ &HOCTL2_D		, 0x01				},	 
   	 	{ &HOCTL_D		, 0x03				},	 
   		{ &HOCTL_D		, 0x01				},	 
    	{ &HOSTA_D		, 0xFF				},
        #endif
};

void Init_SMBus_Regs(void)
{
	BYTE index = 0x00;
    while(index < (sizeof(Init_SMBus_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_SMBus_table[index].address;
		*Tmp_XPntr = Init_SMBus_table[index].initdata;
        index ++;
    }
}

//----------------------------------------------------------------------------
// The function of clearing external ram for OEM code
// Clear external ram (0x100~0xFFF)
//----------------------------------------------------------------------------
void Init_ClearRam(void)
{
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x100;
    while(byte_register_pntr<0x1000)// Clear external ram (0x100~0xFFF)
    {
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }							
}

//----------------------------------------------------------------------------
// The function of DMA for scratch sram
//----------------------------------------------------------------------------
const sDMAScratchSRAM code asDMAScratchSRAM[]=    // For 8500 Dino
{
	{	&SCRA1H,	&SCRA1M,	&SCRA1L	},		// 1024 bytes (externl ram 0x800 ~ 0xBFF)
	{	&SCRA2H,	&SCRA2M,	&SCRA2L	},		// 512 bytes  (externl ram 0xC00 ~ 0xDFF)
	{	&SCRA3H,	&SCRA3M,	&SCRA3L	},		// 256 bytes  (externl ram 0xE00 ~ 0xEFF)
	{	&SCRA4H,	&SCRA4M,	&SCRA4L	}		// 256 bytes  (externl ram 0xF00 ~ 0xFFF)

};
void  CacheDma(BYTE sramnum,WORD addr)
{
	*asDMAScratchSRAM[sramnum].scarh = 0x80;
	*asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;   	// high byte of function address
	*asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;	// low byte of function address
	*asDMAScratchSRAM[sramnum].scarh = 0x00;	// start cache dma     			
}

//----------------------------------------------------------------------------
// Init. DMA for scratch sram
//----------------------------------------------------------------------------
void Init_Cache(void)
{
#ifdef ITE8500					// Dino For 8500 no cache ram 0x800 ~ 0xFFF

#else
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        CacheDma(3, HSPI_RamCode);  // Cache to memory 0xF00 ~ 0xFFF
        #endif
    #endif
#endif

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//----------------------------------------------------------------------------
// Select touch pad, mouse, and keyboard port number
//----------------------------------------------------------------------------
void Init_PS2Port(void)
{

}

//----------------------------------------------------------------------------
// Function Name : Init_OEMVariable
// Purpose : setup default variable when EC reset
//----------------------------------------------------------------------------
void Init_OEMVariable(void)
{
    Init_Brightness();
	LED_FLASH_CNT = 0x0001;	// for LED control
    
	SysPowState=SYSTEM_S5;		
	if(BRAM[63]==0x55&&ShutDnCause == SC_IntWatchDog)
	{
		BRAM[63]=0x00;
		CLEAR_MASK(KBHISR,SYSF);	
        Ccb42_SYS_FLAG=0;
		DelayDoPowerSeq=250;
		Oem_TriggerS5S0();
	}
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      Before jump to main function [WinFlashMark = 0x33;] is necessary.
//----------------------------------------------------------------------------
void Hook_ECExitFollowMode(void)
{
    Init_Cache();
    
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        SET_MASK(IER7,Int_DeferredSPI); // Enable HSPI interrupt
        #endif
    #endif 
    
    InitSMBus();
    
    #if Insyde_Bios
    if(RamCodePort==0x64)   // for insyde bios
    {
        KBHIKDOR = 0xFA;
    }
    else if(RamCodePort==0x66)
    {
	    PM1DO = 0xFA;
    }	
    else if(RamCodePort==0x6C)
    {
	    PM2DO = 0xFA;
    }  
    #endif
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      1. Before jump to main function if want to keep EC setting [return(0x33);] is necessary.
//      2. If you don't understand the use of Hook_ECRetunrMainFuncKeepCondition function, 
//          don't change anything.
//      3. Always at bank0 (0x9000)
//----------------------------------------------------------------------------
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if(WinFlashMark==0x33)
    {
        return(0x33);
    }
    else
    {
        return(0x00);
    }
}