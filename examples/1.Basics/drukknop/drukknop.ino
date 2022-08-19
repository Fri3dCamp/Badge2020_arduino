// DEMO het gebruik van een (druk)knop
//=========================================
// Het resultaat van je drukknop events kan je zien door het serial output scherm te activeren.
// (ga naar Tools > Serial monitor of gebruik de sneltoets ctrl + Shift + M)
// Rechts onderaan selecteer je 9600 baud (indien dit anders zou staan)
// we gebruiken de "boot" knop die onder de batterij te vinden is.

const byte pinBut = 0;
byte butLst;

enum { None, SingleClick, DoubleClick };

// -----------------------------------------------------------------------------
int chkButton (void)
{
    const  unsigned long ButTimeout  = 250;
    static unsigned long msecLst;
           unsigned long msec = millis();

    if (msecLst && (msec - msecLst) > ButTimeout)  {
        msecLst = 0;
        return SingleClick;
    }

    byte but = digitalRead (pinBut);
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
    
    pinMode (pinBut, INPUT_PULLUP);
    butLst = digitalRead (pinBut);
    
}
