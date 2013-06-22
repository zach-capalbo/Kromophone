#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------

# Change this to wherever you have OpenCV installed on windows
OPENCV = C:\\opencv

TARGET = Kromophone
TEMPLATE = app

contains(QMAKE_CXX, arm-poky-linux-gnueabi-g++): CONFIG+=rpi

rpi: message(Making for raspberry pi)

QT       += core gui widgets

contains(QT_VERSION, ^5\\.*\\..*) {
QT	+= multimedia
} 
else {
QT	 += mobility multimediakit
MOBILITY += multimedia
}
win32: QT	 += multimedia
rpi:QT	 += multimedia

CONFIG   += console mobility
CONFIG	 += opencv
rpi:CONFIG	 += multimediakit
CONFIG   += mobility;


target.path = /usr/bin
INSTALLS += target

#INCLUDEPATH += /usr/include/QtMultimediaKit
#INCLUDEPATH += $$OE_QMAKE_INCDIR_QT/QtMultimedia
#LIBS += -lQtMultimediaKit

!rpi: DEFINES+= DESKTOP

opencv:unix: LIBS += -lopencv_core -lopencv_video -lopencv_highgui
opencv: DEFINES += USE_OPENCV
opencv:win32: INCLUDEPATH += $$OPENCV\\include $$OPENCV\\modules\\core\\include $$OPENCV\\modules\\video\\include $$OPENCV\\modules\\imgproc\\include $$OPENCV\\modules\\highgui\\include
opencv:win32: LIBS += -L$$OPENCV\\build\\x86\\vc10\\lib
CONFIG(debug, debug|release):opencv:win32: LIBS += -lopencv_core245d -lopencv_video245d -lopencv_highgui245d
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
    DesktopImageSource.cpp \
    GPIOWatcher.cpp

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
    DesktopImageSource.h \
    GPIOWatcher.h

FORMS    += MainWindow.ui

RESOURCES += \
    Resources/resources.qrc

OTHER_FILES += \
    S30kromophone \
    LICENSE \
    README.md

initscripts.files += S30kromophone
initscripts.path = /etc/rc5.d
rpi:INSTALLS += initscripts
