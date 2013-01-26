#include "AudioEngine.h"

#include <QDebug>
#include <QThread>

/*
const int DurationSeconds = 1;
const int ToneFrequencyHz = 131;
const int DataFrequencyHz = 44100;
const int BufferSize      = 32768;
*/

const int DurationUSeconds = 100000;
const int ToneFrequencyHz = 131;
const int DataFrequencyHz = 44100;
const int BufferSize      = 32768;

AudioEngine::AudioEngine(QObject *parent) :
	SoundOut(),  m_pullTimer(new QTimer(this)), m_buffer(BufferSize, 0), m_output(NULL)
{
}

void AudioEngine::initalizeAudio()
{
    connect(m_pullTimer, SIGNAL(timeout()), SLOT(pullTimerExpired()));

    m_pullMode = false;

    m_format.setSampleRate(DataFrequencyHz);
    m_format.setChannelCount(2);
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

    m_device = info;

    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    m_audioOutput = new QAudioOutput(m_device, m_format, this);

    connect(m_audioOutput, SIGNAL(notify()), SLOT(notified()));
    connect(m_audioOutput, SIGNAL(stateChanged(QAudio::State)), SLOT(stateChanged(QAudio::State)));

    m_generator = new AudioGenerator(m_format, DurationUSeconds, ToneFrequencyHz, NULL); //DurationSeconds*1000000

    QThread* generatorThread = new QThread();

    m_generator->moveToThread(generatorThread);

    connect(this, SIGNAL(updateSound(Sound)), m_generator, SLOT(setSound(Sound)));
    connect(this, SIGNAL(updateSounds(SoundList)), m_generator, SLOT(setSounds(SoundList)));

    generatorThread->start(QThread::HighPriority);

    m_generator->start();

    //m_pullTimer->start(200);

    //m_output = m_audioOutput->start();
    m_audioOutput->start(m_generator);


}

void AudioEngine::pullTimerExpired()
{	
    if (m_audioOutput && m_audioOutput->state() != QAudio::StoppedState) {
        int chunks = m_audioOutput->bytesFree()/m_audioOutput->periodSize();
        while (chunks) {
           const qint64 len = m_generator->read(m_buffer.data(), m_audioOutput->periodSize());
           if (len)
               m_output->write(m_buffer.data(), len);
           if (len != m_audioOutput->periodSize())
               break;
           --chunks;
        }
    }
	
	emit updateSound(currentSound);
}

void AudioEngine::PlaySound(const Sound &otherSound)
{
	currentSound = otherSound;
	//m_audioOutput->stop();
	emit updateSound(currentSound);
	//m_audioOutput->start(m_generator);
}

void AudioEngine::PlaySounds(const SoundList &InputSounds)
{
	emit updateSounds(InputSounds);
}

void AudioEngine::notify()
{
	qDebug() << "Notified";
}

void AudioEngine::stateChanged(QAudio::State newState)
{
	qDebug() << newState;
	
	if (m_audioOutput->error() != QAudio::NoError)
	{
		if (newState == QAudio::IdleState)
		{
			m_audioOutput->start(m_generator);
		}
	}
}
