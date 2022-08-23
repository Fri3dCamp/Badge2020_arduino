// Radiospeler voor de Fri3dBadge 2022 met GameOn en aangesloten speaker
// Werkt met
// - ESP32 Core 1.0.6: ESP8266Audio 1.9.5 (compileert niet met ESP8266Audio 1.9.7)
// - ESP32 Core 2.0.4: ESP8266Audio 1.9.7 (compileert niet met ESP8266Audio 1.9.5)
// Audio is onstabiel in ESP32 Core versie 2.0.0-2.0.3

#include <WiFi.h>
#include "driver/i2s.h"

#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

const char* ssid = "your-ssid";
const char* password = "your-password";

const char *URL = "http://icecast.vrtcdn.be/stubru-high.mp3";

/*
  TOP Radio=http://playerservices.streamtheworld.com/api/livestream-redirect/TOP_RADIO.mp3
  TML=http://23603.live.streamtheworld.com/OWR_INTERNATIONAL_SC
  Q music=http://21293.live.streamtheworld.com/QMUSIC.mp3
  Stu Bru=http://icecast.vrtcdn.be/stubru-high.mp3
  Stu Bru UNTZ=http://icecast.vrtcdn.be/stubru_untz-high.mp3
  MNM=http://icecast.vrtcdn.be/mnm-high.mp3
  MNM hits=http://icecast.vrtcdn.be/mnm_hits-high.mp3
  Klara continuo=http://icecast.vrtcdn.be/klaracontinuo-high.mp3
  Klara=http://icecast.vrtcdn.be/klara-high.mp3
  Radio 1=http://icecast.vrtcdn.be/radio1-high.mp3
*/

AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;

// Deze functie wordt opgeroepen wanneer er een metadata event voorkomt (bv. een ID3 tag, een ICY blok, ...
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void) isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
  char s1[32], s2[64];
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1) - 1] = 0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2) - 1] = 0;
  Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);
  Serial.flush();
}

// Deze functie wordt opgeroepen als er een waarschuwing of fout voorkomt (zoals een buffer underflow of decoder die zich verslikt)
void StatusCallback(void *cbData, int code, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1) - 1] = 0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi");

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  // Blijf proberen
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...Connecting to WiFi");
    delay(1000);
  }
  Serial.println("Connected");

  audioLogger = &Serial;

  file = new AudioFileSourceICYStream(URL);
  file->RegisterMetadataCB(MDCallback, (void*)"ICY");
  buff = new AudioFileSourceBuffer(file, 2048);
  buff->RegisterStatusCB(StatusCallback, (void*)"buffer");

  AudioOutputI2S *out = new AudioOutputI2S(0, 1, 32);
  out->SetGain(0.10); // regel het volume
  
  // De library laat niet toe om enkel pin 25 aan te sturen: het geluid wordt op zowel 25 als 26 gestopt, vandaar een poging om het enkel op pin 25 te krijgen
  out->begin();
  i2s_set_dac_mode(I2S_DAC_CHANNEL_RIGHT_EN);

  mp3 = new AudioGeneratorMP3();
  mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
  mp3->begin(buff, out);
}


void loop()
{
  static int lastms = 0;

  if (mp3->isRunning()) {
    if (millis() - lastms > 1000) {
      lastms = millis();
      Serial.printf("Running for %d ms...\n", lastms);
      Serial.flush();
    }
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
    dacWrite(25, 0);
  }
}
