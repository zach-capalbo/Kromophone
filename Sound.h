#ifndef SOUND_H
#define SOUND_H

#include "Timbre.h"

class Sound
{
public:
	Sound();
	
private:
	float pitch;
	float pan;
	float volume;
    Timbre* timbre;
};

#endif // SOUND_H
