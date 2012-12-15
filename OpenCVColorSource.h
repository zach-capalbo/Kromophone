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

public slots:
	void updateImage(const QImage& image);
	
protected:
	QWidget* displayWidget;
	
	QLabel* imageLabel;
};

#endif

#endif // OPENCVCOLORSOURCE_H
