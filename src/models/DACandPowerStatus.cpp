#include "DACandPowerStatus.h"

String DACandPowerStatus::toString()
{
    String info = "Validity: ";
    info += valid;
    info += "\n";
    info += "Fan: ";
    info += fanOn;
    info += ", LaserDac: ";
    info += laserDACOn;
    info += ", FanDAcVal: ";
    info += fanDACVal;
    info += ", laserDACVal ";
    info += laserDACVal;
    info += ", Laser Switch: ";
    info += laserSwitch;
    info += ", gain and autogain toggle setting: ";
    info += gainAndAutoGainToggleSetting;
    return info;
}
