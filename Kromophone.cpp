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
#include <QMetaType>
#include <QApplication>
#include <QQmlContext>

#include "Kromophone.h"
#include "StaticImageColorSource.h"
#include "LiveImageColorSource.h"
#include "QtCameraSource.h"
#include "QmlCameraSource.h"
#include "Transform.h"

#include "V4L2ImageSource.h"

Kromophone::Kromophone(QObject *parent) :
	QObject(parent), 
    audioEngine(nullptr), 
    colorToSoundTransform(nullptr), 
    imageSource(nullptr), 
    colorSource(nullptr),
    quickView(nullptr)
{
    _platform = new Platform;
}

bool Kromophone::isAndroid()
{
#ifdef DESKTOP
    return false;
#else
    return true;
#endif
}

QObject* Kromophone::settings()
{
    return SettingsCreator::qmlSettingMap();
}

QColor Kromophone::color()
{
    return lastColor;
}

QStringList Kromophone::settingList()
{
    return SettingsCreator::displayedSettings();
}

QObject*Kromophone::platform()
{
    return _platform;
}

void Kromophone::startup()
{
    startup(qApp->arguments());
}

void Kromophone::startup(const QStringList arguments)
{
    args.parse(arguments);
    
    initializeAudio();
    createInitialTransform();
    
    if (!Settings::headless().value().toBool())
    {
        createDisplay();
    }
    
    if (args.contains("camera"))
    {
        startCameraSonification();
    }
    else if (args.contains("spectrum"))
    {
        startFileSonification(":/Images/Resources/spectrum.jpg");
    }
    else if (args.contains("file"))
    {
        startFileSonification(args["file"].toString());
    }
    
    emit startupComplete();
}

void Kromophone::startFileSonification(const QString& path)
{
    if (imageSource != nullptr || colorSource != nullptr)
    {
        qDebug() << "Cannot start file with sonification already in progress";
        return;
    }
    
    this->imageSource = new FileImageSource(path);
    StaticImageColorSource* imageColorSource = new StaticImageColorSource;
    this->colorSource = imageColorSource;
        
    connect(imageSource, SIGNAL(update(QImage)), imageColorSource, SLOT(updateImage(QImage)));
    connect(colorSource, SIGNAL(colorChanged(Color)), colorToSoundTransform, SLOT(ReceiveColor(Color)));
    
    connect(colorSource, SIGNAL(colorChanged(Color)), this, SLOT(onColorChanged(Color)));
    
    imageSource->start();
    audioThread.start();
    emit fileSonificationStarted(path);
}

void Kromophone::startCameraSonification()
{
    if (imageSource != nullptr || colorSource != nullptr)
    {
        qDebug() << "Cannot start camera with sonification already in progress";
        return;
    }
    
    this->imageSource = _platform->isEmbedded() ? (ImageSource*) new V4L2ImageSource : (ImageSource*) new QtCameraSource;
    LiveImageColorSource* imageColorSource = new LiveImageColorSource;
    
    this->colorSource = imageColorSource;
    
    connect(imageSource, SIGNAL(update(QImage)), imageColorSource, SLOT(updateImage(QImage)));
    connect(imageColorSource, SIGNAL(previewImageChanged(QImage)), this, SLOT(onImageChanged(QImage)));
    connect(imageColorSource, SIGNAL(doSweep(bool,QPointF)), this->colorToSoundTransform, SLOT(setSweep(bool,QPointF)));
    connect(colorSource, SIGNAL(colorChanged(Color)), colorToSoundTransform, SLOT(ReceiveColor(Color)));
    connect(colorSource, SIGNAL(colorChanged(Color)), this, SLOT(onColorChanged(Color)));
    
    imageSource->start();
    audioThread.start();
    emit cameraSonificationStarted();
}

void Kromophone::onMouseImageHover(int x, int y)
{
    StaticImageColorSource* imageColorSource = qobject_cast<StaticImageColorSource*>(this->colorSource);
    
    if (imageColorSource != nullptr)
    {
        imageColorSource->setMouse(QPoint(x, y));
    }
}

void Kromophone::onColorChanged(Color newColor)
{
    lastColor = newColor;
    emit colorChanged(lastColor);
}

void Kromophone::onImageChanged(const QImage& image)
{
    this->previewProvider.setImage(image);
}

void Kromophone::initializeAudio()
{
    if (audioEngine != nullptr)
    {
        return;
    }
    
    audioEngine = new AudioEngine;
    audioEngine->moveToThread(&audioThread);
    QMetaObject::invokeMethod(audioEngine, "initializeAudio");

}

void Kromophone::createInitialTransform()
{
    colorToSoundTransform = new RGBYWMode;
    connect(colorToSoundTransform, SIGNAL(SoundGenerated(Sound)), audioEngine, SLOT(PlaySound(Sound)));
	connect(colorToSoundTransform, SIGNAL(SoundsGenerated(SoundList)), audioEngine, SLOT(PlaySounds(SoundList)));
}

void Kromophone::createDisplay()
{
    quickView = new QQuickView;
    quickView->rootContext()->setContextProperty("app", this);
    quickView->engine()->addImageProvider("preview", &previewProvider);
    quickView->setSource(QUrl("qrc:///kromophone-ui/KromophoneContainer.qml"));
    quickView->setWidth(800);
    quickView->setHeight(600);
    
    if (isAndroid())
    {
        quickView->showFullScreen();
    }
    else
    {
        quickView->show();
    }
}
