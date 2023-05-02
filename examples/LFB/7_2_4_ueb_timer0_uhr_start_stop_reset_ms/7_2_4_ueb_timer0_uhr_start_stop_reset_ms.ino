#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int timerNr = 0;
const int Divider = 80;
const unsigned long Alarm = 1000;
volatile uint8_t sekunden = 0;
volatile uint8_t minuten = 0;
volatile uint16_t millisekunden = 0;

LiquidCrystal_I2C lcd(0x27,16,2);
hw_timer_t *timer = NULL;

const int StartButton = 19;  //S3
const int ResetButton = 18;  //S4

void IRAM_ATTR timer_isr(void)
{
  millisekunden++;
  if(millisekunden > 999)
  {
    sekunden++;
    millisekunden = 0;
    if(sekunden>59)
    {
      minuten++;
      sekunden = 0;
      if(minuten>59)
        minuten = 0;
    }
  }
}

void setup()
{
  Wire.begin(21,22,100000);
  lcd.init();
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("3:Strt/Stp 4:Clr");

  pinMode(StartButton, INPUT_PULLUP);
  pinMode(ResetButton, INPUT_PULLUP);
    
  timer = timerBegin(timerNr,Divider,true);
  timerAttachInterrupt(timer,&timer_isr,true);
  timerAlarmWrite(timer,Alarm,true);
}

bool startStopStatus;

void loop() 
{
  char buffer[17];

  pinToggle(StartButton, &startStopStatus);
  if(startStopStatus == true)
    timerAlarmEnable(timer);
  else
    timerAlarmDisable(timer);

  if(digitalRead(ResetButton) == 0)  //S4 gedrückt
  { 
    minuten = 0; sekunden = 0; millisekunden = 0;
  }
  
  sprintf(buffer,"%02u:%02u:%03u",minuten,sekunden,millisekunden);
  lcd.setCursor(0,0);
  lcd.print(buffer);
}
