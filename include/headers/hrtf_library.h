//hrtf_library.h

#ifndef HRTF_LIBRARY_H
#define HRTF_LIBRARY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../lib/PortAudioLibs/include/portaudio.h"
#include "../lib/OpenALlibs/include/AL/al.h"
#include "../lib/OpenALlibs/include/AL/alc.h"

/**
 * @brief Loads HRTF data from the specified file path.
 * @param path Path to the HRTF file.
 * @return True if loading succeeds, false otherwise.
 */
bool loadHRTF(const std::string& path);


#endif // HRTF_LIBRARY_H
