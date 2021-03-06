// based on https://github.com/DFRobot/DFRobot_LIS2DH12

#ifndef Badge2020_Accelerometer_h
#define Badge2020_Accelerometer_h

#include <Wire.h>

#include <stdlib.h>
#include <stdint.h>

#define LIS2DH12_RANGE_2GA	0x00
#define LIS2DH12_RANGE_4GA	0x10
#define LIS2DH12_RANGE_8GA	0x20
#define LIS2DH12_RANGE_16GA	0x30

class Badge2020_Accelerometer {
public:
	int8_t init(uint8_t range, uint8_t sensorAddress = 0x18); ///< Initialization function
	void readXYZ(int16_t&, int16_t&, int16_t&); ///< read x, y, z data
	void mgScale(int16_t&, int16_t&, int16_t&); ///< transform data to millig
  /*!
   *  Through the I2C to specify register read a single data
   */
	uint8_t readReg(uint8_t);
  /*!
   *  Through the I2C to specify register read more data
   */
	void readReg(uint8_t, uint8_t *, uint8_t, bool autoIncrement = true);
  /*!
   *  Write a single data through the I2C to specify register
   */
	uint8_t writeReg(uint8_t, uint8_t);
  /*!
   *  Through the I2C write multiple data on the specified register
   */
	uint8_t writeReg(uint8_t, uint8_t *, size_t, bool autoIncrement = true);
  
private:  
  /*!
   *  Set measurement range
   */
	void setRange(uint8_t range);
	
	uint8_t mgPerDigit;
	uint8_t mgScaleVel;
	uint8_t sensorAddress; ///< IIC address of the sensor
};
	
#endif
