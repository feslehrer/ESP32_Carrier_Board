
#include "esp32CarrierBoard.h"
#include "Arduino.h"
#include <Wire.h>

int pins[] = TASTERPINS;            // ESP32-Carrier-Board Tasterpins
uint64_t debounceTimer[PINANZAHL];  // PINANZAHL muss mit der Anzahl der Tasterpins
                                    // übereinstimmen.

// pinToggle:  Schalten und Entprellen von Tastern
//         pin: Pinnummer des zu Input-Pins
//         toggleState: Schaltzustand des Toggle-Glieds (entprellt)
//         debounceTimer: Zeit der letzten Flankenerkennung
//      Rückgabewert: Tastersignal entprellt
bool pinToggle(int pin, bool *toggleState) 
{
  int i;
  int z = PINANZAHL;

  for (i=0; i<z; i++)
    if(pins[i]== pin) break;
    
  bool pinState = !PRESS;
  uint64_t newTime = millis();
  
  if (digitalRead(pin) == PRESS)
  {
    if(newTime - debounceTimer[i] > 50)
    {
      *toggleState = !*toggleState;
      pinState = PRESS;
    }
    debounceTimer[i] = newTime;
  }
  return pinState;
}

void lm75_init(void)
{
  Wire.begin();
}

// lm75_read:  Liest den Temperaturwert vom LM75 auf dem Carrier_Board
//      Rückgabewert: Temperaturwert als float -55.0 ... +125.0 (°C)
//      Die Auflösung beträgt 0,5°C
float lm75_read(uint8_t adress) 
{
  byte msb=0, lsb=0, msb1=0;
    
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

void eee895_init(void)
{
  Wire.begin();
}

uint16_t eee895_readCO2()
{
  uint8_t i2cResponse[8];
  eee895_read(i2cResponse);
  return (uint16_t)(i2cResponse[0] * 256 + i2cResponse[1]);
}

uint16_t eee895_readPressure()
{
  uint8_t i2cResponse[8];
  eee895_read(i2cResponse);
  return (float)(i2cResponse[6] * 256 + i2cResponse[7])/ 10;
}

float eee895_readTemp()
{
  uint8_t i2cResponse[8];
  eee895_read(i2cResponse);
  return (float)(i2cResponse[2] * 256 + i2cResponse[3])/100;
}

void eee895_read(uint8_t * i2cResponse)
{
  Wire.beginTransmission(eee895Adresse);
  Wire.write(0);                          // Register 0: CO2 high byte
  Wire.endTransmission(true);             // Stop-Bedingung

  Wire.requestFrom(eee895Adresse,8,true);
  uint8_t i=0;
  
  while (Wire.available())
  {
    i2cResponse[i++] = Wire.read();
  }
}