#include <Arduino.h>
#include <MCP3XXX.h>

class LineDetection{
    public:
        LineDetection();
        int *GetValues();
        double GetAngle();
    private:
        int *lineValues;
        MCP3008 adc1;
        MCP3008 adc2;
        MCP3008 adc3;
        MCP3008 adc4;
        MCP3008 adc5;
        MCP3008 adc6;
        

};