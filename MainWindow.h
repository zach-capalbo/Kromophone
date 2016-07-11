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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LiveImageColorSource.h"
#include "AudioEngine.h"
#include "Transform.h"
#include <QThread>
#include "ColorSource.h"
#include "QtCameraSource.h"
#include "StaticImageColorSource.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private slots:

    void on_cButton_clicked();

    void on_fButton_clicked();

	void on_spectrumButton_clicked();
	
	void on_actionAbout_triggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
	
private:
	Ui::MainWindow *ui;
//    FileDialog *fileDialog;

    void getFile();
	void startImageSource(const QString& file);
	
	//Some things we need to get this working
	//Things we'll need for file and camera
	AudioEngine audioOutput;
	QThread audioThread;
	RGBYWMode colorToSoundTransform;
	
	//Things we'll need for just the file source
	QThread fileSourceThread;
	FileImageSource fileImageSource;
	StaticImageColorSource staticColorSource;
	
	//Things we'll need for the camera
	QThread cameraSourceThread;
	LiveImageColorSource liveColorSource;
	QtCameraSource cameraSource;	
};

#endif // MAINWINDOW_H
