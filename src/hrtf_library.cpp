//hrtf_library.cpp

#include "../include/headers/hrtf_library.h"

HRTFLibrary::HRTFLibrary() : hrtfLength(0) {}

HRTFLibrary::~HRTFLibrary() {}

bool HRTFLibrary::loadHRTF(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error opening HRTF file: " << filePath << std::endl;
        return false;
    }

    // Load HRTF data (this is an example; adjust parsing as needed)
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        float value;
        while (ss >> value) {
            if (leftEar.size() < hrtfLength / 2) {
                leftEar.push_back(value); // First half for left ear
            }
            else {
                rightEar.push_back(value); // Second half for right ear
            }
        }
    }

    hrtfLength = leftEar.size() + rightEar.size();
    file.close();
    return true;
}

void HRTFLibrary::applyHRTF(float* input, float* output, unsigned long framesPerBuffer) {
    // Simple HRTF application: convolve input with HRTF for left and right ears
    for (unsigned long i = 0; i < framesPerBuffer; ++i) {
        output[i * 2] = input[i] * leftEar[i % leftEar.size()]; // Left ear
        output[i * 2 + 1] = input[i] * rightEar[i % rightEar.size()]; // Right ear
    }
}
