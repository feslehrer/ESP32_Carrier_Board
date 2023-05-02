const int LED = 32;

void setup() 
{
  pinMode(LED,OUTPUT);
}

void loop() 
{
  int wert = analogRead(34);  
    
  digitalWrite(LED, LOW);    // LED lowaktiv
  delay(wert);
  digitalWrite(LED, HIGH);
  delay(wert);
}
