#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int B1_A = 14;
const int B1_B = 4;

volatile uint16_t counts = 0;
uint16_t turns;

void IRAM_ATTR channelA_isr(void)
{
  counts++;
}

void setup()
{
  Wire.begin(21,22);
  lcd.init();
  lcd.clear();
  lcd.print("counts: ");
  lcd.setCursor(0,1);
  lcd.print("turns:  ");
  
  pinMode(B1_A,INPUT_PULLUP);
  pinMode(B1_B,INPUT_PULLUP);
  attachInterrupt(B1_A,channelA_isr,FALLING);  
}

void loop() 
{
  lcd.setCursor(7,0);
  sprintf(buf,"%5d",counts);
  lcd.print(buf);
  turns = counts/24;      //24 Impulse pro Umdrehung
  sprintf(buf,"%5d",turns);
  lcd.setCursor(7,1);
  lcd.print(buf);
}
