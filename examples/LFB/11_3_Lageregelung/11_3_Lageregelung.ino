#include <esp32CarrierBoard.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int B1_A = 14;
const int B1_B = 4;
const int RESET = S1;
const int DIR = S3;
const int REF = S4;

const int PWM_PIN = 23;
const int PWM_FREQ = 500; 
const int PWM_RESOLUTION = 12; 
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1);

volatile int16_t counts = 0;

uint8_t m = 8;            // 8 Impulse (counts) pro mm

#define KP 400.0

#define LINKS  0
#define RECHTS 1

float Regler( float w, float x, float kp);
void  setMotor( float y);

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
  Serial.begin(9600);

  lcd.init();
  lcd.clear();
  lcd.print("Ist: ");
  lcd.setCursor(0,1);
  lcd.print("Soll:");

  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);     //GPIO 12
  
  pinMode(B1_A,INPUT_PULLUP);
  pinMode(B1_B,INPUT_PULLUP);
  pinMode(RESET,INPUT_PULLUP);
  pinMode(REF,INPUT_PULLUP);
  pinMode(DIR,OUTPUT);
  attachInterrupt(B1_A,channelA_isr,CHANGE);  
  attachInterrupt(B1_B,channelB_isr,CHANGE);  
}

char buf[16];

void loop() 
{
  float soll, ist, yr;

  soll = analogRead(34) & 0x0ff0;        // 12-Bit: 0...4096
                                         // 3*LSB ausmaskiert 
  soll = soll * 120.0 / 4095.0;          // xmax = 120mm
  //Runden auf Vielfache von 0,125mm = 4Q-Sensorauflösung
  int ftemp = soll / 0.125;
  soll = 0.125 * ftemp;

  ist = (float) counts;
  ist = ist / m;         //m: counts pro mm

  if (digitalRead(RESET) == LOW)
  {
    Serial.println("Reset");
    counts = 0; ist = 0.0;
  }

  if(digitalRead(REF) == LOW)
  {
    digitalWrite(DIR,LINKS);
    ledcWrite(PWM_PIN,MAX_DUTY_CYCLE);   // Full Speed Links
  }
  else
  {
    yr = Regler(soll,ist,KP);
    setMotor(yr);
  }
  lcd.setCursor(6,0);   
  sprintf(buf,"%5.3f mm  ",ist);
  lcd.print(buf);

  sprintf(buf,"%5.3f mm  ",soll);
  lcd.setCursor(6,1);
  lcd.print(buf);
}

float Regler( float w, float x, float kp)
{
  float e = w-x;
  float yp = e*kp;

  if (yp<0.0)
  {
    digitalWrite(DIR,LINKS);
    yp = -yp;
  }
  else
  {
    digitalWrite(DIR,RECHTS);
  }
  Serial.println(yp);

  if(yp<15.0)        return 0.0;        // 
  else if(yp<1200.0) return 1200.0;     // Losbrechmoment überwinden!
  else if(yp>MAX_DUTY_CYCLE) return MAX_DUTY_CYCLE;     // Begrenzung  100%
  else               return yp;
}

void setMotor( float y)
{
  if ( y == 0.0 )   ledcWrite(PWM_PIN,0);
  else              ledcWrite(PWM_PIN,y);
}
