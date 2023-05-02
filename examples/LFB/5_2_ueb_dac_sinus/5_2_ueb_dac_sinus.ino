#define DAC1 25

void setup() 
{
  pinMode(DAC1, ANALOG);  
}

void loop() 
{
  for(float n = 0.0; n <= 255.0; n += 5)
  {  
    dacWrite(DAC1, 127*(1+sin(n*0.02464)));
  }
}
