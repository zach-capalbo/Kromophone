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
    void PlaySound(Sound InputSound);
};

#endif // SOUNDOUT_H
