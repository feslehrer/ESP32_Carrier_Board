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

#define SensorAdresse 0x48      // I2C-Adresse fuer LM75 auf dem Carrier-Board

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

//lm75_read
// Gibt den Temperaturwert vom LM75 auf dem Carrier-Board zurück
float lm75_read(uint8_t i2c_adresse) ;
void  lm75_init(void);

// Pindefinitionen
#define D0 9
#define D1 10
#define D2 14
#define D3 4
#define D4 33
#define D5 15
#define D6 13
#define D7 32
#define D8 2
#define D9 27
#define D10 5
#define D11 23
#define D12 19
#define D13 18
#define A0 38
#define A1 37
#define A2 35
#define A3 34
#define A4 36
#define A5 39

#define LED_BUILDIN 12

#endif
