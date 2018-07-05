#ifndef WIDGETLOADER_H
#define WIDGETLOADER_H

#include "./ArduinoJson-v5.13.2.h"
#include "./Adafruit_ILI9341/Adafruit_ILI9341.h"

//
// ─── PROJECT GLOBALS ───────────────────────────────────────────────────────────
//

// Screen object
static Adafruit_ILI9341 tft = Adafruit_ILI9341(A2, A1, A0);

// Memory pool for JSON object tree.
static StaticJsonBuffer<1024> jsonBuffer;

// Hardware specific
static int blinkLed = D7;

#endif