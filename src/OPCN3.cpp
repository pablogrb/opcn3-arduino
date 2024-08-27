#include "OPCN3.h"

#include <Arduino.h>
#include <SPI.h>

// class for logging to serial at different levels
class Logger
{
private:
    // log level
    String logLevel = "info";
public:
    // set log level
    void setLogLevel(String level) {
        if (level == "info" || level == "debug" || level == "error" || level == "quiet") {
            logLevel = level;
        } else {
            Serial.println("Invalid log level, defaulting to info");
        }
    }

    // write to serial at the info, debug, and error levels
    void info(String message) {
        if (logLevel == "info" || logLevel == "debug" || logLevel == "error") {
            Serial.println(message);
        }
    }

    void debug(String message) {
        if (logLevel == "debug" || logLevel == "error") {
            Serial.println(message);
        }
    }

    void error(String message) {
        if (logLevel == "error") {
            Serial.println(message);
        }
    }
};

// create a logger
Logger logger;

// char buffer for printing to serial
char serialBuffer[256];

OPCN3::OPCN3(uint8_t pinSelect, uint32_t speedSelect)
{
    _ssPin = pinSelect;
    _speedMaximum = speedSelect;
}

// Alpha Sensor Functions
void OPCN3::begin()
{
    logger.info("Initializing SPI ");
    // set ss pin to output
    pinMode(_ssPin, OUTPUT);
    SPI.begin();
    // set speed, order and mode
    SPI.beginTransaction(SPISettings(_speedMaximum, MSBFIRST, SPI_MODE1));
    delay(1000);
}

void OPCN3::initialize(String logLevel)
{
    // set the log level
    logger.setLogLevel(logLevel);
    // Initialize the OPC-N3
    delay(1000);
    logger.info("Initialize");
    delay(1000);
    begin();
    delay(1000);
    logger.info("Serial Number:");
    readSerialNumber();
    delay(1000);
    logger.info("DACandPowerStatus");
    readDACandPowerStatus();
    delay(1000);
    logger.debug("ConfigurationVariables");
    readConfigurationVariables();
    delay(10000);
    logger.info("Turn Fan on");
    struct FanDigitalPotShutdownState fanState = setFanDigitalPotShutdownState(true);
    delay(1000);
    logger.info("Turn Laser on");
    struct LaserDigitalPotShutdownState laserState = setLaserDigitalPotShutdownState(true);
    delay(1000);
    logger.info("Turn Laser Switch on");
    struct LaserPowerSwitchState laserPowerState = setLaserPowerSwitchState(true);
    delay(1000);
    logger.info("High Gain");
    struct HighLowGainState gainState = setHighLowGainState(true);
    delay(2000);
    bool reset = resetHistogram();
    delay(2000);
}

struct DACandPowerStatus OPCN3::readDACandPowerStatus()
{
    DACandPowerStatus dACandPowerStatus = sendCommand<DACandPowerStatus>(0X13, 0X13, 6);
    logger.info(dACandPowerStatus.toString());
    return dACandPowerStatus;
}

struct FanDigitalPotShutdownState OPCN3::setFanDigitalPotShutdownState(bool status)
{
    byte commandByte = status ? 0X03 : 0X02;
    FanDigitalPotShutdownState fanDigitalPotShutdownState = sendCommand<FanDigitalPotShutdownState>(0X03, commandByte, 1);
    fanDigitalPotShutdownState.fanOn = status;
    // write the status of the fan to the fanState variable as an On/Off string
    char fanState[3];
    if (fanDigitalPotShutdownState.fanOn) {
        sprintf(fanState, "On ");
    } else {
        sprintf(fanState, "Off");
    }
    // print the validity and the status of the fan
    sprintf(serialBuffer, "Validity: %d, Status: %s", fanDigitalPotShutdownState.valid, fanState);
    logger.info(serialBuffer);
    return fanDigitalPotShutdownState;
}

