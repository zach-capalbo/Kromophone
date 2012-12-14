#ifndef OPENCVCOLORSOURCE_H
#define OPENCVCOLORSOURCE_H

#include "ColorSource.h"
#include "Color.h"

#include <QImage>
#include <opencv2/core/core_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>
#include <QLabel>

class OpenCVColorSource : public ColorSource
{
	Q_OBJECT
public:
	explicit OpenCVColorSource(QObject *parent = 0);
	
	const Color color() { return lastColor; }
	
signals:
	
public slots:
	
	void captureImage();
	
	Color& pickColor(const QImage &image);
	
protected:
	
	void drawCrosshairs(QImage& image);
	
	CvCapture* camera;
	
	Color lastColor;
	
	QWidget* displayWidget;
	
	QLabel* imageLabel;
	
};

#endif // OPENCVCOLORSOURCE_H
