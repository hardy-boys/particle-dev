// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

// use hardware SPI
#define OLED_DC D3
#define OLED_CS D4
#define OLED_RESET D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

String current_time;
bool toggle;
String format_string;
unsigned long uptime;
unsigned long ms = 1000;

void setup()
{
  // start the data retrieval timer
  //   timer.start();

  // fun startup sound
  for(int i = 30; i < 60; i++) {
    tone(D0, (i*100), 10);
    delay(10);
  }

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);

  // Request time synchronization from the Particle Device Cloud
  Particle.syncTime();

  // Wait until Photon receives time from Particle Device Cloud (or connection to Particle Device Cloud is lost)
  waitUntil(Particle.syncTimeDone);

  // init blink toggle
  toggle = false;
}

void loop()
{
  toggle = !toggle;
  if (toggle)
  {
    format_string = "%I:%M %p";
  }
  else
  {
    format_string = "%I %M %p";
  }

  Time.zone(-5);
  if (Time.isDST())
  {
    Time.beginDST();
  }
  else
  {
    Time.endDST();
  }
  current_time = Time.format(Time.now(), format_string);
  uptime = millis() / ms;

  // display stuff
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, World!");
  display.println("");
  display.println("Clock Time: " + current_time);
  display.println("");
  display.println("Uptime: " + String(uptime) + "s");
  display.println("");
  display.println("       :D");

  display.display();

  delay(500);
}