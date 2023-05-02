const int led[] = {9,10,14,4,33,15,13,32};

void setup() 
{
  Serial.begin(9600);
  for (int i = 0; i<8;i++)  pinMode(led[i],OUTPUT);
}

void loop() 
{
  byte wert;

  if (Serial.available() > 0)
  {
    wert = Serial.parseInt(); 
    Serial.read();  //dummy read (CR)
    
    for (int i = 0; i<8;i++)
    { 
      //Jede Bitstelle prüfen!
      if (((wert>>i)&0x01) == 0x01)  
        digitalWrite(led[i], LOW);    // LED lowaktiv
      else
        digitalWrite(led[i], HIGH);
    }
  }
}
