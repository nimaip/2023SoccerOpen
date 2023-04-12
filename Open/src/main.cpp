#include <Arduino.h>
#include <lineDetection.h>

LineDetection lineDetection;
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  lineDetection.GetValues();
  delay(1000);
  // put your main code here, to run repeatedly:
}