// cli_interface.cpp

#include "cli_interface.h"


void CLIInterface::displayDevices(const std::vector<std::string>& devices, const std::string& deviceType) {
    std::cout << "Available " << deviceType << " Devices:\n";
    for (size_t i = 0; i < devices.size(); ++i) {
        std::cout << i + 1 << ": " << devices[i] << std::endl;
    }
}

int CLIInterface::getUserDeviceChoice() {
    int choice;
    std::cout << "Select a device by number: ";
    std::cin >> choice;
    return choice - 1;  // Adjust for 0-based index
}

void CLIInterface::showSelectedDevice(const std::string& deviceName, const std::string& deviceType) {
    std::cout << "Selected " << deviceType << " Device: " << deviceName << std::endl;
}