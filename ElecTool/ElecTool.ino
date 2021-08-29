#include "LIS3DHTR.h"
#include <Arduino.h>
#include <U8x8lib.h>

#include <Wire.h>
LIS3DHTR<TwoWire> LIS;
#define WIRE Wire

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

int x = 0, y = 0, ch = 0, lch = -1;
boolean f = false, goMenu = true;
long ps = 0, out;


void setup()
{
  pinMode(4,  OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(115200);


  LIS.begin(WIRE, 0x19);

  delay(100);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_4G);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  LIS.setHighSolution(true);

  u8x8.begin();
  u8x8.setPowerSave(0);

  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
  u8x8.drawString(0, 2, "Welcome");
  delay(1000);


}

int ct = 0;

void loop()
{


  while (!goMenu)
  {
    if (ch == 0)
    {
      digitalWrite(13, 0);
      u8x8.drawString(0, 2, "Level  ");
      level();
    }


    else if (ch == 1)
    {
      u8x8.drawString(0, 2, "Height ");
      u8x8.drawString(0, 6, "in cm  ");
      theodolite();
    }

    else if (ch == 2)
    {
      digitalWrite(13, 0);
      u8x8.drawString(0, 2, "Freq.  ");
      u8x8.drawString(0, 6, "in Hz  ");
      strob();
    }
      else if (ch == 3)
    {
      digitalWrite(13, 0);
      u8x8.drawString(0, 2, "HVac  ");
      u8x8.drawString(0, 6, "      ");
      liveWire();
    }
      

  }
  selectMenu();
 
}



char buf[10];
float xraw = 0, yraw = 0, zraw = 0, an0 = 0.0;
float ax = 0.0;

void level()
{
  float sum = 0;
  for (int i = 0; i < 100; i++)
  {
    xraw = xraw * 0.98 + 0.02 * LIS.getAccelerationX();
    yraw = yraw * 0.98 + 0.02 * LIS.getAccelerationY();
    zraw = zraw * 0.98 + 0.02 * LIS.getAccelerationZ();

    ax = ax * 0.98 + 0.02 * atan(xraw / sqrt((yraw * yraw) + (zraw * zraw))) ;
    sum += ax;
  }

  ax = sum / 100.0;
  ax -= 0.069;

  int incl = ax * 57.2957795;

  itoa(incl, buf, 10);

  Serial.println(ax);

  if (incl < 10 && ax >= 0)
  {
    buf[1] = ' ';
    buf[2] = ' ';
    buf[3] = ' ';
    buf[4] = ' ';
  }

  u8x8.drawString(0, 5, buf);




  out = millis();

  while (digitalRead(2))
  {
    if (millis() - out >= 3000)
    {
      goMenu = true;
      u8x8.drawString(0, 0, "Going   ");
      u8x8.drawString(0, 2, "back    ");
      u8x8.drawString(0, 4, "....    ");
      u8x8.drawString(0, 6, "        ");
      delay(2500);
      lch = -1;
      return;
    }
  }
}




void theodolite()
{
  digitalWrite(13, HIGH);
  float sum = 0;
  for (int i = 0; i < 100; i++)
  {
    xraw = xraw * 0.98 + 0.02 * LIS.getAccelerationX();
    yraw = yraw * 0.98 + 0.02 * LIS.getAccelerationY();
    zraw = zraw * 0.98 + 0.02 * LIS.getAccelerationZ();

    ax = ax * 0.98 + 0.02 * (xraw / sqrt((yraw * yraw) + (zraw * zraw))) ;

    sum += ax;
  }

  ax = sum / 100.0;
  ax -= 0.069;
  float height = ax * 100;

  itoa(height, buf, 10);
  if (height < 10 && ax >= 0)
  {
    buf[1] = ' ';
    buf[2] = ' ';
    buf[3] = ' ';
    buf[4] = ' ';
  }

  else if (height >= 10 && height <= 99)
  {
    buf[2] = ' ';
    buf[3] = ' ';
    buf[4] = ' ';
  }

  else if (height >= 100 && height <= 999)
  {
    buf[3] = ' ';
    buf[4] = ' ';
  }

  u8x8.drawString(0, 4, buf);
  Serial.println(ax);

  out = millis();

  while (digitalRead(2))
  {
    if (millis() - out >= 3000)
    {
      u8x8.drawString(0, 0, "Going   ");
      u8x8.drawString(0, 2, "back    ");
      u8x8.drawString(0, 4, "....    ");
      u8x8.drawString(0, 6, "        ");
      goMenu = true;
      delay(2500);
      lch = -1;
      return;
    }
  }

}


