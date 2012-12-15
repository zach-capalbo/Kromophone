#include "ColorSource.h"
#include <QTimer>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QRgb>

RandomColorSource::RandomColorSource()
{

}

const Color RandomColorSource::color()
{
    int randomGen = rand() % 255;
    Color randomColor(rand()%255,rand()%255,rand()%255);

    return randomColor;
}



void RandomColorSource::start()
{
	QTimer *timer = new QTimer(this);
	 connect(timer, SIGNAL(timeout()), this, SLOT(doColor()));
	 timer->start(1000);
}

void RandomColorSource::doColor()
{
    emit colorChanged(color());
}

FileImageSource::FileImageSource(const QString &file) : image(file)
{
	
}


//The constructor takes in the file to open, and makes a widget to display it
StaticImageColorSource::StaticImageColorSource()
{
	//The main widget to display
	this->displayWidget = new QWidget();
	
	//The label to display the pixmap
	imageLabel = new QLabel();
	
	//We need to set a layout for the widget so we can add things to it
	displayWidget->setLayout(new QVBoxLayout());
	
	//We went to receive all mouse move events, not just clicks
	imageLabel->setMouseTracking(true);
	
	//Now add the image to our display widget
	displayWidget->layout()->addWidget(imageLabel);
	
	//Show it on the screen
	displayWidget->show();
	
	//Install an event filter so the ImageColorSource gets the label's mouse events
	imageLabel->installEventFilter(this);
}

const Color StaticImageColorSource::color()
{
	//Just return whatever the last color we used was
	return lastColor;
}

//This will get called whenever there's in event in an object we're filtering
bool StaticImageColorSource::eventFilter(QObject *obj, QEvent *event)
{
	//We only care about mouse move events
	if (event->type() == QEvent::MouseMove)
	{
		//Recast it to a mouse event so we can get the data from it
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		
		cursor = mouseEvent->pos() + sweepPos;
		
		QImage displayImage(image);
		
		drawCursor(displayImage);
		
		imageLabel->setPixmap(QPixmap::fromImage(displayImage));
		
		//Get the rgb value at the pixel that the mouse is over
		QRgb rgb = image.pixel(mouseEvent->pos());
		
		//Setup our saved color with the color from the image
		lastColor.Blue = qBlue(rgb) / 255.0f;
		lastColor.Green = qGreen(rgb) / 255.0f;
		lastColor.Red = qRed(rgb) / 255.0f;
		
		//Pass the color on
		emit colorChanged(lastColor);
		
		return true;
	}
	else
	{
		//If it's not a mouse movement, let qobject handle it
		return QObject::eventFilter(obj,event);
	}
}

void StaticImageColorSource::updateImage(const QImage &newImage)
{
	image = newImage;
	//Now we set the pixmap to the pixmap that we got from the image
	imageLabel->setPixmap(QPixmap::fromImage(image));
}

ImageColorSource::ImageColorSource()
	: ColorSource(), cursorSize(5,5), averageEnabled(true), sweepPos(0,0), sweepSize(200, 200)
{
	QTimer *sweepTimer = new QTimer(this);
	connect(sweepTimer, SIGNAL(timeout()), this, SLOT(sweep()));
	//sweepTimer->start(10);
}

void ImageColorSource::setAverage(bool enabled)
{
	averageEnabled = enabled;
	
	if (!enabled)
	{
		cursorSize = QSize(5,5);
	}
}

void ImageColorSource::toggleAverage()
{
	setAverage(!averageEnabled);
}

void ImageColorSource::increaseAverage()
{
	cursorSize += QSize(5,5);
}

void ImageColorSource::decreaseAverage()
{
	cursorSize -= QSize(5,5);
}

void ImageColorSource::drawCursor(QImage& image)
{
	int posx = cursor.x();
	int posy = cursor.y();
	
	int cwidth = cursorSize.width();
	int cheight = cursorSize.height();
	
	for (int x = posx - cwidth; x < posx + cwidth; x++ )
	{
		if (x > 0 && x < image.width())
		{
			image.setPixel(x,posy,qRgb(255, 255, 255));
		}
	}

	for (int y = posy - cheight; y < posy + cheight; y++)
	{
		if (y > 0 && y < image.height())
		{
			image.setPixel(posx,y,qRgb(255, 255, 255));
		}
	}
}

Color &ImageColorSource::pickColor(const QImage& image)
{	
	if (averageEnabled)
	{
		average(image);	
	}
	else
	{
		lastColor = image.pixel(cursor);
	}
	
	return lastColor;
}

void ImageColorSource::average(const QImage& image)
{
	unsigned int sumr = 0;
	
	unsigned int sumg = 0;
	
	unsigned int sumb = 0;
	
	int startX = cursor.x() - cursorSize.width();
	startX = qMax(startX, 0);
	
	int endX = cursor.x() + cursorSize.width();
	endX = qMin(endX, image.width());
	
	int startY = cursor.y() - cursorSize.height();
	startY = qMax(startY, 0);
	
	int endY = cursor.y() + cursorSize.height();
	endY = qMin(endY, image.height());
	
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			QRgb rgb = image.pixel(x,y);
			
			sumr += qRed(rgb);
			
			sumg += qGreen(rgb);
			
			sumb += qBlue(rgb);
		}
	}
	
	lastColor.Red = (float) sumr / ( (float) cursorSize.width() * cursorSize.height() * 4 ) / 255.0f;
	lastColor.Green = (float) sumg / ( (float) cursorSize.width() * cursorSize.height() * 4 ) / 255.0f;
	lastColor.Blue = (float) sumb / ( (float) cursorSize.width() * cursorSize.height() * 4 ) / 255.0f;
}

void ImageColorSource::sweep()
{
	if (sweepDirectionIsRight)
	{
		sweepPos += QPoint(20,0);
	}
	else
	{
		sweepPos += QPoint(-20,0);
	}
	
	if (sweepDirectionIsRight && sweepPos.x() >= sweepSize.width())
	{
		sweepDirectionIsRight = false;
	}
	else if (!sweepDirectionIsRight && sweepPos.x() <= -sweepSize.width())
	{
		sweepDirectionIsRight = true;
	}
	
	emit doSweep(true, QPointF((sweepSize.width() + sweepPos.x()) / ( (float) sweepSize.width()*2.0f ), sweepPos.y() / (float) sweepSize.height() ));
		
}
