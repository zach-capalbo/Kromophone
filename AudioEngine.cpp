/*
    This file is part of The Kromophone.
    Copyright (C) 2014 Zachary Capalbo
 
	The Kromophone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Kromophone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Kromophone.  If not, see <http://www.gnu.org/licenses/>.
	
*/
#include "AudioEngine.h"

#include "Logger.h"
#include <QThread>

#include "Settings.h"


/*
const int DurationSeconds = 1;
const int ToneFrequencyHz = 131;
const int DataFrequencyHz = 44100;
const int BufferSize      = 32768;
*/

const int DurationUSeconds = 100;
const int ToneFrequencyHz = 100;
const int DataFrequencyHz = 48000;
const int BufferSize      = 3276*4;

AudioEngine::AudioEngine(QObject *parent) :
    SoundOut(parent),  m_pullTimer(nullptr), m_buffer(BufferSize, 0), m_output(nullptr), m_generator(nullptr)
{
    m_pullTimer = new QTimer(this);
}

void AudioEngine::initializeAudio()
{
    connect(m_pullTimer, SIGNAL(timeout()), SLOT(pullTimerExpired()));

    m_pullMode = true;

    m_format.setSampleRate(DataFrequencyHz);
    m_format.setChannelCount(2);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);
	
//	LOG_INFO() << "Available devices";
	foreach (QAudioDeviceInfo out, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
	{
//			LOG_INFO() << out.deviceName();
	}

    QAudioDeviceInfo info;
    LOG_TRACE() << "Default: " << info.deviceName();
    QList<QAudioDeviceInfo> il = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    for (QList<QAudioDeviceInfo>::Iterator it = il.begin(); it != il.end(); it++)
    {
//        LOG_INFO() << it->deviceName();
        if (it->deviceName() == Settings::audioDevice().value().toString())
        {
            info = *it;
        }
    }
    
    if (info.deviceName().isEmpty())
    {
        info = QAudioDeviceInfo::defaultOutputDevice();
    }

    m_device = info;
    
    LOG_INFO() << "Using: " << m_device.deviceName();

    if (!info.isFormatSupported(m_format)) {
        LOG_WARNING() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    m_audioOutput = new QAudioOutput(m_device, m_format, this);
	
	m_audioOutput->setBufferSize(BufferSize);

    connect(m_audioOutput, SIGNAL(notify()), SLOT(notified()));
    connect(m_audioOutput, SIGNAL(stateChanged(QAudio::State)), SLOT(stateChanged(QAudio::State)));

    m_generator = new AudioGenerator(m_format, DurationUSeconds, ToneFrequencyHz, NULL); //DurationSeconds*1000000

    QThread* generatorThread = new QThread();

    m_generator->moveToThread(generatorThread);
    generatorThread->start(QThread::HighPriority);

    m_generator->start();

    m_pullTimer->start(1);

    m_output = m_audioOutput->start();
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
    emit updateSound(currentSound);
}

void AudioEngine::PlaySounds(const SoundList &InputSounds)
{
    if (m_generator != nullptr)
    {
        emit updateSounds(InputSounds);
        m_generator->setSounds(InputSounds);
    }
}

void AudioEngine::addSoundEffect(std::unique_ptr<SoundEffect> soundEffect)
{
    if (m_generator != nullptr)
    {
        m_generator->addSoundEffect(std::move(soundEffect));
    }
}

void AudioEngine::notify()
{
    LOG_DEBUG() << "Notified";
}

void AudioEngine::stateChanged(QAudio::State newState)
{
    LOG_DEBUG() << newState;
	
	if (m_audioOutput->error() != QAudio::NoError)
	{
		if (newState == QAudio::IdleState)
		{
			m_audioOutput->start(m_generator);
		}
	}
}
