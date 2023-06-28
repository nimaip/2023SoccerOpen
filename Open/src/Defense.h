#ifndef DEFENSE_H
#define DEFENSE_H

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
    void defense(double ballAngle,int goalAngle, LineDetection& lineDetection, Motor& motor, double xCoord, double yCoord);
    double defenseAngle;
    bool stop;

private:
  
  double ballAngleX;
  double ballAngleY;
  double goalAngleX;
  double goalAngleY;
  double vectorX;
  double vectorY;
  double dotProduct;
  double denominator;
  double robotAngleX;
  double robotAngleY;
  double angleDiff;
  double lineAngle;
};

#endif