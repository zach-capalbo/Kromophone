#ifndef GPIOWATCHER_H
#define GPIOWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>

class GPIOWatcher : public QObject
{
	Q_OBJECT
public:
	explicit GPIOWatcher(int GPIO, QObject *parent = 0);
	
signals:
	void rise();
	void fall();
	
public slots:
	
protected:
	int gpioIndex;
};

#endif // GPIOWATCHER_H
