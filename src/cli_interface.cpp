// cli_interface.cpp
#include "cli_interface.h"
#include <portaudio.h>
#include <iostream>

CLIInterface::CLIInterface() {}
CLIInterface::~CLIInterface() {}

void CLIInterface::displayMenu() {
    std::cout << "Select playback device and HRTF file for surround virtualization." << std::endl;
}

std::vector<std::string> CLIInterface::getAvailablePlaybackDevices() {
    std::vector<std::string> deviceList;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "ERROR: Pa_Initialize failed: " << Pa_GetErrorText(err) << std::endl;
        return deviceList;
    }

    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        std::cerr << "ERROR: Pa_GetDeviceCount returned " << numDevices << " - " << Pa_GetErrorText(numDevices) << std::endl;
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
        std::cerr << "No playback devices available." << std::endl;
        return;
    }
    std::cout << "Available playback devices:" << std::endl;
    for (size_t i = 0; i < deviceList.size(); ++i) {
        std::cout << i << ": " << deviceList[i] << std::endl;
    }
}

int CLIInterface::getSelectedDeviceIndex(const std::vector<std::string>& deviceList) {
    if (deviceList.empty()) {
        std::cerr << "No playback devices available to select." << std::endl;
        return -1;
    }
    int deviceIndex = -1;
    while (deviceIndex < 0 || deviceIndex >= static_cast<int>(deviceList.size())) {
        std::cout << "Enter the index of the playback device: ";
        std::cin >> deviceIndex;
        if (deviceIndex < 0 || deviceIndex >= static_cast<int>(deviceList.size())) {
            std::cerr << "Invalid index. Please enter a valid device index." << std::endl;
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