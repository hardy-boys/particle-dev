#include "./WidgetLoader.h"
#include "./widgets/DateTimeWeatherWidget/DateTimeWeatherWidget.h"
#include "./widgets/StocksWidget/StocksWidget.h"
#include "./widgets/TrafficWidget/TrafficWidget.h"
#include "./widgets/NewsWidget/NewsWidget.h"

//
// ─── WIDGET SETUP ───────────────────────────────────────────────────────────────
//

// Widget enums
#define DATETIMEWEATHERWIDGET 1
#define STOCKSWIDGET 2
#define TRAFFICWIDGET 3
#define NEWSWIDGET 4

// Switch modes
#define MANUAL 1
#define SLIDESHOW 2
#define MOTIONSENSOR 3

// Widget objects
DateTimeWeatherWidget weather_widget;
StocksWidget stocks_widget;
TrafficWidget traffic_widget;
NewsWidget news_widget;

// Active widgets for slideshow loop
int active_widgets[4] = {0, 0, 0, 0};
int loop_position = 1;

// Widget setup selector
void widgetSetup(int widgetEnum) {
  switch (widgetEnum)
  {
  case DATETIMEWEATHERWIDGET:
    weather_widget.widget_setup();
    break;
  case STOCKSWIDGET:
    stocks_widget.widget_setup();
    break;
  case TRAFFICWIDGET:
    traffic_widget.widget_setup();
    break;
  case NEWSWIDGET:
    news_widget.widget_setup();
    break;
  default:
    Serial.println("Invalid widget enum used for setup");
    break;
  }
}

// enum converter for data from client
int widgetNameToEnum(String widgetName) {
  if (widgetName == "DateTimeWeatherWidget")
  {
    return DATETIMEWEATHERWIDGET;
  }
  else if (widgetName == "StocksWidget")
  {
    return STOCKSWIDGET;
  }
  else if (widgetName == "TrafficWidget")
  {
    return TRAFFICWIDGET;
  }
  else if (widgetName == "NewsWidget")
  {
    return NEWSWIDGET;
  }
  else
  {
    // nothing matched, return empty widget enum
    return -1;
  }
}

//
// ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
//

// Currently shown widget
int widgetView;
bool screen_updating = false;

// Function declarations
int setProfile(String widgets);
int changeView(String viewID);  // allow for manual view changes

// Timers
Timer reset_timer(3000, reset_device, true);
bool device_reset = false;
Timer slideshow_timer(5000, slideshow_loop);

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
  Serial.printlnf(
    "Loaded from EEPROM: addr=%d, widget_1=%d widget_2=%d widget_3=%d, widget_4=%d, switchMode=%d, sizeof(data)=%d",
                  addr, data.widget_1, data.widget_2, data.widget_3, data.widget_4, data.switchMode, sizeof(data));
  // If the EEPROM profiles appear uninitialized, flash default profile:
  if (data.widget_1 == -1 && data.widget_2 == -1 && data.widget_3 == -1 && data.widget_4 == -1) {
    data.widget_1 = DATETIMEWEATHERWIDGET;
    data.switchMode = MANUAL;
    EEPROM.put(addr, data);
    Serial.println("Saved default profile to EEPROM");
    widgetView = DATETIMEWEATHERWIDGET;
  } else {
    widgetView = data.widget_1;
  }

  // Go through each profile and initialize if defined
  if (data.widget_1 != -1)
  {
    widgetSetup(data.widget_1);
    active_widgets[0] = data.widget_1;
  }
  if (data.widget_2 != -1)
  {
    widgetSetup(data.widget_2);
    active_widgets[1] = data.widget_2;
  }
  if (data.widget_3 != -1)
  {
    widgetSetup(data.widget_3);
    active_widgets[2] = data.widget_3;
  }
  if (data.widget_4 != -1)
  {
    widgetSetup(data.widget_4);
    active_widgets[3] = data.widget_4;
  }

  // Start slideshow timer
  slideshow_timer.start();

  // // Special one-time screen setup calls
  // tft.begin();
  // tft.setRotation(1);
  // Call widget specific screen setup
  screenInit();
}

//
// ─── MAIN LOOP ──────────────────────────────────────────────────────────────────
//

