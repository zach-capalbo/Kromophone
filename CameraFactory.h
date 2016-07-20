#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "ImageColorSource.h"
#include "Kromophone.h"

class CameraFactory
{
public:
    static ImageSource* create(Kromophone* app);
};

#endif // CAMERAFACTORY_H
