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

#include "Logger.h"

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

QmlCameraSource::QmlCameraSource(QQuickView* view, QObject* parent)
{
    this->view = view;
    frameNum = 0;
}

void QmlCameraSource::start()
{
    if (view == nullptr)
    {
        qWarning() << "No view. Cannot find QML Camera";
        return;
    }
    
    QObject *qmlCamera = view->rootObject()->findChild<QObject*>("qrCameraQML");
    
    if (qmlCamera == nullptr)
    {
        qWarning() << "Cannot find QML camera object";
        return;
    }
    
    camera = qvariant_cast<QCamera*>(qmlCamera->property("mediaObject"));
    
    if (camera == nullptr)
    {
        qWarning() << "Cannot retrieve camera from qml object";
        return;
    }
    
    LOG_INFO() << camera->supportedViewfinderResolutions();
    LOG_INFO() << camera->viewfinderSettings().resolution();
    connect(&probe,SIGNAL(videoFrameProbed(QVideoFrame)),this,SLOT(onFrame(QVideoFrame)));
    probe.setSource(camera);
    connect(view, SIGNAL(closing(QQuickCloseEvent)), qApp, SLOT(quit()));
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
