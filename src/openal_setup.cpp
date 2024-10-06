//openal_setup.cpp

#include "openal_setup.h"

ALCdevice* initOpenAL(ALCcontext*& context, ALuint& source, ALuint& buffer) {
    ALCdevice* device = alcOpenDevice(NULL); // Default audio device
    if (!device) {
        std::cerr << "Failed to open audio device" << std::endl;
        return nullptr;
    }

    context = alcCreateContext(device, NULL);
    if (!context || !alcMakeContextCurrent(context)) {
        std::cerr << "Failed to create or make context current" << std::endl;
        alcCloseDevice(device);
        return nullptr;
    }

    // Enable HRTF (Head-Related Transfer Function)
    ALCint hrtfEnabled;  // Change ALboolean to ALCint
    alcGetIntegerv(device, ALC_HRTF_SOFT, 1, &hrtfEnabled);  // Use ALCint pointer
    if (hrtfEnabled == ALC_TRUE) {
        std::cout << "HRTF is enabled!" << std::endl;
    }
    else {
        std::cerr << "HRTF is not enabled!" << std::endl;
    }

    // Generate OpenAL source and buffer
    alGenSources(1, &source);
    alGenBuffers(1, &buffer);

    return device;
}

void cleanupOpenAL(ALCdevice* device, ALCcontext* context, ALuint source, ALuint buffer) {
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
