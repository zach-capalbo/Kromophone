/*
    This file is part of The Kromophone.
 
	The Kromophone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Kromophone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Kromophone.  If not, see <http://www.gnu.org/licenses/>.
	
*/
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
    void colorChanged(const Color& color);
	
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

class ImageSource : public QObject
{
	Q_OBJECT
	
public slots:
	
	virtual void start() = 0;
	
signals:
	
	void update(const QImage& image);
};

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
	ImageColorSource();
	
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

class FileImageSource : public ImageSource
{
	Q_OBJECT
	
public:
	FileImageSource(const QString& file = QString());
	
	void load(const QString& file);
public slots:
	void start() { emit update(image); }
	
protected:
	
	QImage image;
};

class StaticImageColorSource : public ImageColorSource
{
	Q_OBJECT
public:
	StaticImageColorSource();
	
	const Color color();
	
	QWidget* widget() { return displayWidget; }
	
public slots:
	void updateImage(const QImage& newImage);
	
	void updateColor();
	
protected:
	bool eventFilter(QObject *, QEvent *);
	
signals:
	void colorChanged(Color color);
	
private:
	QWidget* displayWidget;
	QLabel* imageLabel;
	QImage image;
};


#endif // COLORSOURCE_H
