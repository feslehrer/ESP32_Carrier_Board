#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int timerNr = 0;
const int Divider = 80;
const unsigned long Alarm = 1000000;
volatile unsigned int sekunden = 0;
volatile unsigned int minuten = 0;

LiquidCrystal_I2C lcd(0x27,16,2);
hw_timer_t *timer = NULL;

void IRAM_ATTR timer_isr(void)
{
  sekunden++;
  if(sekunden>59)
  {
    minuten++;
    sekunden = 0;
    if(minuten>59)
      minuten = 0;
  }
}

void setup()
{
  Wire.begin(21,22,100000);
  lcd.init();
  lcd.clear();
  
  timer = timerBegin(timerNr,Divider,true);
  timerAttachInterrupt(timer,&timer_isr,true);
  timerAlarmWrite(timer,Alarm,true);
  timerAlarmEnable(timer);
}

void loop() 
{
  char buffer[6];

  sprintf(buffer,"%02u:%02u",minuten,sekunden);
  lcd.setCursor(0,0);
  lcd.print(buffer);
}
