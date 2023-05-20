#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>
#include <trig.h>
#include <lineDetection.h>
#include <motor.h>

class Defense
{
public:
    Defense();
    double defense(double ballAngle, double goalAngle);

private:
  

};