#include "QtCameraSource.h"
#include <QCameraInfo>

QtCameraSource::QtCameraSource(QObject* parent)
{
    camera = new QCamera(QCamera::BackFace);
    q_check_ptr(camera);
    surface = new CallbackVideoSurface;
    connect(surface, &CallbackVideoSurface::update, this, &QtCameraSource::update);
}

void QtCameraSource::start()
{
    if (nullptr == camera)
    {
        qWarning() << "No camera";
        return;
    }
    
    camera->setCaptureMode(QCamera::CaptureViewfinder);
    camera->setViewfinder(surface);
    
    QCameraViewfinderSettings settings;
    settings.setResolution(640,480);
    camera->setViewfinderSettings(settings);
    camera->start();
}

void QtCameraSource::stop()
{
    camera->stop();
}

QList<QVideoFrame::PixelFormat> CallbackVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    return QList<QVideoFrame::PixelFormat> { QVideoFrame::Format_RGB24, QVideoFrame::Format_RGB32, QVideoFrame::Format_RGB555, QVideoFrame::Format_RGB565, QVideoFrame::Format_CameraRaw, QVideoFrame::Format_Jpeg };
}

bool CallbackVideoSurface::present(const QVideoFrame& frame1)
{    
    QVideoFrame frame(frame1);
    QImage::Format format = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage img(frame.bits(), frame.width(), frame.height(), format);
    emit update(img);
    
    return true;
}
