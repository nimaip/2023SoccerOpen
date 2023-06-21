#include <LRF.h>
#include <Arduino.h>

// address we will assign if dual sensor is present


LRF::LRF(){

   
    delay(5000);
Serial.println("hey");

// Serial.begin(115200);

  // wait until serial port opens for native USB devices

};
void LRF::setup(){

     lox1 = Adafruit_VL53L0X();
    lox2 = Adafruit_VL53L0X();

      while (! Serial) { delay(1); }

  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(30, LOW);
  digitalWrite(31, LOW);

  Serial.println(F("Both in reset mode...(pins are low)"));
  
  
  Serial.println(F("Starting..."));
  setID();
  Serial.println("hi");

};

void LRF::setID() {
  // all reset
  digitalWrite(30, LOW);    
  digitalWrite(31, LOW);
  delay(10);
  
  // all unreset
  digitalWrite(30, HIGH);
  digitalWrite(31, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(30, HIGH);
  digitalWrite(31, LOW);
  Serial.println("hi");
  // initing LOX1
  Serial.println(lox1.begin(0x30,false,&Wire1));
//   if(!lox1.begin(0x30,true,&Wire1)) {
//     Serial.println(F("Failed to boot first VL53L0X"));
//     while(1);
//   }
  delay(10);
  Serial.println("hi");
  // activating LOX2
  digitalWrite(31, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(0x31,true,&Wire1)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
};
void LRF::read_dual_sensors() {
  Serial.println("hi");
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  // print sensor one reading
  Serial.print(F("1: "));
  if(measure1.RangeStatus != 4) {     // if not out of range
    Serial.print(measure1.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }
  
  Serial.print(F(" "));

  // print sensor two reading
  Serial.print(F("2: "));
  if(measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
  } else {
    Serial.print(F("Out of range"));
  }
  
  Serial.println();
};
