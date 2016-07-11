/*
    This file is part of The Kromophone.
    Copyright (C) 2014 Zachary Capalbo
 
	The Kromophone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Kromophone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Kromophone.  If not, see <http://www.gnu.org/licenses/>.
	
*/
#include <QApplication>
#include "MainWindow.h"
#include "ColorSource.h"
#include "Color.h"
#include "Transform.h"
#include "SoundOut.h"
#include <QThread>
#include <QMetaType>
#include "LiveImageColorSource.h"
#include "AudioEngine.h"
#include "ColorPreviewWidget.h"
#include "DesktopImageSource.h"
#include <QRegion>
#include <QDebug>
#include <QPushButton>
#include "QmlCameraSource.h"

#include "Kromophone.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<Color>();
	qRegisterMetaType<Sound>();
	qRegisterMetaType<SoundList>();
#ifdef DESKTOP
    Kromophone app;
    app.startup();
#else

	QThread acqthread;
	QmlCameraSource cv;
	cv.moveToThread(&acqthread);
	acqthread.start();	
	LiveImageColorSource ls;
	QObject::connect(&cv,SIGNAL(update(QImage)), &ls, SLOT(updateImage(QImage)));
	cv.start();
	
	RGBYWMode M_T;

	QThread audioThread;
	AudioEngine audio;
	audio.moveToThread(&audioThread);
	
	QMetaObject::invokeMethod(&audio,"initalizeAudio");
	
	audioThread.start(QThread::HighestPriority);
	
	ImageColorSource* source = &ls;
	
	QObject::connect(source, SIGNAL(colorChanged(Color)), &M_T, SLOT(ReceiveColor(Color)));
	QObject::connect(source, SIGNAL(doSweep(bool,QPointF)), &M_T, SLOT(setSweep(bool,QPointF)));
	
	QObject::connect(&M_T, SIGNAL(SoundGenerated(Sound)), &audio, SLOT(PlaySound(Sound)));
	QObject::connect(&M_T, SIGNAL(SoundsGenerated(SoundList)), &audio, SLOT(PlaySounds(SoundList)));
#endif
	
	return a.exec();
#ifndef DESKTOP
	audioThread.quit();
    acqthread.quit();
    audioThread.wait();
    acqthread.wait();
#endif

}
