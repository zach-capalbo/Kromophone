#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------


# Common Configuration
TARGET = Kromophone
TEMPLATE = app

QT       += core gui widgets
CONFIG	 += opencv

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
	OPENCV = /home/zach/src/android/OpenCV-2.4.6-android-sdk
	QT       += core gui multimedia qml quick
	INCLUDEPATH += $$OPENCV/sdk/native/jni/include
	LIBS += -L$$OPENCV/sdk/native/libs/armeabi-v7a/ -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_androidcamera -lopencv_core -ljnigraphics
	LIBS += -L$$OPENCV/sdk/native/3rdparty/libs/armeabi-v7a -llibjpeg -llibpng -llibtiff -llibjasper -lIlmImf -ltbb
	CONFIG += mobility
	MOBILITY = 
	ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
	OTHER_FILES += \
		android/AndroidManifest.xml
	ANDROID_EXTRA_LIBS = $$OPENCV/sdk/native/libs/armeabi-v7a/libnative_camera_r4.1.1.so $$OPENCV/sdk/native/libs/armeabi-v7a/libopencv_java.so $$OPENCV/sdk/native/libs/armeabi-v7a/libopencv_info.so
}
else:unix {
	target.path = /tmp/usr/bin
	INSTALLS += target
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
	# Change this to wherever you have OpenCV installed on windows
	OPENCV = C:\\opencv
	DEFINES+= DESKTOP
	opencv:win32: INCLUDEPATH += $$OPENCV\\include $$OPENCV\\modules\\core\\include $$OPENCV\\modules\\video\\include $$OPENCV\\modules\\imgproc\\include $$OPENCV\\modules\\highgui\\include
	opencv:win32: LIBS += -L$$OPENCV\\build\\x86\\vc10\\lib
	CONFIG(debug, debug|release):opencv:win32: LIBS += -lopencv_core245d -lopencv_video245d -lopencv_highgui245d
	CONFIG(release, debug|release):opencv:win32: LIBS += -lopencv_core245 -lopencv_video245 -lopencv_highgui245
	RC_FILE = icon.rc

}

opencv: DEFINES += USE_OPENCV

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
    functovect.rb \
    playtimbre.m

