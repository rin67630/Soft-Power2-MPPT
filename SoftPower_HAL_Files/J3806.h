// #include JuntekD3806
// All values computed by CalibrationTTGO&ADS1115.xls on GitHub.

// V is output voltage, I is ouput current, P (panel) is input voltage
// BIAS is the value at 0, 
// STEP is the number of PVM or mV feed_back units to increase by 1V or 100mA
// RES is the mV, mA change for one unit of feedback or PWM.
// Panel FB resistor is 2 MOhm to Pin3 on the back of the Motherboard.

#define PWM_Vout_BIAS  30.07
#define PWM_Vout_STEP  48.55
#define PWM_Vout_RES   20.60

#define PWM_Iout_BIAS  57.00
#define PWM_Iout_STEP  28.00
#define PWM_Iout_RES   35.71

#define FB_Vin_BIAS    0.0000
#define FB_Vin_STEP    62.2000
#define FB_Vin_RES     16.0772

#define FB_Vout_BIAS   47.60
#define FB_Vout_STEP   73.00
#define FB_Vout_RES    13.70

#define FB_Iout_BIAS   145.07
#define FB_Iout_STEP   84.93
#define FB_Iout_RES    1.18

#define FB_Vin_BIAS    0.00
#define FB_Vin_STEP    47.22
#define FB_Vin_RES     21.08

#define ADS_Ch0_Range  ADS1115_RANGE_0256
#define ADS_Ch1_Range  ADS1115_RANGE_2048
#define ADS_Ch2_Range  ADS1115_RANGE_2048
#define ADS_Ch3_Range  ADS1115_RANGE_2048
#define FB_Vout_PIN    ADS1115_COMP_2_GND
#define FB_Iout_PIN    ADS1115_COMP_3_GND
#define FB_Vin_PIN     ADS1115_COMP_1_GND
#define FB_Iin_PIN     ADS1115_COMP_0_GND

#define VIN_MAX        40
#define VOUT_MAX       60
#define IOUT_MAX       6

#define FAN_AMPS_0     1.5
#define FAN_AMPS_100   4
