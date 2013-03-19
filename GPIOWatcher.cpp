#include "GPIOWatcher.h"

GPIOWatcher::GPIOWatcher(int GPIO, QObject *parent) :
	QObject(parent), gpioIndex(GPIO)
{
	
}
