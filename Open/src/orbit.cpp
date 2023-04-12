#include <orbit.h>

Orbit::Orbit(){

}

double Orbit::CalculateRobotAngle(int goalAngle)
{

    double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;

    if (goalAngle == -5) {
        goalAngle = 0;
    }
    goalAngle = goalAngle > 180 ? (360 - goalAngle) : goalAngle; 

    double dampenVal = min(1, 0.02 * exp(5.5 * highestValue));
    double orbitvalue = min(90, 0.08 * exp(0.2 * newballAngle));

    robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue * dampenVal);
    Serial.print("robotAngle : ");
    Serial.println(robotAngle);
    return robotAngle;
}