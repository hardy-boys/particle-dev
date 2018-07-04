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
  const int SYMBOL_START_H = 112;
  // Price
  const int PRICE_START_V = 144;
  const int PRICE_START_H = 112;

  //
  // ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
  //

  String symbol = "null";
  String price = "0";

  //
  // ─── FUNCTION DECLARATIONS ──────────────────────────────────────────────────────
  //

  void widget_setup();
  void widget_loop();
  void streamDataHandler(const char *event, const char *data);
  void screenInit();
};

#endif
