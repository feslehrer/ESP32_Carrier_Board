#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <DHT.h>                // Temperatur/Luftfeuchte-Sensor
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  lcd.init();
  lcd.clear();
  dht.begin();
}

void loop() 
{
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();
 
  lcd.setCursor(0,0);
  lcd.print("Temp:    ");lcd.print(temp);lcd.print("\337");lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Feuchte: ");lcd.print(hum);lcd.print("%");
}
