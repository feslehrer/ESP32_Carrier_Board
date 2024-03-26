/*
  Steuerpro

*/
#include <Wire.h>
#include <esp32CarrierBoard.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Input1 = 14;  // L298-Motortreiber: Input1
const int Input2 = 5;   //                    Input2
const int EnableA = 23; //                    EnableA  (pwm-Pin)


const int Start_S3 = 19;
const int Dir_S4 = 18;

#define PWM_Ch 1
#define SPEED_OFFSET 2048     // Wegen Losbrechmoment (speedi = SPEED_OFFSET ... 4095)

void setup()
{
  Wire.begin(21,22);
  lcd.init();
  lcd.clear();

  // Motorsignale
  pinMode(Input1, OUTPUT);            // L298-Pins initialisieren
  pinMode(Input2, OUTPUT);
  //pinMode(EnableA, OUTPUT);

  pinMode(Start_S3, INPUT_PULLUP);
  pinMode(Dir_S4, INPUT_PULLUP);

  digitalWrite(Input1, 0); // Motor aus
  digitalWrite(Input2, 0); // Motor aus


  // PWM-Initialisieren für Motor Links
  ledcSetup(PWM_Ch, 10000, 12);     // PWM initialisieren: Kanal 0, 10kHz, 12 Bit
  ledcAttachPin(EnableA, PWM_Ch);   // PWM-Pin initialisieren: EnableA=Pin 18, Kanal 0
  ledcWrite(PWM_Ch, 0);             // PWM-Tastgrad: Kanal 0, g = 0

  lcd.setCursor(0,1);
  lcd.print("S3:Start  S4:Dir");
}

int speedi;
bool status_start = !PRESS;
bool status_dir = !PRESS;

void loop()
{
    pinToggle(Start_S3,&status_start);
    pinToggle(Dir_S4,&status_dir);

    speedi = analogRead(34)&0xffc;   // Poti 12-Bit-Auflösung (Bit0 und Bit1 = 0)
    speedi = map(speedi,0,4095,SPEED_OFFSET,4095);

    lcd.setCursor(0,0);
    lcd.print("Speed: ");lcd.print(speedi);lcd.print("  ");

    if (status_start == PRESS)
    {
      if (status_dir == PRESS)
      {
        digitalWrite(Input1, LOW);
        digitalWrite(Input2, HIGH);
      }
      else
      {
        digitalWrite(Input1, HIGH);
        digitalWrite(Input2, LOW);
      }
      ledcWrite(PWM_Ch, speedi);
    }
    else
    {
      digitalWrite(Input1, LOW);
      digitalWrite(Input2, LOW);
          
      ledcWrite(PWM_Ch, 0);
    }
}

