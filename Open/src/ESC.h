#include<Servo.h>
#include <trig.h>
#include <math.h>

#ifndef ESC_H
#define ESC_H

class ESC
{
private:
    Servo esc1;
     Servo esc2;
     double tick1;
     int tick2;
     double gradspeed1;
     double gradspeed2;
public:
    ESC();
    void dribbler1(int speed,int first);
    void dribbler2(int speed, int first);
    void spinDribbler();
    void runDribbler(double ballAngle,double dist, bool capture1, bool capture2);
};

#endif