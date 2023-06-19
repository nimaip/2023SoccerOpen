#include <Arduino.h>
#include <trig.h>
#include <compassSensor.h>

class Motor
{

public:
    Motor();
    void Move(double intended_angle, double motor_power);
    void Process(double intended_angle, double motor_power, bool linePresent, double lineAngle);
    void Stop();
    void RecordDirection();
    double FindCorrection(double orientation);
    CompassSensor compassSensor;
    int dirAngle;
    double correction;

private:
    double initialOrientation = 0;
    double max_power;
    double powerFR;
    double powerFL;
    double powerRR;
    double powerRL;

    double speedFR;
    double speedFL;
    double speedRR;
    double speedRL;
    int controlFR;
    int controlFL;
    int controlRR;
    int controlRL;

    int pinspeedFR;
    int pinspeedFL;
    int pinspeedRR;
    int pinspeedRL;
    int pincontrolFR;
    int pincontrolFL;
    int pincontrolRR;
    int pincontrolRL;

    double orientationVal;
};