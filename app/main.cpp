#include "../include/headers/openal_setup.h"
#include "../include/headers/portaudio_setup.h"
#include "../include/headers/cli_interface.h"
#include <iostream>
#include <conio.h>
#include <stdexcept>

// Function to print debug messages
void debugMessage(const std::string& message) {
    std::cout << "[DEBUG] " << message << std::endl;
}

//int main() {
//    CLIInterface cli;
//    PortAudioSetup paSetup;
//
//    // Get input and output devices
//    std::vector<std::string> outputDevices = paSetup.getOutputDevices();
//    std::vector<std::string> inputDevices = paSetup.getInputDevices();
//
//    if (inputDevices.empty() || outputDevices.empty()) {
//        std::cout << "No input or output devices available!" << std::endl;
//        return -1;
//    }
//
//    // Select input device
//    cli.displayDevices(inputDevices, "Input");
//    int inputDeviceIndex = cli.getUserDeviceChoice();
//    if (inputDeviceIndex < 0 || inputDeviceIndex >= inputDevices.size()) {
//        std::cout << "Invalid input device choice!" << std::endl;
//        return -1;
//    }
//    cli.showSelectedDevice(inputDevices[inputDeviceIndex], "Input");
//
//    // Select output device
//    cli.displayDevices(outputDevices, "Output");
//    int outputDeviceIndex = cli.getUserDeviceChoice();
//    if (outputDeviceIndex < 0 || outputDeviceIndex >= outputDevices.size()) {
//        std::cout << "Invalid output device choice!" << std::endl;
//        return -1;
//    }
//    cli.showSelectedDevice(outputDevices[outputDeviceIndex], "Output");
//
//    // Set devices for routing
//    paSetup.setDevices(inputDeviceIndex, outputDeviceIndex);
//
//    // Start audio stream
//    paSetup.startAudioStream();
//
//    unsigned int sampleRate;
//    std::string hrtfFilePath = "C:\\Users\\Sagar\\Documents\\Projects\\AudioApp\\surroundVirtualizer\\lib\\OpenALlibs\\share\\openal\\hrtf\\Default HRTF.mhr"; // Corrected path
//
//    debugMessage("Starting application...");
//
//    // Initialize PortAudio
//    debugMessage("Initializing PortAudio...");
//    if (!initializePortAudio(&sampleRate)) {
//        throw std::runtime_error("PortAudio initialization failed!");
//    }
//    debugMessage("PortAudio initialized with sample rate: " + std::to_string(sampleRate));
//
//    // Initialize HRTF
//    debugMessage("Initializing HRTF with file: " + hrtfFilePath);
//    HRTFProcessor hrtfProcessor;
//    if (!hrtfProcessor.loadHRTF(hrtfFilePath)) {
//        throw std::runtime_error("HRTF initialization failed!");
//    }
//    debugMessage("HRTF initialized successfully.");
//
//    // Open audio stream
//    debugMessage("Opening audio stream...");
//    PaStream* stream = openAudioStream(sampleRate, &hrtfProcessor); // Passing HRTFProcessor to audio callback
//    if (!stream) {
//        throw std::runtime_error("Failed to open audio stream!");
//    }
//    debugMessage("Audio stream opened successfully.");
//
//    // Start audio stream
//    debugMessage("Starting audio stream...");
//    PaError err = Pa_StartStream(stream);
//    if (err != paNoError) {
//        throw std::runtime_error(std::string("PortAudio error: ") + Pa_GetErrorText(err));
//    }
//    debugMessage("Audio stream started.");
//
//    std::cout << "Running audio application..." << std::endl;
//    std::cout << "Press Enter to exit..." << std::endl;
//
//    // Wait for user input
//    std::cin.get();
//
//    // Clean up
//    debugMessage("Cleaning up audio resources...");
//    cleanupPortAudio(stream);
//    debugMessage("Exiting application.");
//
//    return 0;
//}

int main() {
    CLIInterface cli;
    PortAudioSetup paSetup;

    // Get input and output devices
    std::vector<std::string> outputDevices = paSetup.getOutputDevices();
    std::vector<std::string> inputDevices = paSetup.getInputDevices();

    if (inputDevices.empty() || outputDevices.empty()) {
        std::cout << "No input or output devices available!" << std::endl;
        return -1;
    }

    // Select input device
    cli.displayDevices(inputDevices, "Input");
    int inputDeviceIndex = cli.getUserDeviceChoice();
    if (inputDeviceIndex < 0 || inputDeviceIndex >= inputDevices.size()) {
        std::cout << "Invalid input device choice!" << std::endl;
        return -1;
    }
    cli.showSelectedDevice(inputDevices[inputDeviceIndex], "Input");

    // Select output device
    cli.displayDevices(outputDevices, "Output");
    int outputDeviceIndex = cli.getUserDeviceChoice();
    if (outputDeviceIndex < 0 || outputDeviceIndex >= outputDevices.size()) {
        std::cout << "Invalid output device choice!" << std::endl;
        return -1;
    }
    cli.showSelectedDevice(outputDevices[outputDeviceIndex], "Output");

    // Set devices for routing
    paSetup.setDevices(inputDeviceIndex, outputDeviceIndex);

    // Start audio stream (this method now keeps the stream open until Enter is pressed)
    paSetup.startAudioStream();

    unsigned int sampleRate;
    std::string hrtfFilePath = "C:\\Users\\Sagar\\Documents\\Projects\\AudioApp\\surroundVirtualizer\\lib\\OpenALlibs\\share\\openal\\hrtf\\Default HRTF.mhr"; // Corrected path

    debugMessage("Starting application...");

    // Initialize PortAudio
    debugMessage("Initializing PortAudio...");
    if (!initializePortAudio(&sampleRate)) {
        throw std::runtime_error("PortAudio initialization failed!");
    }
    debugMessage("PortAudio initialized with sample rate: " + std::to_string(sampleRate));

    // Initialize HRTF
    debugMessage("Initializing HRTF with file: " + hrtfFilePath);
    HRTFProcessor hrtfProcessor;
    if (!hrtfProcessor.loadHRTF(hrtfFilePath)) {
        throw std::runtime_error("HRTF initialization failed!");
    }
    debugMessage("HRTF initialized successfully.");

    // Open audio stream
    debugMessage("Opening audio stream...");
    PaStream* stream = openAudioStream(sampleRate, &hrtfProcessor); // Passing HRTFProcessor to audio callback
    if (!stream) {
        throw std::runtime_error("Failed to open audio stream!");
    }
    debugMessage("Audio stream opened successfully.");

    // Start audio stream
    debugMessage("Starting audio stream...");
    PaError err = Pa_StartStream(stream);
    if (err != paNoError) {
        throw std::runtime_error(std::string("PortAudio error: ") + Pa_GetErrorText(err));
    }
    debugMessage("Audio stream started.");

    std::cout << "Running audio application..." << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;

    // Wait for user input
    std::cin.get();

    // Clean up
    debugMessage("Cleaning up audio resources...");
    cleanupPortAudio(stream);
    debugMessage("Exiting application.");

    return 0;
}
