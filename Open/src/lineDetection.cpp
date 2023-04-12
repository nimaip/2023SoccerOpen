#include <lineDetection.h>
#include <math.h>
#include <trig.h>

LineDetection::LineDetection(){
    //Constructor
    lineValues = new int[48];
    adc1.begin(23,11, 12, 13);
    adc2.begin(22,11, 12, 13);
    adc3.begin(21,11, 12, 13);
    adc4.begin(20,11, 12, 13);
    adc5.begin(15,11, 12, 13);
    adc6.begin(9,11, 12, 13);
    
}

int *LineDetection::GetValues()
{
    for(int i = 0; i < 48; i++){
        int adcNumber = i/8;
        int val = 0;
        int channel = i % 8;

        switch(adcNumber){
            case(0):
                digitalWrite(23, LOW);
                val = adc1.analogRead(channel);
                digitalWrite(23, HIGH);
                break;
             case(1):
                digitalWrite(22, LOW);
                val = adc2.analogRead(channel);
                digitalWrite(22, HIGH);
                break;
             case(2):
                digitalWrite(21, LOW);
                val = adc3.analogRead(channel);
                digitalWrite(21, HIGH);
                break;
             case(3):
                digitalWrite(20, LOW);
                val = adc4.analogRead(channel);
                digitalWrite(20, HIGH);
                break;
            case(4):
                digitalWrite(15, LOW);
                val = adc5.analogRead(channel);
                digitalWrite(15, HIGH);
                break;
             case(5):
                digitalWrite(9, LOW);
                val = adc6.analogRead(channel);
                digitalWrite(9, HIGH);
                break;
            default:
                break;

            
        }
        lineValues[i] = val;
            
    }
    int x = 3;
    for(int i = 8*x; i < 8*x + 8; i++){
         Serial.print(i);
         Serial.print(" Line sensor : ");
         Serial.println(lineValues[i]);
    }
    // int y = adc2.analogRead(1);
    // Serial.println(y);
    Serial.println();
    return lineValues;
};

 double LineDetection::GetAngle(int *calibrateVal, int *lineVal, int *sensorVal, double *sinVal, double *cosVal){
    lineValues = lineVal;
    sensorAngles = sensorVal;
    negativeLow = false;

    initialAngle = -1;
    linepresent = false;
    double *cosValues = cosVal;
    double *sinValues = sinVal;
    double totalCos = 0;
    double totalSin = 0;  

    for (int i = 0; i < 24; i++)
        {
            if (lineValues[i] < calibrateVal[i])
            {

                lineValues[i] = 0;
                dotProduct[i] = 0;
            }
            else
            {
                lineValues[i] = 1;
                linepresent = true;
                dotProduct[i] = sensorAngles[i];
            }        
        }

    int lowestDot = 2;
    int firstAngle =  0, secondAngle = 0;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (dotProduct[i] != 0 && dotProduct[j] != 0)
            {
                int dot = (sinValues[i] * sinValues[j]) + (cosValues[i] * cosValues[j]);
                if (dot < lowestDot)
                {
                    lowestDot = dot;
                    firstAngle = i;
                    secondAngle = j;
                }
            }
        }
    }

    totalCos = cosValues[firstAngle] + cosValues[secondAngle];
    totalSin = sinValues[firstAngle] + sinValues[secondAngle];
                
    anglebisc = toDegrees(atan2(totalCos, totalSin));
    int sensorAngle = abs(sensorAngles[firstAngle]-sensorAngles[secondAngle]);
       if (sensorAngle > 180)
    {
        sensorAngle = 360 - sensorAngle;
    }

    if (totalCos == 0 && totalSin == 0)
    {
        anglebisc = initialAngle;
    }
    if (anglebisc < 0)
    {

        anglebisc = anglebisc + 360;
    }
    return anglebisc;   
}