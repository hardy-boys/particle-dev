#ifndef STOCKSWIDGET_H
#define STOCKSWIDGET_H

#include "../../WidgetLoader.h"

struct StocksWidget
{

  //
  // ─── CONTENT POSITIONING ────────────────────────────────────────────────────────
  //
  // Symbol
  const int SYMBOL_START_V = 72;
  const int SYMBOL_START_H = 96;
  // Price
  const int PRICE_START_V = 72;
  const int PRICE_START_H = 192;

  //
  // ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
  //

  String symbol_1 = "null";
  String price_1 = "0";
  String symbol_2 = "null";
  String price_2 = "0";
  String symbol_3 = "null";
  String price_3 = "0";
  String symbol_4 = "null";
  String price_4 = "0";

  //
  // ─── FUNCTION DECLARATIONS ──────────────────────────────────────────────────────
  //

  void widget_setup();
  void widget_loop();
  void streamDataHandler(const char *event, const char *data);
  void screenInit();
};

#endif
