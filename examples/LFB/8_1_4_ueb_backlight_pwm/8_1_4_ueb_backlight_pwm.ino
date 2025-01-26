#include <esp32CarrierBoard.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int PWM_FREQU = 1'000;
const int PWM_RES = 12;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RES) - 1); 

void setup()
{
  Wire.begin(21,22);
  lcd.init();
  lcd.clear();
  lcd.print("LCD-Backlight");

  ledcAttach(BACKLIGHT,PWM_FREQU,PWM_RES);
}

void loop()
{ 
  int dimmer = analogRead(A3);         // GPIO 34
  dimmer = map(dimmer,0,4095,0,MAX_DUTY_CYCLE);
  ledcWrite(BACKLIGHT, dimmer);        // (GPIO, duty_cycle)

  delay(50);
}

