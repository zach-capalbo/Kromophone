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
#include "KeyboardFilter.h"

#include <QEvent>
#include <QKeyEvent>

KeyboardFilter::KeyboardFilter(QObject *parent) :
	QObject(parent)
{
}

bool KeyboardFilter::eventFilter(QObject *obj, QEvent *event)
{
	if ( event->type() == QEvent::KeyRelease )
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		
		switch (keyEvent->key())
		{
		case Qt::Key_A:
			QMetaObject::invokeMethod(parent(), "toggleAverage");	
			break;
			
		case Qt::Key_Up:
			QMetaObject::invokeMethod(parent(), "increaseAverage");
			break;
			
		case Qt::Key_Down:
			QMetaObject::invokeMethod(parent(), "decreaseAverage");
			break;
			
		case Qt::Key_S:
			QMetaObject::invokeMethod(parent(), "toggleSweep");
			break;
			
		default:
			return false;
		}
		
		return true;
	}
	
	return false;
}
