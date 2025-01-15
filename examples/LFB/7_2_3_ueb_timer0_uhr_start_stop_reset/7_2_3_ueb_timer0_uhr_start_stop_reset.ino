#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const unsigned long Alarm = 1'000'000;
const unsigned long frequency = 1'000'000;
volatile unsigned int sekunden = 0;
volatile unsigned int minuten = 0;

LiquidCrystal_I2C lcd(0x27,16,2);
hw_timer_t *timer1 = NULL;

const int StartButton = S3;  //19
const int ResetButton = S4;  //18

IRAM_ATTR void timer_isr(void)
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
  pinMode(ResetButton, INPUT_PULLUP);
    
  timer1 = timerBegin(frequency);
  timerAttachInterrupt(timer1,&timer_isr);
  timerAlarm(timer1,Alarm,true,0);
}

bool startStopStatus;

void loop() 
{
  char buffer[6];

  pinToggle(StartButton, &startStopStatus);
  if(startStopStatus == true)
    timerStart(timer1);
  else
    timerStop(timer1);

  if(digitalRead(ResetButton) == 0)  //S4 gedrückt
  { 
    minuten = 0; sekunden = 0;
    timerRestart(timer1);   // Counter = 0
  }
  
  sprintf(buffer,"%02u:%02u",minuten,sekunden);
  lcd.setCursor(0,0);
  lcd.print(buffer);
}
