#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include <stdlib.h>
#include "Sound.h"
#include "Color.h"

#include <QPointF>
/**
*/
class Transform : public QObject {

	Q_OBJECT

public:

    Transform();

private:


signals:

	void SoundGenerated(Sound P);
	
	void SoundsGenerated(SoundList sounds);

public slots:

	virtual void ReceiveColor(Color P);
	
	void setSweep(bool enabled, const QPointF& sweepPct);
	
protected:
	
	QPointF sweep;
	
	bool sweepEnabled;

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

class RGBMode : public Transform
{
	Q_OBJECT
	
public:
	
	RGBMode();
	
signals:
	
	void SoundsGenerated(SoundList sounds);
	
public slots:
	
	virtual void ReceiveColor(Color P);
};

class RGBYWMode : public RGBMode
{
	Q_OBJECT
	
public:
	
	RGBYWMode();
	
public slots:
	
	virtual void ReceiveColor(Color P);
};

#endif
