#include "ColorSource.h"

RandomColorSource::RandomColorSource()
{
    startTimer(1000);
}

const Color RandomColorSource::color()
{
    int randomGen = rand() %255;
    Color randomColor(rand()%255,rand()%255,rand()%255);

    return randomColor;
};





void RandomColorSource::timerEvent(QTimerEvent *event)
{
    emit colorChanged(color());
}










