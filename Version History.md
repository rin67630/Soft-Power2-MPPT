#V3.1
The hardware/serial interface has been completely redesigned and the software streamlined.

Now the changes over the rotary encoder, the buttons up down and the serial interface are working the same way:
Which value to change depends on the screen, ther is one screen for every value.

Long press on either button (up, down, rotary) > 5 seconds toggles between "display change" and "value change".

Over the serial interface you can enter directly the screen number 1-8, 
screen number 0 is black screen (power save), 
screen number 9 is cycling every five seconds between 1-8, this presets "display change".

Value change is possible in the screens 3,4,5 (Vo, Io, Vi setpoints), 
on screen 1, value changes the Ah integration mode between Stop, Run and Daily,
on screen 2 value changes the solar opreation mode between Manu, PvFx,MPPT
else an information is issued" no value change here".

+ and - over the serial interface, changes the value  and presets the "value change" mode, so you just can use the  rotary encoder as well.

Serial comments are stackable:  3+++4--1  increases the voltage, diminishes the current and returns to screen 1 in "display change" mode.

Once in a "value change" mode, you just enter +++ or --.

Value changes are increasing according to a square rule so you can make bigger increments faster e.g: 
+ changes by 0.01, 
++ changes by changes by 0.04, 
+++ changes by changes by 0.09,
 ++++ changes by changes by 0.16
This is also valid for the rotary encoder.

The serial commands % (toggle between coarse and fine), <,> change current have been removed, there is no more need for them.

# V3.0

this major version supports beside the TTGO development board ( which remains the reference ) also Wemos ESP32 borads with an OLED 128*64 BW display and the Heltec LoRa Board,  
that is planned to deliver long-range radio transmission.

The different hardware specific files are provided in a folder "SoftPower_HAL_Files" that should be moved underneath the library folder, to be discovered upon compiling.
Please adapt your a0_Options to the new structure.

This version provides improved on-board screens, better serial communication, and has solved a few issues:  

- the thing_property property records _I_value, _P_value and _FractionVOC, which where sporadically overwritten with zero, jeopardising the MPPT function  
are now preset with useful default values (your main change the values during runtime upon modifying the thinger.io properties)  
- the setpoint for the panel voltage can now be entered into serial monitor using {{{ and }}}  
- a "X" report (eXcel) for calibration has been added to provide all values required during the calibration process.  
- the Ah integration modes can be changed using the "A" function between "STOP", "RUN", "DAILY  
- the Operation mode can be changed using the "O" function between "MANU", "PVFX", "MPPT"  
- some errors in the computation of Ah and WH were corrected, the display shows Ah and Wh corresponding to the cycle, when Ah integration is stopped,    
  it shows the Ah, Wh of the last hour.

# V2.0
this major version (supporting only the TTGO) introduced separate configuration files for different DC/DC converters and for different battery types.

# V1.0
initial version used configuration about the file a0_Options which contained the parameters for one DC/DC converter.
