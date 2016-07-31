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
#include "Logger.h"

#include "Kromophone.h"
#include "StaticImageColorSource.h"
#include "LiveImageColorSource.h"
#include "Transform.h"
#include "CameraFactory.h"
#include "version.h"
#include "Logger.h"
#include "ConsoleAppender.h"
#include "RollingFileAppender.h"

Kromophone::Kromophone(QObject *parent) :
	QObject(parent), 
    audioEngine(nullptr), 
    colorToSoundTransform(nullptr), 
    imageSource(nullptr), 
    colorSource(nullptr),
    quickView(nullptr),
    effectGenerator(nullptr),
    webSocketServer(nullptr),
    remote(nullptr)
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

QString Kromophone::version()
{
    return QString(KROMOPHONE_VERSION);
}

void Kromophone::startup()
{
    startup(qApp->arguments());
}

void Kromophone::startup(const QStringList arguments)
{
    args.parse(arguments);

    initializeLogging();

    LOG_INFO() << "Kromophone " KROMOPHONE_VERSION " initializing";
    LOG_DEBUG() << "Arguments: " << arguments;

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

    if (!args.contains("noSockets"))
    {
        webSocketServer = new WebSocketServer(this);
        remote = new RemoteController(this);
    }
    
    if (!args.contains("noWiiMote"))
    {
        wiiController.start();
    }
    
    emit startupComplete();
}

void Kromophone::startFileSonification(const QString& path)
{
    if (imageSource != nullptr || colorSource != nullptr)
    {
        LOG_INFO() << "Cannot start file with sonification already in progress";
        return;
    }
    
    this->imageSource = new FileImageSource(path);
    StaticImageColorSource* imageColorSource = new StaticImageColorSource;
    this->colorSource = imageColorSource;
        
    connect(imageSource, SIGNAL(update(QImage)), imageColorSource, SLOT(updateImage(QImage)));
    connect(imageColorSource, SIGNAL(doSweep(bool,QPointF)), this->colorToSoundTransform, SLOT(setSweep(bool,QPointF)));
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
        LOG_INFO() << "Cannot start camera with sonification already in progress";
        return;
    }
    
    this->imageSource = CameraFactory::create(this);
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

void Kromophone::stopSonification()
{
    if (imageSource != nullptr)
    {
        imageSource->deleteLater();
        imageSource = nullptr;
    }
    
    if (colorSource != nullptr)
    {
        colorSource->deleteLater();
        colorSource = nullptr;
    }
    
    audioThread.exit();
    
    emit sonificationEnded();
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

void Kromophone::initializeLogging()
{
   ConsoleAppender* consoleAppender = new ConsoleAppender;
   consoleAppender->setFormat("[%{type:-7}] <%{Function}> %{message}\n");
   logger->registerAppender(consoleAppender);

   ConsoleAppender* qmlAppender = new ConsoleAppender;
   qmlAppender->setFormat("[%{type:-7}] <%{File}:%{Function}> %{message}\n");
   logger->registerCategoryAppender("qml", qmlAppender);

   RollingFileAppender* fileAppender = new RollingFileAppender("kromophone-log.txt");
   fileAppender->setDatePattern(RollingFileAppender::DailyRollover);
   fileAppender->setDetailsLevel(Logger::Info);
   logger->registerAppender(fileAppender);
}

void Kromophone::connectToRemote(const QString &address)
{
    this->remote->connectTo(address);
}

void Kromophone::initializeAudio()
{
    if (audioEngine != nullptr)
    {
        return;
    }

    LOG_TRACE("Initializing Audio");
    
    audioEngine = new AudioEngine;
    effectGenerator = new SoundEffectGenerator(audioEngine);
    
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
    LOG_TRACE("Initializing Display");
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
    
    SettingsCreator::qmlSettingMap()->moveToThread(quickView->engine()->thread());
}
