# Frequently Asqued Questions

## My SoftPower device is barely responsive.
This is mainly due to wrong Thinger.io credentials, verify your username, device name and device credentials.
You can also verify using the serial monitor the timing of the different tasks:
Enter sJ to get the job timing every second. A regular timing looks like that:
```
07:59:43.848 -> Job Durations(mS) Current - Max
07:59:43.848 -> Menu:000 - 000 
07:59:43.848 -> Fast:040 - 043
07:59:43.848 -> Slow:000 - 000
07:59:43.848 -> Stat:000 - 000
07:59:43.848 -> Disp:021 - 034
07:59:43.848 -> Seri:001 - 001
07:59:43.848 -> Wifi:007 - 063
```
if the wifi task takes longer than 100mS then there is obviously something wrong in your communication.
Another cause could have been a wonky Internet connection.

## I get the information in my dashboard but no trend
Trends are stored in buckets.
There is a line in a0_Optins to enable writing in buckets:
```
#define WRITE_BUCKETS         // comment out. if this is the second device
```
This line must be commented out, if you use a second device on the same account. 
Only one device can write in buckets.

If you have commented out that line for the main device also, you get no trend.

## I am operating my SCC without input current probe

On the corresponding HAL file assign the ADC for Input to the same value than the ADC for Output, e.g.

#define FB_Iin_PIN     ADS1115_COMP_3_GND  

That will prevent weird values in the calibration file.
When ADC for Input to the same value than the ADC for Output, the software will be emulating the input current, assuming 90% converter efficiency, providing an estimation of the input current (+-20%).
