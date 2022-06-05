#ifndef Badge2020_Buzzer_h
#define Badge2020_Buzzer_h

#define BADGE2020_BUZZER 32

// library interface description
class Badge2020_Buzzer {
public:
  Badge2020_Buzzer();
  void setFrequency( int frequency );
  void setVolume( int volume );
};

#endif