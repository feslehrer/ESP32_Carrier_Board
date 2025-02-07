#include <esp32CarrierBoard.h>

void setup() 
{
  // Not working yet!! Default: fpwm=1000; Resolution=8-Bit
  analogWriteResolution(LED_BUILDIN, 12);   // PWM-Auflösung 12-Bit
  analogWriteFrequency(LED_BUILDIN, 500);  // PWM-Frequenz 500 Hz
  Serial.begin(9600);
}

void loop()
{ 
  int dimmer = analogRead(A3);             // GPIO 34
  //dimmer = map(dimmer,0,4095,0,255);
  analogWrite(LED_BUILDIN, dimmer);        // (GPIO, duty_cycle)
  Serial.println(dimmer);
  delay(50);
}
