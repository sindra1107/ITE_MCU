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
// Define Smbus device address
//-----------------------------------------------------------------------------
#define ThermalAddr	        0x98	// thermal sensor address
#define PCH_Address         0x96    // PCH address

//-----------------------------------------------------------------------------
// Define thermal sensor commands
//-----------------------------------------------------------------------------
#define LocalCmd		    0x00	// Read Local temprature
#define RemoteCmd	        0x01	// Read remote temprature
#define ReadStatsuCmd       0x02	// Read thermal status

#define CPURemoteOVTCmd	    0x19	// HW shutdown command 
#define CPULocalOVTCmd	    0x20	// HW shutdown command
#define CPURACmd            0x0D    // Stores the integer portion of the high limit for the External Diode
#define CPULACmd            0x0B    // Stores the 8-bit high limit for the Internal Diode
#define CPURALCmd           0x0E    // Stores the integer portion of the low limit for the External Diode
#define CPULALCmd           0x0C    // Stores the 8-bit low limit for the Internal Diode
#define ManifactorID        0xFE

#define Configuration       0x09
#define ThermHysteresis     0x21
#define ConsecutiveAlert    0x22
#define DiodeFactor         0x27
#define DiodeFactor2        0x28
#define FilterControl       0x40
#define AlertConfig         0xBF

//-----------------------------------------------------------------------------
// For SMSC thermal sensor setting
//-----------------------------------------------------------------------------
#define SMSC_ID             0x5D
#define SMSC_CPU_Local_OVT  0x78            
#define SMSC_CPU_Remote_OVT 0x78   
#define SMSC_CPURAValue     0x78    
#define SMSC_CPULAValue     0x5A   

#define GMT_ID              0x47
#define GMT_CPU_Local_OVT   0x78          
#define GMT_CPU_Remote_OVT  0x78  
#define GMT_CPURAValue      0x78
#define GMT_CPULAValue      0x5A
#define GMT_CPURALValue     0xC9
#define GMT_CPULALValue     0xC9

#define NS_ID               0x01
#define NS_CPU_Local_OVT    0x78            
#define NS_CPU_Remote_OVT   0x78   
#define NS_CPURAValue       0x78
#define NS_CPULAValue       0x5A
#define NS_CPURALValue      0xC9
#define NS_CPULALValue      0xC9

//-----------------------------------------------------------------------------
// PCH Thermal Command
//-----------------------------------------------------------------------------
#define WriteSTSPreferences 0x41
#define WriteCPUTempLimits  0x42
#define WriteMCHTempLimits  0x43
#define WritePCHTempLimits  0x44
#define WriteDIMMTempLimits 0x45
#define WriteMPCCPUPowerClamp   0x50
#define PCHBlockRead        0x40

//-----------------------------------------------------------------------------
// Fan control define
//-----------------------------------------------------------------------------
#define FanValue		    Fan_volt    // The register of voltage output. (DAC or PWM)
#define FanInitValue	    160
#define	MaxOutValue		    240
#define FullOnCounter	    20		    // time base 100ms
#define RPMACC			    100		    // +- 100 rpm ACC
#define RPM1Max			    7000	    // rpm max value for softwave filter

//-----------------------------------------------------------------------------
// Compute R.P.M to TACH value
//-----------------------------------------------------------------------------
//	Fan Speed(R.P.M) = 60 /((1/Fs) * Tach * P )
//	Fs = FreqEC(9.2MHz) / 128
//	P denotes the numbers of square pulses per revolution.
//	(60 * 9.2M/128  = 4312500
//-----------------------------------------------------------------------------
#define TACH1P		        2			// the numbers of square pulses per revolution.
#define TACH2P		        2			// the numbers of square pulses per revolution.

//-----------------------------------------------------------------------------
// Moniter temperature
//-----------------------------------------------------------------------------
#define CpuTooHot 		    110
#define CpuTooHotTimes 	    3
#define SysTooHot		    80
#define SysTooHotTimes	    20

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------
extern void GetThermalData(void);
extern void FanControl (void);
extern void MoniterTemprature(void);
extern void InitThermalChip(void);
extern void ReadThermalID(void);
extern void FanFullOn(void);
extern void FanFullOff(void);
extern void FanInitOn(void);
extern void GetRPM1(void);
extern void InitThermalTable1(void);
extern void InitThermalTable2(void);
extern void CheckFanRPM1(void);
extern void CheckFanRPM2(void);
extern void FanManager(void);
extern void ReadCPUTemp(void);
extern void ReadSysTemp(void);

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

typedef	struct	TooHotStruct
{
	XBYTE	*Temprature;
	BYTE	Limit;
	XBYTE	*Counter;
	BYTE	Times;
}sTooHot;

typedef struct ThermalInitTablt
{
	BYTE	cmd	;	        // thermal init. command
	BYTE	value	;       // value of command	
	BYTE	RorW	;       // 0: read byte, 1: write byte
} sThermalInitTablt;

extern sThermalInitTablt code asThermalInitTablt[];
#endif

