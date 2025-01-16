#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

const int pwm1Pin = 2;

void setup()
{
  Serial.begin(9600);
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print("LCD dimmen...");
  
  ledcAttach(pwm1Pin, 1000, 12);    // GPIO, Frequenz, Auflösung  
}

uint16_t count = 0;

void loop() 
{
  uint16_t hell = analogRead(34)& 0x0ff8;    // Poti einlesen 12 Bit (letzte 3 Bit = 0)
  ledcWrite(pwm1Pin, hell);

  hell = map(hell,0,4095,0,16);
  
  lcd.setCursor(0,1);
  for (int i = 0; i< 16;i++)
  {
    if (i<hell) lcd.write(0xFF);    // Blocksymbol
    else        lcd.write(0x20);    // Leerzeichen
  }
  delay(100);
}
