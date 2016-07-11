#ifndef IMAGECOLORSOURCE_H
#define IMAGECOLORSOURCE_H

#include "ColorSource.h"

class ImageColorSource : public ColorSource
{
	Q_OBJECT
    
	
public slots:
	
    void setAverage(const QVariant& value);
	
	void toggleAverage();
	
	void toggleSweep();
	
	virtual void updateColor() {}
    
    void averageSizeChanged(const QVariant& value);
    void sweepSizeChanged(const QVariant& value);
	
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
