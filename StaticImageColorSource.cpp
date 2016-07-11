#include "StaticImageColorSource.h"

#include <QVBoxLayout>
#include <QEvent>
#include <QMouseEvent>

#include "KeyboardFilter.h"

//The constructor takes in the file to open, and makes a widget to display it
StaticImageColorSource::StaticImageColorSource()
{
	//The main widget to display
	this->displayWidget = new QWidget();
	
	//The label to display the pixmap
	imageLabel = new QLabel();
	
	//We need to set a layout for the widget so we can add things to it
	displayWidget->setLayout(new QVBoxLayout());
	
	//Set the margin to 0
	displayWidget->layout()->setMargin(0);
	
	//We went to receive all mouse move events, not just clicks
	imageLabel->setMouseTracking(true);
	
	//Now add the image to our display widget
	displayWidget->layout()->addWidget(imageLabel);
	
	//Don't Show it on the screen
//	displayWidget->show();
	
	//Install an event filter so the ImageColorSource gets the label's mouse events
	imageLabel->installEventFilter(this);
	
	//Get key presses
	KeyboardFilter* keyboard = new KeyboardFilter(this);
	displayWidget->installEventFilter(keyboard);
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
        
        setMouse(mouseEvent->pos());
		
		return true;
	}
	else
	{
		//If it's not a mouse movement, let qobject handle it
		return QObject::eventFilter(obj,event);
	}
}

void StaticImageColorSource::setMouse(QPoint pos)
{
    cursor = pos + sweepPos;
    
    updateColor();
}

void StaticImageColorSource::updateColor()
{
	QImage displayImage(image);
	
	drawCursor(displayImage);
	
	imageLabel->setPixmap(QPixmap::fromImage(displayImage));
	
	pickColor(image);
	
	//Pass the color on
	emit colorChanged(lastColor);
}

void StaticImageColorSource::updateImage(const QImage &newImage)
{
	image = newImage;
	//Now we set the pixmap to the pixmap that we got from the image
	imageLabel->setPixmap(QPixmap::fromImage(image));
	
	imageLabel->updateGeometry();
	
	displayWidget->setMaximumSize(imageLabel->minimumSize());	
}
