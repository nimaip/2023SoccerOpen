#include <ESC.h>

#ifndef GOAL_H
#define GOAL_H
class Goal {
    public:
        Goal();
        double Process(double ball, int Orientation, double goalOrientation, int initialOrientation);
        double goalAngle;
        void Kick(double goalDist,bool capture, ESC& esc);
        bool lightGateOne();
        bool lightGateTwo();
    private:
        int kickTimer;
        int kickActivate;
        int kickWait;
        int myTime;
        bool turnOnTimer;

};

#endif