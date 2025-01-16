#include <esp32CarrierBoard.h>

void setup() 
{
  // (GPIO, PWM-Frequenz, Auflösung)      
  ledcAttach(LED_BUILDIN, 1000, 12);     //GPIO 12
  ledcAttach(BACKLIGHT, 1000, 12);       //GPIO 2
  ledcAttach(SPEAKER,1000,12);           //GPIO 27
}

int play = false;

void loop()
{ // ADC hat 12-Bit Auflösung
  int hell = analogRead(A3);   // GPIO 34
  ledcWrite(LED_BUILDIN, hell);
  //(GPIO, duty_cycle)
  ledcWrite(BACKLIGHT,4096-hell);
  if (!play)
  { ledcWriteNote(SPEAKER,NOTE_A,4); // GPIO,Note,Oktave
    delay(3000);
    ledcWriteTone(SPEAKER,0);        // GPIO, Frequenz
    play = true;   
  }
  delay(50);
}
