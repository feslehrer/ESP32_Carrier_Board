# ESP32_Carrier_Board
 Funktionssammlung für ESP32-Carrier-Board
![grafik](https://user-images.githubusercontent.com/24614659/197691402-ae8d4d87-3673-4bed-a442-19f261159832.png)
https://www.ase-elektronik.de

-------------------------------------------------------------------
*** Taster-Auswertung mit Entprellung ***

Prototypen:
<br>   bool pinToggle(int pin, bool *toggleState);

Beschreibung:
<br>pinToggle wertet einen Tastendruck (polling) am pin aus und
liefert ein entprelltes Tastersignal zurück.
<br>Die Variable toggleState muss als Zeiger übergeben werden und
kann als Schaltsignal ausgewertet werden.

Beispiel: 
  <br>#include <esp32CarrierBoard.h>
  <br>uint32_t toggleStateS3;
  <br>const int TasterS3 = 19;

  <br>void setup()
  <br>{ ...
   <br> pinMode(TasterS3,INPUT_PULLUP);
   <br> ...
  <br>}

 <br> uint16_t count = 0;

  <br>void loop()
  <br>{
    <br>if(pinToggle(TasterS3, &toggleStateS3) == PRESS)
      <br>count++;  
  <br>}

*** LM75-Temperatursensor (I²C) ***
<br>Prototypen:
<br>    void  lm75_init(void);
<br>    float lm75_read(uint8_t i2c_adresse);
 
Beschreibung:
<br>lm75_read liefert den Temperaturwert des auf dem Carrier-Board
<br>verbauten LM75-Temperatursensors als float-Wert -55 ... 125°C zurück.
<br>Die i2c_adresse ist 0x48 und in der Konstanten SensorAdresse definiert.
<br>lm75_init muss 1 mal in der setup() aufgerufen werden.

Beispiel: 
<br>  #include <esp32CarrierBoard.h>

<br>  void setup()
<br>    ...
<br>    lm75_init();
<br>    ...
<br>  }

<br>  void loop()
<br>  {
<br>    ...
<br>    float cTemp = lm75_read(SensorAdresse);
<br>    ...
<br>  }

# EEE895-CO2-Sensor für CO2-Sensor-Ampel-Shield
<br>![20230425_184724](https://user-images.githubusercontent.com/24614659/234347802-9cfc7fbd-2dfb-4f09-8f7a-93c3eb24550e.jpg)

<br>Mit dem EEE895 wird die CO2-Konzentration, die Temperatur und Druck gemessen.
<br>https://www.epluse.com/de/produkte/co2-messung/co2-module-und-fuehler/ee895/ 

Prototypen:
<br>  void  eee895_init(void);
<br>  uint16_t eee895_readCO2(void);
<br>  uint16_t eee895_readPressure(void);
<br>  float eee895_readTemp(void); 

Beschreibung:
<br>  eee895_init muss 1 mal in der setup() aufgerufen werden.
<br>  CO2-Wert: 0 ... 5000 ppm (+-50ppm+-3%)
<br>  Pressure: 700 ... 1100 mbar (+-2mbar)
<br>  Temperatur:  -40°C ... 60°C (+-0,5K)
  
Beispiel: 
<br>  #include <esp32CarrierBoard.h>

<br>  void setup()
<br>  { ...
<br>    ee895_init();
<br>    ...
<br>  }

<br> void loop()<br>
<br>  { ...
<br>    uint16_t co2 = eee895_readCO2();
<br>    uint16_t pressure = eee895_readPressure();
<br>    float cTemp = eee895_readTemp();
<br>    ...
<br>  }
