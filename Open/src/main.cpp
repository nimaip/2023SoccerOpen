#include <Arduino.h>
#include <motor.h>
#include <lineDetection.h>
#include <Cam.h>
#include <orbit.h>
#include <ESC.h>
#include <Goal.h>
#include <Defense.h>
#include<calibration.h>
// #include<LRF.h>
#include "Adafruit_VL53L0X.h"
#include <localization.h>

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33

// set the pins to shutdown
#define SHT_LOX1 30
#define SHT_LOX2 31
#define SHT_LOX3 26
#define SHT_LOX4 27
// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;

Localization localization;
LineDetection lineDetection;
Motor motor;
Cam cam;
Orbit orbit;
ESC esc;
Goal goal;
Defense defense;
Calibration calibration;
// LRF lrf;
unsigned long myTime = 0;

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);    
  digitalWrite(SHT_LOX4, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
    digitalWrite(SHT_LOX4, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS,false,&Wire1)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS,false,&Wire1)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

    digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS,false,&Wire1)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }

    digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  //initing LOX4
  if(!lox4.begin(LOX4_ADDRESS,false,&Wire1)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
}


int frontLRF(){
   lox1.rangingTest(&measure1, false);
  if(measure1.RangeStatus != 4) {     // if not out of range
    return measure1.RangeMilliMeter;
  } else {
    return -1;
  }
}
int backLRF(){
   lox3.rangingTest(&measure3, false);
  if(measure3.RangeStatus != 4) {     // if not out of range
    return measure3.RangeMilliMeter;
  } else {
    return -1;
  }
}
int rightLRF(){
   lox4.rangingTest(&measure4, false);
  if(measure4.RangeStatus != 4) {     // if not out of range
    return measure4.RangeMilliMeter;
  } else {
    return -1;
  }
}
int leftLRF(){
     lox2.rangingTest(&measure2, false);
  if(measure2.RangeStatus != 4) {     // if not out of range
    return measure2.RangeMilliMeter;
  } else {
    return -1;
  }
}



void setup() {
  Serial2.begin(19200);
  pinMode(10, OUTPUT);
  // delay(5000);
  esc.dribbler1(0, 0);
  esc.dribbler2(0, 0);
  delay(1000);


}

void loop() {



  esc.dribbler1(0,1);
  esc.dribbler2(0,1);


  cam.CamCalc(goal);
  esc.runDribbler(cam.ball, cam.validDistance, goal.lightGateOne(), goal.lightGateTwo());
  goal.Kick(cam.yellowGoalDistance,goal.lightGateOne(), esc);

  calibration.calState(lineDetection);
  motor.RecordDirection();
  lineDetection.Process(calibration.calVal);


  //defense
  // defense.defense(cam.ball,cam.yellowGoal,lineDetection, motor); // run lineavoidance process before
  // motor.Process(defense.defenseAngle, 0.6, lineDetection.avoidanceAngle, initialOrientation);

  //offense


  motor.Process(orbit.CalculateRobotAngle2(cam.ball, 0, cam.validDistance), 0.7, lineDetection.avoidanceAngle, goal.Process(cam.ball, motor.compassSensor.getOrientation(), cam.yellowGoal, motor.initialOrientation),orbit, goal.lightGateTwo(), cam.yellowGoal, lineDetection.Chord(), lineDetection.linepresent, esc);
  delay(1000);
}

