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
#include "DesktopImageSource.h"
#include <QDesktopWidget>
#include <QApplication>

DesktopImageSource::DesktopImageSource(QObject *parent) :
	ImageSource()
{
}

void DesktopImageSource::start()
{
	startTimer(10);
}

void DesktopImageSource::timerEvent(QTimerEvent *)
{
	QDesktopWidget *desktop = QApplication::desktop();
    QPixmap screenshot = QPixmap::grabWindow(desktop->winId(), 0, 0, desktop->width(), desktop->height());
	emit update(screenshot.toImage());
}
