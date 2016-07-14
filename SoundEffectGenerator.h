#ifndef SOUNDEFFECTGENERATOR_H
#define SOUNDEFFECTGENERATOR_H

#include <QObject>
#include "AudioEngine.h"
#include "SoundEffect.h"

class SoundEffectGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SoundEffectGenerator(AudioEngine* engine, QObject *parent = 0);
    
signals:
    
public slots:
    void beepOn();
    void beepOff();
    
protected slots:
    void settingChanged(const QVariant& value);
    
private:
    void addSoundEffect(SoundEffect* effect);
    AudioEngine* engine;
};

#endif // SOUNDEFFECTGENERATOR_H
