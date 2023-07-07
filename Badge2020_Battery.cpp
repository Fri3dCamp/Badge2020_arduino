#include "Badge2020_Battery.h"
#include "Arduino.h"

uint16_t Battery::m_raw_min = 1400; //1375 measured min
uint16_t Battery::m_raw_max = 2330; //2364 measured max while charging, 2342 max after charging

void Battery::set_raw_min(uint16_t& raw_min) {
    m_raw_min = raw_min;
}

void Battery::set_raw_max(uint16_t& raw_max) {
    m_raw_max = raw_max;
}

uint16_t Battery::read_raw() {
    uint16_t raw_value = _read_raw();
    log_d("Battery raw_value: %d", raw_value);
    return raw_value;
}

uint8_t Battery::raw_to_percent(uint16_t& raw_value) {
    uint16_t bound_value = max(min(raw_value, m_raw_max), m_raw_min);
    uint8_t percent_value = map(bound_value, m_raw_min, m_raw_max, 0, 100);
    return percent_value;
}

uint8_t Battery::read_percent() {
    uint16_t raw_value = _read_raw();
    uint8_t percent_value = raw_to_percent(raw_value);
    log_d("Battery raw_value: %d -> %3d%%", raw_value, percent_value);
    return percent_value;
}

uint16_t Battery::_read_raw(){
    return analogRead(BATTERY_PIN);        
}

