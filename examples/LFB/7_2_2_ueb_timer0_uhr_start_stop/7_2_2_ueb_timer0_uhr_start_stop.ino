#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int timerNr = 0;
const int Divider = 80;
const unsigned long Alarm = 1000000;
volatile unsigned int sekunden = 0;
volatile unsigned int minuten = 0;

LiquidCrystal_I2C lcd(0x27,16,2);
hw_timer_t *timer = NULL;

const int StartButton = 19;  //S3

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

  pinMode(StartButton, INPUT_PULLUP);
  
  timer = timerBegin(timerNr,Divider,true);
  timerAttachInterrupt(timer,&timer_isr,true);
  timerAlarmWrite(timer,Alarm,true);
}

bool startStopStatus;

void loop() 
{
  char buffer[6];

  pinToggle(StartButton, &startStopStatus);
  if(startStopStatus == true)
    timerAlarmEnable(timer);
  else
    timerAlarmDisable(timer);
    
  sprintf(buffer,"%02u:%02u",minuten,sekunden);
  lcd.setCursor(0,0);
  lcd.print(buffer);
}
