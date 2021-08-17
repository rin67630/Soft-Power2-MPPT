void setup()
{

  delay(5000);
  // Serial initialisation
  Serial.begin (SERIAL_SPEED); // On USB port
  Serial.setTimeout(60000);
  // Serial.setDebugOutput(true);

#ifdef CONTR_IS_TTGO
  Wire.begin(I2C_SDA, I2C_SCL);
#endif

#ifdef CONTR_IS_WEMOS
  Wire.begin(I2C_SDA, I2C_SCL);
#endif

#ifdef CONTR_IS_HELTEC
  Wire.begin(SDA_OLED, SCL_OLED);
  //  Heltec.begin(false /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  display.init();
  display.setContrast(160);
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.display();
  uint64_t chipId = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
  Serial.printf("ESP32ChipID=%04X ", (uint16_t)(chipId >> 32)); //print High 2 bytes
  Serial.printf("%08X\n", (uint32_t)chipId); //print Low 4b
#endif

  Console4.printf("\n\n\n\n\nDevice %s resetted!\n", DEVICE_NAME);
  Console4.printf("ESP-Karajan framew. ready:\nSerial @ %u Baud\n", SERIAL_SPEED);

  Console4.printf("Initializing IO \n");
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER_A_PIN, INPUT_PULLDOWN);
  pinMode(ROTARY_ENCODER_B_PIN, INPUT_PULLDOWN);
  pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(I2C_RST, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  digitalWrite(ENA_PIN, LOW); // enable DC/DC converter

  // Settings for PWM  (Usage: ledcWrite(channel, dutycycle);
  Console4.printf("Initializing PWM \n");
  ledcSetup(0, 2000, 11);             // 11 bit resolution@ 2Khz  PWM for Voltage
  ledcSetup(3, 2000, 11);             // 11 bit resolution@ 2Khz  PWM for Current
  ledcSetup(4, 2000, 11);             // 11 bit resolution@ 2Khz  PWM for Fan
  ledcSetup(14, 2000, 11);            // 11 bit resolution@ 2Khz  PWM for Brightness
  ledcAttachPin(PWM_V, 0);
  ledcAttachPin(PWM_I, 3);
  ledcAttachPin(FAN_PIN, 4);

#ifdef DISPLAY_IS_LCD
  ledcAttachPin(TFT_BL, 14);
#endif

#ifdef FET_EXTENSION
  Console4.printf("Initializing FET_Ext \n");
  pcf8574.pinMode(P0, OUTPUT);
  pcf8574.pinMode(P1, OUTPUT);
  pcf8574.pinMode(P2, OUTPUT);
  pcf8574.pinMode(P3, OUTPUT);
  pcf8574.pinMode(P4, INPUT);
  pcf8574.pinMode(P5, INPUT);
  pcf8574.pinMode(P6, INPUT);
  pcf8574.pinMode(P7, INPUT);
#endif

#ifdef ROTARY
  Console4.printf("Initializing ROT \n");
  rotaryEncoder.begin();
  rotaryEncoder.setup
  (
    [] { rotaryEncoder.readEncoder_ISR(); },
    [] { rotary_onButtonClick(); }
  );

  //set boundaries and if values should circle or not
  //in this example we will set possible values between 0 and 1000;
  rotaryEncoder.setBoundaries(-10000, 10000, true); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder.setEncoderValue(0);
  rotaryEncoder.disableAcceleration();
#endif

  Console4.printf("Initializing ADC \n");
#ifdef ADC_IS_ADS1115
  // Settings for ADC
  if (not adc.init())
  {
    Console4.println("ADS1115 not connected!");
  } else {
    adc.setConvRate   (ADS1115_475_SPS);
    adc.setMeasureMode(ADS1115_SINGLE);   //comment line/change parameter to change mode
  }
#endif

#ifdef ADC_IS_ESP
  analogSetWidth(11);               // 11Bit resolution
  analogSetAttenuation(ADC_0db);    // 0=0db (0..1V) 1= 2,5dB; 2=-6dB (0..2V); 3=-11dB  0.2..2.6V ~linear
#endif

  Console4.printf("Initializing DIS \n");
#ifdef DISPLAY_IS_LCD
  tft.init();    // TTGO e_SPI TFT 240*135 pixel
#define GFX_WIDTH 240
#define GFX_HEIGHT 135
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);
  setBrightness (BRIGHTNESS);    // Not part of the tft lib. Function is retrofitted in b_Functions
  tft.setCursor(0, 0, 2); tft.setTextFont(2);  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.print("Device Name: ");
  tft.println(DEVICE_NAME);
  tft.print("Try connecting..  ");
#endif

