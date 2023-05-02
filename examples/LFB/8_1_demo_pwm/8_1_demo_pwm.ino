const int pwm1Pin = 12;
const int pwm2Pin = 2;

#define LED1 1
#define LED2 2

void setup() 
{
  // (Kanal, Frequenz, Auflösung)
  ledcSetup(LED1, 1000, 12);
  ledcSetup(LED2, 1000, 12);

  // Pin mit Kanal verbinden      
  ledcAttachPin(pwm1Pin, LED1);     
  ledcAttachPin(pwm2Pin, LED2);     
}

void loop() 
{ 
  // ADC hat 12-Bit Auflösung
  int hell = analogRead(34);
  ledcWrite(LED1, hell);
  ledcWrite(LED2, 4095-hell);  
  
  delay(100);
}
