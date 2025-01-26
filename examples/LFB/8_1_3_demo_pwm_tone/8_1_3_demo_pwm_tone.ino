#include <esp32CarrierBoard.h>

void setup() 
{
  pinMode(S4,INPUT_PULLUP);
  // (GPIO, PWM-Frequenz, Auflösung)
  ledcAttach(SPEAKER,1000,12);           //GPIO 27
}

void loop()
{
  if (digitalRead(S4)==PRESS)
  { 
    ledcWriteNote(SPEAKER,NOTE_C,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_D,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_E,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_F,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_G,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_A,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_B,4);  // (GPIO, Note, Oktave)
    delay(500);
    ledcWriteNote(SPEAKER,NOTE_C,5);  // (GPIO, Note, Oktave)
    delay(500);
  }
    
  ledcWriteTone(SPEAKER,0);         // (GPIO, Frequenz) Ton ausschalten
  delay(50);
}
