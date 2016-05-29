#ifndef QTCAMERASOURCE_H
#define QTCAMERASOURCE_H

#include "ColorSource.h"
#include "Color.h"

#include <QImage>
#include <QCamera>
#include <QAbstractVideoSurface>

class CallbackVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
signals:
    void update(const QImage& image);
public:
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);
};

class QtCameraSource  : public ImageSource
{
    Q_OBJECT
public:
    explicit QtCameraSource(QObject* parent = nullptr);
    
public slots:
    
    void start();
    
    void stop();
    
protected slots:
    void onError(QCamera::Error);
    
private:
    QCamera* camera;
    CallbackVideoSurface* surface;
};

#endif // QTCAMERASOURCE_H
