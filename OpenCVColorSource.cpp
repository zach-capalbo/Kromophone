#include "OpenCVColorSource.h"

#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QApplication>
#include <QTimer>

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
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(captureImage()));
	timer->start(10);
	
	//Show it on the screen
	displayWidget->show();
}

void OpenCVColorSource::captureImage()
{
	if (!camera)
		return;
	IplImage* frame = 0;
	frame = cvQueryFrame(camera);
	
	//image = ;//.mirrored(true,false);
	QImage image(IplImage2QImage(frame).mirrored(true,false));
	
	QImage displayImage(image);
	
	drawCrosshairs(displayImage);
	
	imageLabel->setPixmap(QPixmap::fromImage(displayImage));
	
	imageLabel->update();
	
	emit colorChanged(pickColor(image));
}

Color& OpenCVColorSource::pickColor(const QImage& image)
{
	int x = image.width() / 2;
	int y = image.height() / 2;
	
	lastColor = image.pixel(x,y);
	
	return lastColor;
}

void OpenCVColorSource::drawCrosshairs(QImage& image)
{
	int posx = image.width() / 2;
	int posy = image.height() / 2;
	
	int cwidth = 5;
	int cheight = 5;
	
	for (int x = posx - cwidth; x < posx + cwidth; x++ )
	{
		image.setPixel(x,posy,qRgb(255, 255, 255));
	}

	for (int y = posy - cheight; y < posy + cheight; y++)
	{
		image.setPixel(posx,y,qRgb(255, 255, 255));
	}
}
