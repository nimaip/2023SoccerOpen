#include <lineDetection.h>
#include <math.h>
#include <trig.h>

LineDetection::LineDetection()
{
    // Constructor
    lineValues = new int[48];
    adc1.begin(23, 11, 12, 13);
    adc2.begin(22, 11, 12, 13);
    adc3.begin(21, 11, 12, 13);
    adc4.begin(20, 11, 12, 13);
    adc5.begin(15, 11, 12, 13);
    adc6.begin(9, 11, 12, 13);

    for (int i = 0; i < 48; i++)
    {
        sensorAngles[i] = i * 7.5;
        cosValues[i] = cos(toRadians(sensorAngles[i]));
        sinValues[i] = sin(toRadians(sensorAngles[i]));
    }
    initialAngle = -1;
    lineSwitch = false;
    outOfBounds = false;
}

int *LineDetection::GetValues()
{
    for (int i = 0; i < 48; i++)
    {
        int adcNumber = i / 8;
        int val = 0;
        int channel = i % 8;

        switch (adcNumber)
        {
        case (0):
            digitalWrite(23, LOW);
            val = adc1.analogRead(channel);
            digitalWrite(23, HIGH);
            break;
        case (1):
            digitalWrite(22, LOW);
            val = adc2.analogRead(channel);
            digitalWrite(22, HIGH);
            break;
        case (2):
            digitalWrite(21, LOW);
            val = adc3.analogRead(channel);
            digitalWrite(21, HIGH);
            break;
        case (3):
            digitalWrite(20, LOW);
            val = adc4.analogRead(channel);
            digitalWrite(20, HIGH);
            break;
        case (4):
            digitalWrite(15, LOW);
            val = adc5.analogRead(channel);
            digitalWrite(15, HIGH);
            break;
        case (5):
            digitalWrite(9, LOW);
            val = adc6.analogRead(channel);
            digitalWrite(9, HIGH);
            break;
        default:
            break;
        }
        lineValues[i] = val;
    }
    // for(int i = 0; i < 48; i++){
    //     Serial.print(i);
    //     Serial.print(": ");
    //     Serial.println(lineValues[i]);
    // }
    return lineValues;
};

double LineDetection::GetAngle(int *calibrateVal)
{
    lineValues = GetValues();
    linepresent = false;
    double totalCos = 0;
    double totalSin = 0;

    for (int i = 0; i < 48; i++)
    {
        if (lineValues[i] < calibrateVal[i]+40)
        {

            lineValues[i] = 0;
            dotProduct[i] = 0;
        }
        else
        {
            lineValues[i] = 1;
            linepresent = true;
            dotProduct[i] = sensorAngles[i];
        }
    }

    double lowestDot = 2;
    int firstAngle = 0, secondAngle = 0;
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            if (dotProduct[i] != 0 && dotProduct[j] != 0)
            {
                double dot = (sinValues[i] * sinValues[j]) + (cosValues[i] * cosValues[j]);
                if (dot < lowestDot)
                {
                    lowestDot = dot;
                    firstAngle = i;
                    secondAngle = j;
                }
            }
        }
    }

    // Serial.print("First Angle: ");
    // Serial.println(firstAngle);
    // Serial.print("Second Angle: ");
    // Serial.println(secondAngle);

    totalCos = cosValues[firstAngle] + cosValues[secondAngle];
    totalSin = sinValues[firstAngle] + sinValues[secondAngle];

    anglebisc = toDegrees(atan2(totalCos, totalSin));
    sensorAngle = abs(sensorAngles[firstAngle] - sensorAngles[secondAngle]);
    if (sensorAngle > 180)
    {
        sensorAngle = 360 - sensorAngle;
    }
    if (totalCos == 0 && totalSin == 0)
    {
        anglebisc = initialAngle;
    }
    if (anglebisc < 0)
        anglebisc = 360 + anglebisc;

    return anglebisc; // returns direction the line is in
}

double LineDetection::Chord()
{
    if (lineSwitch == true)
    {
        return 2 - (1 * sin(toRadians(sensorAngle / 2)));
    }
    return (1 * sin(toRadians(sensorAngle / 2)));
}

double LineDetection::Process(int *calibrateVal)
{
    // MAKE SURE YOU CALL THE PREVIOUS METHOD OTHERWISE NOTHING HAPPENS
    GetAngle(calibrateVal);
    if (linepresent == true)
    {
        outOfBounds = false;

        if (initialAngle == -1)
        {
            initialAngle = anglebisc;
        }
        currentAngle = anglebisc;
        angleDiff = abs(currentAngle - initialAngle);
        initialAngle = currentAngle;
        if (angleDiff > 180)
        {
            angleDiff = 360 - angleDiff;
        }
        // Serial.print("angle Diff: ");
        // Serial.println(angleDiff);
        if (angleDiff > 90 && lineSwitch == false)
        {
            lineSwitch = true;
            angleDiff = 0;
        }
        if (lineSwitch == true)
        {
            avoidanceAngle = anglebisc;
            if (angleDiff > 90)
            {
                lineSwitch = false;
            }
        }
        // Serial.println(lineSwitch);
        if (lineSwitch == false)
        {
            avoidanceAngle = anglebisc + 180;
            if (avoidanceAngle > 360)
            {
                avoidanceAngle = avoidanceAngle - 360;
            }
        }
    }
    else if (linepresent == false)
    {
        if (lineSwitch == true)
        {
            outOfBounds = true;
        }

        else
        {
            initialAngle = -1;
            avoidanceAngle = -1;
            lineSwitch = false;
        }
    }
    Serial.print("line: ");
    Serial.println(avoidanceAngle);
    return avoidanceAngle;
};