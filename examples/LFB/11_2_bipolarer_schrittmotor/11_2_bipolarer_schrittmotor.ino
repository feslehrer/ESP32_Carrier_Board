#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>
#include <esp32CarrierBoard.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

#define PRESS LOW
const int S4_START = 18;
const int S3_DIR = 19;
const int IN1 = 4;
const int IN2 = 14;
const int IN3 = 10;
const int IN4 = 9;
const int SPEED_POTI = 34;


bool  status_start;                     // Debounce-Zeitmerker
bool  status_dir;

#define STOP    0x00
const uint8_t stepCode[] = {  0x06,   //0110
                              //0x04,   //0100
                              0x05,   //0101
                              //0x01,   //0001
                              0x09,   //1001
                              //0x08,   //1000
                              0x0A,   //1010
                              //0x02    //0010
                           };

void setup()
{
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  lcd.setCursor(0,0);
  lcd.print("Bipolar-Stepper");
  lcd.setCursor(0,1);
  lcd.print("");
  
  pinMode(S4_START,INPUT_PULLUP);
  pinMode(S3_DIR,INPUT_PULLUP);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);  
}

uint8_t schritt = 0;
uint16_t speedi;

void loop() 
{
//  char buf[6];
//  sprintf(buf, "%5u", count);
//  lcd.setCursor(8,1);
//  lcd.print(buf);

  pinToggle(S4_START,&status_start);
  pinToggle(S3_DIR,&status_dir);
 
  if(status_start == true)
  { 
    speedi = analogRead(SPEED_POTI); if(speedi<1000) speedi = 1000;
    lcd.setCursor(1,1);
    lcd.print("ON ");

    digitalWrite(IN1,(stepCode[schritt]>>3)&0x01);
    digitalWrite(IN2,(stepCode[schritt]>>2)&0x01);
    digitalWrite(IN3,(stepCode[schritt]>>1)&0x01);
    digitalWrite(IN4,(stepCode[schritt]>>0)&0x01);
    if (schritt <4)    schritt++;
    else schritt = 0;
    delay(speedi);
  }
  else
  {
    lcd.setCursor(1,1);
    lcd.print("OFF ");
  }
}
