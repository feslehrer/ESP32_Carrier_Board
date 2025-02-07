#include <esp32CarrierBoard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define NunchukAdress 0x52  // I2C-Adresse fuer Nunchuk
uint8_t nunchuk_data[6];

void nunchuk_read(uint8_t *ndata); 

void setup() 
{
  Wire.begin();
  Serial.begin(115200);
  lcd.init();  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nunchuk:");    
}

void loop() 
{     
  nunchuk_read(nunchuk_data);
  lcd.setCursor(0,1);
  lcd.print("X:");lcd.print(nunchuk_data[0]);lcd.print(" Y:");lcd.print(nunchuk_data[1]);
  delay(100);
}

void nunchuk_read(uint8_t *ndata) 
{
  byte msb, lsb, msb1;
  
  Wire.beginTransmission(NunchukAdress);  
  Wire.write(0);       
  Wire.endTransmission();
  
  Wire.requestFrom(NunchukAdress, 6); 
  if (Wire.available()) 
  {
    for (int i = 0; i<6;i++)
    { 
      ndata[i] = Wire.read();
      Serial.println(ndata[i]);
    }
  }
  Wire.endTransmission();
}
