#include <calibration.h>
#include <Arduino.h>

Calibration::Calibration(){
  calVal = new int[48];
  for (int i = 0; i < 48; i++)
  {
      calVal[i] = 400;
  }
    
}

void Calibration::calibrate(int *lineVal){


for (int i = 0; i < 48; i++)
{
if(calVal[i]<lineVal[i])
{
    calVal[i] = lineVal[i];    
}

}
}

void Calibration::calState(LineDetection& lineDetection){
    if(digitalRead(40) == LOW){
        calibrate(lineDetection.GetValues());
    }
}