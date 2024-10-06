//hrtf_library.h

#ifndef HRTF_LIBRARY_H
#define HRTF_LIBRARY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class HRTFLibrary {
public:
    HRTFLibrary();
    ~HRTFLibrary();

    bool loadHRTF(const std::string& filePath);
    void applyHRTF(float* input, float* output, unsigned long framesPerBuffer);

private:
    std::vector<float> leftEar; // HRTF for left ear
    std::vector<float> rightEar; // HRTF for right ear
    unsigned int hrtfLength; // Length of the HRTF
};

#endif // HRTF_LIBRARY_H
