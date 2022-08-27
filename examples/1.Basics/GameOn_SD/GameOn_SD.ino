// Test programma voor SD-kaartlezer op GameOn addon van Fri3d Badge 2022
// Compileren voor ESP32 Wrover Dev Module

#include <SPI.h>
#include <SD.h>

// change this to match your SD shield or module;
const int TFCARD_CS_PIN = 4;

void setup()
{
  File sdfile;

  Serial.begin(115200);
  Serial.println("SD kaart initialiseren");

  if (!SD.begin(TFCARD_CS_PIN, SPI, 40000000)) {
    Serial.println("Initialisatie van SD-kaart mislukt!");
    return;
  }
  Serial.println("Initialisatie SD-kaart klaar.");

  // Schrijf het bestand test.txt op de SD-kaart
  sdfile = SD.open("/test.txt", FILE_WRITE);

  // Als het openen gelukt is
  if (sdfile) {
    Serial.print("Schrijf test.txt...");
    sdfile.println("Jawel, de GameOn SD-kaart lezer");
    sdfile.println("van de Fri3d badge werkt!");
    // sluit het bestand
    sdfile.close();
    Serial.println("klaar.");
  } else {
    Serial.println("Fout bij het schrijven van test.txt");
  }

  // Open het bestand om het te lezen
  sdfile = SD.open("/test.txt", FILE_READ);
  if (!sdfile)
  {
    Serial.println("Het openen van het bestand is mislukt");
    return;
  }

  char buffer[255];
  while (sdfile.available()) {
    int l = sdfile.readBytesUntil('\n', buffer, sizeof(buffer));
    buffer[l] = 0;
    Serial.println(buffer);
  }
  sdfile.close();
}

void loop()
{
  // niks hier
}
