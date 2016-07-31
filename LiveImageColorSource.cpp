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
#include "LiveImageColorSource.h"

#include "Logger.h"
#include <QLabel>
#include <QLayout>
#include <QApplication>
#include <QTimer>
#include "KeyboardFilter.h"


LiveImageColorSource::LiveImageColorSource(QObject* parent) : ImageColorSource(parent)
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
}

void LiveImageColorSource::updateImage(const QImage &image)
{
	cursor.setX(image.width()/2);
	cursor.setY(image.height()/2);
	
	cursor += sweepPos;
    
    sweepSize.setWidth(qMin(sweepSize.width(), image.width() / 2));
	
	
	QImage displayImage(image);
	drawCursor(displayImage);
    
    emit previewImageChanged(displayImage);
    
    if(displayWidget->isVisible())
    {	
		imageLabel->setPixmap(QPixmap::fromImage(displayImage));
		
		imageLabel->update();
	}
	
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
