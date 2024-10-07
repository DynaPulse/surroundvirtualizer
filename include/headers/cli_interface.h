// cli_interface.h
#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <string>
#include <vector>

class CLIInterface {
public:
    CLIInterface();
    ~CLIInterface();
    void displayMenu();
    int getSelectedDeviceIndex(const std::vector<std::string>& deviceList);
    std::string getHRTFFilePath();
    void listPlaybackDevices();
    std::vector<std::string> getAvailablePlaybackDevices();
};

#endif // CLI_INTERFACE_H