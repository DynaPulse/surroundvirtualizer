// openal_setup.h
#ifndef OPENAL_SETUP_H
#define OPENAL_SETUP_H

#include <AL/al.h>
#include <AL/alc.h>
#include <string>

class OpenALSetup {
public:
    OpenALSetup();
    ~OpenALSetup();
    bool initialize(const std::string& hrtfFilePath, const std::string& deviceName = "");
    void cleanup();

private:
    ALCdevice* device;
    ALCcontext* context;
};

#endif // OPENAL_SETUP_H