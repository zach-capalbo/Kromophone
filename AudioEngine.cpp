#include "AudioEngine.h"

#include <QDebug>

const int DurationSeconds = 1;
const int ToneFrequencyHz = 600;
const int DataFrequencyHz = 44100;
const int BufferSize      = 32768;

AudioEngine::AudioEngine(QObject *parent) :
	QObject(parent)
{
}

void AudioEngine::initalizeAudio()
{
	connect(m_pullTimer, SIGNAL(timeout()), SLOT(pullTimerExpired()));

    m_pullMode = true;

    m_format.setSampleRate(DataFrequencyHz);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	qDebug() << "Default: " << info.deviceName();
	QList<QAudioDeviceInfo> il = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
	for (QList<QAudioDeviceInfo>::Iterator it = il.begin(); it != il.end(); it++)
	{
		qDebug() << it->deviceName();
	}
	
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }
}
