const int LEDpin = 32;
const int timerNr = 0;
const int Divider = 80;
const unsigned long Alarm = 1000000;

hw_timer_t *timer = NULL;
volatile byte led = LOW;

void IRAM_ATTR timer_isr(void)
{
  led = !led;
  digitalWrite(LEDpin,led);
}

void setup()
{
  pinMode(LEDpin,OUTPUT);
  timer = timerBegin(timerNr,Divider,true);
  timerAttachInterrupt(timer,&timer_isr,true);
  timerAlarmWrite(timer,Alarm,true);
  timerAlarmEnable(timer);
}

void loop() {}
