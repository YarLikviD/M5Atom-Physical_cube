// Controller used m5stack MATRIX
// Created by YarLikViD

#include "M5Atom.h"
#include "config.h"
float accX = 0, accY = 0, accZ = 0; // Accelerometer accelerations
int led_x, led_y;

int deltaTime = 0;

void pixelsHandler(Pixel &pixel)
{
}

void calcCollision(Pixel &pixel)
{
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

  calcCollision(pixel);
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
    pixelsHandler(pixel);
    calcSpeedPos(pixel);
    posToLEDPos(pixel);
    M5.dis.drawpix(led_x, led_y, pixel.color);
  }
}

void loop()
{
  int t = millis();
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  draw();
  delay(10);
  deltaTime = millis() - t;
  // Serial.println(deltaTime);
}
