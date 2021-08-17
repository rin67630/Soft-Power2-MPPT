# SerialCommunication and Menu system
Your Drok-Juntek-on-steroids device operates usually over the cloud functionality of thinger.io.

For debugging purposes it can also be operated over a serial line at 115200 Baud.
you may use the serial monitor functionality of the Arduino IDE, but can also use your smart phone with an appropriate terminal program like 
"Serial USB Terminal" from the Google Store.

## Boot Log
When you start your power supply you will first get the boot log:
```
18:52:06.518 -> 
18:52:06.518 -> Device SteroidsADS resetted!
18:52:06.518 -> ESP-Karajan framew. ready: Serial @ 115200 Baud
18:52:06.518 -> Initializing IO 
18:52:06.518 -> Initializing PWM 
18:52:06.518 -> Initializing ROT 
18:52:06.518 -> Initializing ADC 
18:52:06.518 -> Initializing DIS 
18:52:07.790 -> Connecting to GW-FM-7390
18:52:08.407 -> .
18:52:08.455 -> Done: RRSI= -71dB, IP= 192 . 168 . 188 . 036 
18:52:10.575 -> Initializing Thinger, Username= SoftPower1 
18:52:13.122 -> 
18:52:13.122 -> Now is Friday, 30 July 2021 18:52:14. Epoch =1627663934
18:52:13.122 -> 
18:52:15.109 -> Ready to accept serial commands...

```

In order to put the maximum of functionality into scarce memory of the microcontroller, there is no verbose menu.  
Instead you have a choice of single character commands, from which you can however enter several in one line, they will be executed in sequence.
The single character menu enables also to use keypads with few function keys.  

With V3 I redesigned of the hardware/serial interface in a harmonized way:  

The changes over the rotary encoder, the buttons up down and the serial interface are working similarly:

You can switch screens and enter set points or modes of operation.   

## Screens changes.
With the buttons Up Down or the rotary encoder you can change screens. 
Screen number 0 is black screen (power save), 
Screen number 9 is cycling every five seconds between 1-8  
Over the serial interface you can enter directly the screen number 1-8 , this presets "display change",

# Operation over serial, buttons and rotary encoder

## Set points or modes of operation
A long press >10 seconds on either button up, down, or rotary button enters the set point mode.

Which value is changed is ruled by the current screen:
- on screen 1 value changes the Ah integration mode between Stop, Run and Daily,
- on screen 2 value changes the solar opreation mode between Manu, PvFx,MPPT
- on screen 3 Value change the Vo setpoint
- on screen 4 Value change the Io setpoint
- on screen 5 Value change the Vi setpoint.
- on screen 6 Value will change the charger mode of operation  (planned)  
   "NIGH", Night mode, no charge  
   "RECO", Recover from discharged battery  
   "BULK", Bulk charge  
   "ABSO", Absorption charge  
   "FLOA", Float charge    
   "EQUA", Equalization charge  
   "PAUS", Pause charging  
   Additional non selectable errors  
   "OVER", Overcharge  
   "DISC", Load Disconnection  
   "NOBA", No Battery  
   "NOPA", No Panel  
   "EXAM" 
- on other screens only a message: no set point here! is issued.

