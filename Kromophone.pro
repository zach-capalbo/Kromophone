#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------
TARGET = Kromophone
TEMPLATE = app

contains(QMAKE_CXX, arm-poky-linux-gnueabi-g++): CONFIG+=rpi

rpi: message(Making for raspberry pi)

MOBILITY += multimedia
QT       += core gui widgets
QT	 += mobility multimediakit
win32: QT	 += multimedia
rpi:QT	 += multimedia

CONFIG   += console mobility
CONFIG	 += opencv
rpi:CONFIG	 += multimediakit
CONFIG   += mobility;


target.path = /tmp/
INSTALLS += target

#INCLUDEPATH += /usr/include/QtMultimediaKit
#INCLUDEPATH += $$OE_QMAKE_INCDIR_QT/QtMultimedia
#LIBS += -lQtMultimediaKit

!rpi: DEFINES+= DESKTOP

opencv:unix: LIBS += -lopencv_core -lopencv_video -lopencv_highgui
opencv: DEFINES += USE_OPENCV
opencv:win32: INCLUDEPATH += C:\\opencv\\include C:\\opencv\\modules\\core\\include C:\\opencv\\modules\\video\\include C:\\opencv\\modules\\imgproc\\include C:\\opencv\\modules\\highgui\\include
opencv:win32: LIBS += -LC:\\opencv\\build\\x86\\vc9\\lib
opencv:win32: LIBS += -lopencv_core243 -lopencv_video243 -lopencv_highgui243
#CONFIG(release, debug|release): CONFIG-=debug
#message($$CONFIG)

#Release:CONFIG-=debug

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG
    unix:QMAKE_CXXFLAGS_RELEASE -= -O2
    unix:QMAKE_CXXFLAGS_RELEASE += -O3
    message("Release Mode!")
}


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
    OpenCVColorSource.cpp \
    AudioGenerator.cpp \
    ColorPreviewWidget.cpp \
    KeyboardFilter.cpp \
    DesktopImageSource.cpp

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
    OpenCVColorSource.h \
    AudioGenerator.h \
    ColorPreviewWidget.h \
    KeyboardFilter.h \
    DesktopImageSource.h

FORMS    += MainWindow.ui

RESOURCES += \
    Resources/resources.qrc
