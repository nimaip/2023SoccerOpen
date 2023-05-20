#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>


Motor::Motor()
{
    // corresponding pin values on teensy
    pinspeedU = 5;
    pinspeedD = 3;
    pinspeedL = 2;
    pinspeedR = 24;
    pincontrolU = 0;
    pincontrolD = 32;
    pincontrolL = 25;
    pincontrolR = 1;
    
    
    pinMode(pinspeedU, OUTPUT);
    pinMode(pinspeedD, OUTPUT);
    pinMode(pinspeedL, OUTPUT);
    pinMode(pinspeedR, OUTPUT);
    pinMode(pincontrolU, OUTPUT);
    pinMode(pincontrolD, OUTPUT);
    pinMode(pincontrolL, OUTPUT);
    pinMode(pincontrolR, OUTPUT);
    max_power = 0;
};

void Motor::Move(double intended_angle, int motor_power){
    Move(intended_angle, motor_power, 0);
}

void Motor::Move(double intended_angle, int motor_power, double correction)
{
    // double intended_angle = 0; // intended angle for robot to move
    // robot_base_angle is the angle shift required to work in the reference frame 
    // of a horizontal/vertical square
    intended_angle = intended_angle - robot_base_angle + 360;
    if(intended_angle >= 360){
        intended_angle -= 360;
    }
    // Serial.print("Intended Angle: " );
    // Serial.println(intended_angle);
    double intended_angle_rad = toRadians(intended_angle);
    // Serial.print("Intended Angle (Radians): ");
    // Serial.println(intended_angle_rad);
    
    // powerU, powerD, powerL, powerR are the four sides of the square
    powerL = sin(intended_angle_rad) + correction;
    powerR = -1 * sin(intended_angle_rad) + correction;
    powerU = cos(intended_angle_rad) + correction;
    powerD = -1 * cos(intended_angle_rad) + correction;

    // find max_power among motors to scale
    max_power = max(max(abs(powerU), abs(powerD)), max(abs(powerL), abs(powerR)));
    // Serial.print("Max Power: ");
    // Serial.println(max_power);

    // add correction to account for rotation needed
    // powerL += correction;
    // powerR += correction;
    // powerU += correction;
    // powerD += correction; 

    controlL = powerL > 0 ? LOW : HIGH;
    controlR = powerR < 0 ? LOW : HIGH;
    controlU = powerU > 0 ? LOW : HIGH;
    controlD = powerD < 0 ? LOW : HIGH;
    // Serial.println("Powers:");
    // Serial.println(powerL);
    // Serial.println(powerR);
    // Serial.println(powerU);
    // Serial.println(powerD);

    max_power += 0.01;

    speedL = abs(powerL) / max_power;
    speedR = abs(powerR) / max_power;
    speedU = abs(powerU) / max_power;
    speedD = abs(powerD) / max_power;

    // Serial.println(speedU);
    // Serial.println(speedD);
    // Serial.println(speedR);
    // Serial.println(speedL);

    int multiplier = motor_power;
    int intspeedU = (int) (speedU * multiplier);
    int intspeedD = (int) (speedD * multiplier);
    int intspeedR = (int) (speedR * multiplier);
    int intspeedL = (int) (speedL * multiplier);

    Serial.print("intspeedU: ");
    Serial.println(intspeedU);
    Serial.println("Controls:");
    Serial.print("U: ");
    Serial.println(controlU);
    Serial.print("L: ");
    Serial.println(controlL);
    Serial.print("D: ");
    Serial.println(controlD);
    Serial.print("R: ");
    Serial.println(controlR);

    int motor_switch = 0;
    motor_switch = digitalRead(39);
    if(motor_switch == HIGH){
        analogWrite(pinspeedU, intspeedU);
        analogWrite(pinspeedD, intspeedD);
        analogWrite(pinspeedR, intspeedR);
        analogWrite(pinspeedL, intspeedL);
        digitalWrite(pincontrolU, controlU);
        digitalWrite(pincontrolD, controlD);
        digitalWrite(pincontrolR, controlR);
        digitalWrite(pincontrolL, controlL);
    }
    else{
        Stop();
    }
}

void Motor::Stop(){
    analogWrite(pinspeedU, 0);
    analogWrite(pinspeedD, 0);
    analogWrite(pinspeedR, 0);
    analogWrite(pinspeedL, 0);
    digitalWrite(pincontrolU, 0);
    digitalWrite(pincontrolD, 0);
    digitalWrite(pincontrolR, 0);
    digitalWrite(pincontrolL, 0);
}

void Motor::RecordDirection(){
    if(digitalRead(40) == HIGH){ // compass sensor switch
        dirAngle = compassSensor.getOrientation();
    }
}

double Motor::FindCorrection(){
    int angle = compassSensor.getOrientation();
    double multiplier = 1; // how much rotation there is
    double correction = sin(angle - dirAngle) * multiplier;
    return correction;
}

double Motor::FindCorrectionOffense(double goalAngle){
    int angle = compassSensor.getOrientation();
    double multiplier = 1; // how much rotation there is
    double correction = sin(angle - goalAngle) * multiplier;
    return correction;
}
