#include "QtCameraSource.h"
#include <QCameraInfo>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>

extern QImage qt_imageFromVideoFrame(const QVideoFrame &f);

QtCameraSource::QtCameraSource(QObject* parent)
{
    frameNum = 0;
}

void QtCameraSource::start()
{
    QQuickView* v = new QQuickView;
    v->setSource(QUrl("qrc:///CameraCapture.qml"));
    v->showFullScreen();
    QObject *qmlCamera = v->rootObject()->findChild<QObject*>("qrCameraQML");
    camera = qvariant_cast<QCamera*>(qmlCamera->property("mediaObject"));
    qDebug() << camera->supportedViewfinderResolutions();
    qDebug() << camera->viewfinderSettings().resolution();
    connect(&probe,SIGNAL(videoFrameProbed(QVideoFrame)),this,SLOT(onFrame(QVideoFrame)));
    probe.setSource(camera);
}

void QtCameraSource::stop()
{
    camera->stop();
}

void QtCameraSource::onError(QCamera::Error e)
{
    qWarning() << e << camera->errorString();
}

void QtCameraSource::onFrame(const QVideoFrame& frame)
{
    if (frameNum++ < 5) return;
    QImage img = qt_imageFromVideoFrame(frame);
//    qDebug() << frame.pixelFormat() << frame.width() << frame.height()  << frame.bits();
//    qDebug() << img.width() << img.height() << img.bits();
    emit update(img);
    frameNum = 0;
}

QList<QVideoFrame::PixelFormat> CallbackVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    return QList<QVideoFrame::PixelFormat> { QVideoFrame::Format_RGB24, QVideoFrame::Format_RGB32, QVideoFrame::Format_RGB555, QVideoFrame::Format_RGB565, QVideoFrame::Format_CameraRaw, QVideoFrame::Format_Jpeg, QVideoFrame::Format_NV21 };
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
