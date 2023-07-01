#include <Goal.h>
#include <Arduino.h>


Goal::Goal()
{
    kickTimer = 0;
    kickActivate = 1;
    kickWait = 0;
    myTime = 0;
    turnOnTimer = true;
    pinMode(38,INPUT);

}
double Goal::Process(double ball, int Orientation, double goalOrientation, int initialOrientation, bool tooFar)
{
if(tooFar == true){
    return initialOrientation;
}
else if(ball<60||ball>300){

    if (goalOrientation > 180)
    {
        goalOrientation = goalOrientation - 360;
    }


    goalAngle = Orientation + goalOrientation;

    if (goalAngle > 360)
    {
        goalAngle = goalAngle - 360;
    }
    else if (goalAngle < 0)
    {
        goalAngle = goalAngle + 360;
    }
    // if(goalOrientation > 95 && goalOrientation < 265){
    //     goalAngle = initialOrientation;
    // }

    // Serial.print("goal Angle : ");
    // Serial.println(goalAngle);
    return goalAngle;

}
else{ 
    return initialOrientation;
    }
}


void Goal::Kick(double goalDist, bool capture, ESC& esc)
{
    // Serial.print("Goal dist:   ");
    // Serial.println(goalDist);
if(capture == true&&goalDist<126){
digitalWrite(10,LOW);
    esc.dribbler2(50,1);
    if(turnOnTimer){
        myTime = millis() +250;
        turnOnTimer = false;
    }
    if(millis() > myTime && millis() < (myTime + 100)){
        digitalWrite(10,HIGH);
    }
    if(millis() >= (myTime+100) && millis() <= (myTime + 290)){
        turnOnTimer = true;
    }
}
else{
    turnOnTimer = true;
}
}
//front lightgate
bool Goal::lightGateOne(){
  int lightGate = analogRead(14);
  if(lightGate> 500)
    return false;
  return true;
}
//BACK LIGHTGATE
bool Goal::lightGateTwo(){
  int lightGate = analogRead(38);

  if(lightGate> 710)
    return false;
  return true;
}