#ifdef DISPLAY_IS_OLED
  // Initialising the UI will init the display too.
  digitalWrite(I2C_RST, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(I2C_RST, HIGH);   // while OLED is running, must set GPIO16 in high
  display.init();
  delay(1000);
  display.setColor(WHITE);
  display.setBrightness(BRIGHTNESS / 21);
#ifdef DISPLAY_REVERSED
  display.flipScreenVertically();
#endif
  display.clear();
  delay(50);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0,  "Device Name: ");
  display.drawString(64, 0,  DEVICE_NAME);
  display.drawString(0, 12, "Try connect ");
  display.display();
#endif

#ifdef CREDENTIALS
ssid = WIFI_SSID;
pass = WIFI_PASS;
#endif

  Console4.printf("Init WiFi ");
  // Networking and Time
  
  getWiFi();
  delay(100);

  if (WiFi.status() == WL_CONNECTED)
  {
    // Over the Air Framework
    ArduinoOTA.onStart([]()
    {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else { // U_FS
        type = "filesystem";
      }
      // NOTE: if updating FS this would be the place to unmount FS using FS.end()
      Console4.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]()
    {
      Console4.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
      Console4.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error)
    {
      Console4.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Console4.printf("Auth Failed\n");
      } else if (error == OTA_BEGIN_ERROR) {
        Console4.printf("Begin Failed\n");
      } else if (error == OTA_CONNECT_ERROR) {
        Console4.printf("Connect Failed\n");
      } else if (error == OTA_RECEIVE_ERROR) {
        Console4.printf("Receive Failed\n");
      } else if (error == OTA_END_ERROR) {
        Console4.printf("End Failed\n");
      }
    });
    ArduinoOTA.setHostname(DEVICE_NAME);
    ArduinoOTA.begin();

#ifdef DISPLAY_IS_OLED
    sprintf(charbuff, " Connected!"); display.drawString(60, 12, charbuff);
    sprintf(charbuff, "IP= %03d . %03d . %03d . %03d", ip[0], ip[1], ip[2], ip[3]); display.drawString(0, 24, charbuff);
    display.drawString(0, 36, "User name: ");
    display.drawString(64, 36, THINGER_USERNAME);
    display.display();
#endif

#ifdef DISPLAY_IS_LCD
    tft.print(" Connected!\n");
    sprintf(charbuff, "IP= %03d . %03d . %03d . %03d \nUser Name: ",  ip[0], ip[1], ip[2], ip[3]); tft.print(charbuff); tft.println(THINGER_USERNAME);
#endif

    delay(2000);
    getNTP();

#ifdef THINGER
    Console4.printf("\nInitializing Thinger, Username= %s \n", THINGER_USERNAME);

    //Communication with Thinger.io
    thing.handle();
    delay(500); // Wait for contact to happen.

    // definition of structures for transmission
    // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
    // resource output example (i.e. reading a sensor value) https://docs.thinger.io/coding#define-output-resources
    // https://docs.thinger.io/coding#read-multiple-data
    // it is a bit confusing, but Thinger code placed in setup will be exceuted **periodically when required by the dashboard.


    // On/Off processing
    thing["reset_all"] << [](pson & in)
    { //not yet used: reset all values.
      if (in.is_empty())
      {
        yield();
      } else {
        inbyte = 'z';
      }
    };

    thing["reboot"] << [](pson & in)
    { //not yet used: reboot.
      if (in.is_empty())
      {
        yield();
      } else {
        inbyte = 'Z';
      }
    };

#ifdef FET_EXTENSION
    thing["FET0"] << [](pson & in) // 2,5A channel (12V load)
    {
      if (in.is_empty())
      {
        in = Out_IExt0;
      } else {
        Out_IExt0 = in;
      }
    };
    thing["FET1"] << [](pson & in) // 2,5A channel (19V boost)
    {
      if (in.is_empty())
      {
        in = Out_IExt1;
      } else {
        Out_IExt1 = in;
      }
    };
    thing["FET2"] << [](pson & in) // 10A channel (Grid-tied converter)
    {
      if (in.is_empty())
      {
        in = Out_IExt2;
      } else {
        Out_IExt2 = in;
      }
    };
    thing["FET3"] << [](pson & in) // 2,5A channel 38V boost)
    {
      if (in.is_empty())
      {
        in = Out_IExt3;
      } else {
        Out_IExt3 = in;
      }
    };
