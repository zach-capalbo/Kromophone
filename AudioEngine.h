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
#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
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
	
	void updateSounds(const SoundList& sounds);
	
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
