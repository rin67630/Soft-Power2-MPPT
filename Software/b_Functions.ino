//****** Macro for Timing *****
#define runEvery(t) for (static uint16_t _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

//****** Instantiations ******
WiFiUDP UDP; // Creation of wifi Udp instance

#ifdef THINGER
ThingerESP32 thing(THINGER_USERNAME, THINGER_DEVICE, THINGER_DEVICE_CREDENTIALS);
#endif

MoToButtons Buttons( buttonPins, buttonCount, 130, 5000 ); //  130ms debounce. 5 s to distinguish short/long

#ifdef CONTR_IS_WEMOS
SSD1306Wire display(0x3c, I2C_SCL, I2C_SDA);                  //OLED 128*64 soldered
#endif


#ifdef CONTR_IS_HELTEC
SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED, RST_OLED, GEOMETRY_128_64);
#endif


#ifdef CONTR_IS_TTGO
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
#define TFT_GREY     0x5AEB // better Grey
#define TFT_VERMILON 0xFA60 // better Orange
#endif

#ifdef ADC_IS_ADS1115
ADS1115_WE adc(0x48);
#endif

#ifdef ROTARY
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1 , ROTARY_ENCODER_STEPS);
#endif

#ifdef FET_EXTENSION
ADS1115_WE adc2(0x49);
PCF8574 pcf8574(0x39); //PCF address, initial value
//PCF8574 pcf8574(0x38, INTERRUPTED_PIN, updateEncoder);
//pcf8574.begin();// Start library
#endif

#ifdef BLUETOOTH
BluetoothSerial SerialBT;
#endif

// ***** Functions ******

void rotary_onButtonClick()
{
}

// ************WiFi Managemement****************
void getWiFi()
{
  if ((WiFi.status() != WL_CONNECTED))
  {
    WiFi.mode(WIFI_STA);
    if (ssid.length() && pass.length())
    {
      WiFi.begin(ssid.c_str(), pass.c_str());
    } else {
      WiFi.begin();
    }
    //    WiFi.begin(WIFI_SSID, WIFI_PASS);
    //    WiFi.begin();
    wifiConnectCounter = 1;
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(wifiRepeatInterval);
      Console4.print(".");
      wifiConnectCounter++;
      if (wifiConnectCounter > wifiMaxTries)
      {
        Console4.printf("\nIs %s , %s OK? -> else redo w", ssid.c_str(), pass.c_str());
        AP_mode();
        break;
      }
    }
    delay(50);
    WiFi.setHostname(DEVICE_NAME);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    ip = WiFi.localIP();
  } else {
    Console4.printf("\nStarting Access point\n");
    WiFi.softAP("SoftPower", WIFI_PASS);
    ip = WiFi.softAPIP();
  }
  Console4.print("\nDone: RRSI= ");   Console4.print(WiFi.RSSI());
  myIP();  Console4.printf(charbuff);
}

void AP_mode()
{
      WiFi.disconnect(true, true);
      delay(1000);
      Console4.printf("\nStarting Access point\n");
      WiFi.softAP("SoftPower", WIFI_PASS);
      ip = WiFi.softAPIP();
      myIP(); Console2.printf ("\nNow %s\n", charbuff);  
}

void setWiFifromStream()           // Enter WiFi over Serial/Telnet (Blocking!)
{
  Console2.printf ("\nEnter <SSID Password> (with the <>!)\n");
  while (not Console0.available())
  {}
  // read in the user input
  ssid = Console0.readStringUntil('<');        // ignore evrything up to <  (SSID will be overwritten next)
  ssid = Console0.readStringUntil(' ');        // store SSID
  pass = Console0.readStringUntil('>');        // store password
  while ( Console0.available() )
  {
    Console0.read(); //flush the rest
  }
  Console2.printf("\n Going to '%s'(%u), '%s'(%u)\n", ssid.c_str(), ssid.length(), pass.c_str(), pass.length());
#ifdef TELNET
  TelnetStream.println("bye bye");
  TelnetStream.stop();
#endif
  WiFi.disconnect();
  delay(1000);
  getWiFi();
}

void myIP()    // generate a charbuff string with the IP (for displays that cannot use the Posix Print)
{
  sprintf(charbuff, " IP=%03d.%03d.%03d.%03d", ip[0], ip[1], ip[2], ip[3]);
}

//********* Time management*************
void getNTP()
{
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  now = time(nullptr);
  Epoch = now;
}

void getEpoch()
{
  now = time(nullptr);
  Epoch = now;
}

void getTimeData()
{
  timeinfo  = localtime(&now);  // cf: https://www.cplusplus.com/reference/ctime/localtime/
  Second    = timeinfo->tm_sec;
  Minute    = timeinfo->tm_min;
  Hour      = timeinfo->tm_hour;
  Weekday   = timeinfo->tm_wday + 1 ;
  Day       = timeinfo->tm_mday;
  Month     = timeinfo->tm_mon + 1;
  Year      = timeinfo->tm_year + 1900; //returns years since 1900
  strftime (DayName,   12, "%A", timeinfo); //cf: https://www.cplusplus.com/reference/ctime/strftime/
  strftime (MonthName, 12, "%B", timeinfo);
  strftime (Time,      10, "%T", timeinfo);
  strftime (Date,      12, "%d/%m/%Y", timeinfo);
}

void buffTimeData()   // writes the time/date in Charbuff for print or display
{
  strftime(charbuff, sizeof(charbuff), " %R %d%b ", timeinfo);
}

void setTimefromStream()           // Enter time over Serial/Telnet (Blocking!)
{
  Console2.printf ("\nEnter Date/Time dd/mm/yyyy hh:mm:ss\n");
  while (not Console0.available())
  {}
  // read in the user input
  Day = Console0.parseInt();
  Month = Console0.parseInt();
  Year = Console0.parseInt();
  Hour = Console0.parseInt();
  Minute = Console0.parseInt();
  Second = Console0.parseInt();
  boolean validDate = (inRange(Day, 1, 31) && inRange(Month, 1, 12) && inRange(Year, 2021, 2031));
  boolean validTime = (inRange(Hour, 0, 23) && inRange(Minute, 0, 59) && inRange(Second, 0, 59));
  if (validTime && validDate)
  {
    configTime(0, 0, "pool.ntp.org");    // Repair timezone
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 3);
    tzset();
    struct tm t;                         //Prepare time strucure
    time_t t_of_day;
    t.tm_year = Year - 1900;             // Year - 1900
    t.tm_mon = Month - 1;                // Month, where 0 = jan
    t.tm_mday = Day ;                    // Day of the month
    t.tm_hour = Hour;
    t.tm_min = Minute;
    t.tm_sec = Second;
    t.tm_isdst = -1;                     // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);
    struct timeval tv;                   //Extending to mandatory microseconds
    tv.tv_sec = t_of_day;                // epoch time (seconds)
    tv.tv_usec = 0;                      // microseconds
    settimeofday(&tv, 0);                //Setting Clock
    getEpoch();
    Console2.println(ctime(&now));
  } else {
    Console2.print ("Sorry, try again");
  }
}

//*** Power saving delays ***
void espDelay(int ms)
{
  esp_sleep_enable_timer_wakeup(ms * 1000);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
  esp_light_sleep_start();
}

//****Display***

void setBrightness( int brightness)  // Display brightness 0..2047
{
  ledcWrite(14, brightness);
}


//*** Other Math / conversions ***
bool inRange(int x, int low, int high) // checks if a value is in boundaries
{
  if (x >= low && x <= high)
    return true;
  return false;
}
