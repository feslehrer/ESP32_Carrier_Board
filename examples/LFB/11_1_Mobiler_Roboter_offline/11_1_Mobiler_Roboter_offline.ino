#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Input1 = 14;  // L298-Motortreiber: Input1
const int Input2 = 5;   //                    Input2
const int RaupeLinks = 18; //                 EnableA  (pwm-Pin)

const int Input3 = 23;  // L298-Motortreiber: Input3
const int Input4 = 19;  //                    Input4
const int RaupeRechts = 4; //                 EnableB  (pwm-Pin)

const int IRR = 32;
const int IRM = 10;
const int IRL = 9;
const int RflxL =33;
const int RflxM =15;
const int RflxR =13;
const int EndL = 27;
const int EndR = 0;

const int directions[9][4] = {
    {0, 0, 0, 0}, // stopp
    {0, 1, 0, 1}, // vor
    {1, 0, 1, 0}, // rueck
    {0, 0, 0, 1}, // linksvor
    {0, 1, 0, 0}, // rechtsvor
    {1, 0, 0, 1}, // linksdreh
    {0, 1, 1, 0}, // rechtsdreh
    {1, 0, 0, 0}, // linksrueck
    {0, 0, 1, 0}, // rechtsrueck
};

enum richtung {STOPP,VORWAERTS,RUECKWAERTS,LINKSVOR,RECHTSVOR,
               LINKSDREH,RECHTSDREH,LINKSRUECK,RECHTSRUECK};

void setup()
{
  Wire.begin(21,22,100000);
  lcd.init();
  lcd.clear();

  // Sensorsignale
  pinMode(IRR, INPUT_PULLUP);
  pinMode(IRM, INPUT_PULLUP);
  pinMode(IRL, INPUT_PULLUP);
  pinMode(RflxL, INPUT_PULLUP);
  pinMode(RflxM, INPUT_PULLUP);
  pinMode(RflxR, INPUT_PULLUP);
  pinMode(EndL, INPUT_PULLUP);
  pinMode(EndR, INPUT_PULLUP);

  // Motorsignale
  pinMode(Input1, OUTPUT); // L298-Pins initialisieren
  pinMode(Input2, OUTPUT);
  pinMode(Input3, OUTPUT); // L298-Pins initialisieren
  pinMode(Input4, OUTPUT);

  digitalWrite(Input1, 0); // Motor aus
  digitalWrite(Input2, 0); // Motor aus
  digitalWrite(Input3, 0); // Motor aus
  digitalWrite(Input4, 0); // Motor aus

  // PWM-Initialisieren für Motor Links
  ledcAttach(RaupeLinks,1000,8);        // PWM-Links initialisieren: RaupeLinks=Pin 18, 1kHz, 8 Bit
  ledcWrite(RaupeLinks, 0);             // PWM-Tastgrad: g = 0

  // PWM-Initialisieren für Motor Rechts
  ledcAttach(RaupeRechts,1000,8);       // PWM-Rechts initialisieren: RaupeRechts=Pin 4, 1 kHz, 8 Bit
  ledcWrite(RaupeRechts, 0);           // PWM-Tastgrad: g = 0
}

byte rSpeed;
int  fade;

void loop()
{
    //fade = 127 - (analogRead(34)>>4);
    //rSpeed = 140;
    fade = 0;
    rSpeed = (analogRead(34)>>4);   //Poti
    lcd.setCursor(0,0);
    lcd.print("Speed: ");lcd.print(rSpeed);lcd.print("  ");

    lcd.setCursor(0,1);

    if (!digitalRead(EndL)||!digitalRead(EndR))
    {
      robby_richtung(STOPP, 0, fade);
      lcd.print("NOTHALT     ");      
    }
    else if (!digitalRead(IRM))
    {
      robby_richtung(RECHTSRUECK, rSpeed, fade);
      lcd.print("Rechtsrueck ");
    }
    else if (!digitalRead(IRL))
    {
      robby_richtung(RECHTSVOR, rSpeed, fade);
      lcd.print("Rechtsvor   ");
    }
    else if (!digitalRead(IRR))
    {
      robby_richtung(LINKSVOR, rSpeed, fade);
      lcd.print("Linksvor    ");
    }
    else if (!digitalRead(IRM) && !digitalRead(IRL))
    {
      robby_richtung(RECHTSDREH, rSpeed, fade);
      lcd.print("Rechtsdreh  ");
    }
    else if (!digitalRead(IRM) && !digitalRead(IRR))
    {
      robby_richtung(LINKSDREH, rSpeed, fade);
      lcd.print("Linksdreh   ");
    }
    else if (!digitalRead(IRR) && !digitalRead(IRL))
    {
      robby_richtung(RECHTSRUECK, rSpeed, fade);
      lcd.print("Rechtsrueck ");
    }
    else if (!digitalRead(IRM) && !digitalRead(IRL) && !digitalRead(IRR))
    {
      robby_richtung(RECHTSRUECK, rSpeed, fade);
      lcd.print("Rechtsrueck ");
    }
    else
    {
      robby_richtung(VORWAERTS, rSpeed, fade);
      lcd.print("Vorwaerts   ");
    }
}

void robby_richtung(byte dir, int rSpeed, int fade)
{
  int left,right;

  digitalWrite(Input1, directions[dir][0]);
  digitalWrite(Input2, directions[dir][1]);
  digitalWrite(Input3, directions[dir][2]);
  digitalWrite(Input4, directions[dir][3]);

  left  = rSpeed - fade;
  right = rSpeed + fade;

  if (left > 255)     left = 255;
  else if (left < 0)  left = 0;
  if (right > 255)    right = 255;
  else if (right < 0) right = 0;

  ledcWrite(RaupeLinks, left);
  ledcWrite(RaupeRechts, right);
}
