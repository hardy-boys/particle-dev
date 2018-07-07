#ifndef WIDGETLOADER_H
#define WIDGETLOADER_H

#include "./ArduinoJson-v5.13.2.h"
#include "./Adafruit_ILI9341/Adafruit_ILI9341.h"

//
// ─── PROJECT GLOBALS ───────────────────────────────────────────────────────────
//

// Screen object
static Adafruit_ILI9341 tft = Adafruit_ILI9341(A2, A1, A0);


// Profile object with defaults.  We limit to four active profiles
// due to device limitations (max 4 event listeners)
typedef struct
{
  int widget_1;
  int widget_2;
  int widget_3;
  int widget_4;
  int switchMode;
} ProfileStruct;

// Hardware specific
static int blinkLed = D7;

#endif