void loop()
{
  if(!screen_updating){
    switch (widgetView)
    {
    case DATETIMEWEATHERWIDGET:
      weather_widget.widget_loop();
      break;
    case STOCKSWIDGET:
      stocks_widget.widget_loop();
      break;
    case TRAFFICWIDGET:
      traffic_widget.widget_loop();
      break;
    case NEWSWIDGET:
      news_widget.widget_loop();
      break;
    default:
      // unrecognized widget ID
      Serial.println("Invalid widget enum used for loop");
      tft.setTextSize(1);
      tft.setFont(CALIBRI_24);
      tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
      tft.setCursor(112, 72);
      tft.println("Err Unknown");
      break;
    }

    // Do resets in the loop to avoid faults
    if (device_reset) {
      System.reset();
    }
  }

  // loop interval
  delay(500);
}

//
// ─── UTIL FUNCTIONS ─────────────────────────────────────────────────────────────
//

void screenInit()
{
  switch (widgetView)
  {
  case DATETIMEWEATHERWIDGET:
    weather_widget.screenInit();
    break;
  case STOCKSWIDGET:
    stocks_widget.screenInit();
    break;
  case TRAFFICWIDGET:
    traffic_widget.screenInit();
    break;
  case NEWSWIDGET:
    news_widget.screenInit();
    break;
  default:
    break;
  }
}

int setProfile(String profileData)
{
  StaticJsonBuffer<1024> jsonBuffer;

  int length = profileData.length() + 1;
  char dataCopy[length];
  profileData.toCharArray(dataCopy, length);

  Serial.print("setProfile called: ");
  Serial.println(dataCopy);

  int addr = 0;
  ProfileStruct data;

  JsonObject &root = jsonBuffer.parseObject(dataCopy);
  if (!root.success())
  {
    Particle.publish("parseObject() failed");
    Serial.println("parseObject() failed");
    return -1;
  }
  JsonArray &profile = root["profile"];
  String widgetName_1 = profile[0].asString(); // "widget_1"
  String widgetName_2 = profile[1].asString(); // "widget_2"
  String widgetName_3 = profile[2].asString(); // "widget_3"
  String widgetName_4 = profile[3].asString(); // "widget_4"
  String switchMode = root["switchMode"].asString(); // true

  Serial.println(widgetName_1);

  data.widget_1 = widgetNameToEnum(widgetName_1);
  data.widget_2 = widgetNameToEnum(widgetName_2);
  data.widget_3 = widgetNameToEnum(widgetName_3);
  data.widget_4 = widgetNameToEnum(widgetName_4);

  // convert switchMode string from client to enum
  if(switchMode == "Manual") {
    data.switchMode = MANUAL;
  } else if(switchMode == "Slideshow") {
    data.switchMode = SLIDESHOW;
  } else if (switchMode == "MotionSensor") {
    data.switchMode = MOTIONSENSOR;
  } else {
    data.switchMode = MANUAL;
  }

  EEPROM.put(addr, data);
  Serial.printlnf(
      "Saved new profile to EEPROM: addr=%d, widget_1=%d widget_2=%d widget_3=%d, widget_4=%d, switchMode=%d, sizeof(data)=%d",
      addr, data.widget_1, data.widget_2, data.widget_3, data.widget_4, data.switchMode, sizeof(data));

  // restart the device to set up the new profile
  reset_timer.start();
  Serial.println("System will restart in 3 seconds with new profile...");

  return 1;
}

void reset_device() {
  // callback function to be used with timer
  Serial.println("Restarting...");
  device_reset = true;
}

void slideshow_loop(){
  // loop back to beginning
  if (loop_position > 3) {
    loop_position = 0;
  }
  int widget_no = loop_position + 1;
    switch (widget_no)
    {
    case DATETIMEWEATHERWIDGET:
      localChangeView(DATETIMEWEATHERWIDGET);
      break;
    case STOCKSWIDGET:
      localChangeView(STOCKSWIDGET);
      break;
    case TRAFFICWIDGET:
      localChangeView(TRAFFICWIDGET);
      break;
    case NEWSWIDGET:
      localChangeView(NEWSWIDGET);
      break;
    default:
      Serial.println("Invalid widget enum used for loop");
      break;
    }

    loop_position++;
}

void localChangeView(int widgetEnum){
  // don't try to draw yet!  might corrupt the display while redrawing
  screen_updating = true;
  widgetView = widgetEnum;
  screenInit();
  screen_updating = false;
}

int changeView(String widgetName)
{
  int widgetEnum = widgetNameToEnum(widgetName);
  widgetView = widgetEnum;
  screenInit();

  if(widgetEnum > 0){
    return widgetEnum;
  } else {
    return -1;
  }
}
