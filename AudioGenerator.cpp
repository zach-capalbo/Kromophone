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
	,   m_pos(0), m_format(format), m_durationUs(durationUs), m_frequency(frequency)
{
    //generateData(format, durationUs, frequency);
	
	channelBytes = format.sampleSize() / 8;
    sampleBytes = format.channelCount() * channelBytes;

    bufferLength = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
                        * durationUs / 100000;
	
	//bufferLength = 1256;

    Q_ASSERT(bufferLength % sampleBytes == 0);
    Q_UNUSED(sampleBytes); // suppress warning in release builds

    m_buffer.resize(bufferLength);
    
    sampleIndex = 0;
	readSampleIndex = 0;
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

void Generator::generateData(const QAudioFormat &format, qint64 durationUs, int frequency, char* buffer, qint64 length)
{
	
	unsigned char *ptr = reinterpret_cast<unsigned char *>(buffer);

    while (length) {
			qreal left;
			qreal right;
			generateTone(left, right, frequency, qreal(sampleIndex) / format.sampleRate(), sampleIndex / (float) m_buffer.size());
		
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
	
	//Artificial delay
	delay(100);
}

qint64 Generator::readData(char *data, qint64 len)
{
	//m_buffer.resize(len);
	
	//memcpy(data, m_buffer.data(), len);
	
	readSampleIndex = 0;
	
	qint64 currLen = len;
	
	while (currLen)
	{
		readSampleIndex = (readSampleIndex) % m_buffer.size();
		
		int ammountToCopy = qMin((qint64) (m_buffer.size() - readSampleIndex), currLen);
		memcpy(data, &(m_buffer.data()[readSampleIndex]), ammountToCopy);
		
		readSampleIndex += ammountToCopy;
		data += ammountToCopy;
		
		currLen -= ammountToCopy;
	}
	
    return len;
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
	sampleIndex = (readSampleIndex + 50) % m_buffer.size();
	generateData(m_format, m_durationUs, m_frequency, m_buffer.data(), m_buffer.size());
}

void AudioGenerator::setSound(const Sound &sound)
{
	m_sound = sound;
}

void AudioGenerator::setSounds(const SoundList& sounds)
{
	m_sounds = sounds;
}

void AudioGenerator::generateTone(qreal &left, qreal &right, int frequency, qreal angle, float percent)
{
	left = 0.0f;
	right = 0.0f;
	
	//left = right = generateTimbre(m_sound, frequency, angle, percent);
	
	
	foreach (const Sound& s, m_sounds)
	{
		qreal sweep = generateTimbre(s, frequency, angle, percent);
		
		left += sweep * s.pan;
		
		right += sweep * (1.0 - s.pan);
	}
	
	left /= m_sounds.size();
	
	right /= m_sounds.size();
	
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
	
	return sound.volume * sound.timbre->generateTone(2 * M_PI * (sound.pitch * 200 + frequency) * angle);
}
