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
