#ifndef DATETIMEWEATHERWIDGET_H
#define DATETIMEWEATHERWIDGET_H

#include "../../WidgetLoader.h"

struct DateTimeWeatherWidget
{

  //
  // ─── CONTENT POSITIONING ────────────────────────────────────────────────────────
  //
  // Time/Date
  const int TIMEDATE_START_V = 80;
  const int TIMEDATE_START_H = 180;
  // Weather
  const int WEATHER_START_V = 80;
  const int WEATHER_START_H = 36;

  //
  // ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
  //

  // Time/Weather
  String name = "...";
  String temperature = "...";
  String weather_desc = "...";
  String humidity = "...";
  String wind = "...";
  String current_time;
  bool toggle;
  String format_string;
  String weekday;
  String date;

  //
  // ─── FUNCTION DECLARATIONS ──────────────────────────────────────────────────────
  //

  void widget_setup();
  void widget_loop();
  void streamDataHandler(const char *event, const char *data);
  void screenInit();
  void displayWeather();
  String weekdayLookup(int val);
};

#endif
