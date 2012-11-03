#ifndef COLORSOURCE_H
#define COLORSOURCE_H

#include <QObject>
#include "Color.h"

class ColorSource : public QObject
{
	Q_OBJECT
public:	
    virtual const Color color()=0;
signals:
    void colorChanged(Color color);
	
public slots:
//	virtual void enableSweep() {};
//	virtual void enableAverage() {};
//	virtual void increaseGranularity() {};
//	virtual void decreaseGranularity() {};



};


class RandomColorSource : public ColorSource
{
	Q_OBJECT
public:
    RandomColorSource();

    const Color color();

public slots:
    void doColor();
	void start();

};


#endif // COLORSOURCE_H
