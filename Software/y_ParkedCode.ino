/* 
 #include <WiFiMulti.h>
WiFiMulti wifiMulti;
 wifiMulti.addAP(ssid, password);
 wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
 wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

* ESP 8266 code examples
 * void light_sleep(){
   wifi_station_disconnect();
   wifi_set_opmode_current(NULL_MODE);
   wifi_fpm_set_sleep_type(LIGHT_SLEEP_T); // set sleep type, the above    posters wifi_set_sleep_type() didnt seem to work for me although it did let me compile and upload with no errors 
   wifi_fpm_open(); // Enables force sleep
   gpio_pin_wakeup_enable(GPIO_ID_PIN(2), GPIO_PIN_INTR_LOLEVEL); // GPIO_ID_PIN(2) corresponds to GPIO2 on ESP8266-01 , GPIO_PIN_INTR_LOLEVEL for a logic low, can also do other interrupts, see gpio.h above
   wifi_fpm_do_sleep(0xFFFFFFF); // Sleep for longest possible time
 }
 *
 *
 *
  #if defined (SMARTCONFIG)
  void getWiFi()
  {
  WiFi.mode(WIFI_STA);
  wifi_station_set_auto_connect(true);
  wifi_station_set_hostname(DEVICE_NAME);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    int cnt = 0;
    //    Console3.print(".");
    if (cnt++ >= wifiMaxTries) {
      WiFi.beginSmartConfig();
      while (1) {
        delay(wifiRepeatInterval);
        if (WiFi.smartConfigDone())
        {
          Console3.println("SmartConfig Success");
          break;
        }
      }
    }
  }
  ip = WiFi.localIP();
  }
  #else


  #include <IRremote.h>
 
int RECV_PIN = 15;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
Serial.begin(9600);
irrecv.enableIRIn(); // Start the receiver
}
 
void loop()
{
if (irrecv.decode(&results))
{
Serial.println(results.value, HEX);
irrecv.resume();
}
}
*/
