/*----------------------------------------------------------------------------
 * TITLE: CORE_SMBUS.C - the System Management SMBus Protocol drivers.
 *
 *---------------------------------------------------------------------------*/
 
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

//----------------------------------------------------------------------------
// Read/write SMbus byte/word function	
//----------------------------------------------------------------------------
const sSMBus code asSMBus[]=
{
	{ &HOCTL_A, &TRASLA_A, &HOCMD_A, &HOSTA_A, &D0REG_A, &D1REG_A,	&HOBDB_A,	&IER1,	&ISR1,  Int_SMBUS0,   &PECERC_A},
	{ &HOCTL_B, &TRASLA_B, &HOCMD_B, &HOSTA_B, &D0REG_B, &D1REG_B,	&HOBDB_B,	&IER1,	&ISR1,  Int_SMBUS1,   &PECERC_B},
	{ &HOCTL_C, &TRASLA_C, &HOCMD_C, &HOSTA_C, &D0REG_C, &D1REG_C,	&HOBDB_C,	&IER2,	&ISR2,	Int_SMBUS2,   &PECERC_C},
	{ &HOCTL_D, &TRASLA_D, &HOCMD_D, &HOSTA_D, &D0REG_D, &D1REG_D,	&HOBDB_D,	&IER0,	&ISR0,	Int_SMBUS3,   &PECERC_D}	
};

const sResetSMBusS code asResetSMBusS[]=
{
	{ &HOSTA_A, &HOCTL2_A, &SMBPCTL_A, &GPCRB3, &GPCRB4, &GPDRB,	(BIT3+BIT4),   &SMBus1RecoverCunt },
	{ &HOSTA_B, &HOCTL2_B, &SMBPCTL_B, &GPCRC1, &GPCRC2, &GPDRC,	(BIT1+BIT2),   &SMBus2RecoverCunt },
	{ &HOSTA_C, &HOCTL2_C, &SMBPCTL_C, &GPCRF6, &GPCRF7, &GPDRF,	(BIT6+BIT7),   &SMBus3RecoverCunt },
	{ &HOSTA_D, &HOCTL2_D, &SMBPCTL_D, &GPCRH1, &GPCRH2, &GPDRH,	(BIT1+BIT2),   &SMBus4RecoverCunt }
}; 

//----------------------------------------------------------------------------
// 	
//----------------------------------------------------------------------------
void DelayInact(void) 
{
    BYTE index;
    BYTE counter;
   for(index=0;index<200;index++)
   {
        counter++;
   }
}

//----------------------------------------------------------------------------
// The function of reseting SMbus 	
//----------------------------------------------------------------------------
void ResetSMBus(BYTE Channel)
{
    #ifdef PECI_Support
    if(Channel==SMbusCh3)
    {
        return;
    }
    #endif

    SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_KILL);
    CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_KILL);
	//RSTC3=0x0F;					            // Reset all SMBus module
	*asResetSMBusS[Channel].SMBusSTA = 0xFE;	// clear bits
    *asResetSMBusS[Channel].SMBusPin0 = OUTPUT;
	*asResetSMBusS[Channel].SMBusPin1 = OUTPUT;
	DelayInact();
	*asResetSMBusS[Channel].GPIOReg |= asResetSMBusS[Channel].GPIOData;
	DelayInact();
    *asResetSMBusS[Channel].SMBusPin0 = ALT;
	*asResetSMBusS[Channel].SMBusPin1 = ALT;
	*asResetSMBusS[Channel].SMBusCTL2 = 0x02;
	*asResetSMBusS[Channel].SMBusPinCTL = 0x03;
	DelayInact();
	*asResetSMBusS[Channel].SMBusPinCTL = 0x07;
	*asResetSMBusS[Channel].SMBusCTL2 = 0x01;

    #ifdef SMBusServiceCenterFunc
    *asSSC[Channel].inusing=0x00;
    CLEAR_MASK(*asSMBus[Channel].SMBusIER, asSMBus[Channel].IERFlag);
    *asSMBus[Channel].SMBusISR = asSMBus[Channel].IERFlag;
    *asSSC[Channel].serviceflag=0x00;
    //Init_SMBus_Regs();
    
    if(DB_SMBusAck1==ACK_Start)     // For SMBus utility
    {
        DB_SMBusAddr=0x00;
        if(Channel==0x00)
        {
	        DB_SMBusFlag1=0x00;		
        }
        else if(Channel==0x01)
        {
            DB_SMBusFlag2=0x00;
        }
        else if(Channel==0x02)
        {
            DB_SMBusFlag3=0x00;	
        }				
				
	    DB_SMBusACDID=0x00;	
        DB_SMBusAck1 = ACK_Error;   // For SMBus utility error ACK.
    }
    #endif
}

