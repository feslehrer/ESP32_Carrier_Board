#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

#define PRESS LOW
const int S4_CLEAR = 18;
const int S3_COUNT = 19;
const int S2_COUNTDOWN = 23;
uint32_t  oldTime;                     // Debounce-Zeitmerker

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
  pinMode(S2_COUNTDOWN,INPUT_PULLUP);
  pinMode(S4_CLEAR,INPUT_PULLUP);
}

uint16_t count = 0;

void loop() 
{
  lcd.setCursor(8,1);
  lcd.printf("%5u", count);

  uint32_t newTime = millis();
  
  if(digitalRead(S3_COUNT) == PRESS)
  {
    if(newTime - oldTime > 50)
      count++;
    oldTime = newTime;
  }
  if(digitalRead(S2_COUNTDOWN) == PRESS)
  {
    if(newTime - oldTime > 50)
    {
      if (count>0)  count--;
    }
    oldTime = newTime;
  }

  if(digitalRead(S4_CLEAR) == PRESS)
    count=0;
}
