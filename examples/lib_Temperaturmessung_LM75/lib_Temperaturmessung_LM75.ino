#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lm75_init(lm75Adresse);
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Temperatur");
  lcd.init();  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatur:");
}

void loop()
{
  float temp = lm75_read(lm75Adresse);
  Serial.println(temp);
  lcd.setCursor(0,1);
  lcd.print(temp);lcd.print("\337C"); 
  delay(1000);
}
