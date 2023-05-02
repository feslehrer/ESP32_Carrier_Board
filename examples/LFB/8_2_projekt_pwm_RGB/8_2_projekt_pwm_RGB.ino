#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Pins für die LEDs:
const int redPin = 32;
const int greenPin = 13;
const int bluePin = 15;

#define ROT 1
#define GRUEN 2
#define BLAU 3

void setup() 
{
  SerialBT.begin("ESPRahm");
  SerialBT.setTimeout(100);          //Jetzt wird bei serial.readString() max.
                                     //100 ms (statt 1000 ms) auf Stringende gewartet.
                                     //nicht notwendig aber bessere "User-Experience".
  //Serial.begin(9600);
  //Serial.setTimeout(100);  
        
  // PWM-Initialisieren für RGB-LED
  ledcSetup(ROT, 1000, 8);        // (Kanal, Frequenz, Auflösung)
  ledcSetup(GRUEN, 1000, 8);
  ledcSetup(BLAU, 1000, 8);
  ledcAttachPin(redPin, ROT);     // Pin mit Kanal verbinden
  ledcAttachPin(greenPin, GRUEN);
  ledcAttachPin(bluePin, BLAU);
  ledcWrite(ROT, 0);              // LED ausschalten (Kanal,Tastgrad)
  ledcWrite(GRUEN, 0);
  ledcWrite(BLAU, 0);
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
          ledcWrite(ROT, red);
          break;
          
      case 'g':
      case 'G':
          green = SerialBT.parseInt(); 
          green = constrain(green, 0, 255);
          ledcWrite(GRUEN, green);
          break; 

      case 'b':
      case 'B':
          blue = SerialBT.parseInt();
          blue = constrain(blue, 0, 255);
          ledcWrite(BLAU, blue);   
          break;
      
      case 'e':
      case 'E':
          ledcWrite(ROT, red);              // RGB einschalten
          ledcWrite(GRUEN, green);
          ledcWrite(BLAU, blue);
          break;
          
      case 'a':
      case 'A':
          ledcWrite(ROT, 0);              // RGB ausschalten
          ledcWrite(GRUEN, 0);
          ledcWrite(BLAU, 0);
          break;
          
      default: break;
    }
  }
}
