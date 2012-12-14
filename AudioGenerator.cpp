#include "AudioGenerator.h"
#include <QAudio>
#include <QAudioFormat>

#include <math.h>
#include <qmath.h>
#include <QtEndian>

Generator::Generator(const QAudioFormat &format,
                     qint64 durationUs,
                     int frequency,
                     QObject *parent)
    :   QIODevice(parent)
	,   m_pos(0), m_format(format), m_durationUs(durationUs), m_frequency(frequency)
{
    //generateData(format, durationUs, frequency);
	
	channelBytes = format.sampleSize() / 8;
    sampleBytes = format.channelCount() * channelBytes;

    bufferLength = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
                        * durationUs / 100000;

    Q_ASSERT(bufferLength % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    m_buffer.resize(bufferLength);
    
    sampleIndex = 0;
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

void Generator::convertToFormat(const QAudioFormat &format, unsigned char *ptr, qreal x)
{
	if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt) {
        const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
        *reinterpret_cast<quint8*>(ptr) = value;
    } else if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt) {
        const qint8 value = static_cast<qint8>(x * 127);
        *reinterpret_cast<quint8*>(ptr) = value;
    } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt) {
        quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
        if (format.byteOrder() == QAudioFormat::LittleEndian)
            qToLittleEndian<quint16>(value, ptr);
        else
            qToBigEndian<quint16>(value, ptr);
    } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt) {
        qint16 value = static_cast<qint16>(x * 32767);
        if (format.byteOrder() == QAudioFormat::LittleEndian)
            qToLittleEndian<qint16>(value, ptr);
        else
            qToBigEndian<qint16>(value, ptr);
    }
}

void Generator::generateData(const QAudioFormat &format, qint64 durationUs, int frequency)
{

	qint64 length = bufferLength;
	
	unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());

    while (length) {
			qreal left;
			qreal right;
			generateTone(left, right, frequency, qreal(sampleIndex % format.sampleRate() ) / format.sampleRate(), sampleIndex / (float) m_buffer.size());
		
        //for (int i=0; i<format.channelCount(); ++i) {
			convertToFormat(format, ptr, left );
            ptr += channelBytes;
            length -= channelBytes;
			
			convertToFormat(format, ptr, right );
            ptr += channelBytes;
            length -= channelBytes;
        //}
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
/*
qreal Generator::generateTone(int frequency, qreal angle)
{
	return qSin(2 * M_PI * frequency * angle);
}
*/
AudioGenerator::AudioGenerator(const QAudioFormat &format, qint64 durationUs, int frequency, QObject *parent) 
	: Generator(format,durationUs,frequency,parent)
{
	generateData(format, durationUs, frequency);
}

void AudioGenerator::setSound(const Sound &sound)
{
	m_oldSound = m_sound;
	m_sound = sound;
	
	generateData(m_format, m_durationUs, m_frequency);
	
	m_oldSound = m_sound;
}

void AudioGenerator::generateTone(qreal &left, qreal &right, int frequency, qreal angle, float percent)
{
	qreal sweep = generateSweep(frequency, angle, percent);
	
	left = sweep * m_sound.pan;
	
	right = sweep * (1.0 - m_sound.pan);
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
