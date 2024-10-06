//portaudio_setup.h

#ifndef PORTAUDIO_SETUP_H
#define PORTAUDIO_SETUP_H

#include "../lib/PortAudioLibs/include/portaudio.h"
#include "../lib/OpenALlibs/include/AL/al.h"
#include "../lib/OpenALlibs/include/AL/alc.h"
#include "hrtf_library.h"
#include "hrtf_processor.h"
#include <iostream>
#include <vector>

// Function prototypes
bool initializePortAudio(unsigned int* sampleRate);
PaStream* openAudioStream(unsigned int sampleRate, HRTFProcessor* hrtfProcessor);
void cleanupPortAudio(PaStream* stream);
bool initializeHRTF(const std::string& hrtfFilePath);
#endif

