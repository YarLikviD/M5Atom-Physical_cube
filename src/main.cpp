// Controller used m5stack MATRIX
// The time delta is not used for speed synchronization
// Created by YarLikViD

#include "M5Atom.h"
float accX = 0, accY = 0, accZ = 0; // Accelerometer accelerations

float x_limit = 20, y_limit = 20;

float speedLimit = 5; // set the speed limit

int led_x, led_y;

struct Pixel
{
  float x;
  float y;

  float x_speed;
  float y_speed;

  float elasticity;
  int color;
};

//You can set multiple pixels
Pixel pixels[1] = {
    {10, 10, 0, 0, 0.80, 0xFF0000},
};

void calcSpeedPos(Pixel &pixel)
{

  // Speed calculation
  pixel.x_speed += accX;
  pixel.y_speed += accY;

  if (pixel.x_speed > speedLimit)
  {
    pixel.x_speed = speedLimit;
  }
  if (pixel.y_speed > speedLimit)
  {
    pixel.y_speed = speedLimit;
  }

  // Calculating the position
  pixel.x += pixel.x_speed;
  pixel.y += pixel.y_speed;

  if (pixel.x > x_limit || pixel.x < (-x_limit))
  {
    pixel.x_speed *= -1 * pixel.elasticity;
  }

  if (pixel.y > y_limit || pixel.y < (-y_limit))
  {
    pixel.y_speed *= -1 * pixel.elasticity;
  }

  // limit positions
  pixel.x = (pixel.x > x_limit) ? x_limit : pixel.x;
  pixel.x = (pixel.x < -x_limit) ? -x_limit : pixel.x;

  pixel.y = (pixel.y > y_limit) ? y_limit : pixel.y;
  pixel.y = (pixel.y < -y_limit) ? -y_limit : pixel.y;
}

void posToLEDPos(Pixel &pixel)
{
  led_x = (pixel.x + 20) / 10;
  led_y = (pixel.y + 20) / 10;
}

void setup()
{
  Serial.begin(115200);
  M5.begin(true, true, true); //Init Atom-Matrix(Initialize serial port, LED matrix).
  M5.IMU.Init();              //Init IMU sensor.
}

void draw()
{
  M5.dis.fillpix(0x000000);
  for (auto &pixel : pixels)
  {
    calcSpeedPos(pixel);
    posToLEDPos(pixel);
    M5.dis.drawpix(led_x, led_y, pixel.color);
  }
}

void loop()
{
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  draw();
  delay(10);
}
