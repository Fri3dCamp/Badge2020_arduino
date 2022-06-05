#include "Badge2020_Buzzer.h"
#include "Arduino.h"

Badge2020_Buzzer::Badge2020_Buzzer() {
  ledcSetup( 5, 3000, 8 );
  setVolume( 0 );
  ledcAttachPin(BADGE2020_BUZZER, 0);
}

void 
Badge2020_Buzzer::setFrequency( int frequency ) {
  ledcWriteTone( 0, frequency );
}

void 
Badge2020_Buzzer::setVolume( int volume ) {
  ledcWrite( 0, volume );
}
