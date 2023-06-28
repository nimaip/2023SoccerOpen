#include <orbit.h>

Orbit::Orbit()
{
    inPos = false;
}

double Orbit::CalculateRobotAngle2(double ballAngle, double goalAngle, double distance)
{

    if (ballAngle < 90 || ballAngle > 270)
    {
        double dampenVal = min(1, 4 * exp(-0.1 * distance));

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
        double orbitvalue = min(90, 0.15 * exp(0.19 * newballAngle));
        orbitvalue = orbitvalue * dampenVal;
        robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue);
        if (robotAngle > 360)
        {
            robotAngle -= 360;
        }
        Serial.print("robot Angle: ");
        Serial.println(robotAngle);
        return robotAngle;
    }
    else
    {
        ballAngle += 180;
        if (ballAngle > 360)
        {
            ballAngle -= 360;
        }
        goalAngle += 180;
        if (goalAngle > 360)
        {
            goalAngle -= 360;
        }
        double dampenVal = min(1, 4 * exp(-0.1 * distance));
        if (ballAngle == -5 || ballAngle == 0)
        {
            ballAngle = validBallAngle;
        }
        else
        {
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
        orbitvalue = orbitvalue * dampenVal;

        robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue);
        if (robotAngle > 360)
        {
            robotAngle -= 360;
        }
        robotAngle += 180;
        if (robotAngle > 360)
        {
            robotAngle -= 360;
        }
        Serial.print("robot Angle: ");
        Serial.println(robotAngle);
        return robotAngle;
    }
}

double Orbit::GetToSpinShotPosition(bool linePresent, int goalAngle)
{

    // get to shooting position

    double robotAngle;

    if (goalAngle > 30)
    {
        robotAngle = 90;
    }
    else if (goalAngle < 20)
    {
        robotAngle = 270;
    }

    else if (linePresent == false)
    {
        robotAngle = 25;
    }
    else
    {
        inPos = true;
    }

    return robotAngle;
}


double Orbit::InOrientationSpinShot(double robotOrientation, int initialOrientation)
{
    double orientation = initialOrientation+15;
    if(orientation >360){
        orientation = orientation-360;
    }
    double orientationVal = 0;
     orientationVal = abs(orientation - robotOrientation);

    // Serial.println(orientationVal);
    if (orientationVal > 180)
    {
        orientationVal = 360 - orientationVal;
    }
    if (robotOrientation <180  && orientation > 180)
    {
        orientation = -1*(360-orientation);
    }
    else if (robotOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    if (orientation < robotOrientation)
    {
        orientationVal = -1*orientationVal;
    }
    if (orientationVal > -5 && orientationVal < 0)
    {
      orientationVal = 0; 
       inOrientation = true;
    }
    else if (orientationVal <5 && orientationVal > 0)
    {
        orientationVal = 0;
        inOrientation = true;
    }
return orientationVal;
}

double Orbit::GetToHomePositionOffense(double goalDistance, double goalAngle){
    if(goalAngle == -5){
        return 0;
    }
    
}