//hrtf_processor.cpp

#include "hrtf_processor.h"
#include <fstream>
#include <iostream>

// Constructor
HRTFProcessor::HRTFProcessor() {}

// Load HRTF data from file
bool HRTFProcessor::loadHRTF(const std::string& filePath) {
    return parseHRTFFile(filePath);
}

// Parse HRTF file (dummy implementation, replace with actual logic)
bool HRTFProcessor::parseHRTFFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open HRTF file: " << filePath << std::endl;
        return false;
    }

    // Load HRTF data (this is just an example; replace with actual parsing)
    hrtfDataLeft = { 1.0f, 0.8f, 0.6f };  // Dummy data
    hrtfDataRight = { 1.0f, 0.8f, 0.6f }; // Dummy data

    std::cout << "[DEBUG] HRTF file parsed successfully." << std::endl;
    return true;
}

// Apply HRTF to audio sample (replace with actual processing logic)
float HRTFProcessor::applyHRTF(float sample, int channel) {
    // Dummy HRTF processing: just attenuating the signal
    if (channel == 0) { // Left channel
        return sample * hrtfDataLeft[0];
    }
    else {            // Right channel
        return sample * hrtfDataRight[0];
    }
}
