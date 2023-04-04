#include <Arduino.h>
#include <MCP3XXX.h>

class LineDetection{
    public:
        int initialAngle;
        LineDetection();
        int *GetValues();
        double GetAngle(int *calibrateVal, int *lineVal, int *sensorVal, double *sinVal, double *cosVal);
        int *sensorAngles;
        double *dotProduct;
        int anglebisc;
     
    private:
        int *lineValues;
        MCP3008 adc1;
        MCP3008 adc2;
        MCP3008 adc3;
        MCP3008 adc4;
        MCP3008 adc5;
        MCP3008 adc6;
        bool negativeLow;
        bool linepresent;
        
};