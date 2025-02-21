
#include "esp32CarrierBoard.h"
#include "Arduino.h"
#include <Wire.h>

int pins[] = TASTERPINS;            // ESP32-Carrier-Board Tasterpins
uint64_t oldTime[PINANZAHL];        // PINANZAHL muss mit der Anzahl der Tasterpins
                                    // übereinstimmen (in esp32CarrierBoard.h).

// pinToggle:  Schalten und Entprellen von Tastern
//         pin: Pinnummer des Input-Pins
//         toggleState:   Schaltzustand des Toggle-Glieds (entprellt)
//         debounceTimer: Zeit der letzten Flankenerkennung
//      Rückgabewert: Tastersignal entprellt
bool pinToggle(int pin, bool *toggleState) 
{
  int i;
  
  for (i=0; i<PINANZAHL; i++)
    if(pins[i]== pin) break;
    
  bool pinState = !PRESS;
  uint64_t newTime = millis();
  
  if (digitalRead(pin) == PRESS)
  {
    if(newTime - oldTime[i] > DEBOUNCETIME)
    {
      *toggleState = !*toggleState;
      pinState = PRESS;
    }
    oldTime[i] = newTime;
  }
  return pinState;
}

void lm75_init(byte _i2_adress_)
{
  Wire.begin();
  Wire.beginTransmission(_i2_adress_);  
  Wire.write(0);       
  Wire.endTransmission();  
}

// lm75_read:  Liest den Temperaturwert vom LM75 auf dem Carrier_Board
//      Rückgabewert: Temperaturwert als float -55.0 ... +125.0 (°C)
//      Die Auflösung beträgt 0,5°C
float lm75_read(byte _i2_adress_) 
{
  byte msb=0, lsb=0, msb1=0;
  
  Wire.requestFrom(_i2_adress_, 2); 
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

// fMap: Zur Bereichsanpassung von float-Werten.
// Bsp.: Mappen der Analog-Spannung vom Carrier-Board (5V) zum
//       3,3V-ADC-Eingang des ESP32
//       const float Ulsb = 3.3/pow(2,12); 
//       float spannung = fMap(Ulsb * analogRead(A3), 0.0, 3.3, 0.0, 5.0);
float fMap(float x, float x_min, float x_max, float y_min, float y_max)
{
  float y;
  y = (y_max-y_min)/(x_max-x_min);
  y = y *(x-x_min) + y_min;  

  return y;
}

// CO2-Sensor EEE895
//uint8_t i2cResponse[8];
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
