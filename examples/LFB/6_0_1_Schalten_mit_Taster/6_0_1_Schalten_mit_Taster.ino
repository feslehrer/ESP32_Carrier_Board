
const int LED = 32;
const int tasterS3  = 19;

bool tasterStatus;        //Statusvariable

void setup() 
{
  pinMode(LED,OUTPUT);
  pinMode(tasterS3,INPUT_PULLUP);
}

void loop()
{
  tasterStatus = digitalRead(tasterS3);
  digitalWrite(LED,tasterStatus);
}
