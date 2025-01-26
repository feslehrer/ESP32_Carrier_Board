#include <esp32CarrierBoard.h>
#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

const int PWM_FREQU = 1'000;
const int PWM_RES = 12;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RES) - 1);

void setup()
{
  Serial.begin(9600);
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print("LCD dimmen...");
  
  ledcAttach(BACKLIGHT, PWM_FREQU, PWM_RES);    // GPIO, Frequenz, Auflösung  
}

uint16_t count = 0;

void loop() 
{
  uint16_t dimmer = analogRead(34);    // Poti einlesen 12 Bit (letzte 3 Bit = 0)
  ledcWrite(BACKLIGHT, dimmer);

  dimmer = map(dimmer,0,MAX_DUTY_CYCLE,0,16);
  
  lcd.setCursor(0,1);
  for (int i = 0; i<= 16;i++)
  {
    if (i<dimmer) lcd.write(0xFF);    // Blocksymbol
    else        lcd.write(0x20);    // Leerzeichen
  }
  delay(100);
}
