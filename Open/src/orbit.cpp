#include <orbit.h>

Orbit::Orbit(){

}

double Orbit::CalculateRobotAngle(double ballAngle, int goalAngle)
{
    ballAngle -= goalAngle;
    if(ballAngle < 0){
        ballAngle += 360;
    }
    if(ballAngle < 90 || ballAngle > 270){
        int thing = 20;
        if(ballAngle < thing || ballAngle > 360 - thing){
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

double Orbit::CalculateRobotAngle2(double ballAngle, double goalAngle){
    // double dampenVal = min(1, 0.02 * exp(5.5 * highestValue));

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
    orbitvalue = orbitvalue+180;
    if(orbitvalue > 360){
        orbitvalue -=360;
    }
    // Serial.print("dampen : ");
    // Serial.println(dampenVal);
    // Serial.print("orbit : ");
    // Serial.println(orbitvalue);
    robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue);
    // Serial.print("robotAngle : ");
    // Serial.println(robotAngle);
    if(robotAngle > 360){
        robotAngle -=360;
    }
    return robotAngle;
}