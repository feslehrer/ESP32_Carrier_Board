#include <esp32CarrierBoard.h>
//#include "BluetoothSerial.h"
//BluetoothSerial SerialBT;

// Pins für die LEDs:
const int redPin = 32;
const int greenPin = 13;
const int bluePin = 15;

void setup() 
{
  //SerialBT.begin("MeinESP#01");
  //SerialBT.setTimeout(100);
  Serial.begin(9600);
  
  // PWM-Initialisieren für RGB-LED
  ledcAttach(redPin, 1000, 8);          // Pin mit Kanal verbinden
  ledcAttach(greenPin, 1000, 8);
  ledcAttach(bluePin, 1000, 8);
}

int red, green, blue;

void loop()
{
  while (Serial.available() > 0)     //Für BT-Steuerung im folgenden "Serial" durch "SerialBT" ersetzen.
  {
    int c = Serial.read();

    switch (c)
    {
      case 'r':
      case 'R':
          red = Serial.parseInt(); 
          red = constrain(red, 0, 255);     // Begrenzung
          ledcWrite(redPin, red);
          break;
          
      case 'g':
      case 'G':
          green = Serial.parseInt(); 
          green = constrain(green, 0, 255);
          ledcWrite(greenPin, green);
          break; 

      case 'b':
      case 'B':
          blue = Serial.parseInt();
          blue = constrain(blue, 0, 255);
          ledcWrite(bluePin, blue);   
          break;

      case 'e':
      case 'E':
          ledcWrite(redPin, red);              // RGB einschalten
          ledcWrite(greenPin, green);
          ledcWrite(bluePin, blue);
          break;
          
      case 'a':
      case 'A':
          ledcWrite(redPin, 0);              // RGB ausschalten
          ledcWrite(greenPin, 0);
          ledcWrite(bluePin, 0);
          break;
          
      default: break;
    }
  }
}
