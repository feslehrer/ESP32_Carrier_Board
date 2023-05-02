#include <Wire.h>               // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

// I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen
LiquidCrystal_I2C lcd(0x27, 16, 2);   

void setup() 
{
  Wire.begin(21,22);
  lcd.init();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Analog: ");  
}

void loop() 
{
  lcd.setCursor(8,0);
  lcd.print((int8_t)analogRead(34)); lcd.print("     ");

  delay(100);
}
