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
  Serial.begin(9600);
}

void loop() 
{
  float hum  = dht.readHumidity();
  float temp = dht.readTemperature();
 
  // lcd.setCursor(0,0);
  // lcd.print("Temp:    ");lcd.print(temp);lcd.print("\337");lcd.print("C");
  // lcd.setCursor(0,1);
  // lcd.print("Feuchte: ");lcd.print(hum);lcd.print("%");

  lcd.setCursor(0,0);
  lcd.printf("Temp:   %4.1f\337C",temp);
  lcd.setCursor(0,1);
  lcd.printf("Feuchte: %3.0f%%",hum);

  Serial.printf("Temp:   %4.1f°C\n",temp);
  Serial.printf("Feuchte: %3.0f%%\n",hum);
  delay(500);
}
