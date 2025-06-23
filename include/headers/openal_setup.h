// openal_setup.h
#ifndef OPENAL_SETUP_H
#define OPENAL_SETUP_H

#include <AL/al.h>
#include <AL/alc.h>
#include <string>

/**
 * @class OpenALSetup
 * @brief Handles OpenAL device and context setup, including HRTF initialization.
 */
class OpenALSetup {
public:
    /**
     * @brief Constructor. Initializes pointers to nullptr.
     */
    OpenALSetup();
    /**
     * @brief Destructor. Cleans up OpenAL resources.
     */
    ~OpenALSetup();
    /**
     * @brief Initializes OpenAL with the given HRTF file and device name.
     * @param hrtfFilePath Path to the HRTF file.
     * @param deviceName Name of the audio device (empty for default).
     * @return True if initialization succeeds, false otherwise.
     */
    bool initialize(const std::string& hrtfFilePath, const std::string& deviceName = "");
    /**
     * @brief Cleans up OpenAL resources.
     */
    void cleanup();

private:
    ALCdevice* device; ///< Pointer to the OpenAL device.
    ALCcontext* context; ///< Pointer to the OpenAL context.
};

#endif // OPENAL_SETUP_H