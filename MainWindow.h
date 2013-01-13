#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "OpenCVColorSource.h"
#include "AudioEngine.h"
#include "Transform.h"
#include <QThread>

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
	//Jon, add your stuff here
};

#endif // MAINWINDOW_H
