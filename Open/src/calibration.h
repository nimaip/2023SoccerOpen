#include <lineDetection.h>



class Calibration{

public:
Calibration();
void calibrate(int *lineVal);
void calState(LineDetection& lineDetection);
int *calVal;


private:

};