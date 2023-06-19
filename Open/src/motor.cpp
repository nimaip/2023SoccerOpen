#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>


Motor::Motor()
{
    // corresponding pin values on teensy
    pinspeedRL = 5;
    pinspeedRR = 3;
    pinspeedFL = 2;
    pinspeedFR = 24;
    pincontrolRL = 32;
    pincontrolRR = 0;
    pincontrolFL = 25;
    pincontrolFR = 1;

    
    
    pinMode(pinspeedFR, OUTPUT);
    pinMode(pinspeedFL, OUTPUT);
    pinMode(pinspeedRR, OUTPUT);
    pinMode(pinspeedRL, OUTPUT);
    pinMode(pincontrolFL, OUTPUT);
    pinMode(pincontrolFR, OUTPUT);
    pinMode(pincontrolRR, OUTPUT);
    pinMode(pincontrolRL, OUTPUT);
    max_power = 0;
};

void Motor::Process(double intended_angle, double motor_power, bool linePresent, double lineAngle){
    if(linePresent == true){
        Move(lineAngle, motor_power);
    }
    else{
        Move(intended_angle, motor_power);
    }
}

void Motor::Move(double intended_angle, double motor_power)
{
    speedRR = 0;
    speedRL = 0;
    speedFL = 0;
    speedFR = 0;
    controlRR = 0;
    controlFR = 0;
    controlFL = 0;
    controlRL = 0;

    powerFR = sin(toRadians(intended_angle - 45));
    powerRR = sin(toRadians(intended_angle - 135));
    powerRL = sin(toRadians(intended_angle - 225));
    powerFL = sin(toRadians(intended_angle - 315));
    // find max_power among motors to scale
    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));
    // Serial.print("Max Power: ");
    // Serial.println(max_power);

    FindCorrection(compassSensor.getOrientation());
    // add correction to account for rotation needed



  




    // max_power += 0.01;
    // Serial.println(powerFR);
    // Serial.println(powerFL);
    // Serial.println(powerRR);
    // Serial.println(powerRL);
    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;


    powerFR += correction;
    powerFL += correction;
    powerRR += correction;
    powerRL += correction; 

    controlRL = powerRL < 0 ? LOW : HIGH;
    controlRR = powerRR > 0 ? LOW : HIGH;
    controlFL = powerFL < 0 ? LOW : HIGH;
    controlFR = powerFR > 0 ? LOW : HIGH;

    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));

    speedFR = abs(powerFR) / max_power;
    speedFL = abs(powerFL) / max_power;
    speedRR = abs(powerRR) / max_power;
    speedRL = abs(powerRL) / max_power;


    int multiplier = 255;
    int intspeedFR = (int) ((speedFR * multiplier)*motor_power);
    int intspeedFL = (int) ((speedFL * multiplier)*motor_power);
    int intspeedRR = (int) ((speedRR * multiplier)*motor_power);
    int intspeedRL = (int) ((speedRL * multiplier)*motor_power);


    int motor_switch = 0;
    motor_switch = digitalRead(39);
    if(motor_switch == HIGH){
        analogWrite(pinspeedFR, intspeedFR);
        analogWrite(pinspeedFL, intspeedFL);
        analogWrite(pinspeedRR, intspeedRR);
        analogWrite(pinspeedRL, intspeedRL);
        digitalWrite(pincontrolFL, controlFL);
        digitalWrite(pincontrolFR, controlFR);
        digitalWrite(pincontrolRR, controlRR);
        digitalWrite(pincontrolRL, controlRL);
    }
    else{
        Stop();
    }
}

void Motor::Stop(){
    analogWrite(pinspeedFR, 0);
    analogWrite(pinspeedFL, 0);
    analogWrite(pinspeedRL, 0);
    analogWrite(pinspeedRR, 0);
}
void Motor::RecordDirection(){
    if(digitalRead(36) == LOW){
        initialOrientation = compassSensor.getOrientation();
    }
}



double Motor::FindCorrection(double orientation){
    

    orientationVal = abs(orientation - initialOrientation);

    // Serial.println(orientationVal);
    if (orientationVal > 180)
    {
        orientationVal = 360 - orientationVal;
    }
    if (initialOrientation <180  && orientation > 180)
    {
        orientation = -1*(360-orientation);
    }
    else if (initialOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    if (orientation < initialOrientation)
    {
        orientationVal = -1*orientationVal;
    }


    correction = -1 * (sin(toRadians(orientationVal)));

    if (orientationVal > -8 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 8 && orientationVal > 0)
    {
        correction = 0;
    }
    else if (orientationVal > 90)
    {
        correction = -1;
    }
    else if (orientationVal < -90)
    {
        correction = 1;
    }

    
    

    Serial.println("Correction : ");
    Serial.println(correction);
    return correction;
}


