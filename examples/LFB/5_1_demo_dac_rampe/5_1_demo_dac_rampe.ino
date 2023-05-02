#define DAC1 25
#define DAC2 26

void setup() 
{
  pinMode(DAC1, ANALOG);  
}

void loop() 
{
  for(int n = 0; n <= 255; n += 1)
  {  
    dacWrite(DAC1, n);    
  }
}
