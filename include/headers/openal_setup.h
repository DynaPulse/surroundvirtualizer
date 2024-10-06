//openal_setup.h

#ifndef OPENAL_SETUP_H
#define OPENAL_SETUP_H

#include "../lib/OpenALlibs/include/AL/al.h"
#include "../lib/OpenALlibs/include/AL/alc.h"
#include "../lib/OpenALlibs/include/AL/alext.h"
#include <iostream>

ALCdevice* initOpenAL(ALCcontext*& context, ALuint& source, ALuint& buffer);
void cleanupOpenAL(ALCdevice* device, ALCcontext* context, ALuint source, ALuint buffer);

#endif
