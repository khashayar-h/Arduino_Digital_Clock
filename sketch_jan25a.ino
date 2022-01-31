#include <TimerFreeTone.h>

//------Electronics-project-hub.com-----//
#include "SevSeg.h"
SevSeg Display;
const unsigned long period = 1000; //one second
const unsigned long led_period = 500; //LED blink millisecond
unsigned long startMillis;
unsigned long led_startMillis;
unsigned long currentMillis;
unsigned long led_currentMillis;
const int hrs_btn = A0;
const int min_btn = A5;
const int ledPin = 9;
int Hrs = 00;
int Min = 0;
int Sec = 0;
int Time;
int ledState = LOW;


#define TONE_PIN A3 // Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor).

int melody[] = {  500, 750, 1000,1250,1000, 750, 500, 250 };
int duration[] = { 125, 125, 125, 125, 125, 125, 125, 125 };
int dpState = 0;


void setup()
{
  pinMode(hrs_btn, INPUT_PULLUP);
  pinMode(min_btn, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  byte numDigits = 4;
  byte digitPins[] = {13,12,11,10};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  bool resistorsOnSegments = false;
  bool updateWithDelays = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool leadingZeros = true;
  bool disableDecPoint = true;
  Display.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  Display.setBrightness(100);
}
void loop()
{
if(Min==0 && Sec==0)
{
  for (int thisNote = 0; thisNote < 8; thisNote++) { // Loop through the notes in the array.
    TimerFreeTone(TONE_PIN, melody[thisNote], duration[thisNote]); // Play thisNote for duration.
    delay(50); // Short delay between notes.
  }
}  

  
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    Sec = Sec + 1;
    startMillis = currentMillis;
  }
  led_currentMillis = millis();
  if (led_currentMillis - led_startMillis >= led_period)
  {
    led_startMillis = led_currentMillis;
    if (ledState == LOW)
    {
      ledState = HIGH;
      if (digitalRead(hrs_btn) == LOW)
      {
        Hrs = Hrs + 1;
      }
      if (digitalRead(min_btn) == LOW)
      {
        Min = Min + 1;
        Sec = 0;
      }
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
  if (Sec == 60)
  {
    Sec = 0;
    Min = Min + 1;
  }
  if (Min == 60)
  {
    Min = 0;
    Hrs = Hrs + 1;
  }
  if (Hrs == 24)
  {
    Hrs = 0;
  }
  Time = Hrs * 100 + Min;
  Display.setNumber(Time);
  Display.refreshDisplay();
  
}

//------Electronics-project-hub.com-----//
