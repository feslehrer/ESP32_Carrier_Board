
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