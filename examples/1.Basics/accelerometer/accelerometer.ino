// based on https://github.com/DFRobot/DFRobot_LIS2DH12

#include <Badge2020_Accelerometer.h>

Badge2020_Accelerometer accelerometer;

void setup(){
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

void loop(){
  int16_t x, y, z;
  delay(100);
  accelerometer.readXYZ(x, y, z);
  accelerometer.mgScale(x, y, z);
  Serial.print("Acceleration x: "); //print acceleration
  Serial.print(x);
  Serial.print(" mg \ty: ");
  Serial.print(y);
  Serial.print(" mg \tz: ");
  Serial.print(z);
  Serial.println(" mg");
}