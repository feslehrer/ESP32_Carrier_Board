#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd( 0x27, 16, 2);

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(" Voltmeter");
}

char buf[17];

// Spannungsauflösung des ADC
const float Ulsb = 3.3/pow(2,12);

void loop()
{
  uint16_t wert = analogRead(A3);   //GPIO 34
  Serial.print(wert);
  Serial.print(" -> ");

  float spannung = fMap(Ulsb * wert, 0.0, 3.3, 0.0, 5.0);
  Serial.print(spannung); Serial.println("V");
  sprintf(buf,"U = %4.2fV",spannung);
  lcd.setCursor(0,1);lcd.print(buf);

  delay(200);
}
