#include <Arduino.h>
#include <MCP3XXX.h>

class LineDetection{
    public:
        int initialAngle;
        LineDetection();
        int *GetValues();
        double GetAngle();
        double Process();
        double dotProduct[48];
        int anglebisc;
        bool linepresent;
        int avoidanceAngle;
     
    private:
        int *lineValues;
        MCP3008 adc1;
        MCP3008 adc2;
        MCP3008 adc3;
        MCP3008 adc4;
        MCP3008 adc5;
        MCP3008 adc6;
        bool negativeLow;
        
        double sensorAngles[48];
        double sinValues[48];
        double cosValues[48];

};