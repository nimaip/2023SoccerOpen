#include <orbit.h>

Orbit::Orbit(){

}

double Orbit::CalculateRobotAngle(double ballAngle, int goalAngle)
{

    if(ballAngle < 90 || ballAngle > 270){
        if(ballAngle < 20 || ballAngle > 340){
            return ballAngle;
        }
        else if(ballAngle < 90){
            return 135;
        }
        else{
            return 225;
        }
    }
    else{
        if(ballAngle < 140 || ballAngle > 220){
            return 180;
        }
        else if(ballAngle >= 140 && ballAngle < 180){
            return 270;
        }
        else{
            return 90;
        }
    }

    // double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;

    // if (goalAngle == -5) {
    //     goalAngle = 0;
    // }
    // goalAngle = goalAngle > 180 ? (360 - goalAngle) : goalAngle; 

    // double dampenVal = min(1, 0.02 * exp(5.5 * highestValue));
    // double orbitvalue = min(90, 0.08 * exp(0.2 * newballAngle));

    // robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue * dampenVal);
    // Serial.print("robotAngle : ");
    // Serial.println(robotAngle);
    // return robotAngle;
}