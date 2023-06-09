#include <ESC.h>

ESC::ESC()
{

  esc1.attach(4, 1000, 2000);
  esc2.attach(6, 800, 2000);
  tick1 = 0;
  tick2 = 0;
  gradspeed1 = 0;
  gradspeed2 = 0;
}

void ESC::spinDribbler()
{
  dribbler1(95, 0);
}

void ESC::runDribbler(double ballAngle, double dist, bool capture1, bool capture2, bool inPos, bool defense)
{
  if(defense){
    dribbler1(0,0);
    dribbler2(0,0);
  }
  else{
  if (inPos)
    dribbler1(95, 0);
  else
  {
    double width = 40;
    if (ballAngle < width || ballAngle > 360 - width)
    { // front intake

      if (dist < 20 || capture1)
      {
        dribbler2(70, 0);
      }
      else
      {
        dribbler1(0, 1);
        dribbler2(0, 1);
      }
    }
    else
    {
      dribbler1(0, 1);
      dribbler2(0, 1);
    }
    if (ballAngle > 180 - width && ballAngle < 180 + width)
    {

      if (dist < 20 || capture2)
      {
        dribbler1(70, 0);
      }
      else
      {
        dribbler1(0, 1);
        // dribbler2(0, 1);
      }
    }
    else
    {
      dribbler1(0, 1);
      // dribbler2(0, 1);
    }
  }
  }
}

void ESC::dribbler1(int speed, int first)
{

  esc1.write(speed);
}

void ESC::dribbler2(int speed, int first)
{

  esc2.write(speed);
}