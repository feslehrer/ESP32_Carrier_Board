#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen
#define PRESS LOW                        
const int S3_COUNT = 19;

void setup()
{
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print("Besucherz\xe1hler");      // \0xe1 = ä im Displaycode
  lcd.setCursor(0,1);
  lcd.print("Anzahl:");
  
  pinMode(S3_COUNT,INPUT_PULLUP);
}

uint16_t count = 0;

void loop() 
{
  char buf[6];
  sprintf(buf, "%5u", count);                                         // Für Rechtsbündige Darstellung im Display
  lcd.setCursor(8,1);
  lcd.print(buf);

  if(digitalRead(S3_COUNT) == PRESS)
    count++;
}
