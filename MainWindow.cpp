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
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ColorSource.h"

#include <QFile>
#include <QString>
#include <QFileDialog>

#include <QApplication>
//#include "MainWindow.h"
//#include "ColorSource.h"
#include "Color.h"
#include "Transform.h"
#include "SoundOut.h"


#include <QThread>
#include <QMessageBox>
#include <QMetaType>

#include "OpenCVColorSource.h"
#include "AudioEngine.h"
#include "ColorPreviewWidget.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	//Set up the audio engine
	//Move the audio to a seperate thread so that it can run continually
	audioOutput.moveToThread(&audioThread);
	
	//Initialize the audio in that seperate thread, rather than the current thread
	QMetaObject::invokeMethod(&audioOutput,"initalizeAudio");
	
	//Set up the connections for the pathway for the kromophone
	
	//Move the Source to it's own thread to prevent hanging
	fileImageSource.moveToThread(&fileSourceThread);
	
	//Connect the file source to the color source
	connect(&fileImageSource, SIGNAL(update(QImage)), &staticColorSource, SLOT(updateImage(QImage)));
	
	//Connect the color source to the color-to-sound transformation
	connect(&staticColorSource, SIGNAL(colorChanged(Color)), &colorToSoundTransform, SLOT(ReceiveColor(Color)));

#ifdef USE_OPENCV
    //OpenCV Source Specific Stuff
	connect(&cameraSource, SIGNAL(update(QImage)), &liveColorSource, SLOT(updateImage(QImage)));
	connect(&liveColorSource, SIGNAL(colorChanged(Color)), &colorToSoundTransform, SLOT(ReceiveColor(Color)));
#endif
	
	//Common to File & Camera
	//Connect the output from the transform to the audio engine
	connect(&colorToSoundTransform, SIGNAL(SoundGenerated(Sound)), &audioOutput, SLOT(PlaySound(Sound)));
	connect(&colorToSoundTransform, SIGNAL(SoundsGenerated(SoundList)), &audioOutput, SLOT(PlaySounds(SoundList)));
}

MainWindow::~MainWindow()
{
#ifdef USE_OPENCV
    cameraSource.stop();
#endif

	//Quit the audio
	audioThread.quit();
	
	//Wait for it to clean up
	audioThread.wait();
	
	//Quit the file loader
	fileSourceThread.quit();
	
	//Wait for it to clean up
	fileSourceThread.wait();

#ifdef USE_OPENCV
    cameraSourceThread.quit();
    cameraSourceThread.wait();
#endif

	delete ui;
}

//start kromo with camera
void MainWindow::on_cButton_clicked()
{
    //START
	if (! audioThread.isRunning())
	{
		audioThread.start(QThread::HighestPriority);
	}
#ifdef USE_OPENCV
	if (! cameraSourceThread.isRunning() )
	{
        cameraSourceThread.start();
	}
	
	liveColorSource.widget()->show();
    liveColorSource.widget()->installEventFilter(this);
	
    cameraSource.start();
#endif
}

void MainWindow::startImageSource(const QString& file)
{
    //START
	
	//Start the audio if it's not already running
	if (! audioThread.isRunning())
	{
		audioThread.start(QThread::HighestPriority);
	}
	
	if (! fileSourceThread.isRunning())
	{
		fileSourceThread.start();
	}
	
	//Show the file Display widgets
	staticColorSource.widget()->show();
    staticColorSource.widget()->installEventFilter(this);
	
	//Load the file that we just got from the file dialog
	fileImageSource.load(file);
	
	//Start the source going
	fileImageSource.start();
}

//start kromo on image selected from file dialog
void MainWindow::on_fButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("File (*.*)"));
	
	if (file.length() == 0)
	{
		return;
	}
	
	startImageSource(file);
	
}

void MainWindow::on_spectrumButton_clicked()
{
	startImageSource(":/Images/spectrum.jpg");
}

void MainWindow::on_actionAbout_triggered()
{
    QString msg = tr("The Kromophone version 0.1 http://kromophone.com\n" \
					 "\n" \
					 "Copyright 2008-2013 Zachary Capalbo\n" \
                     "\n" \
                     "This is ALPHA Software. It probably won't work right.\n" \
                     "Report bugs at <https://github.com/zach-capalbo/Kromophone/issues>"
			"\n" \
		    "This program is free software: you can redistribute it and/or modify\n"\
		    "it under the terms of the GNU General Public License as published by\n"\
		    "the Free Software Foundation, either version 3 of the License, or\n"\
		    "(at your option) any later version.\n"
			"\n"\
		    "This program is distributed in the hope that it will be useful,\n"\
		    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
		    "GNU General Public License for more details.\n"
			"\n"
		    "You should have received a copy of the GNU General Public License\n"\
		    "along with this program.  If not, see <http://www.gnu.org/licenses/>.");
	
	QMessageBox::about(this, tr("Kromophone"), msg);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if ( event->type() == QEvent::Close )
    {
        audioThread.quit();
#ifdef USE_OPENCV
        cameraSource.stop();
        cameraSourceThread.quit();
#endif
        fileSourceThread.quit();
    }

    return false;
}
