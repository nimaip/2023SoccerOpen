#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Cam {
	public:
        Cam();
        int *angleAverage;
        int *angle2Average;
        double ball;
        double yellowGoal;
        double blueGoal;
        double camVal;
        double validBallAngle;
        double CamCalc();
        double FilterAngle(double angle, double validAngle);
        std::string buffer;
        char read;
    private:
        int dataNum;

};