#endif

    // Radio button style processing with sliders: Slide value is integer, so take value and issue description out of String array

    thing["AhMode "] = [](pson & in, pson & out) {
      if (in.is_empty())
      {
        in = persistence.AhMode ;
      } else {
        persistence.AhMode  = in;
        Runtime = AhCycle_description[persistence.AhMode];
        if (persistence.AhMode == 0) dashboard.Ahout = dashboard.Whout = persistence.CycleSamples = persistence.CycleVSum = persistence.CycleISum = persistence.CycleWSum = 0;
      }
      out = persistence.AhMode ;
    };

    thing["CtrlMode"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.CtrlMode ;
      } else {
        dashboard.CtrlMode  = in;
      }
      out = CtrlMode_description[dashboard.CtrlMode ];
    };

    // Float processing with sliders: Thinger input is currently only integer, so consider slider value is: float( value * 1000)
    thing["scv"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.SetVout * 1000;
      } else {
        dashboard.SetVout = float(in) / 1000;
      }
      out = dashboard.SetVout;
    };

    thing["scp"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.SetVin * 1000;
      } else {
        dashboard.SetVin = float(in) / 1000;
      }
      out = dashboard.SetVin;
    };

    thing["scc"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.SetIout * 1000;
      } else {
        dashboard.SetIout = float(in) / 1000;
      }
      out = dashboard.SetIout;
    };

    thing["measure"] >> [](pson & out)
    {
      out["Vout"]            = dashboard.Vout ;
      out["Iout"]            = dashboard.Iout ;
      out["Wout"]            = dashboard.Wout ;
      out["Ahout"]           = dashboard.Ahout ;
      out["Whout"]           = dashboard.Whout ;
      out["Vin"]             = dashboard.Vin ;
      out["Iin"]             = dashboard.Iin ;
      out["Iout"]            = dashboard.Iout ;
      out["SetVout"]         = dashboard.SetVout ;
      out["ConVin"]          = dashboard.ConVin ;
      out["ConIout"]         = dashboard.ConIout ;
      out["SetVin"]          = dashboard.SetVin ;
      out["SetIout"]         = dashboard.SetIout ;
      out["DeltaVout"]      = dashboard.Vout - persistence.initial_voltage;
      out["Ohm"]             = dashboard.load_internal_resistance ;
      out["Charge%"]         = dashboard.percent_charged ;
    };

    thing["status"] >> [](pson & out)
    {
      out["Runtime"]         = Runtime ;
      out["Message"]         = Message ;
      out["ChrgPhaseTXT"]    = ChrgPhase_description[dashboard.ChrgPhase];
      out["CtrlModeTXT"]     = CtrlMode_description[dashboard.CtrlMode];

    };


    thing["HOUR"] >> [](pson & out)
    {
      out["Vout"]             = dashboard.Vout ;
      out["Iout"]             = dashboard.Iout ;
      out["Wout"]             = dashboard.Wout ;
      out["Ahout"]            = dashboard.Ahout ;  //Ah of the current cycle
      out["Whout"]            = dashboard.Whout ;  //Wh of the current cycle
      out["Vin"]              = dashboard.Vin ;
      out["Iin"]              = dashboard.Iin ;
      out["Iout"]             = dashboard.Iout ;
      out["SetVout"]          = dashboard.SetVout ;
      out["SetIout"]          = dashboard.SetIout ;
    };

    thing["MIN"] >> [](pson & out)
    {
      out["Vout"]             = dashboard.Vout ;
      out["Iout"]             = dashboard.Iout ;
      out["Ioutx10"]          = dashboard.Iout * 10 ;
      out["Wout"]             = dashboard.Wout ;
      out["Ahout"]            = Ahout ;           //Ah of the current hour
      out["Whout"]            = Whout ;           //Ah of the current hour
      out["Vin"]              = dashboard.Vin ;
      out["Iin"]              = dashboard.Iin ;
      out["Iout"]             = dashboard.Iout ;
      out["SetVout"]          = dashboard.SetVout ;
      out["SetIout"]          = dashboard.SetIout ;
    };

    thing["DAY"] >> [](pson & out)
    {
      out["BAhDay"] = Ah[27];
      out["BV@0h"]  = persistence.voltageAt0H;
      out["BVDiff"] = persistence.voltageDelta;
    };

    //Initially retrieve the values that must persist after reboot
    pson thing_property;
    thing.get_property ("thing_property", thing_property);
    persistence.voltageAt0H = thing_property["voltageAt0H"];
    persistence.voltageDelta = thing_property["voltageDelta"];
    Ahout = thing_property["Ah/hour"];
    Whout = thing_property["Wh/hour"];
    persistence.HourSamples = thing_property["HourSamples"];
    persistence.initial_voltage = thing_property["InitialVoltage"];

    // Controller Settings
    P_value = thing_property["_P_value"];
    I_value = thing_property["_I_value"]; 
    D_value = thing_property["_D_value"];
    MPPT_perturbe = thing_property["_MPPT_perturbe"];
    fractionVoc = thing_property["_fractionVoc"];

    // Menu Settings
    displayPage    = thing_property["_displayPage"];
    displaySubPage = thing_property["_displaySubPage"];  //not yet used
    serialPage     = thing_property["_serialPage"];

    // Retrieve the Ah array
    pson Ah_prop;
    thing.get_property("AhStat", Ah_prop);  // 0..23=hour, 25=dashboard.Ipan, 26=Ah 24h, 27= AhDay, 28=AhNight, 29=Ah22-24
    Ah[0]  = Ah_prop["00h"];
    Ah[1]  = Ah_prop["01h"];
    Ah[2]  = Ah_prop["02h"];
    Ah[3]  = Ah_prop["03h"];
    Ah[4]  = Ah_prop["04h"];
    Ah[5]  = Ah_prop["05h"];
    Ah[6]  = Ah_prop["06h"];
    Ah[7]  = Ah_prop["09h"];
    Ah[8]  = Ah_prop["08h"];
    Ah[9]  = Ah_prop["09h"];
    Ah[10] = Ah_prop["10h"];
    Ah[11] = Ah_prop["11h"];
    Ah[12] = Ah_prop["12h"];
    Ah[13] = Ah_prop["13h"];
    Ah[14] = Ah_prop["14h"];
    Ah[15] = Ah_prop["15h"];
    Ah[16] = Ah_prop["16h"];
    Ah[17] = Ah_prop["17h"];
    Ah[18] = Ah_prop["18h"];
    Ah[19] = Ah_prop["19h"];
    Ah[20] = Ah_prop["20h"];
    Ah[21] = Ah_prop["21h"];
    Ah[22] = Ah_prop["22h"];
    Ah[23] = Ah_prop["23h"];
    Ah[25] = Ah_prop["LastHour"];
    Ah[27] = Ah_prop["Yesterday"];
    Ah[26] = Ah_prop["Today"];

    pson LTData;
    thing.get_property("LongTerm", LTData);
    persistence.initial_voltage = LTData["initial_voltage"];
    persistence.voltageAt0H     = LTData["voltageAt0H"];
    persistence.voltageDelta    = LTData["voltageDelta"];
    persistence.HourVSum        = LTData["HourVSum"];
    persistence.HourISum        = LTData["HourISum"];
    persistence.HourWSum        = LTData["HourWSum"];
    persistence.HourSamples     = LTData["HourSamples"];
    persistence.CycleVSum       = LTData["CycleVSum"];
    persistence.CycleISum       = LTData["CycleISum"];
    persistence.CycleWSum       = LTData["CycleWSum"];
    persistence.CycleSamples    = LTData["CycleSamples"];
    persistence.AhMode          = LTData["AhMode"];

