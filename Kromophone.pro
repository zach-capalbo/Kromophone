#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG   += console mobility debug
CONFIG   -= app_bundle
CONFIG	 += multimediakit
TARGET = Kromophone
TEMPLATE = app

target.path = /tmp/
INSTALLS += target

INCLUDEPATH += /usr/include/QtMultimediaKit
LIBS += -lQtMultimediaKit

LIBS += -lopencv_core -lopencv_video -lopencv_highgui


SOURCES += main.cpp\
        MainWindow.cpp \
    Camera.cpp \
    Kromophone.cpp \
    ColorSource.cpp \
    AudioEngine.cpp \
    Sound.cpp \
    Timbre.cpp \
    Color.cpp \
        SoundOut.cpp \
    Transform.cpp \
   #SoundOutQTAudio.cpp \
	#VideoSource.cpp
    OpenCVColorSource.cpp

HEADERS  += MainWindow.h \
    Camera.h \
    Kromophone.h \
    ColorSource.h \
    AudioEngine.h \
    Sound.h \
    Timbre.h \
    SoundOut.h \
        Color.h \
    Transform.h \
    #SoundOutQTAudio.h \
	#VideoSource.h
    OpenCVColorSource.h

FORMS    += MainWindow.ui
