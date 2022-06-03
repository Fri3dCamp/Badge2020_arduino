#include <Wire.h>
#include <Badge2020_Accelerometer.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS          5
#define TFT_RST        32
#define TFT_DC         33
#define BACKLIGHT      12

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Badge2020_Accelerometer accelerometer;

void setup(void) {

  // setup screen
  
  tft.init(240, 240);
  tft.setRotation( 2 );

  pinMode( BACKLIGHT, OUTPUT );
  digitalWrite( BACKLIGHT, HIGH );

  tft.fillScreen( 0x2c45 );
  tft.fillCircle( 120, 120, 100, ST77XX_WHITE );


  // setup accelerometer

  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  delay(100);
  
  while(accelerometer.init(LIS2DH12_RANGE_2GA) == -1){  
    //Equipment connection exception or I2C address error
    Serial.println("No I2C devices found");
    delay(1000);
  }
}

double previousunitx, previousunity;

void loop(){
  int16_t x, y, z;
  accelerometer.readXYZ(x, y, z);
  accelerometer.mgScale(x, y, z);

  // make it a unit length vector
  double length = sqrt( x*x + y*y + z*z );
  double unitx = x / length;
  double unity = y / length;
  double unitz = z / length;

  // render the eye
  if( ( previousunitx != unitx ) || ( previousunity != unity ) ) {
    tft.fillCircle( 120 - previousunitx * 80, 120 - previousunity * 80, 20, ST77XX_WHITE );
    tft.fillCircle( 120 - unitx * 80, 120 - unity * 80, 20, ST77XX_BLACK );
    previousunitx = unitx;
    previousunity = unity;
  }

  delay(200);

}