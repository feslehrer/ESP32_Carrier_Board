#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Pins für die LEDs:
const int redPin = 32;
const int greenPin = 13;
const int bluePin = 15;

void setup() 
{
  SerialBT.begin("MeinESP#01");
  SerialBT.setTimeout(100);          //Jetzt wird bei serial.readString() max.
                                     //100 ms (statt 1000 ms) auf Stringende gewartet.
                                     //nicht notwendig aber bessere "User-Experience".
  //Serial.begin(9600);
  //Serial.setTimeout(100);  
        
  // PWM-Initialisieren für RGB-LED
  ledcAttach(redPin, 1000, 8);     // Pin mit Kanal verbinden
  ledcAttach(greenPin, 1000, 8);
  ledcAttach(bluePin, 1000, 8);
 // ledcWrite(redPin, 0);              // LED ausschalten (Kanal,Tastgrad)
 // ledcWrite(greenPin, 0);
 // ledcWrite(bluePin, 0);
}

int red, green, blue;

void loop()
{
  while (SerialBT.available() > 0)
  {
    int c = SerialBT.read();

    switch (c)
    {
      case 'r':
      case 'R':
          red = SerialBT.parseInt(); 
          red = constrain(red, 0, 255);     // Begrenzung
          ledcWrite(redPin, red);
          break;
          
      case 'g':
      case 'G':
          green = SerialBT.parseInt(); 
          green = constrain(green, 0, 255);
          ledcWrite(greenPin, green);
          break; 

      case 'b':
      case 'B':
          blue = SerialBT.parseInt();
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
