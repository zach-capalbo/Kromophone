#include "OpenCVColorSource.h"

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

}

void OpenCVImageSource::start()
{
	camera = cvCaptureFromCAM( CV_CAP_ANY );
	
	Q_CHECK_PTR(camera);
	
	if (camera == NULL)
	{
		qFatal("Could not open camera.");
		QApplication::exit(-1);
	}
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(captureImage()));
	timer->start(10);
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
}

LiveImageColorSource::LiveImageColorSource()
{
	//The main widget to display
	displayWidget = new QWidget();
	
	//The label to display the pixmap
	imageLabel = new QLabel();
	
	//We need to set a layout for the widget so we can add things to it
	displayWidget->setLayout(new QVBoxLayout());
	
	//Now add the image to our display widget
	displayWidget->layout()->addWidget(imageLabel);
	
	KeyboardFilter* keyboard = new KeyboardFilter(this);
	displayWidget->installEventFilter(keyboard);
	
	//Show it on the screen
	//displayWidget->show();
}

void LiveImageColorSource::updateImage(const QImage &image)
{
	cursor.setX(image.width()/2);
	cursor.setY(image.height()/2);
	
	cursor += sweepPos;
	
	QImage displayImage(image);
	
	drawCursor(displayImage);
	
	imageLabel->setPixmap(QPixmap::fromImage(displayImage));
	
	imageLabel->update();
	
	emit colorChanged(pickColor(image));	
}

LiveImageHeadlessColorSource::LiveImageHeadlessColorSource()
{
	
}

void LiveImageHeadlessColorSource::updateImage(const QImage &image)
{
	cursor.setX(image.width()/2);
	cursor.setY(image.height()/2);
	
	cursor += sweepPos;
	
	emit colorChanged(pickColor(image));	
}
#endif