//----------------------------------------------------------------------------
// SMbus read byte/word and write byte/word function	
//----------------------------------------------------------------------------
BYTE bRWSMBus(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE PECSupport)
{	
	BYTE counter;
	BYTE error;
    BYTE status;
    BYTE resutl;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
    {
        resutl = FALSE;                             // SMBus interface can't be used.
    }
    else
    {
        error = 0xEE;                               // Pre-set error
        resutl = FALSE;                             // Pre-set result is fail
    
        SMBCRC8_A=0x00;                             // Clear CRC variable

	    if (Protocol&0x80)	                        // Write byte function
	    {	
	        if(PECSupport)    
            {   
                CalcCRC8(Addr);                     // To calculate crc8
            }
		    *asSMBus[Channel].SMBusADR = Addr;      // set address with writing bit
	        if(PECSupport)    
            {   
                CalcCRC8(Comd);                     // To calculate crc8
            }
	        *asSMBus[Channel].SMBusCMD=Comd;	    // Set command
		    Protocol&=(~0x80);
            if(PECSupport)    
            {   
                CalcCRC8(*Var);                     // To calculate crc8
            }
		    *asSMBus[Channel].SMBusData0 = *Var;    // set data1
		    if(Protocol==SMbusRW)		            // write word function
		    {
		        if(PECSupport)    
                {   
                    CalcCRC8(*(Var+0x01));          // To calculate crc8
                }
			    *asSMBus[Channel].SMBusData1 = *(Var+0x01);
		    }						                // set data2
	    }	
	    else 						                // Read function
	    {	
		    *asSMBus[Channel].SMBusADR=Addr|0x01;	
            *asSMBus[Channel].SMBusCMD=Comd;	    // Set command
	    }							                // set address with reading bit


	    *asSMBus[Channel].SMBusSTA=0xFE;		    // clear bits
	    if(PECSupport)
        {
            *asSMBus[Channel].SMBusPEC=SMBCRC8_A;
	        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT|HOCTL_PEC_EN);   // Start transaction
        }
        else
        {
	        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);	// Start transaction
        }

	    TR1 = 0;			                        // disable timer1
        ET1 = 0;                  	                // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_26ms>>8;                        // Set timer1 counter 26ms
        TL1 = Timer_26ms;                           // Set timer1 counter 26ms
        TF1 = 0;                  	                // Clear overflow flag
        TR1 = 1;                 	                // Enable timer1

	    while (!TF1)
	    {
            status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
            if(IS_MASK_SET(status, (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
            {
                TR1=0;
			    TF1=0;
                ET1=1;                  	        // Enable timer1 interrupt
                break;
            }
	    }
	
	    if(TF1)                                     // 26ms time-out and no any status bit is set.
	    {
            TR1=0;
		    TF1=0;
            ET1=1;                                  // Enable timer1 interrupt
            ResetSMBus(Channel);
            error = 0xEE;
	    }
        else
        {
            if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
            {
                if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                {
                    ResetSMBus(Channel);
                }
                error = 0xEE;
            }
            else                                    // Only Finish Interrupt bit is set.
            {
                error = 0x00;
            }
        }
	                  	                    
	    if(error == 0xEE)                           // Fail
	    {
		    resutl = FALSE;
	    }
        else                                        // OK
        {
	        if ((*asSMBus[Channel].SMBusADR & 0x01 != 0x00)) 
	        {
		        *Var = *asSMBus[Channel].SMBusData0;    // read data1
		        if(Protocol==SMbusRW)
		        {
			        *(Var+0x01) = *asSMBus[Channel].SMBusData1;
		        }							            // read data2
	        }
            resutl = TRUE;
        }

	    *asSMBus[Channel].SMBusSTA=0xFE;	            // clear bits
    }

	return(resutl);
}


//----------------------------------------------------------------------------
// Read SMbus block function limit size	
//----------------------------------------------------------------------------
BYTE bRSMBusBlockLS(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE RequestLength)
{
	BYTE ack;
    BYTE bcount;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
    {
        ack = FALSE;                            // SMBus interface can't be used.
    }
    else
    {
	    ack = FALSE;					        // pr-set flag
	    bcount = 0x00;			                // clear byte counter
	
	    *asSMBus[Channel].SMBusADR=Addr|0x01;   // set address with reading bit	
	    *asSMBus[Channel].SMBusCMD=Comd;	    // Set command
        *asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);    // Start transaction

	    TR1 = 0;			                    // disable timer1
        ET1 = 0;                  	            // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_26ms>>8;                    // Set timer1 counter 26ms
        TL1 = Timer_26ms;                       // Set timer1 counter 26ms
        TF1 = 0;                  	            // Clear overflow flag
        TR1 = 1;                 	            // Enable timer1

        while(!TF1)                             // Not time out
        {
            status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
            if(IS_MASK_SET(status, (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
            {
                if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
                {
                    if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                    {
                        ResetSMBus(Channel);
                    }
                    TR1 = 0;			        // disable timer1
 	                TF1 = 0;			        // clear overflow flag
	                ET1 = 1;			        // Enable timer1 interrupt
	                ack = FALSE;
                    break;
                }
                else                            // Only Byte Done Status bit is set.
                {
	                *Var = *asSMBus[Channel].SMBusBData;    // get first data
	                if(bcount ==0x00)
	                {
		                bcount = *asSMBus[Channel].SMBusData0; // get the data of byte count 
		                //Hook_GetSMBusReadBlockByteCount(bcount);
                        //SMB_BCNT = bcount;      // For ACPI SMBus EC SMB1 Block Count register
						if (bcount > RequestLength)
						{
							bcount = RequestLength;
						}
	                }	
	                bcount--;
	                Var++;
    
	                if(bcount == 0x01)
	                {						    // set last byte flag
		                SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);
	                }
    
	                *asSMBus[Channel].SMBusSTA=0xFE;    // clear bits

	                if(bcount == 0x00)
	                {
                        TR1 = 0;			    // disable timer1
 	                    TF1 = 0;			    // clear overflow flag
	                    ET1 = 1;			    // Enable timer1 interrupt
                        ack = TRUE;
                        break;                  // SMBus read block done.
                    }
                }
            }
        }

        if(TF1)                                 // time-out
        {
            TR1 = 0;			                // disable timer1
 	        TF1 = 0;			                // clear overflow flag
	        ET1 = 1;			                // Enable timer1 interrupt
		    ResetSMBus(Channel);
		    ack = FALSE;
        }

	    CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);    // clear last byte flag
	    *asSMBus[Channel].SMBusSTA=0xFE;        // clear bits
    }
    
	return(ack);	
}

//----------------------------------------------------------------------------
// Read SMbus block function	
//----------------------------------------------------------------------------
BYTE bRSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var)
{
	BYTE ack;
    BYTE bcount;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
    {
        ack = FALSE;                            // SMBus interface can't be used.
    }
    else
    {
	    ack = FALSE;					        // pr-set flag
	    bcount = 0x00;			                // clear byte counter
	
	    *asSMBus[Channel].SMBusADR=Addr|0x01;   // set address with reading bit	
	    *asSMBus[Channel].SMBusCMD=Comd;	    // Set command
        *asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);    // Start transaction

	    TR1 = 0;			                    // disable timer1
        ET1 = 0;                  	            // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_26ms>>8;                    // Set timer1 counter 26ms
        TL1 = Timer_26ms;                       // Set timer1 counter 26ms
        TF1 = 0;                  	            // Clear overflow flag
        TR1 = 1;                 	            // Enable timer1

        while(!TF1)                             // Not time out
        {
            status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
            if(IS_MASK_SET(status, (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
            {
                if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
                {
                    if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                    {
                        ResetSMBus(Channel);
                    }
                    TR1 = 0;			        // disable timer1
 	                TF1 = 0;			        // clear overflow flag
	                ET1 = 1;			        // Enable timer1 interrupt
	                ack = FALSE;
                    break;
                }
                else                            // Only Byte Done Status bit is set.
                {
	                *Var = *asSMBus[Channel].SMBusBData;    // get first data
	                if(bcount ==0x00)
	                {
		                bcount = *asSMBus[Channel].SMBusData0; // get the data of byte count 
		                Hook_GetSMBusReadBlockByteCount(bcount);
                        //SMB_BCNT = bcount;      // For ACPI SMBus EC SMB1 Block Count register
	                }	
            
	                bcount--;
	                Var++;
    
	                if(bcount == 0x01)
	                {						    // set last byte flag
		                SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);
	                }
    
	                *asSMBus[Channel].SMBusSTA=0xFE;    // clear bits

	                if(bcount == 0x00)
	                {
                        TR1 = 0;			    // disable timer1
 	                    TF1 = 0;			    // clear overflow flag
	                    ET1 = 1;			    // Enable timer1 interrupt
                        ack = TRUE;
                        break;                  // SMBus read block done.
                    }
                }
            }
        }

        if(TF1)                                 // time-out
        {
            TR1 = 0;			                // disable timer1
 	        TF1 = 0;			                // clear overflow flag
	        ET1 = 1;			                // Enable timer1 interrupt
		    ResetSMBus(Channel);
		    ack = FALSE;
        }

	    CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);    // clear last byte flag
	    *asSMBus[Channel].SMBusSTA=0xFE;        // clear bits
    }
    
	return(ack);	
}

