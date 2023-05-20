#include <Cam.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
Cam::Cam()
{
  buff = 0;
  dist = 0;
  buffer = "";
  angleAverage = new int[20];
  distAverage = new int[20];
  angle2Average = new int[20];
  dist2Average = new int[20];
  dataNum = 0;
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
      Serial.println(buffer.c_str());
      if (read == 'a')
      {
        dist2 = strtod(buffer.c_str(), NULL);
        dataNum = 0;
        buffer = "";
      }

      else if (read == '|'&& dataNum == 0)
      {
        buff = strtod(buffer.c_str(), NULL);
        dataNum++;
        buffer = "";
      }
      else if (read == '|'&& dataNum == 1)
      {
        dist = strtod(buffer.c_str(), NULL);
        dataNum++;
        buffer = "";
      }
      else if (read == '|'&& dataNum == 2)
      {
        buff2 = strtod(buffer.c_str(), NULL);
        dataNum++;
        buffer = "";
      }
      else
      {

        buffer += read;
        //Serial.println(atof(buffer.c_str()));
      }
    }
  }
  return 0;
};