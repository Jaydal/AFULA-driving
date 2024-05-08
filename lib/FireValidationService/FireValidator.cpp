#include "FireValidator.h"
#include <Arduino.h>

const int flameSensorMin = 0;
const int flameSensorMax = 1024;

int FireValidator::ValidateWithIR(int sensor, int min, int max)
{
    int sensorReading = analogRead(sensor);
    int range = map(sensorReading, min, max, 0, 3);
    switch (range)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2;
        break;
    default:
        return 0;
        break;
    }
}
