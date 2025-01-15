const int LED = 32;
const int tasterS3  = 19;

#define PRESS   LOW       // Symbol für gedrückten Taster
                          // Null-Aktiv
bool oldStatus;           // alter Tasterstatus
bool ledStatus;          
      
void setup() 
{
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH); // LED aus
  ledStatus = true;       
  pinMode(tasterS3,INPUT_PULLUP);
}

void loop()
 {
  bool newStatus = digitalRead(tasterS3);   //neuer Tasterstatus
 
  if (newStatus != oldStatus)
  { 
    if(newStatus == PRESS)  
    {
      ledStatus = !ledStatus;
      digitalWrite(LED,ledStatus);
    }
    oldStatus = newStatus;                  // update oldStatus     
  }
}
