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
}

MainWindow::~MainWindow()
{
	delete ui;
}


//start kromo with camera
void MainWindow::on_cButton_clicked()
{
    //START
}

//start kromo on image selected from file dialog
void MainWindow::on_fButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("File (*.*)"));

    //START
}

//[incomplete] to be used on fbutton clicked
void MainWindow::getFile()
{
//    QFile myFile =;
//    myFile.open(QIODevice::ReadOnly);

}
