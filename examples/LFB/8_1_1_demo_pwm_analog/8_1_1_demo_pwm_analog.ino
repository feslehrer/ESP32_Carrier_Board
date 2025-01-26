#include <esp32CarrierBoard.h>

void setup() 
{
  analogWriteResolution(LED_BUILDIN,12);   // PWM-Auflösung 12-Bit
  analogWriteFrequency(LED_BUILDIN, 500);  // PWM-Frequenz 500 Hz
}

void loop()
{ 
  int dimmer = analogRead(A3);             // GPIO 34
  analogWrite(LED_BUILDIN, dimmer);        // (GPIO, duty_cycle)

  delay(50);
}

