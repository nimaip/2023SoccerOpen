#include <ESC.h>

ESC::ESC(){

     esc1.attach(4,1000,2000);
     esc2.attach(6,1000,2000);
}

void ESC::dribbler1(int speed){
    esc1.write(speed);
}
void ESC::dribbler2(int speed){
    esc2.write(speed);
}