#include <Arduino.h>
#include <trig.h>
#include <compassSensor.h>

class Motor
{

public:
    Motor();
    void Move(double intended_angle, int motor_power);
    void Move(double intended_angle, int motor_power, double correction);
    void Stop();
    void RecordDirection();
    double FindCorrection();
    double FindCorrectionOffense(double goalAngle);
    double robot_base_angle = 45;
    CompassSensor compassSensor;
    int dirAngle;

private:
    double max_power;
    double powerU;
    double powerD;
    double powerL;
    double powerR;

    double speedU;
    double speedD;
    double speedL;
    double speedR;
    int controlU;
    int controlD;
    int controlL;
    int controlR;

    int pinspeedU;
    int pinspeedD;
    int pinspeedL;
    int pinspeedR;
    int pincontrolU;
    int pincontrolD;
    int pincontrolL;
    int pincontrolR;

};