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
  dataNum = 0;
  validBallAngle = 0;
}
double Cam::CamCalc()
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
      if (read == 'a')
      {
        ball = strtod(buffer.c_str(), NULL);
        // Serial.print("ball: ");
        // Serial.println(ball);
        ball = FilterAngle(ball, validBallAngle);
        dataNum = 0;
        buffer = "";
        validBallAngle = ball;
      }

      // else if (read == '|'&& dataNum == 0)
      // // {
      // //   blueGoal = strtod(buffer.c_str(), NULL);
      // //   Serial.print("blue: ");
      // //   Serial.println(blueGoal);
      // //   dataNum++;
      // //   buffer = "";
      // // }
      // // else if (read == '|'&& dataNum == 1)
      // // {
      // //   yellowGoal = strtod(buffer.c_str(), NULL);
      // //   Serial.print("yellow: ");
      // //   Serial.println(yellowGoal);
      // //   dataNum++;
      // //   buffer = "";
      // // }
      // else if (read == '|'&& dataNum == 2)
      // {
      //   buff2 = strtod(buffer.c_str(), NULL);
      //   dataNum++;
      //   buffer = "";
      // }
      else
      {

        buffer += read;
        // Serial.println(atof(buffer.c_str()));
      }
    }
    // Serial.print(buffer);
  //   double width = abs(validBallAngle - dist2);
  //   if(width > 180){
  //     width = 360 - width;
  //   }
  //   width *= 0.1;
  //   if(validBallAngle > 180){
  //     if(dist2 <= validBallAngle && dist2 >= validBallAngle - 180){
  //       validBallAngle -= width;
  //     }
  //     else{
  //       validBallAngle += width;
  //     }
  //   }
  //   else{
  //     if(dist2 >= validBallAngle && dist2 <= validBallAngle + 180){
  //       validBallAngle += width;
  //     }
  //     else{
  //       validBallAngle -= width;
  //     }
  //   }
  //   if(validBallAngle > 360){
  //     validBallAngle -= 360;
  //   }
  //   if(validBallAngle < 0){
  //     validBallAngle += 360;
  //   }
    
  // }
  return 0;
}
}
double Cam::FilterAngle(double angle, double validAngle){
  if(angle == -5 || angle == 0){
    return validAngle;
  }
  if(angle > 360 || angle < 0){
    return validAngle;
  }
  else{
    return angle;
  }
}

