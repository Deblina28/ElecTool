#include "LIS3DHTR.h"
#include <Arduino.h>
#include <U8x8lib.h>

#include <Wire.h>
LIS3DHTR<TwoWire> LIS; 
#define WIRE Wire

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

int x = 0, y = 0, ch=0, lch=-1;


void setup()
{
  pinMode(4,  OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);


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
  u8x8.drawString(0, 2, "Level  ");

}

int ct=0;

void loop()
{
  //rpm();
  
  //level();

  theodolite();
}



char buf[10];
float xraw = 0, yraw = 0, zraw = 0, an0=0.0;
float ax = 0.0;

void level()
{
  for (int i = 0; i < 100; i++)
  {
    xraw = xraw * 0.98 + 0.02 * LIS.getAccelerationX();
    yraw = yraw * 0.98 + 0.02 * LIS.getAccelerationY();
    zraw = zraw * 0.98 + 0.02 * LIS.getAccelerationZ();

    ax = ax * 0.98 + 0.02*atan(xraw / sqrt((yraw * yraw) + (zraw * zraw))) * 57.2957795;
  }

  itoa(ax, buf, 10);
  
  Serial.println(ax);
  
  if (ax < 10 && ax >= 0)
  {
    buf[1] = ' ';
    buf[2] = ' ';
    buf[3] = ' ';
    buf[4] = ' ';
  }

  u8x8.drawString(0, 5, buf);
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

    u8x8.drawString(0, 5, buf);
    Serial.println(ax);
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
}
}

