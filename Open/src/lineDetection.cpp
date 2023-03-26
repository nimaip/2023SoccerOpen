#include "lineDetection.h"

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
        int adcNumber = i/6;
        int val = 0;
        int channel = i % 8;

        switch(adcNumber){
            case(0):
                digitalWrite(23, LOW);
                val = adc1.analogRead(channel);
                break;
             case(1):
                digitalWrite(22, LOW);
                val = adc2.analogRead(channel);
                break;
             case(2):
                digitalWrite(21, LOW);
                val = adc3.analogRead(channel);
                break;
             case(3):
                digitalWrite(20, LOW);
                val = adc4.analogRead(channel);
                break;
            case(4):
                digitalWrite(15, LOW);
                val = adc5.analogRead(channel);
                break;
             case(5):
                digitalWrite(9, LOW);
                val = adc6.analogRead(channel);
                break;
            default:
                break;

            lineValues[i] = val;
        }
    }
};

double LineDetection::GetAngle(){

}