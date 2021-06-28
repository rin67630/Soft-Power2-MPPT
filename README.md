# Soft Power2 MPPT.
this is a reload of my project https://github.com/rin67630/Soft-Power-MPPT.  
In that first project I have been using small DC-DC buck converters and controled them by injecting a smoothed PWM signal into their voltage potentiometer to build a WiFi enabled MPPT controller.  
While the injection technique where working quite good, the tiny buck converters have shown to be very prone to failure in the harsh outside environment.  
So I decided to re-launch the project with more robust hardware.   

Juntek and Drok (maybe others) sell some interesting cheap but good programmable buck converter modules e.g.:  
-Juntek B3603 for 20-100W panel class upto 30Vmp (36V/3A buck converter):  
https://www.aliexpress.com/item/32872687512.html
- Drok D6008 for 100W-200W for panel class up to 48Vmp (60V/8A buck converter) 
https://www.aliexpress.com/item/32862110549.html  
- Drok D6012 for 200W-400V panel class up to 75VVmp (80V/12A buck converter) 
https://www.aliexpress.com/item/32863179021.html  

*(links only given to identify the modules, you are encouraged to procure the devices from your favourite source)  

The project began with https://github.com/rin67630/Drok-Juntek-on-steroids, from which this repository is a fork.  
Drok-Juntek-on-Steroids is getting a universal framework to build various solutions around above mentioned programmable power supplies, as of:  
- Solar charge controller
- Battery evaluation module
- Programmable loads
and much more...  
You are encouraged to have a look there and look at the hardware section on how to build your own device.  
(A bit of soldering is required. I expect to get soon a PCB to simplify the wiring.)

## but what is Soft-Power2-MPPT?
It is a **self-contained** WiFi network enabled MPPT controller with:
- a powerful dashboard in the Internet, 
- statistics and long term plotting abilities.
- running on various generally available low-cost DC/DC converters without any "cable spaghetti".

The whole solution is working completely self-contained: 
- no power supply required,
- no additional computer or smartphone required,
- no database to maintain,
- nothing else to program,
- no MQTT broker involved
- no Grafan to configure.

The dashboards are running in the cloud at http://thinger.io, where you can create an account free of charge for up to two devices.
You can create there very powerful dashboards interactively, and modify them on the fly.
Here two examples:
## Control dashboard:
![image](https://user-images.githubusercontent.com/14197155/123584914-82aeb300-d7e2-11eb-97ac-eaa375c6e077.png)  

## Statistics dashboard:
![image](https://user-images.githubusercontent.com/14197155/123584988-aa9e1680-d7e2-11eb-914c-e2682b02a685.png)

These are only examples of what you can do with Soft-Power2-MPPT and thinger.io...




