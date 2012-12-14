#ifndef SOUNDOUT_H
#define SOUNDOUT_H
#include <QObject>
#include "Sound.h"

class SoundOut : public QObject
{
    Q_OBJECT
public:
    SoundOut();

public slots:
    virtual void PlaySound(const Sound &InputSound);
	virtual void PlaySounds(const SoundList& InputSounds);
};

#endif // SOUNDOUT_H
