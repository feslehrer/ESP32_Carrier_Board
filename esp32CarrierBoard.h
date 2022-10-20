/*
    Bibliothek für ESP32-Carrier-Board von AS-Elektronik
    www.ase-schlierbach.de

    Autor: Rahm, R.
    Datum:           20.10.2022
    letzte Änderung: 20.10.2022
*/
#ifndef _ESP32CARRIERBOARD_H_
#define _ESP32CARRIERBOARD_H_
#include "Arduino.h"

#define PRESS   LOW            // Symbol für gedrückten Taster
                               // LOW = Nullaktiv, HIGH = Einsaktiv                   
#define DEBOUNCETIME 50        // Hier die Entprellzeit in ms

#define TASTERPINS {5,23,19,18}     // Tasterpins am ESP32-Carrier-Board
#define PINANZAHL   4               // muss mit der Anzahl der Tasterpins übereinstimmen.

// Funktionsprototypen
//--------------------------------------------------------------------
// pinToggle wertet einen Tastendruck (polling) am pin aus und
// liefert ein entprelltes Tastersignal zurück.
// Die Variable toggleState muss als Zeiger übergeben werden und
// kann als Schaltsignal ausgewertet werden. Im debounceTimer werden 
// Impulsdauern gespeichert.
// Example: 
//  #include <esp32CarrierBoard.h>
//  uint32_t toggleStateS3;
//  const int TasterS3 = 19;
//
//  void setup()
//  { ...
//    pinMode(TasterS3,INPUT_PULLUP);
//    ...
//  }
//
//  uint16_t count = 0;
//
//  void loop()
//  {
//    if(pinToggle(TasterS3, &toggleStateS3) == PRESS)
//      count++;
//    
//  }
bool pinToggle(int pin, bool *toggleState); 

#endif
