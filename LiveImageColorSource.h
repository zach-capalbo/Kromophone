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
#ifndef OPENCVCOLORSOURCE_H
#define OPENCVCOLORSOURCE_H

#include "ImageColorSource.h"
#include "Color.h"

#include <QImage>
#include <QWidget>
#include <QLabel>

class LiveImageColorSource : public ImageColorSource
{
	Q_OBJECT
	
public:
	LiveImageColorSource(QObject* parent = 0);
	
	virtual const Color color() { return lastColor; }
	
	QWidget* widget() { return displayWidget; }
    
signals:
    void previewImageChanged(const QImage& image);

public slots:
	void updateImage(const QImage& image);
	
protected:
	QWidget* displayWidget;
	
	QLabel* imageLabel;
};

class LiveImageHeadlessColorSource : public ImageColorSource
{
	Q_OBJECT
	
public:
	
	LiveImageHeadlessColorSource();
	
	virtual const Color color() { return lastColor; }
    
public slots:
	void updateImage(const QImage& image);
};

#endif // OPENCVCOLORSOURCE_H
