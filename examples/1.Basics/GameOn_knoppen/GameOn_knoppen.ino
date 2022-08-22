// DEMO het gebruik van een GameOn knoppen
//=========================================
// Het resultaat van je drukknop events kan je zien door het serial output scherm te activeren.
// (ga naar Tools > Serial monitor of gebruik de sneltoets ctrl + Shift + M)
// Rechts onderaan selecteer je 9600 baud (indien dit anders zou staan)

//IO Pinconfiguratie
const byte btnBoot = 0;
const byte btnA = 13;
const byte btnB = 12;
const byte btnStart = 32;
const byte btnSelect = 36;
const byte btnBovenRechts = 14;
const byte btnBovenLinks = 27;
const byte joyBoven = 39;
const byte joyBeneden = 15;
const byte joyLinks = 26;
const byte joyRechts = 00;
const byte joyCenter = 34;

byte butLst;

enum { None, SingleClick, DoubleClick };
enum {A, B, Start, Select, Omhoog, Omlaag, Links, Rechts, Center, BovenLinks, BovenRechts}

// ----------------------------------------------------------------------------------------
int chkButton (void)
{
    const  unsigned long ButTimeout  = 250;
    static unsigned long msecLst;
           unsigned long msec = millis();

    if (msecLst && (msec - msecLst) > ButTimeout)  {
        msecLst = 0;
        return SingleClick;
    }

    byte but = digitalRead (btnA);
    if (butLst != but)  {
        butLst = but;
        delay (10);           // **** debounce

        if (LOW == but)  {   // press
            if (msecLst)  { // 2nd press
                msecLst = 0;
                return DoubleClick;
            }
            else
                msecLst = 0 == msec ? 1 : msec;
        }
    }

    return None;
}

// -----------------------------------------------------------------------------
void loop ()
{
    switch (chkButton ())  {
    case SingleClick:
        Serial.println ("eenmalige klik gebeurtenis"); //single click event
        break;

    case DoubleClick:
        Serial.println ("dubbelklik gebeurtenis"); //double click event
        break;
    }
}
// -----------------------------------------------------------------------------
void setup ()
{
    Serial.begin (9600);
    
    pinMode (btnBoot, INPUT_PULLUP);
    pinMode (btnA, INPUT_PULLUP);
    pinMode (btnB, INPUT_PULLUP);
    pinMode (btnStart, INPUT_PULLUP);
    pinMode (btnSelect, INPUT_PULLUP);
    
}
