#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QIODevice>
#include <QAudioFormat>
#include "Sound.h"

class Generator : public QIODevice
{
    Q_OBJECT
public:
    Generator(const QAudioFormat &format, qint64 durationUs, int frequency, QObject *parent);
    ~Generator();

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

protected:
    void generateData(const QAudioFormat &format, qint64 durationUs, int frequency);
	 void generateData(const QAudioFormat &format, qint64 durationUs, int frequency, char* buffer, qint64 length);
	
	virtual void generateTone(qreal& left, qreal& right, int frequency, qreal angle, float percent)=0;
	
	void convertToFormat(const QAudioFormat &format, unsigned char *ptr, qreal x);

protected:
    qint64 m_pos;
    QByteArray m_buffer;
	QAudioFormat m_format;
	qint64 m_durationUs;
	int m_frequency;
	
	int sampleBytes;
	int channelBytes;
	qint64 bufferLength;
	
	unsigned int sampleIndex;
};

class AudioGenerator : public Generator
{
	Q_OBJECT
public:
	explicit AudioGenerator(const QAudioFormat &format, qint64 durationUs, int frequency, QObject *parent);
	
signals:
	
public slots:
	
	void setSound(const Sound& sound);
	void setSounds(const SoundList& sounds);
	
protected:
	Sound m_sound;
	
	SoundList m_sounds;
	
	virtual void generateTone(qreal& left, qreal& right, int frequency, qreal angle, float percent);
	qreal generateSine(int frequency, qreal angle);
	qreal generateSweep(int frequency, qreal angle, float percent);
	qreal generateTimbre(const Sound &sound, int frequency, qreal angle, float percent);
	
};

#endif // AUDIOGENERATOR_H
