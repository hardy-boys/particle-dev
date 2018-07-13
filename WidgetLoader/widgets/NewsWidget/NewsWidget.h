#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H

#include "../../WidgetLoader.h"

struct NewsWidget
{

  //
  // ─── CONTENT POSITIONING ────────────────────────────────────────────────────────
  //

  const int HEADLINE_START_V = 60;
  const int HEADLINE_START_H = 12;

  //
  // ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
  //

  String headline_1 = "...";
  String headline_2 = "...";
  String headline_3 = "...";
  String headline_4 = "...";
  String headline_5 = "...";
  String headline_6 = "...";
  String headline_7 = "...";
  String headline_8 = "...";


  //
  // ─── FUNCTION DECLARATIONS ──────────────────────────────────────────────────────
  //

  void widget_setup();
  void widget_loop();
  void streamDataHandler(const char *event, const char *data);
  void screenInit();
};

#endif
