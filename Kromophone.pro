#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------


# Common Configuration
TARGET = Kromophone
TEMPLATE = app

QT       += core gui widgets quick qml websockets
#hurray for C++11
QMAKE_CXXFLAGS += -std=c++0x

contains(QMAKE_CXX, arm-poky-linux-gnueabi-g++): CONFIG+=rpi

contains(QT_VERSION, ^5\\.*\\..*) {
QT	+= multimedia
} 
else {
QT	 += mobility multimediakit
MOBILITY += multimedia
}

android {
	QT       += core gui multimedia qml quick androidextras
	CONFIG += mobility
	MOBILITY = 
	ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
	OTHER_FILES += \
		android/AndroidManifest.xml
}
else:unix {
	target.path = /home/pi/kromophone
	INSTALLS += target

#	CONFIG += opencv

	opencv: DEFINES += USE_OPENCV
	opencv: LIBS += -lopencv_core -lopencv_video -lopencv_highgui

	rpi {
		QT	 += multimedia
		message(Making for raspberry pi)
		CONFIG	 += mobility
		initscripts.files += S30kromophone
		initscripts.path = /etc/rc5.d
#		INSTALLS += initscripts
	}
	else {
		CONFIG   += mobility
		DEFINES += DESKTOP
	}
}
else:win32 {
	QT	 += multimedia
	DEFINES+= DESKTOP
	RC_FILE = icon.rc

}

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
    Sound.cpp \
    Timbre.cpp \
    Color.cpp \
    Transform.cpp \
    ColorPreviewWidget.cpp \
    KeyboardFilter.cpp \
    GPIOWatcher.cpp \
    Settings.cpp \
    PreviewImageProvider.cpp \
    Platform.cpp \
    ArgParser.cpp \
    WiiMote.cpp \
    WiiBluetoothConnector.cpp \
    WiiMoteInputController.cpp \
    WebSocketServer.cpp


HEADERS  += MainWindow.h \
    Camera.h \
    Kromophone.h \
    Sound.h \
    Timbre.h \
    Color.h \
    Transform.h \
    ColorPreviewWidget.h \
    KeyboardFilter.h \
    GPIOWatcher.h \
    Settings.h \
    PreviewImageProvider.h \
    Platform.h \
    ArgParser.h \
    WiiMote.h \
    WiiBluetoothConnector.h \
    WiiMoteInputController.h \
    version.h \
    WebSocketServer.h

    
FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    S30kromophone \
    LICENSE \
    README.md \
    icon.rc \ 
    functovect.rb \
    playtimbre.m

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/KeepOnActivity.java \ 
    package_for_windows.bat \
    Kromophone.iss \
    Kromophone-bitrock.xml

include(video/video.pri)
include(sources.pri)
include(audio.pri)
