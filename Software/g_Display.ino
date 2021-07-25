void displayRun()
{
#ifdef CONTR_IS_HELTEC
  auto &display = *(Heltec.display);
#endif
  yield();
  rotary_onButtonClick();
  encoderChanged = rotaryEncoder.encoderChanged();
  if (not digitalRead(BUTTON_UP) || (not buttonPressed && encoderChanged > 0))
  {
    encoderChanged = 0;
    ++ displayPage;
    cycleDisplay = false;
    if (displayPage >= 7) displayPage = 0;
#ifdef DISPLAY_IS_LCD
    tft.fillScreen(TFT_BLACK);
#endif
  }

  if (not digitalRead(BUTTON_DOWN) || (not buttonPressed && encoderChanged < 0))
  {
    encoderChanged = 0;
    -- displayPage;
    cycleDisplay = false;
    if (displayPage < 0 ) displayPage = 0;
#ifdef DISPLAY_IS_LCD
    tft.fillScreen(TFT_BLACK);
#endif
  }

#ifdef DISPLAY_IS_LCD  // TTGO e_SPI TFT 240*135 pixel
  if ((Second % 10 == 5) && (cycleDisplay)) // every 6 seconds
  {
    ++ displayPage;
    if (displayPage >= 5) displayPage = 1;
    tft.fillScreen(TFT_BLACK);
  }

  if (displayPage)   // Draw frame elements (if not displayPage = 0)
  {
    // Setpoint line
    setBrightness (BRIGHTNESS);

    // Time line
    tft.setTextColor(TFT_GREY, TFT_BLACK); tft.setCursor(0, 110, 4);
    buffTimeData();  tft.print(charbuff);
    tft.setTextColor(TFT_PURPLE, TFT_BLACK) ; tft.println(Runtime);
    tft.fillRect(0, 130, 120, 2, TFT_BLACK); //clear seconds progress bar
    tft.fillRect(0, 130, Second * 2, 2, TFT_PURPLE); //display seconds progress bar
    tft.setTextColor(TFT_PURPLE, TFT_BLACK) ;

    // Fan Graph
    tft.fillRect(231, 30, 6, 78, TFT_GREY);             //clear fan progress bar
    tft.fillRect(231, 30, 6, 78 - PWM_Fan * 0.076, TFT_BLACK);

    // Button description
    if (buttonPressed)
    {
      tft.setTextColor(TFT_BLACK, TFT_DARKGREY);    // print the button meanings
    } else {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
    }
    tft.setCursor(225, 0, 4);
    tft.print(">");
    tft.setCursor(225, 113, 4);
    tft.print("<");

    // Setpoint Line
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setCursor(0, 0, 2);
    sprintf(charbuff, "Setpoints: %05.2fV | %05.2fA | ", dashboard.SetVout, dashboard.SetIout) ;  tft.println(charbuff);
  }

  switch (displayPage)
  {
    case 0 :
      setBrightness (0);
      break;

    case 1 :     // Volt /Ampere  Display (output)
      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      tft.setCursor(186, 0, 2);  tft.print(" V/A ");  // highlight CV

      // Variables
      tft.setTextColor(TFT_GREEN, TFT_BLACK) ;
      tft.setCursor(10, 16, 7); sprintf(charbuff, "%05.2f ", dashboard.Vout); tft.print(charbuff);
      tft.setCursor(160, 34, 4); tft.print("Volt");
      tft.setTextColor(TFT_VERMILON, TFT_BLACK) ;
      tft.setCursor(10, 64, 7); sprintf(charbuff, "%05.2f ", dashboard.Iout); tft.print(charbuff);
      tft.setCursor(160, 85, 4); tft.print("Amp");
      break;

    case 2 :     // Volt /Ampere  Display (intput)
      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      tft.setCursor(186, 0, 2);  tft.print(" Inp ");  // highlight CV

      // Variables
      tft.setTextColor(TFT_GOLD, TFT_BLACK) ;
      tft.setCursor(10, 16, 7); sprintf(charbuff, "%05.2f ", dashboard.Vin); tft.print(charbuff);
      tft.setCursor(160, 34, 4); tft.print("Volt");
      tft.setTextColor(TFT_VERMILON, TFT_BLACK) ;
      tft.setCursor(10, 64, 7); sprintf(charbuff, "%05.2f ", dashboard.Iin); tft.print(charbuff);
      tft.setCursor(160, 85, 4); tft.print("Amp");
      break;

    case 3 :    // CV Display
      // Setpoint highlight
      if (buttonPressed)
      {
        tft.setTextColor(TFT_BLACK, TFT_WHITE);  tft.setCursor(65, 0, 2);   // highlight CV
        sprintf(charbuff, "%06.2fV", dashboard.SetVout) ;  tft.print(charbuff);
        dashboard.SetVout += float(encoderChanged * abs(encoderChanged)) / 100;
      }

      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);  tft.setCursor(186, 0, 2);   // highlight CV
      tft.print(" CV ");

      // Variables
      tft.setTextColor(TFT_GREEN, TFT_BLACK) ;
      tft.setCursor(10, 16, 7); sprintf(charbuff, "%05.2f ", dashboard.Vout); tft.print(charbuff);
      tft.setCursor(160, 34, 4); tft.print("Volt");
      tft.setCursor(10, 64, 7); sprintf(charbuff, "%05.2f ", dashboard.SetVout); tft.print(charbuff);
      tft.setCursor(160, 85, 4); tft.print("SetP.");
      break;

    case 4 :    // CC Display
      // Setpoint Highlight
      if (buttonPressed)
      {
        tft.setTextColor(TFT_BLACK, TFT_WHITE); tft.setCursor(125, 0, 2);  // highlight CC
        sprintf(charbuff, "%05.2fA ", dashboard.SetIout) ;  tft.print(charbuff);
        dashboard.SetIout += float(encoderChanged * abs(encoderChanged)) / 100;
      }

      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);  tft.setCursor(186, 0, 2);   // highlight CV
      tft.print(" CC ");

      // Variables
      tft.setTextColor(TFT_VERMILON, TFT_BLACK) ;
      tft.setCursor(10, 16, 7); sprintf(charbuff, "%05.2f ", dashboard.Iout); tft.print(charbuff);
      tft.setCursor(160, 34, 4); tft.print("Amp");
      tft.setCursor(10, 64, 7); sprintf(charbuff, "%05.2f ", dashboard.SetIout); tft.print(charbuff);
      tft.setCursor(160, 85, 4); tft.print("SetP.");
      break;

    case 5 :     // Power Supply Display
      // Setpoint Highlight
      if (buttonPressed)
      {
        tft.setTextColor(TFT_BLACK, TFT_WHITE); tft.setCursor(125, 0, 2);  // highlight CC
        sprintf(charbuff, "%05.2fA ", dashboard.SetIout) ;  tft.print(charbuff);
        dashboard.SetIout += float(encoderChanged * abs(encoderChanged)) / 100;
      }

      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);  tft.setCursor(186, 0, 2);   // highlight CV
      tft.print(" PS ");

      // Variables
      tft.setTextColor(TFT_GOLD, TFT_BLACK) ;  tft.setCursor(0, 25, 4);
      sprintf(charbuff, "%06.2fVi ", dashboard.Vin); tft.print(charbuff);
      tft.setTextColor(TFT_GREEN, TFT_BLACK) ; tft.setCursor(110, 25, 4);
      sprintf(charbuff, "%06.3fVo ", dashboard.Vout); tft.println(charbuff);
      tft.setTextColor(TFT_VERMILON, TFT_BLACK) ; tft.setCursor(0, 55, 4);
      sprintf(charbuff, "%06.3fA ", dashboard.Iout); tft.println(charbuff);
      tft.setTextColor(TFT_VERMILON, TFT_BLACK) ; tft.setCursor(110, 55, 4);
      sprintf(charbuff, "%06.2fAh ", dashboard.Ahout); tft.println(charbuff);
      tft.setTextColor(TFT_BLUE, TFT_BLACK); tft.setCursor(0, 85, 4);
      sprintf(charbuff, "%06.2fW ", dashboard.Wout); tft.println(charbuff);
      tft.setTextColor(TFT_BLUE, TFT_BLACK); tft.setCursor(110, 85, 4);
      sprintf(charbuff, "%06.1fWh ", dashboard.Whout); tft.println(charbuff);
      break;

    case 6 :     // BAT Display
      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);  tft.setCursor(186, 0, 2);   // highlight CV
      tft.print(" Bat ");

      // Variables
      tft.setTextColor(TFT_GREEN, TFT_BLACK) ;  tft.setCursor(0, 25, 4);
      sprintf(charbuff, "%06.2fVo ", dashboard.Vout); tft.println(charbuff);
      tft.setTextColor(TFT_GREEN, TFT_BLACK) ; tft.setCursor(130, 25, 4);
      sprintf(charbuff, "45%%"); tft.println(charbuff);        // Placeholder for Charge information (Todo)
      tft.setTextColor(TFT_BLACK, TFT_GREEN) ; tft.setCursor(186, 27, 2);
      sprintf(charbuff, "Bulk"); tft.println(charbuff);        // Placeholder for Charge information (Todo)
      tft.setTextColor(TFT_VERMILON, TFT_BLACK) ; tft.setCursor(0, 55, 4);
      sprintf(charbuff, "%06.3fA ", dashboard.Iout); tft.println(charbuff);
      tft.setTextColor(TFT_BROWN, TFT_BLACK) ; tft.setCursor(110, 55, 4);
      sprintf(charbuff, "%06.4fR ", dashboard.load_internal_resistance / 50); tft.println(charbuff);
      tft.setTextColor(TFT_VERMILON, TFT_BLACK); tft.setCursor(0, 85, 4);
      sprintf(charbuff, "%06.2fAh ", dashboard.Ahout); tft.print(charbuff);
      tft.setTextColor(TFT_BLUE, TFT_BLACK); tft.setCursor(110, 85, 4);
      sprintf(charbuff, "%06.1fWh ", dashboard.Whout); tft.println(charbuff);
      break;

    case 7 :     // STAT Display
      // Page name
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);  tft.setCursor(186, 0, 2);   // highlight CV
      tft.print(" Sta ");

      // Variables
      Ah[31] = 1; // to avoid a division / 0
      for  (byte n = 0; n < 24; n++) // Display 24 hourly bargraphs
      {
        if (Ah[n] > 0)
        {
          tft.fillRect(7 * n + 55, 20, 5, 78, TFT_DARKGREEN); //Bargraphs
          tft.fillRect(7 * n + 55, 20, 5, byte(78 - 78 * Ah[n] / Ah[31]) , TFT_BLACK); //Positive Values
        }
        if (Ah[n] < 0)
        {
          tft.fillRect(7 * n + 55, 20, 5, 78, TFT_MAROON); //Bargraphs
          tft.fillRect(7 * n + 55, 20, 5, byte(78 + 78 * Ah[n] / Ah[31]) , TFT_BLACK); //Negative values
        }
        tft.setCursor(0, 20, 2);   tft.setTextColor(TFT_GREY, TFT_BLACK);   // Axis description
        Ah[31] = max(Ah[31], Ah[n] + 1); // max Ah harvested (+1 to determine plot span)
      }
      tft.setCursor(15, 20, 2);
      sprintf(charbuff, "%05.2f", Ah[31]); tft.println(charbuff);   // printing Axis max
      tft.drawFastVLine(53, 20, 79, TFT_GREY);
      tft.drawFastHLine(54, 99, 170, TFT_GREY);
      tft.setCursor(0, 52, 2);    tft.print("Ah(24)");
      tft.setCursor(43, 84, 2);   tft.print("0");
      break;

  }  // switch (displayPage)
