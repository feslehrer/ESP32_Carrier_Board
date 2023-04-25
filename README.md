# ESP32_Carrier_Board
 Funktionssammlung für ESP32-Carrier-Board
![grafik](https://user-images.githubusercontent.com/24614659/197691402-ae8d4d87-3673-4bed-a442-19f261159832.png)
https://www.ase-elektronik.de

 Funktionsprototypen
--------------------------------------------------------------------
pinToggle wertet einen Tastendruck (polling) am pin aus und
liefert ein entprelltes Tastersignal zurück.
Die Variable toggleState muss als Zeiger übergeben werden und
kann als Schaltsignal ausgewertet werden.

bool pinToggle(int pin, bool *toggleState);


lm75_read liefert den Temperaturwert des auf dem Carrier-Board
verbauten LM75-Temperatursensors als float-Wert -55 ... 125°C zurück.

float lm75_read(void);
