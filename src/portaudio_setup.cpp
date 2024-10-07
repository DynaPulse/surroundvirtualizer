// portaudio_setup.cpp
#include "portaudio_setup.h"
#include <iostream>

PortAudioSetup::PortAudioSetup() : stream(nullptr) {}

PortAudioSetup::~PortAudioSetup() {
    cleanup();
}

bool PortAudioSetup::initialize(int inputChannels, int outputChannels, int outputDeviceIndex) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    PaStreamParameters inputParams, outputParams;
    inputParams.device = Pa_GetDefaultInputDevice();
    if (inputParams.device == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        return false;
    }
    inputParams.channelCount = inputChannels;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = nullptr;

    outputParams.device = outputDeviceIndex;
    if (outputParams.device == paNoDevice) {
        std::cerr << "Error: No output device selected." << std::endl;
        return false;
    }
    outputParams.channelCount = outputChannels;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;

    PaWasapiStreamInfo wasapiInfo;
    wasapiInfo.size = sizeof(PaWasapiStreamInfo);
    wasapiInfo.hostApiType = paWASAPI;
    wasapiInfo.version = 1;
    wasapiInfo.flags = paWinWasapiExclusive | paWinWasapiThreadPriority;
    wasapiInfo.threadPriority = eThreadPriorityProAudio;
    outputParams.hostApiSpecificStreamInfo = &wasapiInfo;

    err = Pa_OpenStream(&stream, &inputParams, &outputParams, 44100, 256, paClipOff, nullptr, nullptr);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    return true;
}

void PortAudioSetup::cleanup() {
    if (stream) {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        stream = nullptr;
    }
    Pa_Terminate();
}

PaStream* PortAudioSetup::getStream() const {
    return stream;
}