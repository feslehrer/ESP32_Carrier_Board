#include <esp32CarrierBoard.h>

const int PWM_FREQ = 1'000; 
const int PWM_RESOLUTION = 12; 
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

void setup() 
{
  // (GPIO, PWM-Frequenz, Auflösung)      
  ledcAttach(LED_BUILDIN, PWM_FREQ, PWM_RESOLUTION);     //GPIO 12
}

int play = false;

void loop()
{ // ADC hat 12-Bit Auflösung
  int hell = analogRead(A3);          // Poti an GPIO 34 (ADC: 12Bit-Auflösung)
  hell = map(hell,0,4095,0,MAX_DUTY_CYCLE);
  ledcWrite(LED_BUILDIN, hell);       // (GPIO, duty_cycle)

  delay(50);
}

