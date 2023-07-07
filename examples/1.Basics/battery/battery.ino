#include <Badge2020_Battery.h>

uint16_t bat_raw;
uint8_t bat_percent;

void setup() {
  Serial.begin(115200);
  while(!Serial);
    delay(100);
}

void loop() {
  bat_raw = Battery::read_raw();
  Serial.print("Battery raw value: ");
  Serial.println(bat_raw);

  bat_percent = Battery::raw_to_percent(bat_raw);
  Serial.print("Battery raw value converted to percent: ");
  Serial.print(bat_percent);
  Serial.println("%");

  Serial.printf("Battery directly reading percent: %3d%%\n", Battery::read_percent());

  Serial.println("");
  delay(1000);
}