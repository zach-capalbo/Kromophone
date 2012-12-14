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
	// TEST VALUES
	RandomColorSource M_RCS;
	QThread sourceThread;
	M_RCS.moveToThread(&sourceThread);
	QMetaObject::invokeMethod(&M_RCS,"start");
	sourceThread.start();
	
	SoundOut testOut;

	ImageColorSource i("/home/zach/Backgrounds/cow-in-space.jpg");
	
	OpenCVColorSource cv;
	
	HSLMode M_T;

	QThread audioThread;
	AudioEngine audio;
	
	ColorPreviewWidget* preview = new ColorPreviewWidget;
	
	preview->show();
	
	audio.moveToThread(&audioThread);
	
	QMetaObject::invokeMethod(&audio,"initalizeAudio");
	
	audioThread.start(QThread::HighestPriority);
	
	ColorSource* source = &cv;
	
	QObject::connect(source, SIGNAL(colorChanged(Color)), &M_T, SLOT(ReceiveColor(Color)));
	QObject::connect(source, SIGNAL(colorChanged(Color)), preview, SLOT(setColor(Color)));
	
	QObject::connect(&M_T, SIGNAL(SoundGenerated(Sound)), &audio, SLOT(PlaySound(Sound)));
	//QObject::connect(&M_T, SIGNAL(SoundGenerated(Sound)), &testOut, SLOT(PlaySound(Sound)));
	//cv.moveToThread(&sourceThread);
	
	return a.exec();
}
