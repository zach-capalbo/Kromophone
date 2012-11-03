#ifndef COLORSOURCE_H
#define COLORSOURCE_H

#include <QObject>
#include "Color.h"

class ColorSource : public QObject
{
	Q_OBJECT
public:
	explicit ColorSource(QObject *parent = 0);
	
    virtual const Color color()=0;
signals:
    void colorChanged(Color color);
	
public slots:
    void doRandomColor();
//	virtual void enableSweep() {};
//	virtual void enableAverage() {};
//	virtual void increaseGranularity() {};
//	virtual void decreaseGranularity() {};



};


class RandomColorSource : public ColorSource
{
public:
    RandomColorSource();

    const Color color();


};


#endif // COLORSOURCE_H
