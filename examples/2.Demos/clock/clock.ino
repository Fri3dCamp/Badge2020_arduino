#include <Badge2020_TFT.h>
#include <Badge2020_arduino.h>
#include <WiFi.h>
#include <time.h>
#include <sntp.h>

const char* SSID = "your ssid";
const char* PASSWORD = "your password";

const char* ntpServer = "time.nist.gov"; //"pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

Badge2020_TFT tft;

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  //I *think* we no longer need wifi after the NTP callback
  //this callback (and the #include <sntp.h>) should be removed if you want constant wifi connectivity
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  DrawClockFace();
}

struct tm timeinfo;
struct tm last = {};

void setup(void) {

  tft.init(240, 240);
  tft.setRotation(2);
  pinMode(BADGE2020_BACKLIGHT, OUTPUT);
  digitalWrite(BADGE2020_BACKLIGHT, HIGH);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);

  if (!getLocalTime(&timeinfo)) {
    ConnectNTP();    
  }
  else {
    DrawClockFace();
  }
}

void ConnectNTP () {
  // set notification call-back function
  sntp_set_time_sync_notification_cb( timeavailable );

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  tft.print("Connect ");
  tft.print(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }
  tft.println("");
  tft.println("WiFi connected");
  tft.println(WiFi.localIP());


}

//customize the look of the clock face:
const int FACE_RADIUS = 100;
const int HOUR_IND = 20;
const int MIN_IND = 5;
const int FACE_COLOR = ST77XX_WHITE;
const int FACE_BG_COLOR = ST77XX_BLACK;

void DrawClockFace() {  
  tft.fillScreen(FACE_BG_COLOR);

  int mid_x = tft.width() / 2;
  int mid_y = tft.height() / 2;
  
  for (int h = 0; h < 12; h++) {
    float angle = h * 2.0 * PI / 12.0;    
    int begin_x = mid_x + FACE_RADIUS * sin(angle);
    int end_x = mid_x + (FACE_RADIUS + HOUR_IND) * sin(angle);
    int begin_y = mid_y - FACE_RADIUS * cos(angle);
    int end_y = mid_y - (FACE_RADIUS + HOUR_IND) * cos(angle);
    tft.drawLine(begin_x, begin_y, end_x, end_y, FACE_COLOR);
  }    

  for (int m = 0; m < 60; m++) {
    float angle = m * 2.0 * PI / 60.0;    
    int begin_x = mid_x + FACE_RADIUS * sin(angle);
    int end_x = mid_x + (FACE_RADIUS + MIN_IND) * sin(angle);
    int begin_y = mid_y - FACE_RADIUS * cos(angle);
    int end_y = mid_y - (FACE_RADIUS + MIN_IND) * cos(angle);
    tft.drawLine(begin_x, begin_y, end_x, end_y, FACE_COLOR);
  }    

}

const int SECONDS_HAND_LENGTH = 95;
const int SECONDS_HAND_COLOR = ST77XX_RED;
const int MINUTES_HAND_LENGTH = 85;
const int MINUTES_HAND_COLOR = ST77XX_WHITE;
const int HOURS_HAND_LENGTH = 50;
const int HOURS_HAND_COLOR = ST77XX_WHITE;
void loop() {

  if(!getLocalTime(&timeinfo)) {
    tft.println("wait4sync");
    delay(400);
    return;
  }

  if (last.tm_sec != timeinfo.tm_sec) {
    
    ///////// SECONDS
    float angle = last.tm_sec * 2.0 * PI / 60.0;
    DrawHand(angle, SECONDS_HAND_LENGTH, true, FACE_BG_COLOR); //erase previous seconds-hand
    angle = timeinfo.tm_sec * 2.0 * PI / 60.0;
    DrawHand(angle, SECONDS_HAND_LENGTH, true, SECONDS_HAND_COLOR);

    ///////// ERASE MINUTES AND HOURS
    if (last.tm_min != timeinfo.tm_min) {
      angle = last.tm_min * 2.0 * PI / 60.0;
      DrawHand(angle, MINUTES_HAND_LENGTH, false, FACE_BG_COLOR); //erase previous minutes-hand

      //since the hours hand also moves (slightly) as the minutes advance, we need to erase the hours hand as well
      angle = ((float) last.tm_hour + last.tm_min/60.0) * 2.0 * PI / 12.0;
      DrawHand(angle, HOURS_HAND_LENGTH, true, FACE_BG_COLOR); //erase previous hours-hand
    }

    ///////// MINUTES
    angle = timeinfo.tm_min * 2.0 * PI / 60.0;
    DrawHand(angle, MINUTES_HAND_LENGTH, false, MINUTES_HAND_COLOR); //always redraw minutes to make sure it wasn't erased by seconds hand

    ///////// HOURS
    angle = ((float) timeinfo.tm_hour + timeinfo.tm_min/60.0) * 2.0 * PI / 12.0;
    DrawHand(angle, HOURS_HAND_LENGTH, true, HOURS_HAND_COLOR); //always redraw hours to make sure it wasn't erased by seconds hand
  }

  last = timeinfo;
  delay(20);
}

void DrawHand(float angle, int length, bool thic, uint16_t color) {
  int mid_x = tft.width() / 2;
  int mid_y = tft.height() / 2;
 
  int end_x = mid_x + length * sin(angle);
  int end_y = mid_y - length * cos(angle);
  tft.drawLine(mid_x, mid_y, end_x, end_y, color);

  if (thic) {
    if ((angle > (PI / 4.0) && angle < (3.0 * PI / 4.0))
      || (angle > (5.0 * PI / 4.0) && angle < (7.0 * PI / 4.0))) {

        tft.drawLine(mid_x, mid_y+1, end_x, end_y+1, color);
        tft.drawLine(mid_x, mid_y-1, end_x, end_y-1, color);
    }
    else {
      tft.drawLine(mid_x+1, mid_y, end_x+1, end_y, color);    
      tft.drawLine(mid_x-1, mid_y, end_x-1, end_y, color);    
    }
  }
}
