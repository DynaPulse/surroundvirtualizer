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
    Logger::log("4. The default HRTF file will be used: HRTF Files/SADIE_D01/SADIE_D01-44100.mhr", Logger::INFO);

    Logger::log("Selected input device index: " + std::to_string(selectedInputDeviceIndex), Logger::INFO);
    Logger::log("Selected output device index: " + std::to_string(selectedOutputDeviceIndex), Logger::INFO);
    Logger::log("Using HRTF file: " + hrtfFilePath, Logger::INFO);

    // Initialize OpenAL for spatial audio processing
    Logger::log("Initializing OpenAL...", Logger::INFO);
    OpenALSetup openAL;
    if (!openAL.initialize(hrtfFilePath, outputDeviceList[selectedOutputDeviceIndex])) {
        Logger::log("Failed to initialize OpenAL with HRTF.", Logger::ERROR);
        return -1;
    }
    Logger::log("OpenAL initialized successfully.", Logger::INFO);

    // Initialize PortAudio for capturing from virtual device and playback to real device
    Logger::log("Initializing PortAudio...", Logger::INFO);
    PortAudioSetup portAudio;
    if (!portAudio.initialize(kInputChannels, kOutputChannels, selectedOutputDeviceIndex, selectedInputDeviceIndex)) {
        Logger::log("Failed to initialize PortAudio.", Logger::ERROR);
        return -1;
    }
    Logger::log("PortAudio initialized successfully.", Logger::INFO);

    // Load the HRTF Processor with the provided HRTF file
    Logger::log("Loading HRTF Processor...", Logger::INFO);
    HRTFProcessor hrtfProcessor(hrtfFilePath);
    Logger::log("HRTF Processor loaded.", Logger::INFO);

    // Buffers for input and output audio
    float inputBuffer[kBlockSize * kInputChannels];
    float outputBuffer[kBlockSize * kOutputChannels];
    PaStream* stream = portAudio.getStream();

    Logger::log("Entering real-time processing loop...", Logger::INFO);
    bool hadError = false;
    // Real-time processing loop
    while (true) {
        PaError err = Pa_ReadStream(stream, inputBuffer, kBlockSize);
        if (err != paNoError) {
            Logger::log(std::string("Failed to read from input stream: ") + Pa_GetErrorText(err), Logger::ERROR);
            hadError = true;
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
            hadError = true;
            break;
        }
    }

    // Cleanup PortAudio and OpenAL
    portAudio.cleanup();
    openAL.cleanup();

    if (hadError) {
        Logger::log("Processing loop exited due to an error. Press Enter to close.", Logger::ERROR);
        std::cin.ignore();
        std::cin.get();
    } else {
        Logger::log("Processing loop exited normally. Press Enter to close.", Logger::INFO);
        std::cin.ignore();
        std::cin.get();
    }
    return 0;
}