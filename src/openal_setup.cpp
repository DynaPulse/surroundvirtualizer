// openal_setup.cpp
#include "openal_setup.h"
#include "logging.h"
#include <AL/alext.h>

OpenALSetup::OpenALSetup() : device(nullptr), context(nullptr) {}

OpenALSetup::~OpenALSetup() {
    cleanup();
}

bool OpenALSetup::initialize(const std::string& hrtfFilePath, const std::string& deviceName) {
    device = alcOpenDevice(deviceName.empty() ? nullptr : deviceName.c_str()); // Open specified audio device or default
    if (!device) {
        Logger::log(std::string("Failed to open audio device: ") + (deviceName.empty() ? "default" : deviceName), Logger::ERROR);
        return false;
    }

    // Check if HRTF extension is available
    if (alcIsExtensionPresent(device, "ALC_SOFT_HRTF")) {
        Logger::log("HRTF extension is available.");
    }
    else {
        Logger::log("HRTF extension is not available.", Logger::WARNING);
    }

    // Set attributes for context creation, including enabling HRTF if available
    ALCint attr[] = { ALC_HRTF_SOFT, ALC_TRUE, 0 };
    context = alcCreateContext(device, attr);
    if (!context || !alcMakeContextCurrent(context)) {
        Logger::log("Failed to create or make context current.", Logger::ERROR);
        cleanup();
        return false;
    }

    // Confirm if HRTF was successfully enabled
    ALCint hrtfStatus;
    alcGetIntegerv(device, ALC_HRTF_SOFT, 1, &hrtfStatus);
    if (hrtfStatus == ALC_TRUE) {
        Logger::log("HRTF is enabled successfully.");
    }
    else {
        Logger::log("Failed to enable HRTF.", Logger::WARNING);
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