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
#include "Transform.h"

Kromophone::Kromophone(QObject *parent) :
	QObject(parent), 
    audioEngine(nullptr), 
    colorToSoundTransform(nullptr), 
    imageSource(nullptr), 
    colorSource(nullptr),
    quickView(nullptr)
{
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

void Kromophone::startup()
{
    startup(qApp->arguments());
}

void Kromophone::startup(const QStringList arguments)
{
    // Will be used later maybe probably
    Q_UNUSED(arguments);
    
    initializeAudio();
    createInitialTransform();
    createDisplay();
    
    emit startupComplete();
}

void Kromophone::startFileSonification(const QString& path)
{
    this->imageSource = new FileImageSource(path);
    StaticImageColorSource* imageColorSource = new StaticImageColorSource;
    this->colorSource = imageColorSource;
        
    connect(imageSource, SIGNAL(update(QImage)), imageColorSource, SLOT(updateImage(QImage)));
    connect(colorSource, SIGNAL(colorChanged(Color)), colorToSoundTransform, SLOT(ReceiveColor(Color)));
    
    connect(colorSource, SIGNAL(colorChanged(Color)), this, SLOT(onColorChanged(Color)));
    
    imageSource->start();
    audioThread.start();
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
    quickView->setSource(QUrl("qrc:///kromophone-ui/KromophoneContainer.qml"));
    
    if (isAndroid())
    {
        quickView->showFullScreen();
    }
    else
    {
        quickView->show();
    }
}
