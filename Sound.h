#ifndef SOUND_H
#define SOUND_H

#include "Timbre.h"
#include <QMetaType>
#include <QVector>

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

typedef QVector<Sound> SoundList;


Q_DECLARE_METATYPE(Sound)

Q_DECLARE_METATYPE(SoundList)

#endif // SOUND_H
