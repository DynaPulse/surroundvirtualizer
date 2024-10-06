// cli_interface.h

#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include "portaudio_setup.h"

class CLIInterface {
public:
    void displayDevices(const std::vector<std::string>& devices, const std::string& deviceType);
    int getUserDeviceChoice();
    void showSelectedDevice(const std::string& deviceName, const std::string& deviceType);
};

#endif