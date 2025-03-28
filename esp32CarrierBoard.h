/*
    Bibliothek für ESP32-Carrier-Board von AS-Elektronik
    www.ase-schlierbach.de

    Autor: Rahm, R.
    Datum:           20.10.2022
    letzte Änderung: 16.01.2025
*/
#ifndef _ESP32CARRIERBOARD_H_
#define _ESP32CARRIERBOARD_H_
#include "Arduino.h"

#define PRESS    LOW            // Symbol für gedrückten Taster
#define RELEASE HIGH           // LOW = Nullaktiv, HIGH = Einsaktiv
#define ON		 LOW			// Symbol für Ausgangssignal (z.B. LED)
#define OFF		 HIGH			// Nullaktiv: ON = LOW, OFF = HIGH
							   
#define DEBOUNCETIME 50         // Hier die Entprellzeit in ms

#define TASTERPINS {5,23,19,18} // Tasterpins am ESP32-Carrier-Board
#define PINANZAHL   4           // muss mit der Anzahl der Tasterpins übereinstimmen.

#define lm75Adresse   0x48      // I2C-Adresse fuer LM75 auf dem Carrier-Board
#define eee895Adresse 0x5E      // I2C-Adresse EE895 (simplified protocol)

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
#define A0 38			// A0...A3 sind ausschließlich als
#define A1 37			// Analogeingänge nutzbar !!
#define A2 35
#define A3 34
//#define A4 36			// Nur als Binäre Inputs zu verwenden !!
//#define A5 39			// dito.

#define LED_BUILDIN 12

#define S1  5
#define S2  23
#define S3  19
#define S4  18
#define SPEAKER 27
#define BACKLIGHT 2
#define POTI A3
#define LDR  A3 

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
void  lm75_init(byte _i2_adress_);
float lm75_read(byte _i2_adress_) ;

// fMap: Zur Bereichsanpassung von float-Werten.
// Bsp.: Mappen der Analog-Spannung vom Carrier-Board (5V) zum
//       3,3V-ADC-Eingang des ESP32
//       const float Ulsb = 3.3/pow(2,12); 
//       float spannung = fMap(Ulsb * analogRead(A3), 0.0, 3.3, 0.0, 5.0);
 float fMap(float x, float x_min, float x_max, float y_min, float y_max);

// CO2-Sensor EEE895
//uint8_t i2cResponse[8];

void  eee895_init(void);
void eee895_read(uint8_t * i2cResponse);
uint16_t eee895_readCO2(void);
uint16_t eee895_readPressure(void);
float eee895_readTemp(void);


#endif
