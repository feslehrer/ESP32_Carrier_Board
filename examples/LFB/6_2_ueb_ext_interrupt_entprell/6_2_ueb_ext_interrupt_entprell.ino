const int LED = 32;
const int tasterS3 = 19;

volatile uint32_t oldTime = 0;
volatile bool ledStatus;

void IRAM_ATTR toggleLED(void)
{
  uint32_t newTime = millis();
  if(newTime - oldTime > 250)
  {
    ledStatus = !ledStatus;
    digitalWrite(LED,ledStatus);
  }
  oldTime = newTime;
}

void setup()
{
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  ledStatus = true;
  attachInterrupt(tasterS3,toggleLED,FALLING);
}

void loop() {}
