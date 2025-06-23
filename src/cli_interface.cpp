// cli_interface.cpp
#include "cli_interface.h"
#include "logging.h"
#include <portaudio.h>
#include <iostream>

CLIInterface::CLIInterface() {}
CLIInterface::~CLIInterface() {}

void CLIInterface::displayMenu() {
    Logger::log("Select playback device and HRTF file for surround virtualization.");
}

std::vector<std::string> CLIInterface::getAvailablePlaybackDevices() {
    std::vector<std::string> deviceList;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        Logger::log(std::string("Pa_Initialize failed: ") + Pa_GetErrorText(err), Logger::ERROR);
        return deviceList;
    }

    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        Logger::log(std::string("Pa_GetDeviceCount returned ") + std::to_string(numDevices) + " - " + Pa_GetErrorText(numDevices), Logger::ERROR);
        return deviceList;
    }
    for (int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if (deviceInfo && deviceInfo->maxOutputChannels > 0) {
            deviceList.push_back(deviceInfo->name);
        }
    }

    Pa_Terminate();
    return deviceList;
}

void CLIInterface::listPlaybackDevices() {
    auto deviceList = getAvailablePlaybackDevices();
    if (deviceList.empty()) {
        Logger::log("No playback devices available.", Logger::WARNING);
        return;
    }
    Logger::log("Available playback devices:");
    for (size_t i = 0; i < deviceList.size(); ++i) {
        std::cout << i << ": " << deviceList[i] << std::endl;
    }
}

int CLIInterface::getSelectedDeviceIndex(const std::vector<std::string>& deviceList) {
    if (deviceList.empty()) {
        Logger::log("No playback devices available to select.", Logger::ERROR);
        return -1;
    }
    int deviceIndex = -1;
    while (deviceIndex < 0 || deviceIndex >= static_cast<int>(deviceList.size())) {
        std::cout << "Enter the index of the playback device: ";
        std::cin >> deviceIndex;
        if (deviceIndex < 0 || deviceIndex >= static_cast<int>(deviceList.size())) {
            Logger::log("Invalid index. Please enter a valid device index.", Logger::WARNING);
        }
    }
    return deviceIndex;
}

std::string CLIInterface::getHRTFFilePath() {
    std::string filePath;
    std::cout << "Enter the path to the HRTF file: ";
    std::cin.ignore();
    std::getline(std::cin, filePath);
    return filePath;
}

std::vector<std::string> CLIInterface::getAvailableInputDevices() {
    std::vector<std::string> deviceList;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        Logger::log(std::string("Pa_Initialize failed: ") + Pa_GetErrorText(err), Logger::ERROR);
        return deviceList;
    }
    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        Logger::log(std::string("Pa_GetDeviceCount returned ") + std::to_string(numDevices) + " - " + Pa_GetErrorText(numDevices), Logger::ERROR);
        return deviceList;
    }
    for (int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if (deviceInfo && deviceInfo->maxInputChannels > 0) {
            deviceList.push_back(deviceInfo->name);
        }
    }
    Pa_Terminate();
    return deviceList;
}

void CLIInterface::listInputDevices() {
    auto deviceList = getAvailableInputDevices();
    if (deviceList.empty()) {
        Logger::log("No input devices available.", Logger::WARNING);
        return;
    }
    Logger::log("Available input devices:");
    for (size_t i = 0; i < deviceList.size(); ++i) {
        std::cout << i << ": " << deviceList[i] << std::endl;
    }
}

int CLIInterface::getSelectedInputDeviceIndex(const std::vector<std::string>& deviceList) {
    if (deviceList.empty()) {
        Logger::log("No input devices available to select.", Logger::ERROR);
        return -1;
    }
    int deviceIndex = -1;
    while (deviceIndex < 0 || deviceIndex >= static_cast<int>(deviceList.size())) {
        std::cout << "Enter the index of the input device: ";
        std::cin >> deviceIndex;
        if (deviceIndex < 0 || deviceIndex >= static_cast<int>(deviceList.size())) {
            Logger::log("Invalid index. Please enter a valid input device index.", Logger::WARNING);
        }
    }
    return deviceIndex;
}