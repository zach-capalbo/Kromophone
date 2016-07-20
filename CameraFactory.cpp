#include "CameraFactory.h"

#include "QmlCameraSource.h"
#include "QtCameraSource.h"
#include "V4L2ImageSource.h"

ImageSource* CameraFactory::create(Kromophone* app)
{
    if (app->_platform->isAndroid() || Settings::forceCameraDriver().value() == "qml")
    {
        return new QmlCameraSource(app->quickView);
    }
    else if (app->_platform->isEmbedded() || Settings::forceCameraDriver().value() == "v4l")
    {
        return new V4L2ImageSource;
    }
    else
    {
        return new QtCameraSource;
    }
    
    return nullptr;
}
