#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS          5
#define TFT_RST        32
#define TFT_DC         33
#define BACKLIGHT      12

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  tft.init(240, 240);
  tft.setRotation( 2 );

  pinMode( BACKLIGHT, OUTPUT );
  digitalWrite( BACKLIGHT, HIGH );

  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(10, 110);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("Hello World!");
}

void loop() {
}
