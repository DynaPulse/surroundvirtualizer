// portaudio_setup.h
#ifndef PORTAUDIO_SETUP_H
#define PORTAUDIO_SETUP_H

#include <portaudio.h>
#include <pa_win_wasapi.h>

/**
 * @class PortAudioSetup
 * @brief Handles PortAudio stream setup and management.
 */
class PortAudioSetup {
public:
    /**
     * @brief Constructor. Initializes stream pointer to nullptr.
     */
    PortAudioSetup();
    /**
     * @brief Destructor. Cleans up PortAudio resources.
     */
    ~PortAudioSetup();
    /**
     * @brief Initializes PortAudio with the given channel counts and output device index.
     * @param inputChannels Number of input channels.
     * @param outputChannels Number of output channels.
     * @param outputDeviceIndex Index of the output device.
     * @return True if initialization succeeds, false otherwise.
     */
    bool initialize(int inputChannels, int outputChannels, int outputDeviceIndex);
    /**
     * @brief Initializes PortAudio with the given channel counts and device indices.
     * @param inputChannels Number of input channels.
     * @param outputChannels Number of output channels.
     * @param outputDeviceIndex Index of the output device.
     * @param inputDeviceIndex Index of the input device.
     * @return True if initialization succeeds, false otherwise.
     */
    bool initialize(int inputChannels, int outputChannels, int outputDeviceIndex, int inputDeviceIndex);
    /**
     * @brief Cleans up PortAudio resources.
     */
    void cleanup();
    /**
     * @brief Returns the current PortAudio stream pointer.
     */
    PaStream* getStream() const;

private:
    PaStream* stream; ///< Pointer to the PortAudio stream.
};

#endif // PORTAUDIO_SETUP_H