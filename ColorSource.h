/*
    This file is part of The Kromophone.
    Copyright (C) 2014 Zachary Capalbo
 
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
#include <QImage>
#include <QPoint>
#include <QLabel>
#include "Color.h"
#include "Settings.h"

class ColorSource : public QObject
{
	Q_OBJECT
public:	
    explicit ColorSource(QObject* parent = 0) : QObject(parent) {}
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
    
public:
    explicit ImageSource(QObject* parent = 0) : QObject(parent) {}
	
public slots:
	
	virtual void start() = 0;
    virtual void stop() = 0;
	
signals:
	
	void update(const QImage& image);
};

class FileImageSource : public ImageSource
{
	Q_OBJECT
	
public:
	FileImageSource(const QString& file = QString());
	
	void load(const QString& file);
public slots:
	void start() { emit update(image); }

    void stop() { }
	
protected:
	
	QImage image;
};


#endif // COLORSOURCE_H
