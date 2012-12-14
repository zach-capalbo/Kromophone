#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include <stdlib.h>
#include "Sound.h"
#include "Color.h"


/**
*/
class Transform : public QObject {

	Q_OBJECT

public:

    Transform();

private:


signals:

	void SoundGenerated(Sound P);

public slots:

	virtual void ReceiveColor(Color P);

};

class HSLMode : public Transform
{
	Q_OBJECT
	
public:
	
	HSLMode();
	
signals:
	
	void SoundGenerated(Sound P);
	
public slots:
	
	virtual void ReceiveColor(Color P);
};

#endif
