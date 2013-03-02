#include "AudioGenerator.h"
#include <QAudioFormat>

#include <math.h>
#include <qmath.h>
#include <QtEndian>

#include <QElapsedTimer>
void delay(unsigned int msecs)
{
	QElapsedTimer t;
	t.start();
	while ( t.elapsed() < msecs )
    {}
        //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Generator::Generator(const QAudioFormat &format,
                     qint64 durationUs,
                     int frequency,
                     QObject *parent)
    :   QIODevice(parent)
    ,   m_pos(0)
    ,   m_format(format)
    ,   m_durationUs(durationUs)
    ,   m_frequency(frequency)
{

}

Generator::~Generator()
{

}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::stop()
{
    m_pos = 0;
    close();
}

qreal soundFunc(qreal val)
{
    return 1.0 / (2.3) * (qSin(val) + qSin(2.0 * val) + 0.3*qCos(1.312*val));
}

void Generator::generateData(const QAudioFormat &format, qint64 durationUs, int frequency)
{
    const int channelBytes = format.sampleSize() / 8;
    const int sampleBytes = format.channelCount() * channelBytes;

    qint64 length = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
                        * durationUs / 100000;

    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;
    QVector<qreal> channels;
    channels.resize(2);

    while (length) {
        generateTone(channels[0], channels[1], frequency, qreal(sampleIndex) / qreal(format.sampleRate()), 1.0);
        //const qreal x = soundFunc(2 * M_PI * frequency * qreal(sampleIndex  ) / format.sampleRate());
        for (int i=0; i<format.channelCount(); ++i) {
            if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt) {
                const quint8 value = static_cast<quint8>((1.0 + channels[i]) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt) {
                const qint8 value = static_cast<qint8>(channels[i] * 127);
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt) {
                quint16 value = static_cast<quint16>((1.0 + channels[i]) / 2 * 65535);
                if (format.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<quint16>(value, ptr);
                else
                    qToBigEndian<quint16>(value, ptr);
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt) {
                qint16 value = static_cast<qint16>(channels[i] * 32767);
                if (format.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<qint16>(value, ptr);
                else
                    qToBigEndian<qint16>(value, ptr);
            }

            ptr += channelBytes;
            length -= channelBytes;
        }
        ++sampleIndex;
    }
}

qint64 Generator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    while (len - total > 0) {
        const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
        memcpy(data + total, m_buffer.constData() + m_pos, chunk);
        m_pos = (m_pos + chunk) % m_buffer.size();
        total += chunk;
    }
    return total;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 Generator::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}

AudioGenerator::AudioGenerator(const QAudioFormat &format, qint64 durationUs, int frequency, QObject *parent)
    : Generator(format,durationUs,frequency,parent)
{
    generateData(format, durationUs, frequency);
}

void AudioGenerator::start()
{
    Generator::start();

    //Make sure the timer starts in the right thread
    QMetaObject::invokeMethod(this, "initializeTimer");
}

void AudioGenerator::initializeTimer()
{
    startTimer(0);
}

void AudioGenerator::timerEvent(QTimerEvent *)
{
//    sampleIndex = (readSampleIndex + 50) % m_buffer.size();
    generateData(m_format, m_durationUs, m_frequency);//, m_buffer.data(), m_buffer.size());
}

void AudioGenerator::setSound(const Sound &sound)
{
    m_sound = sound;
}

void AudioGenerator::setSounds(const SoundList& sounds)
{
	if (m_mutex.tryLock())
	{
		m_sounds = sounds;
		m_mutex.unlock();
	}
}

void AudioGenerator::generateTone(qreal &left, qreal &right, int frequency, qreal angle, float percent)
{
    left = 0.0f;
    right = 0.0f;

    //left = right = generateTimbre(m_sound, frequency, angle, percent);

	m_mutex.lock();
    foreach (const Sound& s, m_sounds)
    {
        qreal sweep = generateTimbre(s, frequency, angle, percent);

        left += sweep * s.pan;

        right += sweep * (1.0 - s.pan);
    }

    left /= m_sounds.size();

    right /= m_sounds.size();
	m_mutex.unlock();
}

qreal AudioGenerator::generateSine(int frequency, qreal angle)
{
    return qSin(2 * M_PI * (m_sound.pitch + frequency) * angle );
}

qreal AudioGenerator::generateSweep(int frequency, qreal angle, float percent)
{
    qreal newsound = m_sound.volume * qSin(2 * M_PI * (m_sound.pitch * 200 + frequency) * angle );
    //qreal oldsound = m_oldSound.volume * qSin(2 * M_PI * (m_oldSound.pitch + frequency) * angle );
    return newsound;// * percent + oldsound * (1.0 - percent);
}

qreal AudioGenerator::generateTimbre(const Sound& sound, int frequency, qreal angle, float percent)
{
    if (sound.timbre == NULL)
    {
        return 0.0;
    }

    return sound.volume * sound.timbre->getTone(2 * M_PI * (sound.pitch * /** 200 +*/ frequency) * angle);
}
