/*-----------------------------------------------------------------------------
 * TITLE: OEM_FAN.H
 *
 * Author : Dino
 *
 * Note : These functions are reference only.
 *        Please follow your project software specification to do some modification.
 *---------------------------------------------------------------------------*/

#ifndef OEM_FAN_H
#define OEM_FAN_H

//-----------------------------------------------------------------------------
// Fan control define
//-----------------------------------------------------------------------------
#define FanValue		    DCR0    // The register of voltage output. (DAC or PWM)
#define FanValue2			DCR1
#define FanInitValue	    160
#define	MaxOutValue		    240
#define RPMACC			    100		    // +- 100 rpm ACC
#define RPM1Max			    7000	    // rpm max value for softwave filter
#define RPM2Max			    7000	    // rpm max value for softwave filter

//-----------------------------------------------------------------------------
// Compute R.P.M to TACH value
//-----------------------------------------------------------------------------
//	Fan Speed(R.P.M) = 60 /((1/Fs) * Tach * P )
//	Fs = FreqEC(9.2MHz) / 128
//	P denotes the numbers of square pulses per revolution.
//	(60 * 9.2M/128  = 4312500
//-----------------------------------------------------------------------------
#define TACH1P		        1			// the numbers of square pulses per revolution.
#define TACH2P		        1			// the numbers of square pulses per revolution.


//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void FanControl (void);
extern void FanFullOff(void);
extern void GetRPM1(void);
extern void GetRPM2(void);
extern void InitThermalTable1(void);
extern void InitThermalTable2(void);
extern void CheckFanRPM1(void);
extern void CheckFanRPM2(void);
extern void FanManager(void);
extern void ReadCPUTemp(void);
extern void ReadDgpuTemp(void);

extern void FineTuneFan2PRM(void);

//-----------------------------------------------------------------------------
// Structure define
//-----------------------------------------------------------------------------
typedef struct thermalstruct
{
	BYTE 	Level;
	BYTE 	CFanOn;
	BYTE 	CFanOff;
	BYTE	CRPM;
	XBYTE	*FanOn;
	XBYTE	*FanOff;
	XBYTE	*RPM;
}thermal;

#endif

