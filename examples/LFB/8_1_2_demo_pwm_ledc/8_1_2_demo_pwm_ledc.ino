#include <esp32CarrierBoard.h>

void setup() 
{  
  ledcAttach(LED_BUILDIN, 500, 12);     //GPIO 12, Resolution 12-Bit
}                                       //Frequenz: 500 Hz

void loop()
{ 
  int dimmer = analogRead(A3);          // Poti an GPIO 34 (ADC: 12Bit-Auflösung)
  ledcWrite(LED_BUILDIN, dimmer);       // (GPIO, duty_cycle)

  delay(50);
}

