// pinToggle:  Schalten und Entprellen von Tastern
//         pin: Pinnummer des zu Input-Pins
//         toggleState: Schaltzustand des Toggle-Glieds (entprellt)
//         debounceTimer: Zeit der letzten Flankenerkennung
//      Rückgabewert: Tastersignal entprellt
#include "esp32CarrierBoard.h"

bool pinToggle(int pin, bool *toggleState) 
{
  uint8_t i;
  uint8_t z = (uint8_t) sizeof(debounceTimer)/4;

  for (i=0; i<z; i++)
    if(pins[i]== pin) break;
    
  bool pinState = !PRESS;
  uint32_t newTime = millis();
  
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
