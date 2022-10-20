# ESP32_Carrier_Board
 Funktionssammlung für ESP32-Carrier-Board

 Funktionsprototypen
--------------------------------------------------------------------
pinToggle wertet einen Tastendruck (polling) am pin aus und
liefert ein entprelltes Tastersignal zurück.
Die Variable toggleState muss als Zeiger übergeben werden und
kann als Schaltsignal ausgewertet werden.

bool pinToggle(int pin, bool *toggleState);
