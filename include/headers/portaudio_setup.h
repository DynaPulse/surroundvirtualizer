// portaudio_setup.h
#ifndef PORTAUDIO_SETUP_H
#define PORTAUDIO_SETUP_H

#include <portaudio.h>
#include <pa_win_wasapi.h>

class PortAudioSetup {
public:
    PortAudioSetup();
    ~PortAudioSetup();
    bool initialize(int inputChannels, int outputChannels, int outputDeviceIndex);
    void cleanup();
    PaStream* getStream() const;

private:
    PaStream* stream;
};

#endif // PORTAUDIO_SETUP_H