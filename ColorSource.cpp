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
    int randomGen = rand() %255;
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


//The constructor takes in the file to open, and makes a widget to display it
ImageColorSource::ImageColorSource(const QString& file) : image(file)
{
	//The main widget to display
	this->displayWidget = new QWidget();
	
	//The label to display the pixmap
	QLabel* imageLabel = new QLabel();
	
	//We need to set a layout for the widget so we can add things to it
	displayWidget->setLayout(new QVBoxLayout());
	
	//Now we set the pixmap to the pixmap that we got from the image
	imageLabel->setPixmap(QPixmap::fromImage(image));
	
	//We went to receive all mouse move events, not just clicks
	imageLabel->setMouseTracking(true);
	
	//Now add the image to our display widget
	displayWidget->layout()->addWidget(imageLabel);
	
	//Show it on the screen
	displayWidget->show();
	
	//Install an event filter so the ImageColorSource gets the label's mouse events
	imageLabel->installEventFilter(this);
}

const Color ImageColorSource::color()
{
	//Just return whatever the last color we used was
	return lastColor;
}

//This will get called whenever there's in event in an object we're filtering
bool ImageColorSource::eventFilter(QObject *obj, QEvent *event)
{
	//We only care about mouse move events
	if (event->type() == QEvent::MouseMove)
	{
		//Recast it to a mouse event so we can get the data from it
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		
		//Get the rgb value at the pixel that the mouse is over
		QRgb rgb = image.pixel(mouseEvent->pos());
		
		//Setup our saved color with the color from the image
		lastColor.Blue = qBlue(rgb);
		lastColor.Green = qGreen(rgb);
		lastColor.Red = qRed(rgb);
		
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
