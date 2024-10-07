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

bool loadHRTF(const std::string& path);


#endif // HRTF_LIBRARY_H
