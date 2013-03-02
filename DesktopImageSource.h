#ifndef DESKTOPIMAGESOURCE_H
#define DESKTOPIMAGESOURCE_H

#include <ColorSource.h>

class DesktopImageSource : public ImageSource
{
	Q_OBJECT
public:
	explicit DesktopImageSource(QObject *parent = 0);
	
signals:
	
public slots:
	
	virtual void start();
	virtual void timerEvent(QTimerEvent *);
	
};

#endif // DESKTOPIMAGESOURCE_H
