//portaudio_setup.cpp

#include "portaudio_setup.h"

#define SAMPLE_RATE 384000
#define FRAMES_PER_BUFFER (512)


// Callback for audio processing with HRTF
static int audioCallback(const void* inputBuffer,
    void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    HRTFProcessor* hrtfProcessor = static_cast<HRTFProcessor*>(userData);
    float* out = static_cast<float*>(outputBuffer);
    const float* in = static_cast<const float*>(inputBuffer);

    // Clear output buffer
    std::fill(out, out + framesPerBuffer * 2, 0.0f);

    // Process each sample through HRTF
    for (unsigned long i = 0; i < framesPerBuffer; ++i) {
        float leftSample = in[i * 2];   // Left channel
        float rightSample = in[i * 2 + 1]; // Right channel

        // Apply HRTF filtering
        float hrtfLeft = hrtfProcessor->applyHRTF(leftSample, 0);
        float hrtfRight = hrtfProcessor->applyHRTF(rightSample, 1);

        // Output processed audio
        out[i * 2] = hrtfLeft;
        out[i * 2 + 1] = hrtfRight;
    }

    return paContinue;
}

// Initialize PortAudio
bool initializePortAudio(unsigned int* sampleRate) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "[ERROR] PortAudio initialization failed: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    *sampleRate = 44100;  // Default sample rate
    std::cout << "[DEBUG] PortAudio initialized." << std::endl;
    return true;
}

PaStream* openAudioStream(unsigned int sampleRate, HRTFProcessor* hrtfProcessor) {
    PaStream* stream;
    PaError err;

    err = Pa_OpenDefaultStream(&stream,
        2,  // Stereo input
        2,  // Stereo output
        paFloat32, // 32-bit floating point output
        sampleRate,
        256,  // Frames per buffer
        audioCallback,
        hrtfProcessor);  // Pass HRTF processor as user data

    if (err != paNoError) {
        std::cerr << "[ERROR] Failed to open audio stream: " << Pa_GetErrorText(err) << std::endl;
        return nullptr;
    }

    return stream;
}

PortAudioSetup::PortAudioSetup() {
    Pa_Initialize();
}

PortAudioSetup::~PortAudioSetup() {
    if (stream) {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
    }
    Pa_Terminate();
}

std::vector<std::string> PortAudioSetup::getOutputDevices() {
    std::vector<std::string> devices;

    int numDevices = Pa_GetDeviceCount();
    for (int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if (deviceInfo->maxOutputChannels > 0) {
            devices.push_back(deviceInfo->name);
        }
    }

    return devices;
}

std::vector<std::string> PortAudioSetup::getInputDevices() {
    std::vector<std::string> devices;

    int numDevices = Pa_GetDeviceCount();
    for (int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if (deviceInfo->maxInputChannels > 0) {
            devices.push_back(deviceInfo->name);
        }
    }

    return devices;
}

void PortAudioSetup::setDevices(int inputDeviceIndex, int outputDeviceIndex) {
    // Configure input device
    inputParameters.device = inputDeviceIndex;
    inputParameters.channelCount = 2;  // Stereo input
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputDeviceIndex)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    // Configure output device
    outputParameters.device = outputDeviceIndex;
    outputParameters.channelCount = 2;  // Stereo output
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputDeviceIndex)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    std::cout << "Devices configured for input and output.\n";
}

void PortAudioSetup::startAudioStream() {
    // Open audio stream between input and output devices
    PaError err = Pa_OpenStream(
        &stream,
        &inputParameters,
        &outputParameters,
        44100,            // Sample rate
        256,              // Frames per buffer
        paClipOff,        // Disable clipping
        NULL,             // No callback (could implement callback for real-time processing)
        NULL              // No callback user data
    );

    if (err != paNoError) {
        std::cerr << "Error opening stream: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Error starting stream: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    std::cout << "Audio stream started. Press Enter to stop...\n";

    // Keep the stream open and running until the user hits Enter
    std::cin.get();  // Wait for user input to stop

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "Error stopping stream: " << Pa_GetErrorText(err) << std::endl;
    }

    Pa_CloseStream(stream);  // Ensure the stream is closed properly after stopping
}

// Clean up PortAudio
void cleanupPortAudio(PaStream* stream) {
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    std::cout << "[DEBUG] PortAudio cleaned up." << std::endl;
}