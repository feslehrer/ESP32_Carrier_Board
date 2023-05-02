#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int triggerPin = 10;
const int echoPin = 9;
unsigned long pulse;
float distance;

LiquidCrystal_I2C lcd(0x27, 16, 2);   

void setup()
{
  Wire.begin(21,22);
  lcd.init();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Entfernung:");

  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop()
{
  //Trigger-Impuls erzeugen
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(3);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  // Echo-Pulslänge messen in µs
  pulse = pulseIn(echoPin,HIGH);
  distance = pulse / 58.31;
  
  lcd.setCursor(2,1);
  lcd.print(distance); lcd.print("cm");lcd.print("     ");

  delay(200);
}
