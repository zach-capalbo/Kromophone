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
//	qRegisterMetaType<Color>();
//	qRegisterMetaType<Sound>();
//	qRegisterMetaType<SoundList>();

    MainWindow w;

//    QObject::connect(fButton1, SIGNAL(clicked()), &a, SLOT(quit()));

//    w.show();

//    /*

	// TEST VALUES
    RandomColorSource M_RCS;
    QThread sourceThread;
    M_RCS.moveToThread(&sourceThread);
    QMetaObject::invokeMethod(&M_RCS,"start");
    sourceThread.start();
	
//	SoundOut testOut;

    //FileImageSource fs(":/Images/cow-in-space.jpg");
    //StaticImageColorSource i;
    //QObject::connect(&fs, SIGNAL(update(QImage)), &i, SLOT(updateImage(QImage)));
    //fs.start();


    w.show();


	OpenCVImageSource cv;
	LiveImageColorSource ls;
	QObject::connect(&cv,SIGNAL(update(QImage)), &ls, SLOT(updateImage(QImage)));
	cv.start();
	
	RGBYWMode M_T;

	QThread audioThread;
	AudioEngine audio;
	
	ColorPreviewWidget* preview = new ColorPreviewWidget;
	
	preview->show();
	
	audio.moveToThread(&audioThread);
	
	QMetaObject::invokeMethod(&audio,"initalizeAudio");
	
	audioThread.start(QThread::HighestPriority);
	
	ImageColorSource* source = &ls;
	
	QObject::connect(source, SIGNAL(colorChanged(Color)), &M_T, SLOT(ReceiveColor(Color)));
	QObject::connect(source, SIGNAL(colorChanged(Color)), preview, SLOT(setColor(Color)));
	QObject::connect(source, SIGNAL(doSweep(bool,QPointF)), &M_T, SLOT(setSweep(bool,QPointF)));
	
	QObject::connect(&M_T, SIGNAL(SoundGenerated(Sound)), &audio, SLOT(PlaySound(Sound)));
	QObject::connect(&M_T, SIGNAL(SoundsGenerated(SoundList)), &audio, SLOT(PlaySounds(SoundList)));
	//QObject::connect(&M_T, SIGNAL(SoundGenerated(Sound)), &testOut, SLOT(PlaySound(Sound)));
	//cv.moveToThread(&sourceThread);

//    */
	
	return a.exec();

}
