#ifndef TRAFFICWIDGET_H
#define TRAFFICWIDGET_H

#include "../../WidgetLoader.h"

struct TrafficWidget
{

  //
  // ─── CONTENT POSITIONING ────────────────────────────────────────────────────────
  //
  // Symbol
  const int DISTANCE_START_V = 72;
  const int DISTANCE_START_H = 148;
  // Price
  const int TRAFFICTIME_START_V = 72;
  const int TRAFFICTIME_START_H = 72;

  //
  // ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
  //

  String distance = "...";
  String traffic_time = "...";
  String normal_time = "...";

  //
  // ─── FUNCTION DECLARATIONS ──────────────────────────────────────────────────────
  //

  void widget_setup();
  void widget_loop();
  void streamDataHandler(const char *event, const char *data);
  void screenInit();
};

#endif
