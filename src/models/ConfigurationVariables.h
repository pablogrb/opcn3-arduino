#include <Arduino.h>

struct ConfigurationVariables
{

    uint16_t binBoundariesADC[25];

    uint16_t binBoundaryDiameters[25];

    uint16_t binWeights[24];

    uint16_t pmDiameterA;
    uint16_t pmDiameterB;
    uint16_t pmDiameterC;

    uint16_t maximumTimeOfFlight;
    uint16_t AMSamplingIntervalCount;
    uint16_t AMIdleIntervalCount;
    uint16_t AMMaxDataArraysInFile;

    uint8_t AMOnlySavePMData;
    uint8_t AMFanOnInIdle;

    bool valid;

    String toString();
};
