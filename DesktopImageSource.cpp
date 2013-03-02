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