void strob()
{

while(1)
{
  digitalWrite(4, HIGH);
  delay(an0);
  
  an0 = analogRead(A0) / 4;
  
  digitalWrite(4, LOW);
  delay(an0);

  out = millis();

  while (digitalRead(2))
  {

    
    float temp=1/an0*2000;
    itoa(temp, buf, 10);

    if (temp < 10 && temp >= 0)
  {
    buf[1] = ' ';
    buf[2] = ' ';
    buf[3] = ' ';
    buf[4] = ' ';
  }

  else if (temp >= 10 && temp <= 99)
  {
    buf[2] = ' ';
    buf[3] = ' ';
    buf[4] = ' ';
  }

  else if (temp >= 100 && temp <= 999)
  {
    buf[3] = ' ';
    buf[4] = ' ';
  }
    
    u8x8.drawString(0, 4,buf);
    if (millis() - out >= 3000)
    {
      u8x8.drawString(0, 0, "Going   ");
      u8x8.drawString(0, 2, "back    ");
      u8x8.drawString(0, 4, "....    ");
      u8x8.drawString(0, 6, "        ");
      goMenu = true;
      delay(2500);
      lch = -1;
      return;
    }
  }
}

}

void liveWire()
{
  if(analogRead(A1)>2)
  {
    u8x8.drawString(0, 4, "Detected");
    digitalWrite(4,HIGH);
  }
  
  else
  {
    u8x8.drawString(0, 4, "--------");
     digitalWrite(4,LOW);
  }

  out = millis();

  while (digitalRead(2))
  {
    if (millis() - out >= 3000)
    {
      u8x8.drawString(0, 0, "Going   ");
      u8x8.drawString(0, 2, "back    ");
      u8x8.drawString(0, 4, "....    ");
      u8x8.drawString(0, 6, "        ");
      goMenu = true;
      delay(2500);
      lch = -1;
      return;
    }
  }

  
}




void selectMenu()
{
  ch = map(analogRead(A0), 0, 1020, 0, 3);
  Serial.println(ch);
  x = 0;
  y = 0;

  if (lch != ch)
  {
    if (ch == 0)
    {
      u8x8.drawString(0, 0, "Incl.  ");
      u8x8.drawString(0, 2, "Level  ");
    }

    else if (ch == 1)
    {
      u8x8.drawString(0, 0, "Measure ");
      u8x8.drawString(0, 2, "Height  ");
    }

    else if (ch == 2)
    {
      u8x8.drawString(0, 0, "Strob.  ");
      u8x8.drawString(0, 2, "        ");
      u8x8.drawString(0, 4, "        ");
      u8x8.drawString(0, 6, "        ");
    }

    else if (ch == 3)
    {
      u8x8.drawString(0, 0, "Live    ");
      u8x8.drawString(0, 2, "Wire    ");
      u8x8.drawString(0, 4, "        ");
      u8x8.drawString(0, 6, "        ");
    }

    lch = ch;
  }

  if (digitalRead(2) == 1)
  {
    u8x8.drawString(0, 0, "        ");
    u8x8.drawString(0, 2, "        ");
    goMenu = false;
    delay(100);
  }

  out = millis();
}
