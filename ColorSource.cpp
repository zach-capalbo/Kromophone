#include "ColorSource.h"

RandomColorSource::RandomColorSource()
{

}

const Color RandomColorSource::color()
{
    int randomGen = rand() %255;
    Color randomColor = Color.FromArgb(randomGen.Next(255), randomGen.Next(255),
    randomGen.Next(255));

    return randomColor;
};
















