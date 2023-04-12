#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>


Motor::Motor()
{
    // corresponding pin values on teensy
    speedU = 4;
    speedD = 5;
    speedL = 7;
    speedR = 16;
    controlU = 17;
    controlD = 24;
    controlL = 2;
    controlR = 3;
    
    
    pinMode(speedU, OUTPUT);
    pinMode(speedD, OUTPUT);
    pinMode(speedL, OUTPUT);
    pinMode(speedR, OUTPUT);
    pinMode(controlU, OUTPUT);
    pinMode(controlD, OUTPUT);
    pinMode(controlL, OUTPUT);
    pinMode(controlR, OUTPUT);
    max_power = 0;
};

void Motor::Move(double intended_angle)
{
    double intended_angle = 0; // intended angle for robot to move
    // robot_base_angle is the angle shift required to work in the reference frame 
    // of a horizontal/vertical square
    intended_angle = (intended_angle - robot_base_angle + 360) % 360;
    double intended_angle_rad = toRadians(intended_angle);
    
    // powerU, powerD, powerL, powerR are the four sides of the square
    powerL = sin(intended_angle_rad);
    powerR = -1 * sin(intended_angle_rad);
    powerU = cos(intended_angle_rad);
    powerD = -1 * cos(intended_angle_rad);

    // find max_power among motors to scale
    max_power = max(max(abs(powerU), abs(powerD)), max(abs(powerL), abs(powerR)));

    // add correction to account for rotation needed
    powerL += correction;
    powerR += correction;
    powerU += correction;
    powerD += correction; 

    controlL = powerL < 0 ? LOW : HIGH;
    controlR = powerR < 0 ? LOW : HIGH;
    controlU = powerU < 0 ? LOW : HIGH;
    controlD = powerD < 0 ? LOW : HIGH;


    speedL = abs(powerL) / max_power - 0.01;
    speedR = abs(powerR) / max_power - 0.01;
    speedU = abs(powerU) / max_power - 0.01;
    speedD = abs(powerD) / max_power - 0.01;
}