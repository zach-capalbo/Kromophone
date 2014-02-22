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
#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QIODevice>
#include <QAudioFormat>
#include "Sound.h"
#include <QMutex>


class Generator : public QIODevice
{
	Q_OBJECT
	void generateData(const QAudioFormat& format, unsigned char* ptr, qint64 length);
public:
    Generator(const QAudioFormat &format, qint64 durationUs, int frequency, QObject *parent);
    ~Generator();

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

protected:
    virtual void generateTone(qreal& left, qreal& right, int sampleIndex)=0;
	virtual void initializeSounds()=0;

protected:
    void generateData(const QAudioFormat &format, qint64 durationUs, int frequency);

protected:
    qint64 m_pos;
    QByteArray m_buffer;
    QAudioFormat m_format;
    qint64 m_durationUs;
    int m_frequency;
	int m_sampleIndex;
	QMutex m_mutex;
};

class AudioGenerator : public Generator
{
	Q_OBJECT
public:
	explicit AudioGenerator(const QAudioFormat &format, qint64 durationUs, int frequency, QObject *parent);
	
	virtual void start();
	
signals:
	
public slots:
	
	void setSound(const Sound& sound);
	void setSounds(const SoundList& sounds);
	
	void initializeTimer();
	
protected:
	Sound m_sound;
	
	SoundList m_sounds;
	
	
	float lastFloatRight, lastFloatLeft;
	
	virtual void generateTone(qreal& left, qreal& right, int sampleIndex);
	virtual void initializeSounds();
	qreal generateSine(int frequency, qreal angle);
	qreal generateSweep(int frequency, qreal angle, float percent);
	qreal generateTimbre(const Sound &sound, int sampleIndex);
	
	void timerEvent(QTimerEvent *);
};

#endif // AUDIOGENERATOR_H
