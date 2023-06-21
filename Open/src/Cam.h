#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Cam {
	public:
        Cam();
        double ball;
        double yellowGoal;
        double blueGoal;
        double distance;
        double actualDistance;


        double CamCalc();
        double FilterAngle(double angle, double validAngle);
        std::string buffer;
    private:
        char read;
                double validBallAngle;
        double validBlueAngle;
        double validYellowAngle;
        double validDistance;

};