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
  if (digitalRead(tasterS3) == PRESS)
  {
    uint32_t newTime = millis();
    
    if(newTime - oldTime > 50)
    {
      toggleState = !toggleState;
    }
    //oldTime = newTime;
    oldTime = millis();
  }
  digitalWrite(LED,toggleState);
  delay(100);  // Wartezeit führt bei gedrücktem Taster zu Problem!
               // newTime-oldTime ist dann immer > 50 !!
               // Es wird fortlaufend getoggled 

}
