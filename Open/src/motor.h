#include <Arduino.h>
#include <trig.h>
#include <compassSensor.h>
#include <orbit.h>
#include <ESC.h>

#ifndef MOTOR_H
#define MOTOR_H
class Motor
{

public:
    Motor();
    void Move(double intended_angle, double motor_power, double robotOrientation);
    void Process(double intended_angle, double motor_power, double lineAngle, double robotOrientation, Orbit& orbit, bool backGate, int goalAngle, double Chord, bool linePresent, ESC& esc, int anglebisc, double homeAngle, int ballDistance, int ballAngle, bool defense);
    void Stop();
    double RecordDirection();
    double FindCorrection(double orientation, double robotOrientation);
    double getOrientation();
    void Spin(double speed, int direction);
    int projectionCalc(int anglebisc, int robotAngle);
    void FinalSpin(double speed, int direction);
    double slowDown(int ballDistance, int ballAngle, double motorPower);
    CompassSensor compassSensor;
    int dirAngle;
    double correction;
    bool defenseStop;

    double initialOrientation = 0;
private:
    double max_power;
    double powerFR;
    double powerFL;
    double powerRR;
    double powerRL;

    double speedFR;
    double speedFL;
    double speedRR;
    double speedRL;
    int controlFR;
    int controlFL;
    int controlRR;
    int controlRL;

    int pinspeedFR;
    int pinspeedFL;
    int pinspeedRR;
    int pinspeedRL;
    int pincontrolFR;
    int pincontrolFL;
    int pincontrolRR;
    int pincontrolRL;

    double orientationVal;
    int stopTime;
    bool setTime;
      double vectorX;
  double vectorY;
  double dotProduct;
  double denominator;
    double robotAngleX;
  double robotAngleY;
  bool projection;
  int goalAAngleSide;
};

#endif