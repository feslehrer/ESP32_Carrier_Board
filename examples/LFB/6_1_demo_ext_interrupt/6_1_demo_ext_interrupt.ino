
const int LED = 32;
const int S3  = 19;

volatile bool LedStatus = false;

void IRAM_ATTR toggle_isr(void)
{
  LedStatus = !LedStatus;
  digitalWrite(LED,LedStatus);
}

void setup() 
{
  pinMode(LED,OUTPUT);
  pinMode(S3,INPUT_PULLUP);
  attachInterrupt(S3,toggle_isr,FALLING);
}

void loop() {}
