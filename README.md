# ESP32-Carrier-Board
## Funktionssammlung für ESP32-Carrier-Board
<img src="https://user-images.githubusercontent.com/24614659/235747329-3b294437-124a-4d40-9fe2-bfb1395ae811.jpg" alt="ESP32-Carrier-Board" width="600">
https://www.ase-schlierbach.de

## Taster-Auswertung mit Entprellung

### Prototypen:
```c
bool pinToggle(int pin, bool *toggleState);
```

### Beschreibung:
**pinToggle()** wertet einen Tastendruck (polling) am pin aus und
liefert ein entprelltes Tastersignal zurück.
Die Variable **toggleState** muss als Zeiger übergeben werden und
kann als Schaltsignal ausgewertet werden.

### Beispiel: 
```c
  #include <esp32CarrierBoard.h>
  bool toggleStateS3;
  const int TasterS3 = 19;

  void setup()
  { 
    pinMode(TasterS3,INPUT_PULLUP);
  }

  uint16_t count = 0;

  void loop()
  {
    if(pinToggle(TasterS3, &toggleStateS3) == PRESS)
      count++;  
  }
 ```

## LM75-Temperatursensor (I²C)
### Prototypen:
```c
void  lm75_init(void);
float lm75_read(void);
```

### Beschreibung:
**lm75_read()** liefert den Temperaturwert des auf dem Carrier-Board verbauten LM75-Temperatursensors als float-Wert -55 ... 125°C zurück.
Die i2c_adresse ist 0x48 und in der Konstanten **SensorAdresse** definiert. 
**lm75_init()** muss 1 mal in der **setup()** aufgerufen werden.

### Beispiel:
```c
#include <esp32CarrierBoard.h>
void setup()
{
  lm75_init();
}

void loop()
{
  float cTemp = lm75_read();
}
```
## Mapping von float-Werten
### Prototypen:
```c
float  fMap(float x, float x_min, float x_max, float y_min, float y_max);
```

### Beschreibung:
**fMap()** Führt eine Bereichsanpassung von float-Werten, ähnlich zur Arduino map()-Funktion für Integer, durch.
Benötigt wird die Funktion z.B. im Zusammenhang mit dem ADC-Eingang am Carrier-Board.
Die 5V-ADC-Eingänge des Carrierboards werden durch einen Spannungsteiler auf max. 3,3V herunter geteilt. Benötigt man den exakten Spannungswert, muss man von 3.3V auf 5.0V hochrechnen.
![grafik](https://github.com/user-attachments/assets/95c898c3-26c8-4781-a92a-2a5c2b8feb54)
<img src="https://github.com/user-attachments/assets/95c898c3-26c8-4781-a92a-2a5c2b8feb54.jpg" alt="Kennlinie" width="300">
Parameter: 
```c
float x:       Quellwert
float x_min:   Unterer Grenzwert Quelle
float x_max:   Oberer Grenzwert Quelle
float y_min:   Unterer Grenzwert Ziel
float y_max:   Oberer Grenzwert Ziel
```

### Beispiel:
```c
#include <esp32CarrierBoard.h>
// Spannungsauflösung des ADC
const float Ulsb = 3.3/pow(2,12);
char buf[17];

void loop()
{ // Die Analogspannung wird vom Carrierboard von 5V auf 3.3V heruntergeteilt.
  // Messen und Berechnen der Spannung und Bereichsanpassung 3.3V --> 5V.
  float spannung = fMap(Ulsb * analogRead(A3), 0.0, 3.3, 0.0, 5.0);
  sprintf(buf,"U = %4.2fV\n",spannung);
  Serial.print(buf);
  delay(200);
}
```

## EEE895-CO2-Sensor für CO2-Sensor-Ampel-Shield
<img src="https://user-images.githubusercontent.com/24614659/234347802-9cfc7fbd-2dfb-4f09-8f7a-93c3eb24550e.jpg" alt="CO2-Sensor-Ampel" width="600">

Mit dem EEE895 wird die CO2-Konzentration, die Temperatur und Druck gemessen.
<br>https://www.epluse.com/de/produkte/co2-messung/co2-module-und-fuehler/ee895/ 

### Prototypen:
```c
void  eee895_init(void);
uint16_t eee895_readCO2(void);
uint16_t eee895_readPressure(void);
float eee895_readTemp(void);
```

### Beschreibung:

**eee895_init()** muss 1 mal in der **setup()** aufgerufen werden.
+ CO2-Wert: 0 ... 5000 ppm (+-50ppm+-3%)
+ Pressure: 700 ... 1100 mbar (+-2mbar)
+ Temperatur:  -40°C ... 60°C (+-0,5K)

Die WS2812 (Neopixel) liegen an GPIO 13 und können mit der **Adafruit_Neopixel**-Bibliothek programmiert werden.
  
### Beispiel:
```c
#include <esp32CarrierBoard.h>

void setup()
{
  ee895_init();
}

void loop()
{
  uint16_t co2 = eee895_readCO2();
  uint16_t pressure = eee895_readPressure();
  float cTemp = eee895_readTemp();
}
```
