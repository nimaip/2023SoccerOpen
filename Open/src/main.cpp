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
  Serial.begin(9600);
  Serial2.begin(19200);
  Serial.print(" ");
  delay(500);
}

void loop() {
  Serial.println("ha");
  motor.Move(0, 80);
  // cam.CamCalc();
  // double ballAngle = cam.buff;
  // double robotAngle = orbit.CalculateRobotAngle(ballAngle, 0);
  // Serial.println(robotAngle);
  // motor.Move(robotAngle, 80);
  // int main_switch = 0;
  // main_switch = digitalRead(36);

  // if(main_switch == HIGH){

  //   motor.RecordDirection();
  //   Serial.print("Motor Dir Angle: ");
  //   Serial.println(motor.dirAngle);

  //   // double angle = 0;
  //   // angle = lineDetection.GetAngle();
  //   // Serial.print("Line Angle: ");
  //   // Serial.println(angle);
  //   // angle += 180;
  //   // if(angle > 360){
  //   //   angle -= 360;
  //   // }
  //   // if(lineDetection.linepresent)
  //   //   motor.Move(angle, 120);
  //   // else 
  //   //   motor.Move(0, 0);
  // }
  // else{
  //   motor.Stop();
  // }

  // Serial.print(Serial2.available());
  delay(200);
}