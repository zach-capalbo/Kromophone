#ifndef COLORSOURCE_H
#define COLORSOURCE_H

#include <QObject>
#include <QColor>

class ColorSource : public QObject
{
	Q_OBJECT
public:
	explicit ColorSource(QObject *parent = 0);
	
	virtual const QColor& color()=0;
signals:
	void colorChanged(QColor color);
	
public slots:
	virtual void enableSweep() {};
	virtual void enableAverage() {};
	virtual void increaseGranularity() {};
	virtual void decreaseGranularity() {};
};

#endif // COLORSOURCE_H
