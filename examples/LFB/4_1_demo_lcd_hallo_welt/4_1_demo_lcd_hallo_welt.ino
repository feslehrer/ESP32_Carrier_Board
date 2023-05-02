#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

void setup()
{
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print("Hallo Welt");
  lcd.noBacklight();
}

void loop() {}
