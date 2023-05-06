#include <Arduino.h>
#include <motor.h>
#include <lineDetection.h>

LineDetection lineDetection;
Motor motor;

void setup() {
  Serial.print(" ");
  delay(500);
}

void loop() {
  motor.Move(270);
  double angle = 0;
  angle = lineDetection.GetAngle();
  Serial.print("Line Angle: ");
  Serial.println(angle);
  delay(1000);
  // put your main code here, to run repeatedly:
}