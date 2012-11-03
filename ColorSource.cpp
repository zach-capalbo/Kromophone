#include "ColorSource.h"
#include <QTimer>

RandomColorSource::RandomColorSource()
{

}

const Color RandomColorSource::color()
{
    int randomGen = rand() %255;
    Color randomColor(rand()%255,rand()%255,rand()%255);

    return randomColor;
};



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










