#include <Arduino.h>
#include <motor.h>
#include <lineDetection.h>
#include <Cam.h>
#include <orbit.h>
#include <ESC.h>
#include <Goal.h>
#include <Defense.h>
#include<calibration.h>
#include<LRF.h>

LineDetection lineDetection;
Motor motor;
Cam cam;
Orbit orbit;
ESC esc;
Goal goal;
Defense defense;
Calibration calibration;
LRF lrf;
double initialOrientation = 0;
void setup() {
  Serial2.begin(19200);
  esc.dribbler1(0);
  esc.dribbler2(0);
  lrf.setup();

}

void loop() {
//   cam.CamCalc();
//   calibration.calState(lineDetection);
//   initialOrientation = motor.RecordDirection();
//   lineDetection.Process(calibration.calVal);
//   initialOrientation = motor.RecordDirection();
//   //defense
//   Serial.print("angle bisc: ");
// Serial.println(lineDetection.anglebisc);

//   defense.defense(cam.ball,cam.yellowGoal,lineDetection, motor); // run lineavoidance process before
// Serial.print("line: ");
// Serial.println(lineDetection.avoidanceAngle);
//   motor.Process(defense.defenseAngle, 0.6, lineDetection.avoidanceAngle, initialOrientation);

//   //offense
//   // motor.Process(orbit.CalculateRobotAngle2(cam.ball, 0, cam.actualDistance), 0.6, lineDetection.avoidanceAngle, goal.Process(cam.ball, motor.compassSensor.getOrientation(), cam.yellowGoal, initialOrientation));
  
  lrf.read_dual_sensors();
  delay(200);
}