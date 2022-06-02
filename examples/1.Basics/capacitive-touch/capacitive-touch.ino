void setup() {
  Serial.begin(115200);
}

void loop() {
  if(touchRead(27)<40){
    Serial.println("TOUCH 0 activated");
  }
  if(touchRead(14)<40){
    Serial.println("TOUCH 1 activated");
  }
  if(touchRead(13)<40){
    Serial.println("TOUCH 2 activated");
  }
}