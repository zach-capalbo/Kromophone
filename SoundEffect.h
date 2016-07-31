#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <QVector>

class SoundEffect
{
public:
    SoundEffect(int durationMs, float volume = 0.25);
    void fillBuffer(unsigned int sampleRate);
    qreal getSample();
    bool isDone();
    
private:
    QVector<qreal> buffer;
    int index;
protected:
    virtual qreal generateTone(float percentOfDuration) = 0;
    float duration;
    float volume;
};

class SinSoundEffect : public SoundEffect
{
public:
    SinSoundEffect(float startFrequency, float endFrequency, int durationMs);
protected:
    qreal generateTone(float percentOfDuration);
private:
    float startFrequency;
    float endFrequency;
};

#endif // SOUNDEFFECT_H
