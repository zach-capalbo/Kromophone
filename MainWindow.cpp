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
#include <QMetaType>

#include "OpenCVColorSource.h"
#include "AudioEngine.h"
#include "ColorPreviewWidget.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
//    QObject::connect(ui->fButton1, SIGNAL(clicked()), , SLOT());
	
	//Set up the audio engine
	//Move the audio to a seperate thread so that it can run continually
	audioOutput.moveToThread(&audioThread);
	
	//Initialize the audio in that seperate thread, rather than the current thread
	QMetaObject::invokeMethod(&audioOutput,"initalizeAudio");
	
	//Set up the connections for the pathway for the kromophone
	
	//File Source Specific stuff
	
	//Move the Source to it's own thread to prevent hanging
	fileImageSource.moveToThread(&fileSourceThread);
	
	//Connect the file source to the color source
	connect(&fileImageSource, SIGNAL(update(QImage)), &staticColorSource, SLOT(updateImage(QImage)));
	
	//Connect the color source to the color-to-sound transformation
	connect(&staticColorSource, SIGNAL(colorChanged(Color)), &colorToSoundTransform, SLOT(ReceiveColor(Color)));
	
	//OpenCV Source Specific Stuff
	//Jon, your code goes here
	
	//Common to File & Camera
	//Connect the output from the transform to the audio engine
	connect(&colorToSoundTransform, SIGNAL(SoundGenerated(Sound)), &audioOutput, SLOT(PlaySound(Sound)));
	connect(&colorToSoundTransform, SIGNAL(SoundsGenerated(SoundList)), &audioOutput, SLOT(PlaySounds(SoundList)));
	
	
	
}

MainWindow::~MainWindow()
{
	//Quit the audio
	audioThread.quit();
	
	//Wait for it to clean up
	audioThread.wait();
	
	//Quit the file loader
	fileSourceThread.quit();
	
	//Wait for it to clean up
	fileSourceThread.wait();
	
	delete ui;
}


//start kromo with camera
void MainWindow::on_cButton_clicked()
{
    //START
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

//[incomplete] to be used on fbutton clicked
void MainWindow::getFile()
{
//    QFile myFile =;
//    myFile.open(QIODevice::ReadOnly);

}

void MainWindow::on_spectrumButton_clicked()
{
	startImageSource(":/Images/spectrum.jpg");
}
