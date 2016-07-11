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
#include "ColorSource.h"
#include <QTimer>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QRgb>
#include <QDebug>
#include "KeyboardFilter.h"

RandomColorSource::RandomColorSource()
{

}

const Color RandomColorSource::color()
{
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

FileImageSource::FileImageSource(const QString &file)
{
	load(file);
}

void FileImageSource::load(const QString &file)
{
    QString parsedPath = file;
    
    if (file.startsWith("file://")) {
        parsedPath = QUrl(file).toLocalFile();
    }
    
	image = QImage(parsedPath);
    
    if (image.isNull())
    {
        qWarning() << "Invalid image " << file;
    }
}
