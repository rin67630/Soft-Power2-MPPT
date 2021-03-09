void setup()
{
 
  // Serial initialisation
  Serial.begin (SERIAL_SPEED); // On USB port
  Serial.setDebugOutput(true);
  Wire.begin(OLED_SDA, OLED_SCL);


  // Settings for ADC
  analogSetWidth(11);               // 11Bit resolution
  analogSetAttenuation(ADC_0db);    // 0=0db (0..1V) 1= 2,5dB; 2=-6dB (0..2V); 3=-11dB  0.2..2.6V ~linear
  //adc1_get_raw(ADC1_CHANNEL_0);


  // Settings for PWM
  ledcSetup(0, 2000, 11);             // 11 bit resolution@ 2Khz
  ledcSetup(3, 2000, 11);             // 11 bit resolution@ 2Khz
  ledcAttachPin(PWM0, 0);
  ledcAttachPin(PWM3, 3);
  //ledcWrite(channel, dutycycle);

  
  Console4.printf("\nESP-Karajan at work,Serial @ %u Baud\nTrying to connect\n\n", SERIAL_SPEED);


#ifdef DISPLAY_IS_OLED128x64
  // Initialising the UI will init the display too.
  pinMode(16, OUTPUT);
  pinMode(25, OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH);   // while OLED is running, must set GPIO16 in high
  display.init();
  delay(1000);
  display.setColor(WHITE);
  //display.setBrightness(100);
#ifdef DISPLAY_REVERSED
  display.flipScreenVertically();
#endif
  display.clear();
  delay(50);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0,  DEVICE_NAME);
  display.drawString(0, 12, "Try connect..");
  display.display();
#endif

  // Networking and Time

  WiFi.mode(WIFI_STA);

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
//    Console4.printf("OTA Ready\n MAC address: %s\nHostname: %s \n", WiFi.macAddress().c_str(), WiFi.hostname().c_str());

#ifdef DISPLAY_IS_OLED128x64
    sprintf(charbuff, "Connected!"); display.drawString(60, 24, charbuff);
    sprintf(charbuff, "IP= %03d . %03d",  ip[2], ip[3]); display.drawString(0, 36, charbuff);
    display.display();
    delay(2000);
#endif
    getNTP();

#if defined (THINGER)
    Console4.printf(" Initializing Thinger\n");
    // definition of structures for transmission
    // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
    // resource output example (i.e. reading a sensor value) https://docs.thinger.io/coding#define-output-resources
    // https://docs.thinger.io/coding#read-multiple-data
    // it is a bit confusing, but Thinger code placed in setup will be exceuted **periodically when required by the dashboard.

    thing["menu"] << [](pson & in) {
      displayPage    = in["displayPage"];
      displaySubPage = in["displaySubPage"];
      serialPage     = in["serialPage"];
    };

    thing["scv"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.Vset;
      } else {
        dashboard.Vset = in;
      }
      dashboard.Vset = float(in) / 1000;
      out = dashboard.Vset;
    };

    thing["scc"]  = [](pson & in, pson & out)
    {
      if (in.is_empty())
      {
        in = dashboard.Iset;
      } else {
        dashboard.Iset = in;
      }
      dashboard.Iset = float(in) / 1000;
      out = dashboard.Iset;
    };    

    thing["measure"] >> [](pson & out)
    {
      out["Vout"]            = dashboard.Vout ;
      out["Iout"]            = dashboard.Iout ;
      out["Wout"]            = dashboard.Wout ;
      out["Ahout"]           = dashboard.Ahout ;
      out["Whpan"]           = dashboard.Whout ;
      out["Vin"]             = dashboard.Vin ;
      out["Iin"]             = dashboard.Iin ;
      out["Iout"]            = dashboard.Iout ;
      out["Vset"]            = dashboard.Vset ;
      out["Iset"]            = dashboard.Iset ;
    };

    thing["HOUR"] >> [](pson & out)
    {
      out["Vout"]             = dashboard.Vout ;
      out["Iout"]             = dashboard.Iout ;
      out["Wout"]             = dashboard.Wout ;
      out["Ahout"]            = dashboard.Ahout ;
      out["Whpan"]            = dashboard.Whout ;
      out["Vin"]              = dashboard.Vin ;
      out["Iin"]              = dashboard.Iin ;
      out["Iout"]            = dashboard.Iout ;
      out["Vset"]            = dashboard.Vset ;
      out["Iset"]            = dashboard.Iset ;
    };

    thing["MIN"] >> [](pson & out)
    {
      out["Vout"]             = dashboard.Vout ;
      out["Iout"]             = dashboard.Iout ;
      out["Wout"]             = dashboard.Wout ;
      out["Ahout"]            = dashboard.Ahout ;
      out["Whpan"]            = dashboard.Whout ;
      out["Vin"]              = dashboard.Vin ;
      out["Iin"]              = dashboard.Iin ;
      out["Iout"]            = dashboard.Iout ;
      out["Vset"]            = dashboard.Vset ;
      out["Iset"]            = dashboard.Iset ;
    };

    //Communication with Thinger.io
    thing.handle();
    delay(1000); // Wait for contact to happen.
    // Retrieve Persistance values
#endif

  }

  delay(1000);

  getEpoch();            // writes the Epoch (Numbers of seconds till 1.1.1970...
  getTimeData();         // breaks down the Epoch into discrete values.

  sprintf(charbuff, "Now is %s, %02d %s %04d %02d:%02d:%02d. Epoch =%10lu\n", DayName, Day, MonthName, Year, Hour, Minute, Second, Epoch);  Console4.println(charbuff);


  // Initialisations.

  serialPage = '0';           // default reporting page AK Modulbus

  dashboard.Vset = 14.4;
  dashboard.Iset = 0.7;
  CVinj = 673;  // =~14.4V
  CCinj = 185;  // =~ 0.5A
  lastA0 = lastA3 = 500;
}
//end Setup