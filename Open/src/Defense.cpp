#include <Defense.h>

Defense::Defense()
{

}

double Defense::defense(double ballAngle, double goalAngle)
{
    // preprocessing 
    if(goalAngle ==-5){
        goalAngle = 180;
    }
    if(ballAngle == -5){
        ballAngle = 0;
    }
    if(goalAngle >360){
        goalAngle = goalAngle-360;
    }

    // calculate direction robot should move in 
    double robotAngle = -1;
    double diff = abs(ballAngle - goalAngle);
    double restWindow = 30; 
    // if the robot is within restWindow degrees of the line then it won't move
    if(diff < 180 - restWindow){
        robotAngle = (ballAngle + goalAngle)/2;
    }
    if(diff > 180 + restWindow){
        robotAngle = (ballAngle + goalAngle)/2;
        if(robotAngle >= 360){
            robotAngle -= 360;
        }
    }

    if(robotAngle == -1){
        // don't move
    }
    else{
        // motor.Move(robotAngle, motorPower)
    }
    // additionally, make sure you're always running the line avoidance algorithm
    // to ensure that it stays outside of the box 

    // Serial.print("defense Tick : ");
    // Serial.println(defenseTick);
    // Serial.print("defense angle : ");
    // Serial.println(defenseAngle);
    // Serial.print("ball angle: ");
    // Serial.println(ballAngle);
    // Serial.print("goal angle: ");
    // Serial.println(goalAngle);
}