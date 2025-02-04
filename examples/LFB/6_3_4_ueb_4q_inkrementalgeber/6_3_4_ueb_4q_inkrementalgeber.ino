#include <esp32CarrierBoard.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int B1_A = D2;   //GPIO 14
const int B1_B = D3;   //GPIO 4
const int RESET = S1;  //GPIO 5

volatile int16_t counts = 0;
float pos;

void IRAM_ATTR channelA_isr(void)
{
  if (digitalRead(B1_A) == LOW)
  {  // Interrupt bei fallender Flanke an A
    if (digitalRead(B1_B) == HIGH)
      counts--;
    else  
      counts++;
  }
  else
  {  //Interrupt bei steigender Flanke an A
    if (digitalRead(B1_B) == LOW)
      counts--;
    else  
      counts++;
  }
}

void IRAM_ATTR channelB_isr(void)
{
  if (digitalRead(B1_B) == LOW)
  { // Interrupt bei fallender Flanke an B
    if (digitalRead(B1_A) == LOW)
      counts--;
    else
      counts++;
  }
  else   
  {  //Interrupt bei steigender Flanke an B
    if (digitalRead(B1_A) == HIGH)
      counts--;
    else
      counts++;
  }
}

void setup()
{
  Wire.begin(21,22);
  lcd.init();
  lcd.clear();
  lcd.print("counts: ");
  lcd.setCursor(0,1);
  lcd.print("Pos:  ");
  
  pinMode(B1_A,INPUT_PULLUP);
  pinMode(B1_B,INPUT_PULLUP);
  pinMode(RESET,INPUT_PULLUP);
  attachInterrupt(B1_A,channelA_isr,CHANGE);  
  attachInterrupt(B1_B,channelB_isr,CHANGE);  
}

char buf[10];
void loop() 
{
  if (digitalRead(RESET) == LOW)
  {
    counts = 0; pos = 0;
  }
  lcd.setCursor(7,0);
  sprintf(buf,"%5d",counts);
  lcd.print(buf);
  pos = (float)counts/8;      //8 Impulse pro mm
  sprintf(buf,"%6.3f mm",pos);
  lcd.setCursor(7,1);
  lcd.print(buf);
}
