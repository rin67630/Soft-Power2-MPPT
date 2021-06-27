# Soft Power2 MPPT.
this is a reload of my project https://github.com/rin67630/Soft-Power-MPPT.  
In that first project I have been using small DC-DC buck converters and controled them by injecting a smoothed PWM signal into their voltage potentiometer.  
While the injection technique where working quite good, the small buck converters have shown to be very prone to failure.  
So I decided to re-launch the project with more robust hardware.   

Juntek and Drok (maybe others) sell some interesting cheap programmable buck converter modules e.g.:
- DPS3806         (60V/6A boost/buck converter) https://www.aliexpress.com/item/1005001591485527.html
- Buck3603        (36V/3A buck converter) https://www.aliexpress.com/item/32872687512.html
- Drok low Power  (60V/8A buck converter) https://www.aliexpress.com/item/32862110549.html
- Drok high power (80V/12A buck converter) https://www.aliexpress.com/item/32863179021.html  
*(links only given to identify the modules, you are encouraged to procure the devices from your favourite source)  

The project began with https://github.com/rin67630/Drok-Juntek-on-steroids, from which this repository is a fork.  
Drok-Juntek-on-Steroids is getting a universal framework to build various solutions around programmable power supplies, as of:  
- Solar charge controller
- Battery evaluation module
- Programmable loads
and much more...  
You are encouraged to have a look there and look at the hardware section on how to build your own device.  
A bit of soldering is required. I expect to get soon a PCB to simplify the wiring.
 

## but what is Soft-Power2-MPPT?
It is before all a **self-contained** WiFi network enabled MPPT controller with:
- a powerful dashboard in the Internet, 
- statistics and long term plotting abilities.
- running on various generally available low-cost DC/DC converters without cable salad.

The whole solution is working completely self-contained: 
- no power supply required,
- no additional computer required,
- no database to maintain,
- nothing else to program,
- no MQTT broker involved.

The dashboards are running in the cloud at http://thinger.io, where you can create an account free of charge for up to two devices.
You can create there very powerful dashboards interactively, and modify them on the fly.
This is just an example, much more will come:  
![image](https://user-images.githubusercontent.com/14197155/121425793-16732900-c973-11eb-972a-bc29875c6cbc.png)
![image](https://user-images.githubusercontent.com/14197155/121425599-e1ff6d00-c972-11eb-9692-d7096f89d966.png)



