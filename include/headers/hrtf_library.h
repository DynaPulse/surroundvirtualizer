//hrtf_library.h

#ifndef HRTF_LIBRARY_H
#define HRTF_LIBRARY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "portaudio.h"
#include "AL/al.h"
#include "AL/alc.h"

/**
 * @brief HRTFLibrary class for handling HRTF data loading and application.
 */
class HRTFLibrary {
public:
    HRTFLibrary();
    ~HRTFLibrary();
    
    /**
     * @brief Loads HRTF data from the specified file path.
     * @param filePath Path to the HRTF file.
     * @return True if loading succeeds, false otherwise.
     */
    bool loadHRTF(const std::string& filePath);
    
    /**
     * @brief Applies the HRTF to the input signal.
     * @param input Pointer to the input signal buffer.
     * @param output Pointer to the output signal buffer.
     * @param framesPerBuffer Number of frames per buffer.
     */
    void applyHRTF(float* input, float* output, unsigned long framesPerBuffer);

private:
    std::vector<float> leftEar;  ///< Left ear HRTF data
    std::vector<float> rightEar; ///< Right ear HRTF data
    size_t hrtfLength;           ///< Length of the HRTF data
};

#endif // HRTF_LIBRARY_H
