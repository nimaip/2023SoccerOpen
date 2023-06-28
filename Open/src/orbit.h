#include <trig.h>
#include <lineDetection.h>
#ifndef ORBIT_H
#define ORBIT_H
class Orbit {

    public: 
        Orbit();
        double validBallAngle;
        double highestValue; // highest of the sensor values
        double robotAngle;
        bool capture = false;
        int kickState = 1;
        void kickButton();
        bool ballpresent = false;
        int realhighestVal;
        int xbeeHighVal;
        double CalculateRobotAngle2(double ballAngle, double goalAngle, double distance);
        double GetToSpinShotPosition(bool linePresent, int goalAngle);
        double InOrientationSpinShot(double robotOrientation, int initialOrientation);
        double GetToHomePositionOffense(double goalDistance, double goalAngle);
        bool inPos;
        bool inOrientation;
    private:
        int multiplier;

         
        
};
#endif