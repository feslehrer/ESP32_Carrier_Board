#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>
#include <esp32CarrierBoard.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen
                        
const int CLEAR = S4;     // GPIO 18
const int COUNTUP = S3;   // GPIO 19
const int COUNTDOWN = S2; // GPIO 23
bool      toggleStateUP;
bool      toggleStateDOWN;

void setup()
{
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print("Besucherz\xe1hler");      // \0xe1 = ä im Displaycode
  lcd.setCursor(0,1);
  lcd.print("Anzahl:");
  
  pinMode(COUNTUP,INPUT_PULLUP);
  pinMode(COUNTDOWN,INPUT_PULLUP);
  pinMode(CLEAR,INPUT_PULLUP);
}

uint16_t count = 0;

void loop() 
{
  lcd.setCursor(8,1);
  lcd.printf("%5u", count);

  if(pinToggle(COUNTUP, &toggleStateUP) == PRESS)
    count++;

  if(pinToggle(COUNTDOWN, &toggleStateDOWN) == PRESS)
    if(count!=0) count--;
    
  if(digitalRead(CLEAR) == PRESS)
    count=0;
}
