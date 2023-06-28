#include <orbit.h>

Orbit::Orbit(){

}

double Orbit::CalculateRobotAngle2(double ballAngle, double goalAngle, double distance){
    
    if(ballAngle < 90 || ballAngle > 270){
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
        orbitvalue = orbitvalue*dampenVal;
        robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue);
        if(robotAngle > 360){
            robotAngle -=360;
        }
            Serial.print("robot Angle: ");
    Serial.println(robotAngle);
        return robotAngle;
    }
    else{
        ballAngle += 180;
        if(ballAngle > 360){
            ballAngle -= 360;
        } 
        goalAngle += 180;
        if(goalAngle > 360){
            goalAngle -= 360;
        }
        double dampenVal = min(1, 4 * exp(-0.1 * distance));
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
        if(robotAngle > 360){
            robotAngle -=360;
        }
        robotAngle += 180;
        if(robotAngle > 360){
            robotAngle -= 360;
        }
        Serial.print("robot Angle: ");
    Serial.println(robotAngle);
        return robotAngle;
    }

}

double Orbit::GetToSpinShotPosition(bool linePresent, int goalAngle){
    // get to shooting position

    
    double vectorX = 0;
    double vectorY = 0;
    double lineX = 0;
    double lineY = 0;
    if(goalAngle>45){
        vectorX = sin(toRadians(90));
        vectorY = cos(toRadians(90));
    }
    else if(goalAngle < 45){
        vectorX = sin(toRadians(270));
        vectorY = cos(toRadians(270));
    }
    if(linePresent == false){
        lineX = sin(toRadians(0));
        lineY = cos(toRadians(0));
    }
    else{
        lineX = 0;
        lineY = 0;
    }
    double robotAngleX = vectorX + lineX;
    double robotAngleY = vectorY + lineY;
    double robotAngle = toDegrees(atan2(robotAngleX, robotAngleY));
    
    

    return robotAngle;
}

bool Orbit::InSpinShotPosition(double left_lrf, double front_lrf, double right_lrf, double back_lrf){
    double left_dist;
    double front_dist;
    if(left_lrf == -1){ // not detected
        left_dist = 182 - right_lrf/10.0;
    }
    else{
        left_dist = left_lrf/10.0;
    }
    if(front_lrf == -1){
        // front_dist = 243 - back_lrf/10.0;
        return false;
    }
    else{
        front_dist = front_lrf/10.0;
    }
    Serial.print("Left distance: ");
    Serial.println(left_dist);
    Serial.print("Front distance: ");
    Serial.println(front_dist);
    double left_desired = 60;
    double front_desired = 60;
    double left_delta = left_desired - left_dist;
    double front_delta = front_desired - front_dist;
    if(abs(left_delta) < 5 && abs(front_delta) < 5){
        return true;
    }
    else{
        return false;
    } 
}

bool Orbit::InOrientationSpinShot(double robot_orientation){
    double desired_angle;
    if(abs(desired_angle - robot_orientation) < 15){
        return true;
    }
    else{
        return false;
    }
}