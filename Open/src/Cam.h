

#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>
#include <Goal.h>
#ifndef CAM_H
#define CAM_H
class Cam {
	public:
        Cam();
        double ball;
        double yellowGoal;
        double blueGoal;
        double ballDistance;
        double actualBallDistance;
        double yellowGoalDistance;
        double blueGoalDistance;
        bool tooFar;
double validDistance;


        double CamCalc(Goal& goal);
        double FilterAngle(double angle, double validAngle);
        double ComplimentaryFilterAngle(double angle, double validAngle);
        double ComplimentaryFilterDistance(double dist, double validDist);
        double dissapear(double angle, double distance, double validAngle);
        std::string buffer;
    private:
        char read;
                double validBallAngle;
        double validBlueAngle;
        double validYellowAngle;
        double validBallDistance;
        double validYellowGoalDistance;
        double validBlueGoalDistance;
        int invalidCounter;
        int validCounter;
        bool dissapeared;

        double validAngle;

};
#endif