//----------------------------------------------------------------------------
// Write SMbus block function	
//----------------------------------------------------------------------------
BYTE bWSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,XBYTE *Var,BYTE ByteCont,BYTE PECsupport)
{	
	BYTE ack;
    BYTE BCTemp;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
    {
        ack = FALSE;                            // SMBus interface can't be used.
    }
    else
    {
	    ack = FALSE;					        // pre-set flag
	    BCTemp = 0x00;			                // clear byte count

        if(PECsupport)
        {   
            SMBCRC8_A=0x00;
            CalcCRC8(Addr);
            CalcCRC8(Comd);
            CalcCRC8(ByteCont);
            CalcCRC8(*Var);
        }
    
	    Protocol&=(~0x80);			
	    *asSMBus[Channel].SMBusADR=Addr;	    // set address with writing flag
        *asSMBus[Channel].SMBusCMD=Comd;	    // Set command
        *asSMBus[Channel].SMBusData0=ByteCont;  // set byte count
        BCTemp=ByteCont;	                    // sync byte count 
        *asSMBus[Channel].SMBusBData=*Var;	    // set first data
        *asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
	    if(PECsupport)
        {   
            *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT|HOCTL_PEC_EN);// Start transaction
        }
        else
        {
            *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);// Start transaction
        }

	    TR1 = 0;			                    // disable timer1
        ET1 = 0;                  	            // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_26ms>>8;                    // Set timer1 counter 26ms
        TL1 = Timer_26ms;                       // Set timer1 counter 26ms
        TF1 = 0;                  	            // Clear overflow flag
        TR1 = 1;                 	            // Enable timer1

        while(!TF1)                             // Not time out
        {
            status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
            if(IS_MASK_SET(status, (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
            {
                if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
                {
                    if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                    {
                        ResetSMBus(Channel);
                    }
                    TR1 = 0;			        // disable timer1
 	                TF1 = 0;			        // clear overflow flag
	                ET1 = 1;			        // Enable timer1 interrupt
	                ack = FALSE;
                    break;
                }
                else                            // Only Byte Done Status bit is set.
                {
	                BCTemp--;
	                Var++;					    // point to next address of variable

	                if(BCTemp != 0x00)
	                {
                        if(PECsupport)
                        {
                            *asSMBus[Channel].SMBusBData=*Var;
                            CalcCRC8(*Var);
                            if(BCTemp==0x01)    // last byte of byte count
                            {
                                *asSMBus[Channel].SMBusPEC = SMBCRC8_A;
                            }
                        }
                        else
                        {
		                    *asSMBus[Channel].SMBusBData=*Var;
                        }
                        *asSMBus[Channel].SMBusSTA=0xFE;    // clear bits
	                }
                    else                        // write block transaction done
                    {
	                    TR1 = 0;			    // disable timer1
 	                    TF1 = 0;			    // clear overflow flag
	                    ET1 = 1;			    // Enable timer1 interrupt
	                    ack = TRUE;
	                    break;
                    }
                }
            }
        }
        
        if(TF1)                                 // time-out
        {
            TR1 = 0;			                // disable timer1
 	        TF1 = 0;			                // clear overflow flag
	        ET1 = 1;			                // Enable timer1 interrupt
		    ResetSMBus(Channel);
		    ack = FALSE;
        }
        
	    *asSMBus[Channel].SMBusSTA=0xFE;        // clear bits
    }
    
	return(ack);
} 

//----------------------------------------------------------------------------
// The function of SMbus send byte	
//----------------------------------------------------------------------------
BYTE bSMBusSendByte(BYTE Channel,BYTE Addr,BYTE SData)
{
	BYTE error;
    BYTE result;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
    {
        result = FALSE;                             // SMBus interface can't be used.
    }
    else
    {
        error = 0xEE;                               // Pre-set error
        result = FALSE;                             // Pre-set result is fail
        
	    *asSMBus[Channel].SMBusADR = Addr;	        // set address with writing bit
	    *asSMBus[Channel].SMBusCMD = SData;	        // Set command
	    *asSMBus[Channel].SMBusSTA = 0xFE;	        // clear bits
	    *asSMBus[Channel].SMBusCTL = (0x04|HOCTL_SRT);  // Start transaction

        TR1 = 0;                                    // Disable timer1
        ET1 = 0;                  	                // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_26ms>>8;                        // Set timer1 counter 26ms
        TL1 = Timer_26ms;                           // Set timer1 counter 26ms
        TF1 = 0;                  	                // Clear overflow flag
        TR1 = 1;                 	                // Enable timer1

	    while (!TF1)
	    { 
            status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
            if(IS_MASK_SET(status, (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
            {
                TR1=0;                              // Disable timer1
			    TF1=0;                              // Clear overflow flag
                ET1=1;                  	        // Enable timer1 interrupt
                break;
            }
	    }
	
	    if(TF1)                                     // 26ms time-out and no any status bit is set.
	    {
            TR1=0;
		    TF1=0;
            ET1=1;                                  // Enable timer1 interrupt
            ResetSMBus(Channel);
            error = 0xEE;
	    }
        else
        {
            if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
            {
                if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                {
                    ResetSMBus(Channel);
                }
                error = 0xEE;
            }
            else                                    // Only Finish Interrupt bit is set.
            {
                error = 0x00;
            }
        }
    
	    if(error == 0xEE)
	    {
		    result = FALSE;
	    }
        else
        {
            result = TRUE;
        }
	    *asSMBus[Channel].SMBusSTA=0xFE;	// clear bits
    }
    
	return(result);
}

//----------------------------------------------------------------------------
// The function of SMbus receive byte	
//----------------------------------------------------------------------------
BYTE bSMBusReceiveByte(BYTE Channel,BYTE Addr,XBYTE *Var)
{
	BYTE error;
    BYTE result;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==SMBus_CanNotUse)
    {
        result = FALSE;                             // SMBus interface can't be used.
    }
    else
    {
        error = 0xEE;                               // Pre-set error
        result = FALSE;                             // Pre-set result is fail
        
	    *asSMBus[Channel].SMBusADR = (Addr|0x01);   // set address with writing bit
	    *asSMBus[Channel].SMBusSTA = 0xFE;		    // clear bits
	    *asSMBus[Channel].SMBusCTL = (0x04|HOCTL_SRT);  // Start transaction

	    TR1 = 0;			                        // disable timer1
        ET1 = 0;                  	                // Disable timer1 interrupt
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        TH1 = Timer_26ms>>8;                        // Set timer1 counter 26ms
        TL1 = Timer_26ms;                           // Set timer1 counter 26ms
        TF1 = 0;                  	                // Clear overflow flag
        TR1 = 1;                 	                // Enable timer1

	    while (!TF1)
	    { 
            status = *asSMBus[Channel].SMBusSTA;    // Read SMBus Host Status
            if(IS_MASK_SET(status, (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
            {
                TR1=0;
			    TF1=0;
                ET1=1;                  	        // Enable timer1 interrupt
                break;
            }
	    }
	
	    if(TF1)                                     // 26ms time-out and no any status bit is set.
	    {
            TR1=0;
		    TF1=0;
            ET1=1;                                  // Enable timer1 interrupt
            ResetSMBus(Channel);
            error = 0xEE;
	    }
        else
        {
            if(IS_MASK_SET(status, (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE)))
            {
                if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                {
                    ResetSMBus(Channel);
                }
                error = 0xEE;
            }
            else                                    // Only Finish Interrupt bit is set.
            {
                error = 0x00;
            }
        }
	 
	    if(error == 0xEE)
	    {
		    result = FALSE; 
	    }	
        else
        {
	        *Var = *asSMBus[Channel].SMBusData0;    // read data
	        result = TRUE; 
        }
	    *asSMBus[Channel].SMBusSTA=0xFE;	    // clear bits
    }
    
	return(result);
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void CalcCRC8(BYTE sourcebyte)
{
    BYTE temp;
	SMBCRC8_A ^=sourcebyte;
    temp = SMBCRC8_A;

    if(IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp<<1;
        SMBCRC8_A ^= temp;
    }
    else
    {
        temp = temp<<1;
        SMBCRC8_A ^= 0x09;
        SMBCRC8_A ^= temp;
    }
    
    if(IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp<<1;
        SMBCRC8_A ^= temp;
    }
    else
    {
        temp = temp<<1;
        SMBCRC8_A ^= 0x07;
        SMBCRC8_A ^= temp;
    }
}

//----------------------------------------------------------------------------
// The function of Checking SMbus clock and data pins are both high	
//----------------------------------------------------------------------------
BYTE CheckSMBusFree(BYTE channel)
{
    BYTE pinstatus;

    pinstatus = *asResetSMBusS[channel].SMBusPinCTL;

    if((pinstatus&=0x03)==0x03) // Check BIT0 and BIT1
    {
        return(SMBus_Free);
    }
    else
    {
        return(SMBus_Busy);
    }
}

//----------------------------------------------------------------------------
// The function of Checking SMbus pins are all alt
//----------------------------------------------------------------------------
BYTE CheckSMBusInterfaceIsALT(BYTE channel)
{
    if(((*asResetSMBusS[channel].SMBusPin0 & 0xFB)!=0x00)||((*asResetSMBusS[channel].SMBusPin1 & 0xFB)!=0x00))
    {
        return(SMBusPin_GPIO);
    }
    else
    {
        return(SMBusPin_ALT);
    }
}

//----------------------------------------------------------------------------
// The function of Checking SMbus pins are all alt
//----------------------------------------------------------------------------
BYTE CheckSMBusInterfaceCanbeUse(BYTE channel, BYTE accesstype)
{
    BYTE checksmbus;

    checksmbus = SMBus_CanUse;                  // Pre-set smbus interface can be used
    
    #ifdef PECI_Support
    if(channel==SMbusCh3)                       // If PECI function enable, return.
    {
        checksmbus = SMBus_CanNotUse;           // Interface can't be used
        return(checksmbus);                     // return result
    }
    #endif
    
    if(CheckSMBusInterfaceIsALT(channel)==SMBusPin_GPIO)    // SMBus interface is GPIO function
    {
        checksmbus = SMBus_CanNotUse;           // Interface can't be used
    }
    else                                        // SMBus interface is ALT function
    {
        if(accesstype==SMBus_AccessType_Fucn)
        {
            #ifdef SMBusServiceCenterFunc
            WatiSMBusCHxFree(channel);          // Check smbus is in used or not.
            #endif
        }

        if(CheckSMBusFree(channel)==SMBus_Busy)
        {
            checksmbus = SMBus_CanNotUse;       // Interface can't be used
            if( (*asResetSMBusS[channel].recoverCunt)++ >SMBus_BusyRecover)
            {
                ResetSMBus(channel);
            }
        }
        else
        {
            *asResetSMBusS[channel].recoverCunt=0x00;
            checksmbus = SMBus_CanUse;          // smbus interface can be used
        }
    }

    return(checksmbus);                         // return result
}

//----------------------------------------------------------------------------
// To init. SMBus setting
//----------------------------------------------------------------------------
void Core_Init_SMBus(void)
{
    SMBus_BusyRecover = 20;         // Reset SMBus interface if bus clock pin or data pin is low greater than SMBus_BusyRecover times.
}