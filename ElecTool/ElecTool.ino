#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS; 
#define WIRE Wire


char buf[10];
float xraw = 0, yraw = 0, zraw = 0;
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


}
