#include <QApplication>
#include "MainWindow.h"
#include "ColorSource.h"
#include "Color.h"
#include "Transform.h"
#include "SoundOut.h"
#include <QThread>
#include <QMetaType>
#include "OpenCVColorSource.h"
#include "AudioEngine.h"
#include "ColorPreviewWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<Color>();
	qRegisterMetaType<Sound>();
	qRegisterMetaType<SoundList>();

    MainWindow w;

    w.show();
	
	return a.exec();

}
