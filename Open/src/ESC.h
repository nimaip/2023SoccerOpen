#include<Servo.h>

class ESC
{
private:
    Servo esc1;
     Servo esc2;
public:
    ESC();
    void dribbler1(int speed);
    void dribbler2(int speed);
};

