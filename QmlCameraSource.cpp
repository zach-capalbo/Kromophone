#include "QmlCameraSource.h"
#include <QCameraInfo>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>

extern QImage qt_imageFromVideoFrame(const QVideoFrame &f);
static const int FRAMES_TO_SKIP = 5;

QmlCameraSource::QmlCameraSource(QObject* parent)
{
    frameNum = 0;
}

void QmlCameraSource::start()
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

void QmlCameraSource::stop()
{
    camera->stop();
}

void QmlCameraSource::onFrame(const QVideoFrame& frame)
{
    if (frameNum++ < FRAMES_TO_SKIP) return;
    QImage img = qt_imageFromVideoFrame(frame);
    emit update(img);
    frameNum = 0;
}
