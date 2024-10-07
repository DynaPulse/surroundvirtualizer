// main.cpp
#include "openal_setup.h"
#include "portaudio_setup.h"
#include "cli_interface.h"
#include "hrtf_processor.h"
#include <iostream>
#include <vector>

int main() {
    CLIInterface cli;
    cli.displayMenu();
    cli.listPlaybackDevices();
    auto deviceList = cli.getAvailablePlaybackDevices();
    int selectedDeviceIndex = cli.getSelectedDeviceIndex(deviceList);
    if (selectedDeviceIndex == -1) {
        return -1;
    }
    std::string hrtfFilePath = cli.getHRTFFilePath();

    // Initialize OpenAL for spatial audio processing
    OpenALSetup openAL;
    if (!openAL.initialize(hrtfFilePath, deviceList[selectedDeviceIndex])) {
        std::cerr << "Error: Failed to initialize OpenAL with HRTF." << std::endl;
        return -1;
    }

    // Initialize PortAudio for capturing and playback
    PortAudioSetup portAudio;
    if (!portAudio.initialize(8, 2, selectedDeviceIndex)) { // 8 input channels (7.1.4), 2 output channels (stereo)
        std::cerr << "Error: Failed to initialize PortAudio." << std::endl;
        return -1;
    }

    // Load the HRTF Processor with the provided HRTF file
    HRTFProcessor hrtfProcessor(hrtfFilePath);

    // Buffers for input and output audio
    float inputBuffer[256 * 8]; // 8 channels
    float outputBuffer[256 * 2]; // 2 channels
    PaStream* stream = portAudio.getStream();

    // Real-time processing loop
    while (true) {
        PaError err = Pa_ReadStream(stream, inputBuffer, 256);
        if (err != paNoError) {
            std::cerr << "Error: Failed to read from input stream: " << Pa_GetErrorText(err) << std::endl;
            break;
        }

        // Convert the input buffer to a vector for processing
        std::vector<float> input(inputBuffer, inputBuffer + 256 * 8);
        std::vector<float> output;

        // Process the audio using HRTFProcessor
        hrtfProcessor.processAudio(input, output);

        // Convert the output vector back to the output buffer
        for (size_t i = 0; i < output.size(); ++i) {
            outputBuffer[i] = output[i];
        }

        err = Pa_WriteStream(stream, outputBuffer, 256);
        if (err != paNoError) {
            std::cerr << "Error: Failed to write to output stream: " << Pa_GetErrorText(err) << std::endl;
            break;
        }
    }

    // Cleanup PortAudio and OpenAL
    portAudio.cleanup();
    openAL.cleanup();

    return 0;
}