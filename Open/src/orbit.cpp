#include <orbit.h>

Orbit::Orbit(){

}

double Orbit::CalculateRobotAngle2(double ballAngle, double goalAngle, double distance){
    
    
    double dampenVal = min(1, 4 * exp(-0.1 * distance));
    Serial.print("dampen: ");
    Serial.println(dampenVal);
    if(ballAngle == -5 || ballAngle == 0){
        ballAngle = validBallAngle;
    }
    else{
        validBallAngle = ballAngle;
    }

    double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;
    // Serial.print("ballangle : ");
    // Serial.println(newballAngle);
    if (goalAngle == -5)
    {
        goalAngle = 0;
    }
    if (goalAngle > 180)
    {
        goalAngle = 360 - goalAngle;
    }

    multiplier = 0.05 * (goalAngle) + 1;
    double orbitvalue = min(90, 0.08 * exp(0.2 * newballAngle));
    orbitvalue = orbitvalue*dampenVal;

    robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue);
    Serial.print("robotAngle : ");
    Serial.println(robotAngle);
    if(robotAngle > 360){
        robotAngle -=360;
    }
    return robotAngle;
}