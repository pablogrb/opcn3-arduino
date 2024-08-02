#include "HistogramData.h"

float HistogramData::getTempC()
{
    return -45 + 175 * (temperature / (pow(2, 16) - 1));
}
float HistogramData::getTempF()
{
    return -49 + 347 * (temperature / (pow(2, 16) - 1));
}
float HistogramData::getHumidity()
{
    return 100 * (humidity / (pow(2, 16) - 1));
}

String HistogramData::toString() {

    String info = "-----Histogram Data-----\n";
    info += "Validity: ";
    info += valid;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Bin Counts";
    info += "\n";
    for (int i = 0; i < 24; i++) {
        info += binCounts[i];
        info += " ";
        if (i + 1 % 10 == 0) {
            info += "\n";
        }
    }
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Time To Cross";
    info += "\n";
    info += bin1TimeToCross;
    info += " ";
    info += bin3TimeToCross;
    info += " ";
    info += bin5TimeToCross;
    info += " ";
    info += bin7TimeToCross;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Sampling Period";
    info += "\n";
    info += samplingPeriod;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Sample Flow Rate";
    info += "\n";
    info += sampleFlowRate;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Temperature";
    info += "\n";
    info += temperature;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "Humidity";
    info += "\n";
    info += humidity;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "pm1";
    info += "\n";
    info += pm1;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "pm2.5";
    info += "\n";
    info += pm2_5;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "pm10";
    info += "\n";
    info += pm10;
    info += "\n";
    info += "-------------------------------------------------";
    info += "\n";
    info += "rCountGlitch, rCountLTOF, rCountRatio, rCountOOR, fanRevCount, laserStatus, checkSum";
    info += "\n";
    info += rejectCountGlitch;
    info += " ";
    info += rejectCountLongTOF;
    info += " ";
    info += rejectCountRatio;
    info += " ";
    info += rejectCountOutOfRange;
    info += " ";
    info += fanRevCount;
    info += " ";
    info += laserStatus;
    info += " ";
    info += checkSum;
    info += "";

    return info;
}