#ifndef SOUND_H
#define SOUND_H

#include "Timbre.h"
#include <QMetaType>

class Sound
{
public:
	Sound();
	
public:
	float pitch;
	float pan;
	float volume;
    Timbre* timbre;
};


Q_DECLARE_METATYPE(Sound)
#endif // SOUND_H
