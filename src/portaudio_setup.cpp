// portaudio_setup.cpp
#include "portaudio_setup.h"
#include "logging.h"
#include <iostream>

PortAudioSetup::PortAudioSetup() : stream(nullptr) {}

PortAudioSetup::~PortAudioSetup() {
    cleanup();
}

bool PortAudioSetup::initialize(int inputChannels, int outputChannels, int outputDeviceIndex) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        Logger::log(std::string("PortAudio error: ") + Pa_GetErrorText(err), Logger::ERROR);
        return false;
    }

    PaStreamParameters inputParams, outputParams;
    inputParams.device = Pa_GetDefaultInputDevice();
    if (inputParams.device == paNoDevice) {
        Logger::log("No default input device.", Logger::ERROR);
        return false;
    }
    inputParams.channelCount = inputChannels;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = nullptr;

    outputParams.device = outputDeviceIndex;
    if (outputParams.device == paNoDevice) {
        Logger::log("No output device selected.", Logger::ERROR);
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
        Logger::log(std::string("PortAudio error: ") + Pa_GetErrorText(err), Logger::ERROR);
        return false;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        Logger::log(std::string("PortAudio error: ") + Pa_GetErrorText(err), Logger::ERROR);
        return false;
    }

    return true;
}

bool PortAudioSetup::initialize(int inputChannels, int outputChannels, int outputDeviceIndex, int inputDeviceIndex) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        Logger::log(std::string("PortAudio error: ") + Pa_GetErrorText(err), Logger::ERROR);
        return false;
    }

    PaStreamParameters inputParams, outputParams;
    inputParams.device = inputDeviceIndex;
    if (inputParams.device == paNoDevice) {
        Logger::log("No input device selected.", Logger::ERROR);
        return false;
    }
    inputParams.channelCount = inputChannels;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = nullptr;

    outputParams.device = outputDeviceIndex;
    if (outputParams.device == paNoDevice) {
        Logger::log("No output device selected.", Logger::ERROR);
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
        Logger::log(std::string("PortAudio error: ") + Pa_GetErrorText(err), Logger::ERROR);
        return false;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        Logger::log(std::string("PortAudio error: ") + Pa_GetErrorText(err), Logger::ERROR);
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