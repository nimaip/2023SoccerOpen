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
  double ballAngle = cam.buff;
  double yellowGoalAngle = cam.dist;
  double blueGoalAngle = cam.buff2;
  
  Serial.println("Values:");
  Serial.println(ballAngle);
  Serial.println(yellowGoalAngle);
  Serial.println(blueGoalAngle);
  if(ballAngle < 360 && yellowGoalAngle < 360 && blueGoalAngle < 360
      && -5 <= ballAngle && -5 <= yellowGoalAngle && -5 <= blueGoalAngle){
    ballAngle = -1*(ballAngle - 90);
    if(ballAngle < 0){
      ballAngle += 360;
    }
    yellowGoalAngle = -1*(yellowGoalAngle - 90);
    if(yellowGoalAngle < 0){
      yellowGoalAngle += 360;
    }
    blueGoalAngle = -1*(blueGoalAngle - 90);
    if(blueGoalAngle < 0){
      blueGoalAngle += 360;
    }
    
    double robotAngle = orbit.CalculateRobotAngle2(ballAngle, 0);
    // Serial.println(robotAngle);

    Serial.println(robotAngle);
    motor.Move(robotAngle, 100, 0);
  }




  // delay(400);
//  lineDetection.GetValues();

  // analogWrite(pinspeedU, 80);
  // digitalWrite(pincontrolU, LOW);
  // analogWrite(pinspeedD, 80);
  // digitalWrite(pincontrolD, LOW);
  // analogWrite(pinspeedL, 80);
  // digitalWrite(pincontrolL, LOW);
  // analogWrite(pinspeedR, 80);
  // digitalWrite(pincontrolR, LOW);
  // motor.Move(180, 80, 0);

  // delay(200);
  // motor.Move(0, 80, 0);
  // motor.RecordDirection();
  // int angle = motor.dirAngle;
  // Serial.println(angle);
  // cam.CamCalc();
  // double ballAngle = cam.buff;
  // double robotAngle = orbit.CalculateRobotAngle(ballAngle, 0);
  // Serial.println(robotAngle);
  // motor.Move(robotAngle, 120);
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
  delay(100);
}