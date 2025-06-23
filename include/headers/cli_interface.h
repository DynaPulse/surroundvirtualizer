// cli_interface.h
#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <string>
#include <vector>

/**
 * @class CLIInterface
 * @brief Handles command-line user interaction for device and HRTF selection.
 */
class CLIInterface {
public:
    /**
     * @brief Constructor.
     */
    CLIInterface();
    /**
     * @brief Destructor.
     */
    ~CLIInterface();
    /**
     * @brief Displays the main menu to the user.
     */
    void displayMenu();
    /**
     * @brief Prompts the user to select a playback device index.
     * @param deviceList List of available playback device names.
     * @return Selected device index, or -1 if none selected.
     */
    int getSelectedDeviceIndex(const std::vector<std::string>& deviceList);
    /**
     * @brief Returns the default HRTF file path from the repository.
     * @return The default HRTF file path.
     */
    std::string getHRTFFilePath();
    /**
     * @brief Lists available playback devices to the user.
     */
    void listPlaybackDevices();
    /**
     * @brief Returns a list of available playback device names.
     * @return Vector of device names.
     */
    std::vector<std::string> getAvailablePlaybackDevices();
    /**
     * @brief Lists available input (capture) devices to the user.
     */
    void listInputDevices();
    /**
     * @brief Returns a list of available input (capture) device names.
     * @return Vector of input device names.
     */
    std::vector<std::string> getAvailableInputDevices();
    /**
     * @brief Prompts the user to select an input device index.
     * @param deviceList List of available input device names.
     * @return Selected device index, or -1 if none selected.
     */
    int getSelectedInputDeviceIndex(const std::vector<std::string>& deviceList);
};

#endif // CLI_INTERFACE_H