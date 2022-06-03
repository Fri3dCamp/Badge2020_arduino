#include <Badge2020_TFT.h>

Badge2020_TFT tft;

void setup(void) {
  tft.init(240, 240);
  tft.setRotation( 2 );

  pinMode( BADGE2020_BACKLIGHT, OUTPUT );
  digitalWrite( BADGE2020_BACKLIGHT, HIGH );

  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(10, 110);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("Hello World!");
}

void loop() {
}