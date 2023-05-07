#include <Arduino.h>
#include <motor.h>
#include <lineDetection.h>

LineDetection lineDetection;
Motor motor;

void setup() {
  // Serial.print(" ");
  // delay(500);
}

void loop() {
  
  int main_switch = 0;
  main_switch = digitalRead(36);

  if(main_switch == HIGH){

    motor.RecordDirection();
    Serial.print("Motor Dir Angle: ");
    Serial.println(motor.dirAngle);

    // double angle = 0;
    // angle = lineDetection.GetAngle();
    // Serial.print("Line Angle: ");
    // Serial.println(angle);
    // angle += 180;
    // if(angle > 360){
    //   angle -= 360;
    // }
    // if(lineDetection.linepresent)
    //   motor.Move(angle, 120);
    // else 
    //   motor.Move(0, 0);
  }
  else{
    motor.Stop();
  }

  delay(1000);
}