#include "SoundEffect.h"

SoundEffect::SoundEffect(int durationMs, float volume)
    : duration((float) durationMs / 1000.0f),
      index(0),
      volume(volume)
{
}

void SoundEffect::fillBuffer(unsigned int sampleRate)
{
    int numberOfPoints = (float) sampleRate * duration;
    buffer.resize(numberOfPoints);
    
    for (unsigned int i = 0; i < numberOfPoints; i++)
    {
        buffer[i] = volume * generateTone((float) i / (float) numberOfPoints);
    }
}

qreal SoundEffect::getSample()
{
    return buffer[index++];
}

bool SoundEffect::isDone()
{
    return index >= buffer.size();
}

SinSoundEffect::SinSoundEffect(float startFrequency, float endFrequency, int durationMs)
    : SoundEffect(durationMs),
      startFrequency(startFrequency),
      endFrequency(endFrequency)
{
}

qreal SinSoundEffect::generateTone(float phase)
{
    float sample = phase * duration;
    float freq = (1.0 - phase) * startFrequency + phase * endFrequency;
    
    return sin(M_2_PI * sample * freq);
}
