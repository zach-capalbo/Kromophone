#include <QApplication>
#include "MainWindow.h"
#include "ColorSource.h"
#include "Color.h"
#include "Transform.h"
#include "SoundOut.h"
#include <QThread>
#include <QMetaType>

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
	
	ImageColorSource i("/home/zach/Backgrounds/cow-in-space.jpg");
	
	Transform M_T;
	SoundOut M_SO;
	//
	//
	QObject::connect(&i, SIGNAL(colorChanged(Color)),
					 &M_T, SLOT(fromJon(Color)));
	QObject::connect(&M_T, SIGNAL(toNathan(Sound)),
					 &M_SO, SLOT(PlaySound(Sound)));
	//

	
	MainWindow w;
	w.show();
	
	return a.exec();
}
