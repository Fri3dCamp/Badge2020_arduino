#ifndef Badge2020_TFT_h
#define Badge2020_TFT_h

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define BADGE2020_TFT_CS          5
#define BADGE2020_TFT_RST        -1
#define BADGE2020_TFT_DC         33

#define BADGE2020_ACC_ADDRESS    0x18
#define BADGE2020_ACC_CTRL_REG6  0x25

class Badge2020_TFT : public Adafruit_ST7789 {
public:
	Badge2020_TFT();

	// NOTE: these methods only work if the backlight switch is set to AUTO
	void enableBacklight();
	void disableBacklight();  // NOTE: this will also disable the select button of the game-on
private:

};
	
#endif
