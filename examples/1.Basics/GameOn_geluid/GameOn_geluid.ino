#include "icq.h"
#include "XT_DAC_Audio.h"

XT_Wav_Class Sound(icq);                                          
XT_DAC_Audio_Class DacAudio(25,0);    

uint32_t DemoCounter=0;               

void setup() {
  Serial.begin(115200);
  DacAudio.DacVolume=5;
}


void loop() {
  
  DacAudio.FillBuffer();                
  if(Sound.Playing==false && DemoCounter < 3){
          DacAudio.Play(&Sound);       
          Serial.println(DemoCounter++);  
          delay(1500);
  }       
}
