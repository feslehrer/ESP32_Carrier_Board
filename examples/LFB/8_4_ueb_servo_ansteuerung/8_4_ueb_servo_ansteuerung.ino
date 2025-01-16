#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

const int pwm1Pin = 32;

void setup()
{
  Serial.begin(9600);
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print(" Servo-Steuerung");
  
  // (GPIO, Frequenz, Auflösung)
  ledcAttach(pwm1Pin, 50, 12);         // Pin mit Kanal verbinden  
}

uint16_t count = 0;

void loop() 
{
  uint16_t pos = analogRead(34)& 0x0ff8;    // Poti einlesen 12 Bit (letzte 3 Bit = 0)

  pos = map(pos,0,4095,100,450);
  ledcWrite(pwm1Pin, pos);

  pos = map(pos,100,450,0,16);
  
  lcd.setCursor(0,1);
  for (int i = 0; i< 16;i++)
  {
    if (i<pos) lcd.write(0xFF);     // Blocksymbol
    else        lcd.write(0x20);    // Leerzeichen
  }
  //delay(100);
}
