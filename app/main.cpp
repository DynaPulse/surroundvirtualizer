// main.cpp
#include "openal_setup.h"
#include "portaudio_setup.h"
#include "cli_interface.h"
#include "hrtf_processor.h"
#include "logging.h"
#include <iostream>
#include <vector>

constexpr int kBlockSize = 256;
constexpr int kInputChannels = 8;
constexpr int kOutputChannels = 2;

int main(int argc, char* argv[]) {
    // Help option
    if (argc > 1 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        std::cout << "Surround Virtualizer\n";
        std::cout << "Usage: SurroundVirtualizer [options]\n";
        std::cout << "Options:\n  --help, -h    Show this help message\n";
        return 0;
    }
    CLIInterface cli;
    cli.displayMenu();
    // --- Virtual Device Pipeline ---
    Logger::log("Select the virtual (input/capture) device (e.g., VB-Cable, Virtual Audio Cable) that will receive audio from your game or media player.");
    cli.listInputDevices();
    auto inputDeviceList = cli.getAvailableInputDevices();
    int selectedInputDeviceIndex = cli.getSelectedInputDeviceIndex(inputDeviceList);
    if (selectedInputDeviceIndex == -1) {
        Logger::log("No input device selected. Exiting.", Logger::WARNING);
        return -1;
    }
    Logger::log("Select the real output (playback) device (your headphones or speakers).", Logger::INFO);
    cli.listPlaybackDevices();
    auto outputDeviceList = cli.getAvailablePlaybackDevices();
    int selectedOutputDeviceIndex = cli.getSelectedDeviceIndex(outputDeviceList);
    if (selectedOutputDeviceIndex == -1) {
        Logger::log("No output device selected. Exiting.", Logger::WARNING);
        return -1;
    }
    std::string hrtfFilePath = cli.getHRTFFilePath();

    // --- User Instructions ---
    Logger::log("\nINSTRUCTIONS:", Logger::INFO);
    Logger::log("1. Install a virtual audio device such as VB-Cable or Virtual Audio Cable.", Logger::INFO);
    Logger::log("2. Set the virtual device as the default output in Windows or in your game/media player.", Logger::INFO);
    Logger::log("3. This application will capture audio from the virtual device, process it, and output stereo to your real device.", Logger::INFO);

    // Initialize OpenAL for spatial audio processing
    OpenALSetup openAL;
    if (!openAL.initialize(hrtfFilePath, outputDeviceList[selectedOutputDeviceIndex])) {
        Logger::log("Failed to initialize OpenAL with HRTF.", Logger::ERROR);
        return -1;
    }

    // Initialize PortAudio for capturing from virtual device and playback to real device
    PortAudioSetup portAudio;
    if (!portAudio.initialize(kInputChannels, kOutputChannels, selectedOutputDeviceIndex, selectedInputDeviceIndex)) {
        Logger::log("Failed to initialize PortAudio.", Logger::ERROR);
        return -1;
    }

    // Load the HRTF Processor with the provided HRTF file
    HRTFProcessor hrtfProcessor(hrtfFilePath);

    // Buffers for input and output audio
    float inputBuffer[kBlockSize * kInputChannels];
    float outputBuffer[kBlockSize * kOutputChannels];
    PaStream* stream = portAudio.getStream();

    // Real-time processing loop
    while (true) {
        PaError err = Pa_ReadStream(stream, inputBuffer, kBlockSize);
        if (err != paNoError) {
            Logger::log(std::string("Failed to read from input stream: ") + Pa_GetErrorText(err), Logger::ERROR);
            break;
        }

        // Convert the input buffer to a vector for processing
        std::vector<float> input(inputBuffer, inputBuffer + kBlockSize * kInputChannels);
        std::vector<float> output;

        // Process the audio using HRTFProcessor
        hrtfProcessor.processAudio(input, output);

        // Convert the output vector back to the output buffer
        for (size_t i = 0; i < output.size(); ++i) {
            outputBuffer[i] = output[i];
        }

        err = Pa_WriteStream(stream, outputBuffer, kBlockSize);
        if (err != paNoError) {
            Logger::log(std::string("Failed to write to output stream: ") + Pa_GetErrorText(err), Logger::ERROR);
            break;
        }
    }

    // Cleanup PortAudio and OpenAL
    portAudio.cleanup();
    openAL.cleanup();

    return 0;
}