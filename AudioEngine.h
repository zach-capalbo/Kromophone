#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QObject>
#include <QColor>
#include "Sound.h"

class AudioEngine : public QObject
{
	Q_OBJECT
public:
	explicit AudioEngine(QObject *parent = 0);
	
signals:
	
public slots:
    void setSound(const Sound& otherSound) {currentSound = otherSound;}
	
private:
	Sound currentSound;
};

#endif // AUDIOGENERATOR_H
