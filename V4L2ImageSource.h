#ifndef V4L2IMAGESOURCE_H
#define V4L2IMAGESOURCE_H

#include <QObject>
#include "ImageColorSource.h"

class V4L2ImageSource : public ImageSource
{
    Q_OBJECT
public:
    explicit V4L2ImageSource();
    ~V4L2ImageSource();
    
public slots:
    void start();
    void stop();
    
private slots:
    void getImage();
    void onSaturationChanged(const QVariant& value);
    void onLockExposureChanged(const QVariant& value);
    void onHueChanged(const QVariant& value);
};

#endif // V4L2IMAGESOURCE_H
