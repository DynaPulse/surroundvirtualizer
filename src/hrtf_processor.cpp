// hrtf_processor.cpp
#include "hrtf_processor.h"
#include <iostream>
#include <fstream>

HRTFProcessor::HRTFProcessor(const std::string& filePath) {
    loadHRTFData(filePath);
}

HRTFProcessor::~HRTFProcessor() {}

void HRTFProcessor::loadHRTFData(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to load HRTF data." << std::endl;
        return;
    }

    float value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(float))) {
        std::vector<float> hrtfSample(2, value); // Left and Right ear coefficients
        hrtfData.push_back(hrtfSample);
    }
}

void HRTFProcessor::processAudio(const std::vector<float>& input, std::vector<float>& output) {
    output.clear();
    for (size_t i = 0; i < input.size(); i += 8) { // Process 8-channel input to 2-channel output
        float left = 0.0f, right = 0.0f;
        for (size_t j = 0; j < 8 && (i + j) < input.size(); ++j) {
            if (j < hrtfData.size()) {
                left += input[i + j] * hrtfData[j][0];
                right += input[i + j] * hrtfData[j][1];
            }
        }
        output.push_back(left);
        output.push_back(right);
    }
}
