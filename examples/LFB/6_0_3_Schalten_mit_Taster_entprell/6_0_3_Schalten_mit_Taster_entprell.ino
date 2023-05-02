const int LED = 32;
const int tasterS3  = 19;

#define PRESS   LOW       // Symbol für gedrückten Taster
                          // Null-Aktiv
//bool oldStatus;           // alter Tasterstatus
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

//void loop()
//{
//  bool newStatus = digitalRead(tasterS3);     // neuer Tasterstatus
//  
//  if (newStatus != oldStatus)
//  {    
//    if(newStatus == PRESS)  
//    {
//      uint32_t newTime = millis(); 
//
//      if (newTime-oldTime > 200)              // Impulse >200ms ?
//      {
//        ledStatus = !ledStatus;
//        digitalWrite(LED,ledStatus);
//      }
//      oldTime = newTime;                      // update oldTime
//    }
//    oldStatus = newStatus;                    // update oldStatus
//  }
//}
