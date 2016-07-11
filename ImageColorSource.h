#ifndef IMAGECOLORSOURCE_H
#define IMAGECOLORSOURCE_H

#include "ColorSource.h"

class ImageColorSource : public ColorSource
{
	Q_OBJECT
    
	
public slots:
	
	void setAverage(bool enabled = true);
	
	void toggleAverage();
	
	void increaseAverage();
	
	void decreaseAverage();
	
	void toggleSweep();
	
	virtual void updateColor() {}
	
signals:
	void doSweep(bool enabled, QPointF sweepPct);
	
protected slots:
	void sweep();
	
protected:
	ImageColorSource(QObject* parent = 0);
	
	void drawCursor(QImage& displayImage);
	
	Color& pickColor(const QImage& image);
	
	void average(const QImage& image);
	
	QPoint cursor;
	
	QPoint sweepPos;
	
	QSize sweepSize;
	
	bool sweepDirectionIsRight;
	
	QSize cursorSize;
	
	Color lastColor;
	
	bool averageEnabled;
	
	QTimer* sweepTimer;
};

#endif // IMAGECOLORSOURCE_H
