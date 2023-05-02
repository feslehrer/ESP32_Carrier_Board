#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SensorAdresse 0x48  // I2C-Adresse fuer LM75

void setup() 
{
  Wire.begin();
  lcd.init();  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatur:");    
}

void loop() 
{     
  float temp = lm75_read(SensorAdresse);
  lcd.setCursor(0,1);
  lcd.print(temp);lcd.print("\337C");    
  delay(500);
}

float lm75_read(int adress) 
{
  byte msb, lsb, msb1;
  
  Wire.beginTransmission(adress);  
  Wire.write(0);       
  Wire.endTransmission();
  
  Wire.requestFrom(adress, 2); 
  if (Wire.available()) 
  {
     msb1 = Wire.read();
     msb = msb1 << 1; 
     lsb = Wire.read();
  }
  lsb = (lsb & 0x80 ) >> 7;
  Wire.endTransmission();
  float temp = float(msb + lsb) / 2;
  if (msb1 < 0x80)    return temp; 
  else                return temp - 128;
}
