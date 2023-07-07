#ifndef Badge2020_Battery_h
#define Badge2020_Battery_h

#include <stdint.h>

class Battery {
    public:

    static uint16_t m_raw_min;
    static uint16_t m_raw_max;

    static void set_raw_min(uint16_t& raw_min);
    
    static void set_raw_max(uint16_t& raw_max);
    
    static uint16_t read_raw();

    static uint8_t raw_to_percent(uint16_t& raw_value);

    static uint8_t read_percent();

    private:
    static const uint8_t BATTERY_PIN = 35;

    static uint16_t _read_raw();
};

#endif