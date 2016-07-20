#include "SoundEffectGenerator.h"
#include "Settings.h"

SoundEffectGenerator::SoundEffectGenerator(AudioEngine* engine, QObject *parent) 
    : QObject(parent),
      engine(engine)
{
    connect(&Settings::average(), &Setting::valueChanged, this, &SoundEffectGenerator::settingChanged);
    connect(&Settings::sweep(), &Setting::valueChanged, this, &SoundEffectGenerator::settingChanged);
    connect(&Settings::lockExposure(), &Setting::valueChanged, this, &SoundEffectGenerator::settingChanged);
}

void SoundEffectGenerator::beepOn()
{
    addSoundEffect(new SinSoundEffect(4400.0, 5100.0, 100));
}

void SoundEffectGenerator::beepOff()
{
    addSoundEffect(new SinSoundEffect(5100.0, 4400.0, 100));
}

void SoundEffectGenerator::settingChanged(const QVariant& value)
{
    if (value.type() == QVariant::Bool)
    {
        if (value.toBool())
        {
            beepOn();
        }
        else
        {
            beepOff();
        }
    }
}

void SoundEffectGenerator::addSoundEffect(SoundEffect* effect)
{
    engine->addSoundEffect(std::unique_ptr<SoundEffect>(effect));
}
