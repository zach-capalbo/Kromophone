#include "QmlCameraSource.h"
#include <QCameraInfo>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <QApplication>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#endif

extern QImage qt_imageFromVideoFrame(const QVideoFrame &f);
static const int FRAMES_TO_SKIP = 5;

#ifdef Q_OS_ANDROID
static void keepScreenOn() 
{
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (activity.isValid()) {
        QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");

        if (window.isValid()) {
            const int FLAG_KEEP_SCREEN_ON = 128;
            window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
        }
    }
}
#else
static void keepScreenOn() {}
#endif

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
    connect(v, SIGNAL(closing(QQuickCloseEvent)), qApp, SLOT(quit()));
}

void QmlCameraSource::stop()
{
}

void QmlCameraSource::onFrame(const QVideoFrame& frame)
{
    if (frameNum++ < FRAMES_TO_SKIP) return;
    QImage img = qt_imageFromVideoFrame(frame);
    emit update(img);
    frameNum = 0;
}
