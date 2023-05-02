const int led[] = {9,10,14,4,33,15,13,32};

void setup() 
{
  for (int i = 0; i<8;i++)  
  { 
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],HIGH);            // alle LEDs aus    
  }
}

void loop()
{ 
  int c;
  for (c = 0; c < 8; c++)
  {
    digitalWrite(led[c], LOW);            // aktuelle LED ein
    if(c>0) digitalWrite(led[c-1], HIGH); // letzte LED aus
    
    delay(150);
  }
  for (c = 7; c >= 0; c--)
  {
    digitalWrite(led[c], LOW);            // aktuelle LED ein
    if(c<7) digitalWrite(led[c+1], HIGH); // letzte LED aus
    
    delay(150);
  }
}
