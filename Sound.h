#ifndef SOUND_H
#define SOUND_H

#include "Timber.h"

class Sound
{
public:
	Sound();
	
private:
	float pitch;
	float pan;
	float volume;
	Timber* timber;
};

#endif // SOUND_H
