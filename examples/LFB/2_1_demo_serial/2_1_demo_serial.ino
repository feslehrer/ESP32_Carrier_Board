
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.print("Hallo ");
  Serial.println("Welt");
  
  delay(1000);
}
