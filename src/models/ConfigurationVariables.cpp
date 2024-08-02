#include "ConfigurationVariables.h"

String ConfigurationVariables::toString() {
    String info = "Validity: ";
    info += valid;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Bin Boundaries ADC";
    info += "\n";
    for (int i = 0; i < 25; i++) {
        info += binBoundariesADC[i];
        info += " ";
        if (i + 1 % 10 == 0) {
            info += "\n";
        }
    }
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Bin Boundary Diameters um x 100";
    info += "\n";
    for (int i = 0; i < 25; i++) {
        info += binBoundaryDiameters[i];
        info += " ";
        if (i + 1 % 10 == 0) {
            info += "\n";
        }
    }
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Bin Weights %";
    info += "\n";
    for (int i = 0; i < 24; i++) {
        info += binWeights[i];
        info += " ";
        if (i + 1 % 10 == 0) {
            info += "\n";
        }
    } 
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "PM Diameters um x 100";
    info += "\n";
    info += pmDiameterA;
    info += " ";
    info += pmDiameterB;
    info += " ";
    info += pmDiameterC;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "MaxTOF SmpInt IdleInt MaxData SavePM FanOnIdle";
    info += "\n";
    info += maximumTimeOfFlight;
    info += " ";
    info += AMSamplingIntervalCount;
    info += " ";
    info += AMIdleIntervalCount;
    info += " ";
    info += AMMaxDataArraysInFile;
    info += " ";
    info += AMOnlySavePMData;
    info += " ";
    info += AMFanOnInIdle;
    info += " ";

    return info;
}
