#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd( 0x27, 16, 2);

float adcMap(float x, float x_min, float x_max, float y_min, float y_max);

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(" Voltmeter");
}

char buf[17];

void loop()
{
  uint16_t wert = analogRead(34);
  Serial.print(wert);
  Serial.print(" -> ");

  float spannung = 0.0008057 * (float)wert;
  spannung = adcMap(spannung,0.0,3.3,0.0,5.0);
  Serial.print(spannung); Serial.println("V");
  sprintf(buf,"U = %4.2fV",spannung);
  lcd.setCursor(0,1);lcd.print(buf);

  delay(50);
}

float adcMap(float x, float x_min, float x_max, float y_min, float y_max)
{
  float y;
  y = (y_max-y_min)/(x_max-x_min);
  y = y *(x-x_min) + y_min;  

  return y;
}
