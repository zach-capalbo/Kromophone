#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------

MOBILITY += multimedia
QT       += core gui widgets
QT	 += mobility multimediakit
#QT	 += multimedia

CONFIG   += console mobility debug
CONFIG   -= app_bundle
CONFIG	 += opencv
#CONFIG	 += multimediakit
CONFIG   += mobility;
TARGET = Kromophone
TEMPLATE = app

target.path = /tmp/
INSTALLS += target

#INCLUDEPATH += /usr/include/QtMultimediaKit
#INCLUDEPATH += $$OE_QMAKE_INCDIR_QT/QtMultimedia
#LIBS += -lQtMultimediaKit

opencv: LIBS += -lopencv_core -lopencv_video -lopencv_highgui
opencv: DEFINES += USE_OPENCV
#release: CONFIG-=debug
#message($$CONFIG)

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3
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
    KeyboardFilter.cpp

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
    KeyboardFilter.h

FORMS    += MainWindow.ui

RESOURCES += \
    Resources/resources.qrc