#endif

  } //end if WiFi Status == Connected

  delay(1000);

  getEpoch();            // writes the Epoch (Numbers of seconds till 1.1.1970...
  getTimeData();         // breaks down the Epoch into discrete values.

  sprintf(charbuff, "\nNow is %s, %02d %s %04d %02d:%02d:%02d. Epoch =%10lu\n", DayName, Day, MonthName, Year, Hour, Minute, Second, Epoch);  Console4.println(charbuff);
  sprintf(charbuff, "%s, %02d %s %04d %02d:%02d:%02d", DayName, Day, MonthName, Year, Hour, Minute, Second);

#ifdef DISPLAY_IS_OLED
  display.drawString(0, 48, charbuff);
  display.display();
#endif

#ifdef DISPLAY_IS_LCD
  tft.println();
  tft.print(charbuff);
#endif

  delay(2000);
#ifdef DISPLAY_IS_LCD
  tft.fillScreen(TFT_BLACK);
#endif

#ifdef TELNET
TelnetStream.begin();
#endif

#ifndef THINGER
  // read/write persistence from EEPROM (Adress = 100...)
  for ( int i = 0; i < sizeof(persistence); ++i ) persistence_punning[i] = EEPROM.read ( i + 100 );
  memcpy(&persistence, persistence_punning, sizeof(persistence));
  //  EEPROM.write ( i + 100,  persistence_punning[i] );
#endif

  serialPage = '0';           // default reporting page
  displayPage = 1;
  serialPeriodicity = '!';

  if (dashboard.SetVout == 0)   // still uninitialized, loading defaults
  {
    dashboard.SetVout = dashboard.ConVout = phase_voltage[4];
    dashboard.SetIout = 4;
    dashboard.SetVin = dashboard.ConVin = PANEL_MPP;
    lastADC_Vout = lastADC_Iout = 500;
  }
#ifdef TELNET
  Console4.print("Ready to accept TELNET commands\n " );
  TelnetStream.print("Ready to accept commands\n " );#else
  Console4.print("Ready to accept Serial commands\n " );
#endif  
}
//end Setup