struct LaserDigitalPotShutdownState OPCN3::setLaserDigitalPotShutdownState(bool status)
{
    byte commandByte = status ? 0X05 : 0X04;
    LaserDigitalPotShutdownState laserDigitalPotShutdownState = sendCommand<LaserDigitalPotShutdownState>(0X03, commandByte, 1);
    laserDigitalPotShutdownState.laserOn = status;
    // write the status of the laser to the laserState variable as an On/Off string
    char laserState[3];
    if (laserDigitalPotShutdownState.laserOn) {
        sprintf(laserState, "On ");
    } else {
        sprintf(laserState, "Off");
    }
    // print the validity and the status of the laser
    sprintf(serialBuffer, "Validity: %d, Status: %s", laserDigitalPotShutdownState.valid, laserState);
    logger.info(serialBuffer);
    return laserDigitalPotShutdownState;
}

struct LaserPowerSwitchState OPCN3::setLaserPowerSwitchState(bool status)
{
    byte commandByte = status ? 0X07 : 0X06;
    LaserPowerSwitchState laserPowerSwitchState = sendCommand<LaserPowerSwitchState>(0X03, commandByte, 1);
    laserPowerSwitchState.laserOn = status;
    // write the status of the laser swtich to the laserState variable as an On/Off string
    char laserState[3];
    if (laserPowerSwitchState.laserOn) {
        sprintf(laserState, "On ");
    } else {
        sprintf(laserState, "Off");
    }
    // print the validity and the status of the laser switch
    sprintf(serialBuffer, "Validity: %d, Status: %s", laserPowerSwitchState.valid, laserState);
    logger.info(serialBuffer);
    return laserPowerSwitchState;
}

struct HighLowGainState OPCN3::setHighLowGainState(bool status)
{
    byte commandByte = status ? 0X10 : 0X11;
    HighLowGainState highLowGainState = sendCommand<HighLowGainState>(0X03, commandByte, 1);
    highLowGainState.highLow = status;
    // write the status of the Gain to the laserState variable as an High/Low string
    char gainState[4];
    if (highLowGainState.highLow) {
        sprintf(gainState, "High");
    } else {
        sprintf(gainState, "Low ");
    }
    // print the validity and the status of the gain
    sprintf(serialBuffer, "Validity: %d, Status: %s", highLowGainState.valid, gainState);
    logger.info(serialBuffer);
    return highLowGainState;
}

struct HistogramData OPCN3::readHistogramData()
{
    HistogramData histogramData = sendCommand<HistogramData>(0X30, 0X30, 86);
    logger.debug(histogramData.toString());
    return histogramData;
}

bool OPCN3::resetHistogram()
{
    HistogramData data = readHistogramData();
    return data.valid;
}

struct SerialNumber OPCN3::readSerialNumber()
{
    SerialNumber serialNumber = sendCommand<SerialNumber>(0X10, 0X10, 60);
    String serialString = "";
    for (int i = 0; i < 60; i++)
    {
        serialString += String(serialNumber.serial[i]);
    }
    sprintf(serialBuffer, "Validity: %d Serial Number: %s", serialNumber.valid, serialString.c_str());
    logger.info(serialBuffer);
    return serialNumber;
}

struct ConfigurationVariables OPCN3::readConfigurationVariables()
{
    ConfigurationVariables configurationVariables = sendCommand<ConfigurationVariables>(0X3C, 0X3C, 163);
    logger.debug(configurationVariables.toString());
    return configurationVariables;
}

void OPCN3::beginTransfer()
{
    digitalWrite(_ssPin, LOW);
    delay(1);
}

void OPCN3::endTransfer()
{
    delay(1);
    digitalWrite(_ssPin, HIGH);
}

bool OPCN3::validate(byte arrayOne[], byte arrayTwo[], int size)
{
    bool valid = true;
    for (int i = 0; i < size; i++)
    {
        if (arrayOne[i] != arrayTwo[i])
        {
            valid = false;
        }
    }

    return valid;
}
