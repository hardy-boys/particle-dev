#include "./WidgetLoader.h"
#include "./widgets/DateTimeWeatherWidget/DateTimeWeatherWidget.h"
#include "./widgets/StocksWidget/StocksWidget.h"


// Widget enums
#define WEATHERWIDGET 1
#define STOCKSWIDGET 2

DateTimeWeatherWidget weather_widget;
StocksWidget stocks_widget;

//
// ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
//

// Set starting widget
int widgetView = STOCKSWIDGET;

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
  if (widgetView == WEATHERWIDGET)
  {
    weather_widget.widget_setup();
  }

  else if (widgetView == STOCKSWIDGET)
  {
    stocks_widget.widget_setup();
  }

  // Call initial screen setup
  screenInit();
}

//
// ─── MAIN LOOP ──────────────────────────────────────────────────────────────────
//

void loop(void)
{

  if (widgetView == WEATHERWIDGET)
  {
    weather_widget.widget_loop();
  }

  else if (widgetView == STOCKSWIDGET)
  {
    stocks_widget.widget_loop();
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
  if (viewID == "WEATHERWIDGET")
  {
    widgetView = WEATHERWIDGET;
    weather_widget.widget_setup();
    screenInit();
    return 0;
  }
  else if (viewID == "STOCKSWIDGET")
  {
    widgetView = STOCKSWIDGET;
    stocks_widget.widget_setup();
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
  
  // Switch header info based on widget
  if (widgetView == WEATHERWIDGET)
  {
    weather_widget.screenInit();
  }
  else if (widgetView == STOCKSWIDGET)
  {
    stocks_widget.screenInit();
  }
}

