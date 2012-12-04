#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QObject>
#include <QtMultimediaKit/QAbstractAudioOutput>
#include <QAudioOutput>
#include "Sound.h"
#include <QTimer>

class AudioEngine : public QObject
{
	Q_OBJECT
public:
	explicit AudioEngine(QObject *parent = 0);
	
signals:
	
public slots:
    void setSound(const Sound& otherSound) {currentSound = otherSound;}
	
	void initalizeAudio();
	
private:
	Sound currentSound;
	
	QTimer*          m_pullTimer;
	
	QAudioDeviceInfo m_device;
    QAudioOutput*    m_audioOutput;
    QIODevice*       m_output; // not owned
    QAudioFormat     m_format;
	
	bool m_pullMode;
};

#endif // AUDIOGENERATOR_H
