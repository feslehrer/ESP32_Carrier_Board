const int LEDpin = 32;
const unsigned long Alarm = 1'000'000;
const unsigned long frequency = 1'000'000;

hw_timer_t *timer1 = NULL;
volatile byte led = LOW;

void IRAM_ATTR timer_isr(void)
{
  led = !led;
  digitalWrite(LEDpin,led);
}

void setup()
{
  pinMode(LEDpin,OUTPUT);

  timer1 = timerBegin(frequency);
  timerAttachInterrupt(timer1,&timer_isr);
  timerAlarm(timer1,Alarm,true,0);
}

void loop() {}





