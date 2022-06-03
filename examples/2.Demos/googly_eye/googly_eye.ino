#include <Badge2020_Accelerometer.h>
#include <Badge2020_TFT.h>

Badge2020_Accelerometer accelerometer;
Badge2020_TFT tft;

void setup(void) {

  // setup screen
  
  tft.init(240, 240);
  tft.setRotation( 2 );

  pinMode( BADGE2020_BACKLIGHT, OUTPUT );
  digitalWrite( BADGE2020_BACKLIGHT, HIGH );

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