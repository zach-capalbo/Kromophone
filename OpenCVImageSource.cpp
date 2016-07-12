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
#include "OpenCVImageSource.h"

#ifdef USE_OPENCV

#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QApplication>
#include <QTimer>
#include "KeyboardFilter.h"

static QImage IplImage2QImage(const IplImage *iplImage)
{
    int height = iplImage->height;
    int width = iplImage->width;
 
    if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
      QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
      return img.rgbSwapped();
    } else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
	const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
	QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);
 
	QVector<QRgb> colorTable;
	for (int i = 0; i < 256; i++){
	    colorTable.push_back(qRgb(i, i, i));
	}
	img.setColorTable(colorTable);
	return img;
    }else{
      qWarning() << "Image cannot be converted.";
      return QImage();
    }
}

OpenCVImageSource::OpenCVImageSource(QObject *parent) :
	ImageSource()
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    camera = NULL;
}

void OpenCVImageSource::start()
{
    QMetaObject::invokeMethod(this, "threadStart");
}

void OpenCVImageSource::threadStart()
{
    camera = cvCreateCameraCapture( 0 );

//    Q_CHECK_PTR(camera);

    if (camera == NULL)
    {
        qFatal("Could not open camera.");
        QApplication::exit(-1);
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(captureImage()));
    timer->start(10);
}

void OpenCVImageSource::stop()
{
    QMetaObject::invokeMethod(this, "threadStop");
}

void OpenCVImageSource::threadStop()
{
    timer->stop();
    if (camera != NULL)
    {
        cvReleaseCapture(&camera);
        camera = 0;
    }
}

void OpenCVImageSource::captureImage()
{
	if (!camera)
		return;
	IplImage* frame = 0;
	frame = cvQueryFrame(camera);
	
	//image = ;//.mirrored(true,false);
	QImage image(IplImage2QImage(frame).mirrored(true,false));
	
	emit update(image);

    timer->start(10);
}

#endif
