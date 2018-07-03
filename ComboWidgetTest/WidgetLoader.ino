#include "./WidgetLoader.h"
#include "./DateTimeWeatherWidget.h"

//
// ─── WIDGET INCLUDES ───────────────────────────────────────────────────────────────────
//


// Widget enums
#define WIDGET1 1
#define WIDGET2 2
#define WIDGET3 3
#define WIDGET4 4

DateTimeWeatherWidget weather_widget;

//
// ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
//

// Set starting widget
int widgetView = WIDGET1;

// Function declarations
int changeView(String viewID);

//
// ─── DEVICE SETUP ──────────────────────────────────────────────────────────────────────
//

void setup()
{
  /***** Device Setup *****/
  Serial.begin(9600);
  while (!Serial)
  {
    // wait serial port initialization
  }
  Serial.println("Hello World!");

  // Cloud functions
  Particle.function("changeView", changeView);

  // Hardware setup
  pinMode(blinkLed, OUTPUT);

  /***** Widget Setup *****/
  if (widgetView == WIDGET1)
  {
    weather_widget.widget_setup();
  }

  else if (widgetView == WIDGET2)
  {
    // other namespace
  }

  // Call initial screen setup
  screenInit();
}

//
// ─── MAIN LOOP ──────────────────────────────────────────────────────────────────
//

void loop(void)
{

  if (widgetView == WIDGET1)
  {
    weather_widget.widget_loop();
  }

  else if (widgetView == WIDGET2)
  {
    // other namespace
  }

  else
  {
    // unrecognized widget ID
    tft.setTextSize(1);
    tft.setFont(CALIBRI_24);
    tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
    tft.setCursor(112, 72);
    tft.println(" Unknown: " + widgetView);
  }

  delay(500);
}

//
// ─── UTIL FUNCTIONS ─────────────────────────────────────────────────────────────
//

int changeView(String viewID)
{
  if (viewID == "WIDGET1")
  {
    widgetView = WIDGET1;
    screenInit();
    return 0;
  }
  else if (viewID == "WIDGET2")
  {
    widgetView = WIDGET2;
    screenInit();
    return 1;
  }
  else
  {
    // nothing matched, return error code
    return -1;
  }
}

void screenInit()
{
  // Sync time with particle cloud
  Particle.syncTime();
  waitUntil(Particle.syncTimeDone);

  /***** Initial screen setup *****/
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_WHITE);
  tft.drawFastHLine(0, 50, 320, ILI9341_BLACK);
  tft.drawFastVLine(60, 0, 50, ILI9341_BLACK);

  // Switch header info based on widget
  if (widgetView == WIDGET1)
  {
    weather_widget.screenInit();
  }
  else if (widgetView == WIDGET2)
  {
    // etc
  }
}

