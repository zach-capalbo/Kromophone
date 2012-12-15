#include "KromophoneKeyboardFilter.h"

#include <QEvent>
#include <QKeyEvent>

KromophoneKeyboardFilter::KromophoneKeyboardFilter(QObject *parent) :
	QObject(parent)
{
}

bool KromophoneKeyboardFilter::eventFilter(QObject *obj, QEvent *event)
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
			
		default:
			return false;
		}
		
		return true;
	}
	
	return false;
}
