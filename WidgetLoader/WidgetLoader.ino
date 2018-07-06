#include "./WidgetLoader.h"
#include "./widgets/DateTimeWeatherWidget/DateTimeWeatherWidget.h"
#include "./widgets/StocksWidget/StocksWidget.h"

//
// ─── WIDGET SETUP ───────────────────────────────────────────────────────────────
//

// Widget enums
#define TIMEWEATHERWIDGET 1
#define STOCKSWIDGET 2

// Widget objects
DateTimeWeatherWidget weather_widget;
StocksWidget stocks_widget;

// Widget setup selector
void widgetSetup(int widgetEnum) {
  switch (widgetEnum)
  {
  case TIMEWEATHERWIDGET:
    weather_widget.widget_setup();
    break;
  case STOCKSWIDGET:
    stocks_widget.widget_setup();
    break;
  default:
    Serial.println("Invalid widget enum used for setup");
    break;
  }
}

//
// ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
//

// Set starting widget
int widgetView = STOCKSWIDGET;

// Function declarations
int setProfile(String widgets);
int changeView(String viewID);  // allow for manual view changes

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
  Particle.function("setProfile", setProfile);
  Particle.function("changeView", changeView);

  // Hardware setup
  pinMode(blinkLed, OUTPUT);

  /***** Widget Setup *****/

  // Load default active profile
  ProfileStruct data;
  int addr = 0;
  EEPROM.get(addr, data);
  Serial.printlnf("Loaded from EEPROM: addr=%d, profile_1=%d profile_2=%d profile_3=%d, profile_4=%d, sizeof(data)=%d",
                  addr, data.profile_1, data.profile_2, data.profile_3, data.profile_4, sizeof(data));
  // If the EEPROM profiles appear uninitialized, flash default profile:
  if (data.profile_1 == -1 && data.profile_2 == -1 && data.profile_3 == -1 && data.profile_4 == -1) {
    data.profile_1 = TIMEWEATHERWIDGET;
    EEPROM.put(addr, data);
    Serial.println("Saved default profile to EEPROM");
  }

  // Go through each profile and initialize if defined
  if (data.profile_1 != -1)
  {
    widgetSetup(data.profile_1);
  }
  if (data.profile_2 != -1)
  {
    widgetSetup(data.profile_2);
  }
  if (data.profile_3 != -1)
  {
    widgetSetup(data.profile_3);
  }
  if (data.profile_4 != -1)
  {
    widgetSetup(data.profile_4);
  }

  // Call initial screen setup
  screenInit();
}

//
// ─── MAIN LOOP ──────────────────────────────────────────────────────────────────
//

void loop(void)
{

  if (widgetView == TIMEWEATHERWIDGET)
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

int setProfile(String widgets)
{
  static StaticJsonBuffer<1024> jsonBuffer;
  ProfileStruct data;
  

  return 1;
}

int changeView(String viewID)
{
  if (viewID == "TIMEWEATHERWIDGET")
  {
    widgetView = TIMEWEATHERWIDGET;
    screenInit();
    return 0;
  }
  else if (viewID == "STOCKSWIDGET")
  {
    widgetView = STOCKSWIDGET;
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
  if (widgetView == TIMEWEATHERWIDGET)
  {
    weather_widget.screenInit();
  }
  else if (widgetView == STOCKSWIDGET)
  {
    stocks_widget.screenInit();
  }
}

