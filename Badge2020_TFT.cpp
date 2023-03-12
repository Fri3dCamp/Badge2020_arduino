#include <Badge2020_TFT.h>
#include <Wire.h>

Badge2020_TFT::Badge2020_TFT() : Adafruit_ST7789( BADGE2020_TFT_CS, BADGE2020_TFT_DC, BADGE2020_TFT_RST )
{
  // open Wire connection to talk to accelerometer
  Wire.begin();
}

void Badge2020_TFT::enableBacklight()
{
  Wire.beginTransmission(BADGE2020_ACC_ADDRESS);
  Wire.write(BADGE2020_ACC_CTRL_REG6);
  Wire.write(0x0A);  // enable INT2; pulling IO36 HIGH
  Wire.endTransmission(true);
}

void Badge2020_TFT::disableBacklight()
{
  Wire.beginTransmission(BADGE2020_ACC_ADDRESS);
  Wire.write(BADGE2020_ACC_CTRL_REG6);
  Wire.write(0x00);  // disable INT2; pulling IO36 LOW
  Wire.endTransmission(true);
}
