#include <esp32CarrierBoard.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  eee895_init();          // Wire.begin() in eee895_init()
  lcd.init();  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CO2:");   
}

void loop()
{
  uint16_t co2 = eee895_readCO2();
  lcd.setCursor(5,0);
  lcd.print(co2);lcd.print("ppm");
  uint16_t pressure = eee895_readPressure();
  lcd.setCursor(0,1);
  lcd.print(pressure);lcd.print("mbar  ");
  float  cTemp = eee895_readTemp();
  lcd.print(cTemp);lcd.print("\337C");   
  delay(10000);
}
