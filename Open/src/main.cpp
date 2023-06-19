#include <Arduino.h>
#include <motor.h>
#include <lineDetection.h>
#include <Cam.h>
#include <orbit.h>

LineDetection lineDetection;
Motor motor;
Cam cam;
Orbit orbit;


void setup() {
  Serial2.begin(19200);
}

void loop() {
  cam.CamCalc();
  double angle = lineDetection.Process();
  motor.RecordDirection();
  motor.Process(orbit.CalculateRobotAngle2(cam.ball, 0), 0.8, lineDetection.linepresent, angle);
}