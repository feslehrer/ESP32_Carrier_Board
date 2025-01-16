#include <esp32CarrierBoard.h>
//#include "BluetoothSerial.h"
//BluetoothSerial SerialBT;
// Für Blutooth Serial durch SerialBT ersetzen

// GPIO's für die LEDs:
const int redPin = 32;
const int greenPin = 13;
const int bluePin = 15;

void setup()
{
  //SerialBT.begin("MeinESP31#01");  //Eindeutiger Name für Bluetooth
  Serial.begin(9600);
  Serial.setTimeout(100);
  analogWriteResolution(redPin,8);  analogWriteFrequency(redPin,12000);
  analogWriteResolution(greenPin,8);  analogWriteFrequency(greenPin,12000);
  analogWriteResolution(bluePin,8);  analogWriteFrequency(bluePin,12000);
}

int red, green, blue;

void loop()
{
  while (Serial.available() > 0)
  {
    int c = Serial.read();

    switch (c)
    {
      case 'r':
      case 'R':
          red = Serial.parseInt(); 
          red = constrain(red, 0, 255);     // Begrenzung
          analogWrite(redPin, red);
          break;
          
      case 'g':
      case 'G':
          green = Serial.parseInt(); 
          green = constrain(green, 0, 255);
          analogWrite(greenPin, green);
          break;

      case 'b':
      case 'B':
          blue = Serial.parseInt();
          blue = constrain(blue, 0, 255);
          analogWrite(bluePin, blue);
          break;
      
      case 'e':
      case 'E':
          analogWrite(redPin, red);              // RGB einschalten
          analogWrite(greenPin, green);
          analogWrite(bluePin, blue);
          break;
          
      case 'a':
      case 'A':
          analogWrite(redPin, 0);              // RGB ausschalten
          analogWrite(greenPin, 0);
          analogWrite(bluePin, 0);
          break;
      default: break;
    }
  }
}
