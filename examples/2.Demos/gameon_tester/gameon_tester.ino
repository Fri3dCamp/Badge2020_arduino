#include <Badge2020_TFT.h>
Badge2020_TFT tft;

#define GAMEON_UP 39
#define GAMEON_DOWN 15
#define GAMEON_LEFT 26
#define GAMEON_RIGHT 00
#define GAMEON_BUTTON 34
#define GAMEON_SELECT 36
#define GAMEON_START 32
#define GAMEON_A 13
#define GAMEON_B 12
#define GAMEON_SHOULDERLEFT 27
#define GAMEON_SHOULDERRIGHT 14

void gameon_select_pinmode_input_pullup()
{
  // initialiseer de accelerometer om GPIO36 (SELECT) high te trekken
  Wire.begin();
  Wire.beginTransmission(0x18);
  Wire.write(0x25);
  Wire.write(0x0A);
  Wire.endTransmission(true);
  
  pinMode(GAMEON_SELECT, INPUT); 
}

void setup(void)
{
  tft.init(240, 240);
  tft.setRotation(2);

  pinMode(BADGE2020_BACKLIGHT, OUTPUT);
  digitalWrite(BADGE2020_BACKLIGHT, HIGH);

  pinMode(GAMEON_UP, INPUT_PULLUP);
  pinMode(GAMEON_DOWN, INPUT_PULLUP);
  pinMode(GAMEON_LEFT, INPUT_PULLUP);
  pinMode(GAMEON_RIGHT, INPUT_PULLUP);
  pinMode(GAMEON_BUTTON, INPUT_PULLUP);
  gameon_select_pinmode_input_pullup();
  pinMode(GAMEON_START, INPUT_PULLUP);
  pinMode(GAMEON_A, INPUT_PULLUP);
  pinMode(GAMEON_B, INPUT_PULLUP);
  pinMode(GAMEON_SHOULDERLEFT, INPUT_PULLUP);
  pinMode(GAMEON_SHOULDERRIGHT, INPUT_PULLUP);

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 110);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
}

void loop()
{
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 10);
  tft.print("Up: ");
  tft.println(digitalRead(GAMEON_UP));
  tft.print("Down: ");
  tft.println(digitalRead(GAMEON_DOWN));
  tft.print("Left: ");
  tft.println(digitalRead(GAMEON_LEFT));
  tft.print("Right: ");
  tft.println(digitalRead(GAMEON_RIGHT));
  tft.print("Button: ");
  tft.println(digitalRead(GAMEON_BUTTON));
  tft.print("Select: ");
  tft.println(digitalRead(GAMEON_SELECT));
  tft.print("Start: ");
  tft.println(digitalRead(GAMEON_START));
  tft.print("A: ");
  tft.println(digitalRead(GAMEON_A));
  tft.print("B: ");
  tft.println(digitalRead(GAMEON_B));
  tft.print("L Shoulder: ");
  tft.println(digitalRead(GAMEON_SHOULDERLEFT));
  tft.print("R Shouder: ");
  tft.println(digitalRead(GAMEON_SHOULDERRIGHT));
  // delay(100);
}
