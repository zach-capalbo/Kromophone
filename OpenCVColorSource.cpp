#include "OpenCVColorSource.h"

#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QApplication>

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

OpenCVColorSource::OpenCVColorSource(QObject *parent) :
	ColorSource()
{
	camera = cvCaptureFromCAM( CV_CAP_ANY );
	
    qWarning() <<"ERROR: capture is NULL";
	
	//The main widget to display
	displayWidget = new QWidget();
	
	//The label to display the pixmap
	imageLabel = new QLabel();
	
	//We need to set a layout for the widget so we can add things to it
	displayWidget->setLayout(new QVBoxLayout());
	
	//Now add the image to our display widget
	displayWidget->layout()->addWidget(imageLabel);
	
	
	
	//Show it on the screen
	displayWidget->show();
}

void OpenCVColorSource::run()
{
	forever
	{
		
		IplImage* frame = 0;
		frame = cvQueryFrame(camera);
		
		imageLabel->setPixmap(QPixmap::fromImage(IplImage2QImage(frame)));
		
		QApplication::processEvents();
	}
}