#endif //DISPLAY_IS_LCD

#ifdef DISPLAY_IS_OLED
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  switch (displayPage)
  {
    case 0 :
      display.clear();
      break;

    case 1 :     // Set Value Cycle matrix
    case 3 :
    case 5 :
      display.drawString(10, 0,  "| Set");
      display.drawString(50, 0,  "| Value");
      display.drawString(90, 0,  "| Cycle");
      display.drawString(0, 12, "V ");
      sprintf(charbuff, "| %2.2f", dashboard.SetVout); display.drawString(10, 12, charbuff);
      sprintf(charbuff, "| %2.2f", dashboard.Vout); display.drawString(50, 12, charbuff);
      sprintf(charbuff, "| %2.2f", dashboard.Vout - persistence.initial_voltage); display.drawString(90, 12, charbuff);
      display.drawString(0, 24, "A ");
      sprintf(charbuff, "| %1.3f", dashboard.SetIout); display.drawString(10, 24, charbuff);
      sprintf(charbuff, "| %1.3f", dashboard.Iout); display.drawString(50, 24, charbuff);
      sprintf(charbuff, "| %1.3f", dashboard.Ahout / 60); display.drawString(90, 24, charbuff);
      display.drawString(0, 36, "W ");
      sprintf(charbuff, "| %2.3f", dashboard.Wout); display.drawString(50, 36, charbuff);
      sprintf(charbuff, "| %2.3f", dashboard.Whout); display.drawString(90, 36, charbuff);
      break;

    case 2 :     // Panel Battr Cycle matrix
    case 4 :
    case 6 :
      display.drawString(10, 0,  "| Panel");
      display.drawString(50, 0,  "| Battr");
      display.drawString(90, 0,  "| Cycle");
      display.drawString(0, 12, "V ");
      sprintf(charbuff, "| %2.2f", dashboard.Vin); display.drawString(10, 12, charbuff);
      sprintf(charbuff, "| %2.2f", dashboard.Vout); display.drawString(50, 12, charbuff);
      sprintf(charbuff, "| %2.2f", dashboard.Vout - persistence.initial_voltage); display.drawString(90, 12, charbuff);
      display.drawString(0, 24, "A ");
      sprintf(charbuff, "| %1.3f", dashboard.Iin); display.drawString(10, 24, charbuff);
      sprintf(charbuff, "| %1.3f", dashboard.Iout); display.drawString(50, 24, charbuff);
      sprintf(charbuff, "| %1.3f", dashboard.Ahout); display.drawString(90, 24, charbuff);
      display.drawString(0, 36, "W ");
      sprintf(charbuff, "| %2.3f", dashboard.Wout); display.drawString(50, 36, charbuff);
      sprintf(charbuff, "| %2.3f", dashboard.Whout); display.drawString(90, 36, charbuff);
      break;
  }

  buffTimeData();
  display.drawString(0, 50, charbuff);
  display.drawString(60, 50, CtrlMode_description[dashboard.CtrlMode]);  
  display.drawString(95, 50, Runtime);
  display.fillRect(0, 63, Second * 2, 1); //display seconds progress bar
  display.display();

#endif //DISPLAY_IS_OLED

}
