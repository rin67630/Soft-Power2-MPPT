# SerialCommunication and Menu system
Your Drok-Juntek-on-steroids device operates usually over the cloud functionality of thinger.io.

For debugging purposes it can also be operated over a serial line at 115200 Baud.
you may use the serial monitor functionality of the Arduino IDE, but can also use your smart phone with an appropriate terminal program like 
"Serial USB Terminal" from the Google Store.

## Boot Log
When you start your power supply you will first get the boot log:
```
22:08:28.803 -> Resetted! 
22:08:28.803 -> Device name: SteroidsADS 
22:08:28.803 -> ESP-Karajan framework at work, Serial @ 115200 Baud
22:08:28.803 -> Try connecting to GW-FM-7390 
22:08:29.979 -> . Done!
22:08:30.027 -> RRSI= -49dB, IP= 192 . 168 188 . 076 
22:08:32.101 -> Initializing Thinger, Username= SoftPower1
22:08:35.026 -> Now is Thursday, 15 April 2021 22:08:36. Epoch =1618517316
```

In order to put the maximum of functionality into scarce memory of the microcontroller, there is no verbose menu.  
Instead you have a choice of single character commands, from which you can however enter several in one line, they will be executed in sequence.
The single character menu enables also to use keypads with few function keys.  

## Control commands
From the serial menu, you can control several operations of Soft-Power.  

- '%' toggle between small step changes  (10mV/10mA) and coarse steps (100mV/50mA)
the menu answers with fine or coarse and keeps that setting until toggled again.

- '+' or '-' increases or decreases in small steps the setpoint of the output voltage
the menu answers with ++ Volt=14.500 or + Volt=14.510 depending if it was a coarse or a fine step.

- '>' or '<' increases or decreases in coarse steps the setpoint of the output current
the menu answers with ++  Amp=00.650 or +  Amp=00.640 depending if it was a coarse or a fine step.

- '}' or '{' increases or decreases in coarse steps the setpoint of the input voltaage regulation (in case of soalr input)
the menu answers with ++  Amp=00.650 or +  Amp=00.640 depending if it was a coarse or a fine step.


The commands can be stacked: you may type ++++++++++++, ------, >>>>>, <<<<<<<<<<< then enter and it will increasedecrease the corresponding number of steps.

## Modes of Operation:

These commands control different operation modes:  (every time the letter is entered, the next mode will be activated)  

- 'A' controls the Ah integration:  
    "STOP" stops and resets the Ah integration  
    "RUN" lets  the Ah integratio until stooped  
    "DAILY"  lest the Ah integration, which is daily reset at 00:00  

- 'O' controls the solar operation modes:  
   "MANU" the DC/DC controller runs according to output Voltage/Current setpoints.  
   "PVFX" like above + the output Current setpoint will be limited to control the input voltage to a fixed set point  
   "MPTT" like above + the panel voltage set point track the maximum power point.  

- "C" Controls the charger mode of operation  (Work in progress)  
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


## Setting the pace for periodical reports
The pace for next 2 reports is given with a lower case prefix:  
's', 'm', 'h', 'd' staying for every second, minutely, hourly, daily.  
Once the pace for periodical reports is given, it stays valid for every report called after, until another pace is choosen or a '!' stop command is entered.  

## Periodical reports
currently the following periodical reports are available (more to come)

### 'D':  //Debug Report
Debug Report shows important internal varables to calibrate your system:
ADC_VinRaw:627 Vin:21.040 ADC_VoutRaw:421 Vout:14.434 ADC_IoutRaw:114 Iout:00.037 PWM_Vset:0262 Vset:14.500 PWM_Cset:0125 Iset:00.650

### 'E':  //Energy Report
Energy report shows the measurments values.
Vset:14.500 Vout:14.434 Iset:00.650 Iout:00.045 Wout:+00.566

example: If you type "sE" you will get the energy report issued every second, if you type "mE" to get the same report issued every minute.

In that last case the output is best suitable with Arduino's serial plotter to get a plot of all values:
![image](https://user-images.githubusercontent.com/14197155/107235100-9ff60700-6a24-11eb-9ed8-552b373d9c1a.png) 

### 'S':  //Summary Report (one shot only)
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

### 't': // Print time
Thu Apr 15 15:49:19 2021

### 'T': // Enter time
this command is only valued off-line, with an Internet connection the time is given from the NTP server.

## Display control commands
You will be able to control which information is displayed on the TFT Display:  
- '0' switch of the display
- '1' Volt /Ampere  Display (output)
- '2' Volt /Ampere  Display (intput)
- '3' Output Voltage display (with set point control)
- '3' Output Current display (with set point control)
- '4' Input Voltage display  (with set point control)
- '5' Power Supply Display
- '6' Battery Display
- '7' Statistics display

- '9' Cycling throughh the displays

 
