// pinToggle:  Schalten und Entprellen von Tastern
//         pin: Pinnummer des zu Input-Pins
//         toggleState: Schaltzustand des Toggle-Glieds (entprellt)
//         debounceTimer: Zeit der letzten Flankenerkennung
//      Rückgabewert: Tastersignal entprellt
#include "esp32CarrierBoard.h"
#include "Arduino.h"

int pins[] = TASTERPINS;            // ESP32-Carrier-Board Tasterpins
uint64_t debounceTimer[PINANZAHL];  // PINANZAHL muss mit der Anzahl der Tasterpins
                                    // übereinstimmen.

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
