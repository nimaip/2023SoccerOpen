
#include <Cam.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
Cam::Cam()
{
  ball = 0;
  yellowGoal = 0;
  blueGoal = 0;
  buffer = "";
  validBallAngle = 0;
  dissapeared = false;
}
double Cam::CamCalc(Goal &goal)
{
  // Read the most recent byte
  // Serial.println("hi");
  // Serial.print(Serial2.available());
  if (Serial2.available() > 0)
  {

    for (int i = 0; i < Serial2.available(); i++)
    {
      read = Serial2.read();
      // Serial.println(buffer.c_str());
      if (read == 'b')
      {
        ball = strtod(buffer.c_str(), NULL);
        ball = FilterAngle(ball, validBallAngle);
        ball = dissapear(ball, actualBallDistance, validBallAngle);


        buffer = "";
        if (goal.lightGateOne() == true)
        {
          ball = 0;
        }
        else if (goal.lightGateTwo() == true)
        {
          ball = 180;
        }
        Serial.print("ball: ");
        Serial.println(ball);
        validBallAngle = ball;
      }

      else if (read == 'c')
      {
        blueGoal = strtod(buffer.c_str(), NULL);
        blueGoal = FilterAngle(blueGoal, validBlueAngle);
        // blueGoal =ComplimentaryFilterAngle(blueGoal, validBlueAngle);
        // Serial.print("blue: ");
        // Serial.println(blueGoal);
        buffer = "";
        validBlueAngle = blueGoal;
      }
      else if (read == 'd')
      {
        yellowGoal = strtod(buffer.c_str(), NULL);

        yellowGoal = FilterAngle(yellowGoal, validYellowAngle);
                Serial.print("yellow: ");
        Serial.println(yellowGoal);
        // yellowGoal = ComplimentaryFilterAngle(yellowGoal, validYellowAngle);
        buffer = "";
        validYellowAngle = yellowGoal;
      }
      else if (read == 'a')
      {
        ballDistance = strtod(buffer.c_str(), NULL);
        ballDistance = FilterAngle(ballDistance, validBallDistance);
        // actualBallDistance = ComplimentaryFilterDistance(ballDistance, validBallDistance);
        actualBallDistance = 6.8 * exp(0.019 * ballDistance);

        Serial.print("Actual Distance: ");
        Serial.println(actualBallDistance);
        buffer = "";
        validBallDistance = ballDistance;
      }
      else if (read == 'e')
      {
        yellowGoalDistance = strtod(buffer.c_str(), NULL);
        yellowGoalDistance = FilterAngle(yellowGoalDistance, validYellowGoalDistance);
        // yellowGoalDistance= ComplimentaryFilterDistance(yellowGoalDistance, validYellowGoalDistance);
        buffer = "";
        validYellowGoalDistance = yellowGoalDistance;
        // Serial.print("Yellow Goal Distance: ");
        // Serial.println(validYellowGoalDistance);
      }
      else if (read == 'f')
      {
        blueGoalDistance = strtod(buffer.c_str(), NULL);
        blueGoalDistance = FilterAngle(blueGoalDistance, validBlueGoalDistance);
        // blueGoalDistance = ComplimentaryFilterDistance(blueGoalDistance, validBlueGoalDistance);
        buffer = "";
        validBlueGoalDistance = blueGoalDistance;
        // Serial.print("Blue Goal Distance: ");
        // Serial.println(validBlueGoalDistance);
      }
      else
      {

        buffer += read;
        // Serial.println(atof(buffer.c_str()));
      }
    }
    // Serial.print(buffer);

    return 0;
  }
}
double Cam::FilterAngle(double angle, double validAngle)
{
  if (angle == -5)
  {
    return -5;
  }
  if (angle == 0)
  {
    return validAngle;
  }
  if (angle > 360 || angle < 0)
  {
    return validAngle;
  }
  else
  {
    return angle;
  }
}

double Cam::dissapear(double angle, double distance, double validAngle)
{
  if (dissapeared == true)
  {

    if (angle != -5)
    {
      validCounter++;
    }
    else
    {
      validCounter = 0;
    }
    if (validCounter >= 3)
    {
      dissapeared = false;
    }
    if (validDistance < 40)
    {
      return validAngle;
    }
    else{
      tooFar = true;
      return -5;
    }
  }
  else
  {
    if (invalidCounter >= 3)
    {

      dissapeared = true;
    }
    if (angle == -5)
    {
      invalidCounter++;
      return validAngle;
    }
    else
    {
      invalidCounter = 0;
      validDistance = distance;
      validAngle = angle;
      return ball;
    }
  }
}
double Cam::ComplimentaryFilterAngle(double angle, double validAngle)
{
  double diff = abs(angle - validAngle);
  diff = min(diff, 360 - diff);
  if (diff > 20)
  {
    return 0.1 * angle + 0.9 * validAngle;
  }
  else
  {
    return 0.9 * angle + 0.1 * validAngle;
  }
}

double Cam::ComplimentaryFilterDistance(double dist, double validDist)
{
  double diff = abs(dist - validDist);
  diff = min(diff, 360 - diff);
  if (diff > 20)
  {
    return 0.1 * dist + 0.9 * validDist;
  }
  else
  {
    return 0.9 * dist + 0.1 * validDist;
  }
}
