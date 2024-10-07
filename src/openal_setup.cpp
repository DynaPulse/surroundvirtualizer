// openal_setup.cpp
#include "openal_setup.h"
#include <AL/alext.h>
#include <iostream>

OpenALSetup::OpenALSetup() : device(nullptr), context(nullptr) {}

OpenALSetup::~OpenALSetup() {
    cleanup();
}

bool OpenALSetup::initialize(const std::string& hrtfFilePath, const std::string& deviceName) {
    device = alcOpenDevice(deviceName.empty() ? nullptr : deviceName.c_str()); // Open specified audio device or default
    if (!device) {
        std::cerr << "Failed to open audio device: " << (deviceName.empty() ? "default" : deviceName) << std::endl;
        return false;
    }

    // Check if HRTF extension is available
    if (alcIsExtensionPresent(device, "ALC_SOFT_HRTF")) {
        std::cout << "HRTF extension is available." << std::endl;
    }
    else {
        std::cerr << "HRTF extension is not available." << std::endl;
    }

    // Set attributes for context creation, including enabling HRTF if available
    ALCint attr[] = { ALC_HRTF_SOFT, ALC_TRUE, 0 };
    context = alcCreateContext(device, attr);
    if (!context || !alcMakeContextCurrent(context)) {
        std::cerr << "Failed to create or make context current." << std::endl;
        cleanup();
        return false;
    }

    // Confirm if HRTF was successfully enabled
    ALCint hrtfStatus;
    alcGetIntegerv(device, ALC_HRTF_SOFT, 1, &hrtfStatus);
    if (hrtfStatus == ALC_TRUE) {
        std::cout << "HRTF is enabled successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to enable HRTF." << std::endl;
    }

    return true;
}

void OpenALSetup::cleanup() {
    if (context) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
        context = nullptr;
    }
    if (device) {
        alcCloseDevice(device);
        device = nullptr;
    }
}