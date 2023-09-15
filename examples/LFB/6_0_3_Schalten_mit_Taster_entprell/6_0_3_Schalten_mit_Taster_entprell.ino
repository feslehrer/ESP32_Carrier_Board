const int LED = 32;
const int tasterS3  = 19;

#define PRESS   LOW       // Symbol für gedrückten Taster
                          // Null-Aktiv
uint32_t oldTime;         // Zeitmerker
bool toggleState;

void setup()
{
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH); // LED aus
  toggleState = true;
  pinMode(tasterS3,INPUT_PULLUP);
}

void loop()
{
  uint32_t newTime = millis();
  
  if (digitalRead(tasterS3) == PRESS)
  {
    if(newTime - oldTime > 50)
    {
      toggleState = !toggleState;
    }
    oldTime = newTime;
  }

  digitalWrite(LED,toggleState);
}
