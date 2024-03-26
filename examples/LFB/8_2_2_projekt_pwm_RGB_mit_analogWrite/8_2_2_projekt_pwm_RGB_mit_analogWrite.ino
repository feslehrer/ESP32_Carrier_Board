#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Pins für die LEDs:
const int redPin = 32;
const int greenPin = 13;
const int bluePin = 15;

void setup()
{
  SerialBT.begin("ESPRahm");      // Hier eindeutigen Namen vergeben
  SerialBT.setTimeout(100);
}

int red, green, blue;

void loop()
{
  while (SerialBT.available() > 0)
  {
    int c = SerialBT.read();
    //SerialBT.write(c);        //Echo

    switch (c)
    {
      case 'r':
      case 'R':
          red = SerialBT.parseInt(); 
          red = constrain(red, 0, 255);     // Begrenzung
          analogWrite(redPin, red);
          break;
          
      case 'g':
      case 'G':
          green = SerialBT.parseInt(); 
          green = constrain(green, 0, 255);
          analogWrite(greenPin, green);
          break;

      case 'b':
      case 'B':
          blue = SerialBT.parseInt();
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
