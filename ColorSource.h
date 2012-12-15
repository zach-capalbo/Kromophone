#ifndef COLORSOURCE_H
#define COLORSOURCE_H

#include <QObject>
#include "Color.h"
#include <QImage>
#include <QPoint>
#include <QLabel>

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

class ImageSource : public ColorSource
{
	Q_OBJECT
	
public slots:
	
	void setAverage(bool enabled = true);
	
	void toggleAverage();
	
	void increaseAverage();
	
	void decreaseAverage();
	
protected slots:
	void sweep();
	
protected:
	ImageSource();
	
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

class ImageColorSource : public ImageSource
{
	Q_OBJECT
public:
	ImageColorSource(const QString& file);
	
	const Color color();
	
protected:
	bool eventFilter(QObject *, QEvent *);
	
signals:
	void colorChanged(Color color);
	
private:
	Color lastColor;
	QImage image;
	QWidget* displayWidget;
	QLabel* imageLabel;
};


#endif // COLORSOURCE_H
