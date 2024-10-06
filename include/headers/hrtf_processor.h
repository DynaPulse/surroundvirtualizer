//hrtf_processor.h

#ifndef HRTF_PROCESSOR_H
#define HRTF_PROCESSOR_H

#include <string>
#include <vector>

class HRTFProcessor {
public:
    HRTFProcessor();
    bool loadHRTF(const std::string& filePath);
    float applyHRTF(float sample, int channel);

private:
    std::vector<float> hrtfDataLeft;  // HRTF data for left ear
    std::vector<float> hrtfDataRight; // HRTF data for right ear

    bool parseHRTFFile(const std::string& filePath);
};

#endif // HRTF_PROCESSOR_H
