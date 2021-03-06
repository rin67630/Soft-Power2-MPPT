void menuRun()
{
  if (Year < 2020) setTimefromStream();
#ifdef TELNET
  if (TelnetStream.available())   inbyte = TelnetStream.read(); //Telnet input available
#endif
  if (Serial.available())   inbyte = Serial.read();         //Serial input available
  /*  // Provision for I2C Keyboard
    Wire.requestFrom(0x08, 1)
    while (Wire.available())
    {
      inbyte = = Wire.read();                  // receive a byte as character
      if (key_val != 0) {
        if (key_val >= 0x20 && key_val < 0x7F) { // ASCII String
          Serial.print((char)key_val);
        } else {
          Serial.printf("0x%02X ", key_val);
        }
      }
    }
  */
  Buttons.processButtons();
  if ( Buttons.longPress(UP) || Buttons.longPress(DOWN) ||  Buttons.longPress(ROT)  )
  {
    setpointMode = not setpointMode;
    Console2.printf("SetpointMode is %s\n", setpointMode ? "on" : "off" );
  }
  if ( Buttons.shortPress(UP) )
  {
    action = action + 1;
  }
  if ( Buttons.shortPress(DOWN) )
  {
    action = action - 1;
  }

  switch (inbyte)
  {
    //====(Serial Menu)======

    // *** Actions***
    case '0': //Clear screen
      displayPage = 0;
#ifdef DISPLAY_IS_LCD
      setBrightness (0);
#endif
#ifdef DISPLAY_IS_OLED
      display.clear();
#endif
      Console2.printf ("Off\n");
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
      // switch screen pages
      cycleDisplay = false;
      setpointMode = false;
      displayPage = inbyte - 48;  // Ascii to number
#ifdef DISPLAY_IS_LCD
      tft.fillScreen(TFT_BLACK);
#endif
#ifdef DISPLAY_IS_OLED
      display.setContrast(255);
#endif
      Console2.printf ("Display= %i\n", inbyte - 48);
      break;
    case '9': //Cycle Displays
      cycleDisplay = true;
#ifdef DISPLAY_IS_LCD
      tft.fillScreen(TFT_BLACK);
#endif
      Console2.printf ("Cycling displays\n");
      break;
    case '+': //Increase Vout Setpoint
      ++action;
      setpointMode = true;
      break;
    case '-': //Reduce Vout Setpoint
      --action;
      setpointMode = true;
      break;
    case 'Z':  // Write persistence and Reset
      for ( int i = 0; i < sizeof(persistence); ++i ) EEPROM.write ( i + 100,  persistence_punning[i] );
      EEPROM.commit();
      memcpy(persistence_punning, &persistence, sizeof(persistence));
      Console2.printf ("\nResetting in 10s...\n");
      delay(10000);
#ifdef TELNET
      TelnetStream.println("bye bye");
      TelnetStream.stop();
#endif
      ESP.restart();
      break;
    case 'z':  //Reset runtime
      Console2.printf ("\nRt:%06ui m, Ah:%06.3f Wh:%06.3f \n", persistence.CycleSamples, Ahout, Whout);
      Console2.printf ("\nResetting \n");
      persistence.HourSamples = 0;
      Ahout = Whout = 0;
      persistence.CycleVSum = persistence.CycleISum = persistence.CycleSamples = 0;
      persistence.initial_voltage = dashboard.Vout;
#if defined (THINGER)
      thing.stream("status");
#endif
      break;
    case 'j':  //Reset Job Maxes
      Console2.printf ("\nReset Job Timings \n");
      for (int i = 14; i < 21; i++) RunMillis[i] = 0;  // Reset job timing stats
      break;
    //*** Changes of Modes ***
    case 'C': //Charger modes "NIGH", "RECO", "BULK", "PANL", "ABSO", "FLOA", "EQUA", "OVER", "DISC", "PAUS", "NOBA", "NOPA", "EXAM"
      dashboard.ChrgPhase  ++;
      if (dashboard.ChrgPhase >= 13) dashboard.ChrgPhase  = 0;
      Console2.print ("Char.Mode changed to " + ChrgPhase_description[dashboard.ChrgPhase] + "\n" );
      break;
    case 'A': //Ah Cycles "STOP", "RUN", "DAILY"
      persistence.AhMode  ++;
      if (persistence.AhMode  > DAILY) persistence.AhMode  = STOP;
      Runtime = AhCycle_description[persistence.AhMode];
      Console2.print ("Ah.Mode changed to " + AhCycle_description[persistence.AhMode] + "\n" );
      break;
    case 'O': //Operation mode ""Manu ", "PVFx ", "MPPT "}"
      dashboard.CtrlMode  ++;
      if (dashboard.CtrlMode  > MPPT) dashboard.CtrlMode  = MANU;
      Console2.print ("CtrlMode changed to " + CtrlMode_description[dashboard.CtrlMode] + "\n" );
      break;
    // ***One shot Reports**
    case 'S':  //Summary Report
      serialPage = 'S';
      break;
    case 'D':  //Debug Report
      Console2.printf ("\nDebug Report\n");
      serialPage = 'D';
      break;
    case 'X':  //Calibration Report
      Console2.printf ("\neXcel Calibration Report\n");
      serialPage = 'X';
      break;
    case 'J':  //Job duration Report
      Console2.printf ("\nJob Timing\n");
      serialPage = 'J';
      break;
    case 'I':  //Internal Parameter List
      Console2.printf("Int.Par.List \nAhCycle= %i\t CtrlMode= %i\t ChrgPhase= %i I_value= %5.2f, MPPT_perturbe= %5.2f,  fractionVoc=  %5.2f \n", persistence.AhMode, dashboard.CtrlMode, dashboard.ChrgPhase, I_value, MPPT_perturbe, fractionVoc);
      break;
    case 't':  // Print time
      Console2.println(ctime(&now));
      break;
    case 'T': // Enter time
      setTimefromStream();        // blocking!
      break;
#ifdef TELNET
    case 'Q': // Logoff from telnet
      TelnetStream.println("bye bye");
      TelnetStream.flush();
      TelnetStream.stop();
      break;
#endif
    case 'W':  // Change WiFi, Goto AP on failure
      while (Console1.read() != -1); // discard all other received characters
      Console2.printf ("\nNew WiFi, fail-> LOCAL AP, confirm? Y or N\n");
      while (not Console0.available())
      {}
      // read in the user input
      switch (Console0.read())
      {
        default:
          Console2.printf ("\n a wise decision!\n");
          break;
        case 'Y':
          Console2.printf ("\n Y? you were warned!\n");
          while (Console1.read() != -1); // discard all other received characters
          Console1.printf("\nEnter <SSID Password> (with the <>!)\n");
          while (not Console1.available());
          // read in the user input
          Console1.readStringUntil('<'); // ignore everything up to <  (SSID will be overwritten next)
          ssid = Console1.readStringUntil(' ');        // store SSID
          pass = Console1.readStringUntil('>');        // store password
          while (Console1.read() != -1); // discard the reset of the input
          Console1.printf("\n Going to '%s'(%u), '%s'(%u)\n", ssid.c_str(), ssid.length(), pass.c_str(), pass.length());
#ifdef TELNET
          TelnetStream.println("bye bye");
          TelnetStream.stop();
#endif
          WiFi.disconnect();
          delay(1000);
          getWiFi();
          break;
      }
      break;
    case 'w': //Print WiFi status
      serialPage = 'w';
      break;

    case 'P': // Write persistence data to EEPROM (Adress = 100...)
      for ( int i = 0; i < sizeof(persistence); ++i ) EEPROM.write ( i + 100,  persistence_punning[i] );
      EEPROM.commit();
      memcpy(persistence_punning, &persistence, sizeof(persistence));
      //persistence_punning[i] = EEPROM.read ( i + 100 );
      break;
    // ***Options for periodical Reports**
    case 'd': //Day Report
      serialPeriodicity = 'd';
      break;
    case 'h': //Hour Report
      serialPeriodicity = 'h';
      break;
    case 'm': //Minute Report
      serialPeriodicity = 'm';
      break;
    case 's': //Second Report
      serialPeriodicity = 's';
      break;
    case '!': //Unique (One shot)
      serialPeriodicity = '!';
      break;
    case '#': //Completely Stop Reports (also Events and Summary)
      serialPeriodicity = '0';
      break;
    case 'e': //Toggle Events
      serialEvent = not serialEvent;
      break;
    // ***Periodical Reports/Plots**
    case 'E':  //Energy Plot
      Console2.printf ("Energy Plot\n");
      serialPage = 'E';
      break;
  } //end switch (inbyte)
  inbyte = 0 ;
}
