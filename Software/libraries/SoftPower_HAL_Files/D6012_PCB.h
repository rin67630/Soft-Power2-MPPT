// #include Drok6012
// All values computed by CalibrationTTGO&ADS1115.xls on GitHub.

// V is output voltage, I is ouput current, P (panel) is input voltage
// BIAS is the value at 0, 
// STEP is the number of PVM or mV feed_back units to increase by 1V or 100mA
// RES is the mV, mA change for one unit of feedback or PWM.I2C (Grove) connector
// Panel Volt FB resistor is 3.0M Ohm (external wire)

#define PWM_Vout_BIAS	28.598
#define PWM_Vout_STEP	21.026
#define PWM_Vout_RES	47.561
	
#define PWM_Iout_BIAS	50.000
#define PWM_Iout_STEP	5.739
#define PWM_Iout_RES	17.425
	
#define FB_Vin_BIAS   	0.000
#define FB_Vin_STEP    	58.910
#define FB_Vin_RES   	16.975
	
#define FB_Iin_BIAS   	0.100
#define FB_Iin_STEP   	58.139
#define FB_Iin_RES   	1.720
	
#define FB_Vout_BIAS	46.357
#define FB_Vout_STEP	33.641
#define FB_Vout_RES 	29.726
	
#define FB_Iout_BIAS	71.590
#define FB_Iout_STEP	9.210
#define FB_Iout_RES 	10.858
	
#define FB_Iload_BIAS	-6
#define FB_Iload_STEP	6
#define FB_Iload_RES 	16.52 


// Assign ranges to ADS channels (0256 for shunts, 2048 or 4096 for voltages)
#define ADS_Ch0_Range ADS1115_RANGE_2048
#define ADS_Ch1_Range ADS1115_RANGE_4096
#define ADS_Ch2_Range ADS1115_RANGE_0256
#define ADS_Ch3_Range ADS1115_RANGE_0256

// Assign inputs to ADS channels 
#define FB_Vout_PIN  ADS1115_COMP_0_GND
#define FB_Iout_PIN  ADS1115_COMP_1_GND
#define FB_Iload_PIN ADS1115_COMP_2_GND
#define FB_Iin_PIN   ADS1115_COMP_3_GND
//#define FB_Vin_PIN   ADS1115_COMP_2_GND

// Assign inputs to ESP ADC inputs 
#define VIN_ON_ESP
#define ADC_VIN        39  //ADC3
//#define ADC_RES      38  //ADC2
//#define ADC_IOUT     37  //ADC1
//#define ADC_VOUT     36  //ADC0
//#define ADC_ILOAD    39  //ADC3

#define VIN_MAX      75
#define VOUT_MAX     60
#define IOUT_MAX     12
#define FAN_AMPS_0   2
#define FAN_AMPS_100 8 

#define FAN_AMPS_0    2
#define FAN_AMPS_100  8
