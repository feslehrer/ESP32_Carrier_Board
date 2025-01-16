#include <esp32CarrierBoard.h>

void setup() 
{
  // (GPIO, PWM-Frequenz, Auflösung)      
  ledcAttach(LED_BUILDIN, 1000, 12);     //GPIO 12
  ledcAttach(BACKLIGHT, 1000, 12);       //GPIO 2
  ledcAttach(SPEAKER,1000,12);           //GPIO 27
}

void loop()
{ 
  // ADC hat 12-Bit Auflösung
  int hell = analogRead(A3);   // GPIO 34
  ledcWrite(LED_BUILDIN, hell);
  //(GPIO, duty_cycle)
  ledcWrite(BACKLIGHT,4096-hell);
  delay(50);
}
