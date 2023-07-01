#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

Motor::Motor()
{
    // corresponding pin values on teensy
    pinspeedRL = 5;
    pinspeedRR = 3;
    pinspeedFL = 2;
    pinspeedFR = 24;
    pincontrolRL = 32;
    pincontrolRR = 0;
    pincontrolFL = 25;
    pincontrolFR = 1;

    defenseStop = false;

    pinMode(pinspeedFR, OUTPUT);
    pinMode(pinspeedFL, OUTPUT);
    pinMode(pinspeedRR, OUTPUT);
    pinMode(pinspeedRL, OUTPUT);
    pinMode(pincontrolFL, OUTPUT);
    pinMode(pincontrolFR, OUTPUT);
    pinMode(pincontrolRR, OUTPUT);
    pinMode(pincontrolRL, OUTPUT);
    max_power = 0;
};

void Motor::Process(double intended_angle, double motor_power, double lineAngle, double robotOrientation, Orbit &orbit, bool backGate, int goalAngle, double Chord, bool linePresent, ESC &esc, int anglebisc, double homeAngle, int ballDistance, int ballAngle, bool defense)
{
    if(defense == true){
        if(lineAngle != -1){
            Move(lineAngle, motor_power, robotOrientation);
        }
        else{
        Move(intended_angle, motor_power, robotOrientation);
        }
    }
    else{
    if (homeAngle != -1)
    {
        if (homeAngle == -2)
        {
            Stop();
        }
        else if (lineAngle != -1)
        {
            if (Chord < 0.8 && ((abs(anglebisc - homeAngle)) < 110))
            {
                lineAngle = projectionCalc(anglebisc, intended_angle);
                Move(lineAngle, motor_power, robotOrientation);
            }
            else
            {
                Move(lineAngle, motor_power, robotOrientation);
            }
        }
        else
        {
            Move(homeAngle, motor_power, robotOrientation);
        }
    }
    else
    {
        if (backGate == true)
        {
            if (lineAngle != -1 && Chord < 0.8 && ((abs(anglebisc - orbit.GetToSpinShotPosition(linePresent, goalAngle, anglebisc))) < 110))
            {
                projection = true;
            }
            else
            {
                projection = false;
            }
            if (lineAngle != -1 && orbit.inOrientation == false && projection == false)
            {
                robotOrientation = compassSensor.getOrientation();
                Move(lineAngle, 0.28, robotOrientation);
            }
            else if (orbit.inPos == true)
            {
                    orbit.GetToSpinShotPosition(linePresent, goalAngle, anglebisc);
                esc.spinDribbler();
                if (orbit.inOrientation == true)
                { 
                    if (setTime == true)
                    {
                        stopTime = millis() + 4000;
                        setTime = false;
                    }
                    esc.spinDribbler();
                    if (millis() >= (stopTime - 2000))
                    {
                        if(goalAAngleSide >180){
                           FinalSpin(0.2, -1); 
                        }
                        else{
                        FinalSpin(0.2, 1);
                        }
                    }
                }
                else{
                    setTime = true;
                }
                Spin(0.13, orbit.InOrientationSpinShot(compassSensor.getOrientation(), initialOrientation,goalAAngleSide));
            }
            else
            {
                
                goalAAngleSide = goalAngle;
                setTime = true;
                if (projection)
                {
                    Move(projectionCalc(anglebisc, orbit.GetToSpinShotPosition(linePresent, goalAngle, anglebisc)), 0.33, robotOrientation);
                }
                else
                {
                    Move(orbit.GetToSpinShotPosition(linePresent, goalAngle, anglebisc), 0.33, robotOrientation);
                }
            }
        }

        else if (lineAngle != -1)
        {
            orbit.inOrientation = false;
            orbit.inPos = false;
            if (Chord < 0.8 && ((abs(anglebisc - intended_angle)) < 90))
            {
                lineAngle = projectionCalc(anglebisc, intended_angle);
                Move(lineAngle, slowDown(ballDistance, ballAngle, motor_power), robotOrientation);
            }
            else
            {
                Move(lineAngle, slowDown(ballDistance, ballAngle, motor_power), robotOrientation);
            }
        }
        else
        {
            orbit.inOrientation = false;
            orbit.inPos = false;
            Move(intended_angle, slowDown(ballDistance, ballAngle, motor_power), robotOrientation);
        }
    }
    }
}

