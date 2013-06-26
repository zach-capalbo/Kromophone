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

CONFIG   += mobility
CONFIG	 += opencv
rpi:CONFIG	 += multimediakit


target.path = /usr/bin
INSTALLS += target

#INCLUDEPATH += /usr/include/QtMultimediaKit
#INCLUDEPATH += $$OE_QMAKE_INCDIR_QT/QtMultimedia
#LIBS += -lQtMultimediaKit

!rpi: DEFINES+= DESKTOP

andoird: QMAKE_CXXFLAGS += -frtti -fexceptions
android: INCLUDEPATH += /home/zach/src/android/OpenCV-2.4.0/include
android: LIBS += -L/home/zach/src/android/OpenCV-2.4.0/libs/armeabi-v7a/ -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_androidcamera -lopencv_core -ljnigraphics
android: LIBS += -L/home/zach/src/android/OpenCV-2.4.0/share/OpenCV/3rdparty/libs/armeabi-v7a/ -ltbb -llibjpeg -llibpng -llibtiff -llibjasper

!android:opencv:unix: LIBS += -lopencv_core -lopencv_video -lopencv_highgui
opencv: DEFINES += USE_OPENCV
opencv:win32: INCLUDEPATH += $$OPENCV\\include $$OPENCV\\modules\\core\\include $$OPENCV\\modules\\video\\include $$OPENCV\\modules\\imgproc\\include $$OPENCV\\modules\\highgui\\include
opencv:win32: LIBS += -L$$OPENCV\\build\\x86\\vc10\\lib
CONFIG(debug, debug|release):opencv:win32: LIBS += -lopencv_core245d -lopencv_video245d -lopencv_highgui245d
CONFIG(release, debug|release):opencv:win32: LIBS += -lopencv_core245 -lopencv_video245 -lopencv_highgui245
#CONFIG(release, debug|release): CONFIG-=debug
#message($$CONFIG)

#Release:CONFIG-=debug

win32: RC_FILE = icon.rc

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
    README.md \
    icon.rc \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/version.xml \
    android/AndroidManifest.xml \
    android/res/values-it/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/layout/splash.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ro/strings.xml

initscripts.files += S30kromophone
initscripts.path = /etc/rc5.d
rpi:INSTALLS += initscripts
