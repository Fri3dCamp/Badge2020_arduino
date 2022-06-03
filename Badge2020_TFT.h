#ifndef Badge2020_TFT_h
#define Badge2020_TFT_h

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define BADGE2020_TFT_CS          5
#define BADGE2020_TFT_RST        32
#define BADGE2020_TFT_DC         33
#define BADGE2020_BACKLIGHT      12

class Badge2020_TFT : public Adafruit_ST7789 {
public:
	Badge2020_TFT() : Adafruit_ST7789( BADGE2020_TFT_CS, BADGE2020_TFT_DC, BADGE2020_TFT_RST ) {}
private:  

};
	
#endif
