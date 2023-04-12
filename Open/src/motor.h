#include <Arduino.h>
#include <trig.h>


class Motor
{

public:
    Motor();
    void Move(double intended_angle);
    double correction;
    double robot_base_angle = 45;
    


private:
    double max_power;
    double powerU;
    double powerD;
    double powerL;
    double powerR;

    int speedU;
    int speedD;
    int speedL;
    int speedR;
    int controlU;
    int controlD;
    int controlL;
    int controlR;
};