You change the value over the rotary encoder, the keys up / down, or 
over the serial interface with the keys + and -, this presets "value change change". (no need for a long press to change mode over serial.

Serial comments are stackable:  3+++4--1  increases the voltage, diminishes the current and returns to screen 1 in "display change" mode.

Value changes are increasing according to a square rule so you can make bigger increments faster e.g: 
+ changes by 0.01, 
++ changes by changes by 0.04, 
+++ changes by changes by 0.09,
 ++++ changes by changes by 0.16
This is also valid for the rotary encoder.


The serial commands from previous versions:
- % (toggle between coarse and fine), 
- <,> change current
- {,} change Vin setpoint
have **been removed**, there is no more need for them any more.

- O Operation mode change Manu, PvFx,MPPT
- A Ah mode change Stop, Run and Daily
are now redundant

## Reports control over serial

Reports can only be controlled over serial.

### Setting the pace for periodical reports
The pace for periodical reports is given with a lower case prefix:  
's', 'm', 'h', 'd' staying for every second, minutely, hourly, daily.  
Once the pace for periodical reports is given, it stays valid for every report called after, 
until another pace is choosen or a '!' stop command is entered.  

### Periodical reports
currently the following periodical reports are available (more to come)

#### 'D':  //Debug Report
Debug Report shows important internal varables to calibrate your system:
ADC_VinRaw:627 Vin:21.040 ADC_VoutRaw:421 Vout:14.434 ADC_IoutRaw:114 Iout:00.037 PWM_Vset:0262 Vset:14.500 PWM_Cset:0125 Iset:00.650

#### 'E':  //Energy Report
Energy report shows the measurments values.
Vset:14.500 Vout:14.434 Iset:00.650 Iout:00.045 Wout:+00.566

#### "X":  // EXcel report for calibration

#### "J":   // Job duration report for debugging purposes.

#### "j":   // Reset Job duration totals

example: If you type "sE" you will get the energy report issued every second, if you type "mE" to get the same report issued every minute.

In that last case the output is best suitable with Arduino's serial plotter to get a plot of all values:
![image](https://user-images.githubusercontent.com/14197155/107235100-9ff60700-6a24-11eb-9ed8-552b373d9c1a.png) 

### Onte time reports

#### 'S':  //Summary Report (one shot only)
This command issues a report for the past 24hours:
```
Daily Report for 
Sunday, 07 February 2021 
Hour|   Ah    |    V    |    W    |
00  | -00.033 | +12.376 | -00.405 |
01  | -00.031 | +12.376 | -00.383 |
02  | -00.031 | +12.368 | -00.384 |
03  | -00.032 | +12.368 | -00.391 |
04  | -00.031 | +12.368 | -00.388 |
05  | -00.031 | +12.360 | -00.387 |
06  | -00.032 | +12.360 | -00.402 |
07  | -00.032 | +12.360 | -00.394 |
08  | -00.009 | +12.400 | -00.115 |
09  | +00.022 | +12.440 | +00.275 |
10  | +00.036 | +12.480 | +00.445 |
11  | +00.262 | +12.984 | +03.402 |
12  | +00.596 | +13.760 | +08.206 |
13  | +00.712 | +13.168 | +09.375 |
14  | +00.392 | +12.953 | +05.080 |
15  | +00.233 | +12.896 | +03.002 |
16  | +00.131 | +12.769 | +01.674 |
17  | -00.007 | +12.648 | -00.092 |
18  | -00.028 | +12.608 | -00.357 |
19  | -00.027 | +12.584 | -00.346 |
20  | -00.028 | +12.568 | -00.358 |
21  | -00.030 | +12.557 | -00.378 |
22  | -00.030 | +12.544 | -00.378 |
23  | -00.030 | +12.536 | -00.371 |
Extra hours 25:H-1, 26:today, 27:D-1, 28:D-2..
25  | -00.030 | +12.536 | -00.371 |
26  | +01.970 | +12.096 | +23.828 |
27  | +01.970 | +12.096 | +23.828 |
28  | +01.970 | +12.096 | +23.828 |
29  | +01.970 | +12.096 | +23.828 |
30  | +01.970 | +12.096 | +23.828 |
```


#### "I":   // Prints internal parameters for debugging purposes.

#### 't': // Print time
Thu Apr 15 15:49:19 2021

#### 'T': // Enter time  **Blocking command**
this command is only useful off-line, with an Internet connection the time is given from the NTP server.

#### "W":   // wiFi report : Field stength -IP Address  / *if not connected* Enter WiFi access data.  **Blocking command**
               WiFi access data survive resets.

#### "w":   // WiFi disconnect and enter in AP mode  (This can cut you from Access if you are remote)

## System commands

### 'Z' System reset
### 'z' reset integration values

### 'P' write Persistance Data to EEPROM (if no thinger)
This command writes the persistaence parameters to EEPROM, so that a subsequent reset will restore the Ah and Wh integration values to continue seamlessly.
If thinger.io is active, persistance will be automatically taken over by this server, so resets will mainly preserve data, without need to call 'P'


 
