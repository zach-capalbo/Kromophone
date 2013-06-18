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
#ifndef OPENCVCOLORSOURCE_H
#define OPENCVCOLORSOURCE_H

#ifdef USE_OPENCV

#include "ColorSource.h"
#include "Color.h"

#include <QImage>
#include <opencv2/core/core_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>
#include <QLabel>

class OpenCVImageSource : public ImageSource
{
	Q_OBJECT
public:
	explicit OpenCVImageSource(QObject *parent = 0);
	
signals:
	
public slots:
	
	void start();
	
	void captureImage();
	
protected:
	
	void drawCrosshairs(QImage& image);
	
	CvCapture* camera;
	
};

class LiveImageColorSource : public ImageColorSource
{
	Q_OBJECT
	
public:
	LiveImageColorSource();
	
	virtual const Color color() { return lastColor; }
	
	QWidget* widget() { return displayWidget; }

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

#endif

#endif // OPENCVCOLORSOURCE_H
