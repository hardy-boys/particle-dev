#include "./StocksWidget.h"

// Icons
const unsigned char stocks_icon[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0xe0, 0x00, 0x00, 0x00,
		0x3f, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0xe0, 0x00,
		0x00, 0x00, 0x0f, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xf8,
		0xe0, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xf8, 0xe0, 0x00, 0x10, 0x01,
		0xff, 0x38, 0xe0, 0x00, 0x38, 0x03, 0xfe, 0x18, 0xe0, 0x00, 0x7c, 0x07, 0xfc, 0x00, 0xe0, 0x00,
		0xfe, 0x0f, 0xf8, 0x00, 0xe0, 0x01, 0xff, 0x1f, 0xf0, 0x00, 0xe0, 0x03, 0xff, 0xbf, 0xe0, 0x00,
		0xe0, 0x07, 0xff, 0xff, 0xc0, 0x00, 0xe0, 0x0f, 0xff, 0xff, 0x80, 0x00, 0xe0, 0x1f, 0xff, 0xff,
		0x00, 0x00, 0xe0, 0x3f, 0xef, 0xfe, 0x00, 0x00, 0xe0, 0x7f, 0xc7, 0xfc, 0x00, 0x00, 0xe0, 0xff,
		0x83, 0xf8, 0x00, 0x00, 0xe1, 0xff, 0x01, 0xf0, 0x00, 0x00, 0xe3, 0xfe, 0x00, 0xe0, 0x00, 0x00,
		0xe3, 0xfc, 0x00, 0x40, 0x00, 0x00, 0xe1, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x00, 0x00,
		0x00, 0x00, 0xe0, 0x60, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//
// ───  SETUP AND LOOP ─────────────────────────────────────────────────────────────
//

void StocksWidget::widget_setup()
{
	Serial.println("Stocks widget loaded");

	// Event listeners
	Particle.subscribe("stocks", [this](const char *a, const char *b) { streamDataHandler(a, b); });
}

void StocksWidget::widget_loop()
{
	tft.setTextSize(1);
	tft.setFont(CALIBRI_18);
	tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);

	// Stock symbols & prices
	tft.setCursor(SYMBOL_START_H, SYMBOL_START_V);
	tft.println(symbol_1);
	tft.setCursor(PRICE_START_H, PRICE_START_V);
	tft.println(price_1);
	tft.setCursor(SYMBOL_START_H, SYMBOL_START_V + 24 * 1);
	tft.println(symbol_2);
	tft.setCursor(PRICE_START_H, PRICE_START_V + 24 * 1);
	tft.println(price_2);
	tft.setCursor(SYMBOL_START_H, SYMBOL_START_V + 24 * 2);
	tft.println(symbol_3);
	tft.setCursor(PRICE_START_H, PRICE_START_V + 24 * 2);
	tft.println(price_3);
	tft.setCursor(SYMBOL_START_H, SYMBOL_START_V + 24 * 3);
	tft.println(symbol_4);
	tft.setCursor(PRICE_START_H, PRICE_START_V + 24 * 3);
	tft.println(price_4);

}

//
// ─── UTIL FUNCTIONS ─────────────────────────────────────────────────────────────
//

void StocksWidget::streamDataHandler(const char *event, const char *data)
{
	// Allocate buffer for handling JSON, automatically destoyed after this handler finishes
	StaticJsonBuffer<512> jsonBuffer;

	Serial.print("Recieved event: ");
	Serial.println(event);
	if (data)
	{
		int length = strlen(data) + 1;
		char dataCopy[length];
		strcpy(dataCopy, data);
		Serial.print("Recieved data: ");
		Serial.println(dataCopy);
		JsonArray &root = jsonBuffer.parseArray(dataCopy);
		if (!root.success())
		{
			Particle.publish("parseArray() failed");
			Serial.println("parseArray() failed");
			return;
		}

		// Update JSON data into our display variables
		symbol_1 = root[0]["Symbol"].asString();
		price_1 = root[0]["Price"].asString();
		symbol_2 = root[1]["Symbol"].asString();
		price_2 = root[1]["Price"].asString();
		symbol_3 = root[2]["Symbol"].asString();
		price_3 = root[2]["Price"].asString();
		symbol_4 = root[3]["Symbol"].asString();
		price_4 = root[3]["Price"].asString();

		Serial.println("Prices updated");
	}
	else
	{
		Serial.println("NULL");
	}
	digitalWrite(blinkLed, HIGH);
	delay(500);
	digitalWrite(blinkLed, LOW);
}

void StocksWidget::screenInit()
{
	Serial.println("Rendering StocksWidget");

	// Sync time with particle cloud
	Particle.syncTime();
	waitUntil(Particle.syncTimeDone);

	/***** Initial screen setup *****/
	tft.begin();
	tft.setRotation(1);
	tft.fillScreen(ILI9341_WHITE);
	tft.drawFastHLine(0, 50, 320, ILI9341_BLACK);
	tft.drawFastVLine(60, 0, 50, ILI9341_BLACK);

	tft.setCursor(96, 12);
	tft.setTextColor(ILI9341_BLACK);
	tft.setTextWrap(false);
	tft.setTextSize(1);
	tft.setFont(CALIBRI_24);

	tft.println("   Stock    Updates");
	tft.drawBitmap(6, 0, stocks_icon, 48, 48, ILI9341_GREEN);
}