// hrtf_processor.h
#ifndef HRTF_PROCESSOR_H
#define HRTF_PROCESSOR_H

#include <vector>
#include <string>

class HRTFProcessor {
public:
    HRTFProcessor(const std::string& filePath);
    ~HRTFProcessor();
    void processAudio(const std::vector<float>& input, std::vector<float>& output);

private:
    void loadHRTFData(const std::string& filePath);
    std::vector<std::vector<float>> hrtfData;
};

#endif // HRTF_PROCESSOR_H
