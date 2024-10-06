//portaudio_setup.cpp

#include "../include/headers/portaudio_setup.h"

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

// Clean up PortAudio
void cleanupPortAudio(PaStream* stream) {
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    std::cout << "[DEBUG] PortAudio cleaned up." << std::endl;
}