int Motor::projectionCalc(int anglebisc, int robotAngle)
{

    int lineAngle = anglebisc + 90;
    if (lineAngle > 360)
    {
        lineAngle = lineAngle - 360;
    }
    vectorX = sin(toRadians(lineAngle));
    vectorY = cos(toRadians(lineAngle));
    robotAngleX = sin(toRadians(robotAngle));
    robotAngleY = cos(toRadians(robotAngle));
    dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
    denominator = pow(vectorX, 2) + pow(vectorY, 2);
    robotAngleX = (dotProduct / denominator) * vectorX;
    robotAngleY = (dotProduct / denominator) * vectorY;

    double projectionAngle = toDegrees(atan2(robotAngleX, robotAngleY));
    if (projectionAngle < 0)
    {
        projectionAngle = projectionAngle + 360;
    }
    return projectionAngle;
}
void Motor::Move(double intended_angle, double motor_power, double robotOrientation)
{
    speedRR = 0;
    speedRL = 0;
    speedFL = 0;
    speedFR = 0;
    controlRR = 0;
    controlFR = 0;
    controlFL = 0;
    controlRL = 0;

    powerFR = sin(toRadians(intended_angle - 45));
    powerRR = sin(toRadians(intended_angle - 135));
    powerRL = sin(toRadians(intended_angle - 225));
    powerFL = sin(toRadians(intended_angle - 315));
    // find max_power among motors to scale
    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));
    // Serial.print("Max Power: ");
    // Serial.println(max_power);

    FindCorrection(compassSensor.getOrientation(), robotOrientation);
    // add correction to account for rotation needed

    // max_power += 0.01;
    // Serial.println(powerFR);
    // Serial.println(powerFL);
    // Serial.println(powerRR);
    // Serial.println(powerRL);
    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    powerFR += correction;
    powerFL += correction;
    powerRR += correction;
    powerRL += correction;

    controlRL = powerRL < 0 ? LOW : HIGH;
    controlRR = powerRR > 0 ? LOW : HIGH;
    controlFL = powerFL < 0 ? LOW : HIGH;
    controlFR = powerFR > 0 ? LOW : HIGH;

    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));

    speedFR = abs(powerFR) / max_power;
    speedFL = abs(powerFL) / max_power;
    speedRR = abs(powerRR) / max_power;
    speedRL = abs(powerRL) / max_power;

    int multiplier = 255;
    int intspeedFR = (int)((speedFR * multiplier) * motor_power);
    int intspeedFL = (int)((speedFL * multiplier) * motor_power);
    int intspeedRR = (int)((speedRR * multiplier) * motor_power);
    int intspeedRL = (int)((speedRL * multiplier) * motor_power);

    int motor_switch = 0;
    motor_switch = digitalRead(39);
    if (defenseStop == true)
    {
        Stop();
    }
    else if (motor_switch == HIGH)
    {
        analogWrite(pinspeedFR, intspeedFR);
        analogWrite(pinspeedFL, intspeedFL);
        analogWrite(pinspeedRR, intspeedRR);
        analogWrite(pinspeedRL, intspeedRL);
        digitalWrite(pincontrolFL, controlFL);
        digitalWrite(pincontrolFR, controlFR);
        digitalWrite(pincontrolRR, controlRR);
        digitalWrite(pincontrolRL, controlRL);
    }
    else
    {
        Stop();
    }
}

void Motor::Stop()
{
    analogWrite(pinspeedFR, 0);
    analogWrite(pinspeedFL, 0);
    analogWrite(pinspeedRL, 0);
    analogWrite(pinspeedRR, 0);
}
double Motor::RecordDirection()
{
    if (digitalRead(36) == LOW)
    {
        initialOrientation = compassSensor.getOrientation();
    }
    return initialOrientation;
}

double Motor::getOrientation()
{
    return compassSensor.getOrientation();
}

double Motor::FindCorrection(double orientation, double robotOrientation)
{

    orientationVal = abs(orientation - robotOrientation);

    // Serial.println(orientationVal);
    if (orientationVal > 180)
    {
        orientationVal = 360 - orientationVal;
    }
    if (robotOrientation < 180 && orientation > 180)
    {
        orientation = -1 * (360 - orientation);
    }
    else if (robotOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    if (orientation < robotOrientation)
    {
        orientationVal = -1 * orientationVal;
    }

    correction = -1 * (sin(toRadians(orientationVal)));
    correction *= 0.55;

    if (orientationVal > -5 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 5 && orientationVal > 0)
    {
        correction = 0;
    }
    else if (orientationVal > 90)
    {
        correction = -1;
    }
    else if (orientationVal < -90)
    {
        correction = 1;
    }

    Serial.println("Correction : ");
    Serial.println(correction);

    return correction;
}

void Motor::Spin(double speed, int direction)
{
    Serial.println("hello");
    speed *= 255;
    if (digitalRead(39) == HIGH)
    {
        controlRL = direction < 0 ? LOW : HIGH;
        controlRR = direction > 0 ? LOW : HIGH;
        controlFL = direction < 0 ? LOW : HIGH;
        controlFR = direction > 0 ? LOW : HIGH;
        analogWrite(pinspeedFR, speed);
        analogWrite(pinspeedFL, speed);
        analogWrite(pinspeedRR, speed);
        analogWrite(pinspeedRL, speed);
        digitalWrite(pincontrolFL, controlFL);
        digitalWrite(pincontrolFR, controlFR);
        digitalWrite(pincontrolRR, controlRR);
        digitalWrite(pincontrolRL, controlRL);
    }
    else
    {
        Stop();
    }
}

void Motor::FinalSpin(double speed, int direction)
{
    speed *= 255;
    if (digitalRead(39) == HIGH)
    {
        controlRL = direction < 0 ? LOW : HIGH;
        controlRR = direction > 0 ? LOW : HIGH;
        controlFL = direction < 0 ? LOW : HIGH;
        controlFR = direction > 0 ? LOW : HIGH;
        analogWrite(pinspeedFR, speed);
        analogWrite(pinspeedFL, speed);
        analogWrite(pinspeedRR, speed);
        analogWrite(pinspeedRL, speed);
        digitalWrite(pincontrolFL, controlFL);
        digitalWrite(pincontrolFR, controlFR);
        digitalWrite(pincontrolRR, controlRR);
        digitalWrite(pincontrolRL, controlRL);
        delay(300);
Stop();
        delay(1000);
    }
    else
    {
        Stop();
    }
}

double Motor::slowDown(int ballDistance, int ballAngle, double motorPower){
    if(ballAngle<195 && ballAngle>165 && ballDistance < 20){
        return 0.36;
    }
    else{
        return motorPower;
    }
}
