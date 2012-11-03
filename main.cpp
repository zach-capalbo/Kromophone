#include <QApplication>
#include "MainWindow.h"
#include "ColorSource.h"
#include "Transform.h"
#include "SoundOut.h"

int main(int argc, char *argv[])
{
	// TEST VALUES
	RandomColorSource M_RCS;
	Transform M_T;
	SoundOut M_SO;
	//
	//
	QObject::connect(&M_RCS, SIGNAL(colorChanged(Color)),
					 &M_T, SLOT(fromJon(Color)));
	QObject::connect(&M_T, SIGNAL(toNathan(Sound)),
					 &M_SO, SLOT(PlaySound(Sound)));
	//

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
}
