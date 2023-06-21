#include <trig.h>
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

    private:
        int multiplier;
         
        
};