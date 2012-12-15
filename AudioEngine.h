#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
#include <QAbstractAudioOutput>
#include <QAudioOutput>
#include "Sound.h"
#include <QTimer>
#include "AudioGenerator.h"
#include "SoundOut.h"

class AudioEngine : public SoundOut
{
	Q_OBJECT
public:
	explicit AudioEngine(QObject *parent = 0);
	
signals:
	
	void updateSound(const Sound& sound);
	
public slots:
    virtual void PlaySound(const Sound& otherSound);
	
	virtual void PlaySounds(const SoundList &InputSounds);
	
	void initalizeAudio();
	
	void pullTimerExpired();
	
	void stateChanged(QAudio::State newState);
	
	void notify();
	
private:
	Sound currentSound;
	
	QTimer*          m_pullTimer;
	
	QAudioDeviceInfo m_device;
    QAudioOutput*    m_audioOutput;
    QIODevice*       m_output; // not owned
    QAudioFormat     m_format;
	QByteArray m_buffer;
	
	AudioGenerator* m_generator;
	
	bool m_pullMode;
};

#endif // AUDIOGENERATOR_H
