#include <esp32CarrierBoard.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  uint16_t wert = analogRead(A3);  // A3 = GPIO 34
  Serial.print(wert);
  Serial.print(" -> ");

  float spannung = 0.0008057 * (float)wert;
  Serial.print(spannung); Serial.println("V");

  delay(50);
}
