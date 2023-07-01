#include <Defense.h>

Defense::Defense()
{
}

void Defense::defense(double ballAngle, int goalAngle, LineDetection &lineDetection, Motor &motor, bool dissapear)
{
    if (dissapear == true)
    {
        motor.defenseStop = false;

        if (goalAngle > 185)
        {
            xcomp = -0.98;
        }
        else if (goalAngle < 175)
        {
            xcomp = 0.98;
        }
        else
        {
            xcomp = 0;
        }

        if (lineDetection.linepresent == false)
        {
            ycomp = -1;
        }
        else
        {
            ycomp = 0;
        }
        if (xcomp == 0 && ycomp == 0)
            motor.defenseStop = true;
        else
        {
            defenseAngle = toDegrees(atan2(xcomp, ycomp));
            if (defenseAngle < 0)
            {
                defenseAngle = defenseAngle + 360;
            }
        if (lineDetection.linepresent == true && lineDetection.Chord() < 0.8 && ((abs(lineDetection.anglebisc - defenseAngle)) < 110))
        {
            lineDetection.avoidanceAngle = -1;
            
            defenseAngle = motor.projectionCalc(lineDetection.anglebisc,defenseAngle);
        }
        }
    }
    else
    {

        Serial.println(lineDetection.Chord());
        if (lineDetection.Chord() < 0.8)
        {
            lineDetection.avoidanceAngle = -1;
        }
        angleDiff = abs(ballAngle - goalAngle);
        if (angleDiff > 180)
        {
            angleDiff = 360 - angleDiff;
        }
        Serial.print("Diff:");
        Serial.println(angleDiff);
        if ((angleDiff > 180 && angleDiff < 192) || (angleDiff <= 180 && angleDiff > 168))
        {
            motor.defenseStop = true;
        }
        else
        {
            motor.defenseStop = false;
            if (goalAngle > 360)
            {
                goalAngle = goalAngle - 360;
            }
            ballAngleX = sin(toRadians(ballAngle));
            ballAngleY = cos(toRadians(ballAngle));
            goalAngleX = sin(toRadians(goalAngle));
            goalAngleY = cos(toRadians(goalAngle));

            robotAngleX = ballAngleX + goalAngleX;
            robotAngleY = ballAngleY + goalAngleY;

            defenseAngle = toDegrees(atan2(robotAngleX, robotAngleY));
            if (defenseAngle < 0)
            {

                defenseAngle = defenseAngle + 360;
            }
            if (lineDetection.linepresent == true)
            {
                lineAngle = lineDetection.anglebisc + 90;
                if (lineAngle > 360)
                {
                    lineAngle = lineAngle - 360;
                }
                vectorX = sin(toRadians(lineAngle));
                vectorY = cos(toRadians(lineAngle));

                dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
                denominator = pow(vectorX, 2) + pow(vectorY, 2);
                robotAngleX = (dotProduct / denominator) * vectorX;
                robotAngleY = (dotProduct / denominator) * vectorY;

                defenseAngle = toDegrees(atan2(robotAngleX, robotAngleY));
                if (defenseAngle < 0)
                {
                    defenseAngle = defenseAngle + 360;
                }
            }
            else if (defenseAngle > 270 || defenseAngle < 90)
            {
                vectorX = sin(toRadians(90));
                vectorY = cos(toRadians(90));

                dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
                denominator = pow(vectorX, 2) + pow(vectorY, 2);
                robotAngleX = (dotProduct / denominator) * vectorX;
                robotAngleY = (dotProduct / denominator) * vectorY;

                defenseAngle = toDegrees(atan2(robotAngleX, robotAngleY));
                if (defenseAngle < 0)
                {
                    defenseAngle = defenseAngle + 360;
                }
            }
        }

        Serial.print("defense angle : ");
        Serial.println(defenseAngle);
        Serial.print("ball angle: ");
        Serial.println(ballAngle);
        Serial.print("goal angle: ");
        Serial.println(goalAngle);
    }
}