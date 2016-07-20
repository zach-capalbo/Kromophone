#ifndef QMLCAMERASOURCE_H
#define QMLCAMERASOURCE_H

#include "ColorSource.h"

#include <QObject>
#include <QImage>
#include <QCamera>
#include <QVideoProbe>
#include <QQuickView>

class QmlCameraSource  : public ImageSource
{
    Q_OBJECT
public:
    explicit QmlCameraSource(QQuickView* view, QObject* parent = nullptr);
    
public slots:
    void start();
    void stop();
    
protected slots:
    void onFrame(const QVideoFrame& frame);
    
private:
    QCamera* camera;
    QQuickView* view;
    QVideoProbe probe;
    int frameNum;
};

#endif // QMLCAMERASOURCE_H
