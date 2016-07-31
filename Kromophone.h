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
#ifndef KROMOPHONE_H
#define KROMOPHONE_H

#include <QObject>
#include <QQuickView>
#include <QThread>

#include "ColorSource.h"
#include "AudioEngine.h"
#include "Transform.h"
#include "Settings.h"
#include "ColorSource.h"
#include "PreviewImageProvider.h"
#include "Platform.h"
#include "ArgParser.h"
#include "WiiMoteInputController.h"
#include "SoundEffectGenerator.h"
#include "WebSocketServer.h"
#include "RemoteController.h"

#include <memory>

class Kromophone : public QObject
{
    friend class CameraFactory;
	Q_OBJECT
    Q_PROPERTY(bool isAndroid READ isAndroid NOTIFY startupComplete)
    Q_PROPERTY(QString version READ version NOTIFY startupComplete)
    Q_PROPERTY(QObject* settings READ settings NOTIFY startupComplete)
    Q_PROPERTY(QObject* platform READ platform NOTIFY startupComplete)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(QStringList settingList READ settingList NOTIFY startupComplete)
    
public:
	explicit Kromophone(QObject *parent = 0);
    bool isAndroid();
    QObject* settings();
	QColor color();
    QStringList settingList();
    QObject* platform();
    QString version();
    
signals:
    void startupComplete();
    void colorChanged(QColor color);
    
    void cameraSonificationStarted();
    void fileSonificationStarted(const QString& file);
    void sonificationEnded();
	
public slots:
    void startup();
    void startup(const QStringList arguments);
    void startFileSonification(const QString& path);
    void startCameraSonification();
    void stopSonification();
    
    void connectToRemote(const QString& address);
    void onMouseImageHover(int x, int y);    
    void onColorChanged(Color newColor);
    void onImageChanged(const QImage& image);
        
private:
    void initializeLogging();
    void initializeAudio();
    void createInitialTransform();
    void createDisplay();
    
    //Some things we need to get this working
	//Things we'll need for file and camera
	AudioEngine* audioEngine;
	QThread audioThread;
	Transform* colorToSoundTransform;
	
	//Color source things
	QThread imageSourceThread;
	ImageSource* imageSource; // TODO: smart pointers
	ColorSource* colorSource;
    
    // GUI Stuff
    QQuickView* quickView;
    QColor lastColor;
    PreviewImageProvider previewProvider;
    
    // App Stuff
    Platform* _platform;
    ArgParser args;
    WiiMoteInputController wiiController;
    SoundEffectGenerator* effectGenerator;
    WebSocketServer* webSocketServer;
    RemoteController* remote;
};

#endif // KROMOPHONE_H
