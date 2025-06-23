// hrtf_processor.h
#ifndef HRTF_PROCESSOR_H
#define HRTF_PROCESSOR_H

#include <vector>
#include <string>

/**
 * @class HRTFProcessor
 * @brief Processes audio using HRTF data for spatialization.
 */
class HRTFProcessor {
public:
    /**
     * @brief Constructor. Loads HRTF data from file.
     * @param filePath Path to the HRTF file.
     */
    HRTFProcessor(const std::string& filePath);
    /**
     * @brief Destructor.
     */
    ~HRTFProcessor();
    /**
     * @brief Processes input audio and writes spatialized output.
     * @param input Input audio buffer.
     * @param output Output audio buffer.
     */
    void processAudio(const std::vector<float>& input, std::vector<float>& output);

private:
    /**
     * @brief Loads HRTF data from the specified file.
     * @param filePath Path to the HRTF file.
     */
    void loadHRTFData(const std::string& filePath);
    std::vector<std::vector<float>> hrtfData; ///< Loaded HRTF data.
};

#endif // HRTF_PROCESSOR_H
