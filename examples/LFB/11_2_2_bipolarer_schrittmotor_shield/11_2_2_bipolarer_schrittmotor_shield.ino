#include <Wire.h>                      // Wire Bibliothek für I2C-Display
#include <LiquidCrystal_I2C.h>
#include <esp32CarrierBoard.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C-Display: adresse 0x27, 2 Zeilen á 16 Zeichen

const int IN1 = 14;   //4
const int IN2 = 5;    //14
const int IN3 = 18;   //10
const int IN4 = 19;   //9
const int SPEED_POTI = 34;
const int ENABLEA = 23;
const int ENABLEB = 4;  

bool  status_start;                     // 
bool  status_dir;
bool  status_voll;

#define STOP    0x00
const uint8_t stepCode[] = {  0b0110,   //0x06,   //0110
                              0b0100,   //0x04,   //0100
                              0b0101,   //0x05,   //0101
                              0b0001,   //0x01,   //0001
                              0b1001,   //0x09,   //1001
                              0b1000,   //0x08,   //1000
                              0b1010,   //0x0A,   //1010
                              0b0010    //0x02    //0010
                           };

void setup()
{
  Wire.begin(21,22);                   // I2C-Bus initialisieren SDA = 21, SCL = 22
  lcd.init();                          // LDC initialisieren
  lcd.clear();                         // LCD Anzeige löschen

  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.print("Bipolar-Stepper");
  lcd.setCursor(0,1);
  lcd.print("");

  Serial.print("\n\rBipolar-Stepper Kommandos:");
  Serial.print("\n\re,E: Einschalten");  
  Serial.print("\n\ra,A: Ausschalten");  
  Serial.print("\n\rl,L: Drehrichtung Links");  
  Serial.print("\n\rr,R: Drehrichtung Rechts");
  Serial.print("\n\rv,V: Vollschrittbetrieb");  
  Serial.print("\n\rh,H: Halbschrittbetrieb");  
  Serial.print("\n\rsxxxx,Sxxxx: Speed, xxxx=0 ... 1023");  

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);  
  pinMode(ENABLEA,OUTPUT);  
  pinMode(ENABLEB,OUTPUT);
  digitalWrite(ENABLEA,1);
  digitalWrite(ENABLEB,1);
}

int8_t  schritt = 0;
uint16_t speedi = 128;

char buf[16];

void loop() 
{
  if(Serial.available())
  {
    int c = Serial.read();
    switch (c)
    {
      case 'e':
      case 'E': status_start = 1; 
                lcd.setCursor(13, 1);
                lcd.print("ON ");
                break;
      case 'a':
      case 'A': status_start = 0;
                lcd.setCursor(13, 1);
                lcd.print("OFF");
                break;
      case 'l':
      case 'L': status_dir = 1; 
                lcd.setCursor(13, 1);
                lcd.print("Lft");
                break;
      case 'r':
      case 'R': status_dir = 0;
                lcd.setCursor(13, 1);
                lcd.print("Rgt");      
                break;
      case 'v':
      case 'V': status_voll = 1;
                lcd.setCursor(13, 1);
                lcd.print("Voll");      
                break;
      case 'h':
      case 'H': status_voll = 0;
                lcd.setCursor(13, 1);
                lcd.print("Hlb");      
                break;
      case 's':
      case 'S': speedi = Serial.parseInt(); 
                speedi = constrain(speedi,1,1023);
                lcd.setCursor(0,1);
                sprintf(buf,"Speed: %4u  ",speedi);      // Rechtsbündige Ausgabe
                lcd.print(buf);
                speedi = 1024 - speedi;
                break;
      default: break;
    }
  }

  if(status_start == true)
  {
    digitalWrite(IN1,(stepCode[schritt]>>3)&0x01);
    digitalWrite(IN2,(stepCode[schritt]>>2)&0x01);
    digitalWrite(IN3,(stepCode[schritt]>>1)&0x01);
    digitalWrite(IN4,(stepCode[schritt]>>0)&0x01);
    delay(speedi);

    if(status_dir == true)
    {
      if (status_voll == true)
      {
        if (schritt <6)    schritt+=2;
        else schritt = 0;
      }
      else
      {
        if (schritt <7)    schritt++;
        else schritt = 0;
      }
    }
    else
    {
      if (status_voll == true)
      {
        if (schritt >=2)    schritt-=2;
        else schritt = 6;
      }
      else
      {
        if (schritt >0)    schritt--;
        else schritt = 7;
      }
    }
  }
  else
  {
    lcd.setCursor(0,1);
    sprintf(buf,"Speed: %4u  ",speedi);      // Rechtsbündige Ausgabe
    lcd.print(buf);  
    lcd.setCursor(13, 1);
    lcd.print("OFF");
  }
}
