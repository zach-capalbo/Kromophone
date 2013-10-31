#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T15:35:46
#
#-------------------------------------------------

QT       += core gui multimedia qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kromophone-droid
TEMPLATE = app

android: INCLUDEPATH += /home/zach/src/android/OpenCV-2.4.6-android-sdk/sdk/native/jni/include
android: LIBS += -L/home/zach/src/android/OpenCV-2.4.6-android-sdk/sdk/native/libs/armeabi-v7a/ -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_androidcamera -lopencv_core -ljnigraphics
android: LIBS += -L/home/zach/src/android/OpenCV-2.4.6-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a -llibjpeg -llibpng -llibtiff -llibjasper -lIlmImf -ltbb

DEFINES += USE_OPENCV

SOURCES += main.cpp\
        DroidWidget.cpp \
    AudioEngine.cpp \
    AudioGenerator.cpp \
    Camera.cpp \
    Color.cpp \
    ColorPreviewWidget.cpp \
    Timbre.cpp \
    Transform.cpp \
    Sound.cpp \
    SoundOut.cpp \
    MainWindow.cpp \
    OpenCVColorSource.cpp \
    ColorSource.cpp \
    DesktopImageSource.cpp \
    GPIOWatcher.cpp \
    ImageSourceWidget.cpp \
    KeyboardFilter.cpp \
    Kromophone.cpp

HEADERS  += DroidWidget.h \
    AudioEngine.h \
    AudioGenerator.h \
    Camera.h \
    Color.h \
    SoundOut.h \
    Timbre.h \
    Transform.h \
    Sound.h \
    MainWindow.h \
    OpenCVColorSource.h \
    ColorPreviewWidget.h \
    ColorSource.h \
    DesktopImageSource.h \
    GPIOWatcher.h \
    ImageSourceWidget.h \
    KeyboardFilter.h \
    Kromophone.h

FORMS    += DroidWidget.ui \
    MainWindow.ui \
    ImageSourceWidget.ui

CONFIG += mobility
MOBILITY = 

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

ANDROID_EXTRA_LIBS = ../../android/OpenCV-2.4.6-android-sdk/sdk/native/libs/armeabi-v7a/libnative_camera_r4.1.1.so ../../android/OpenCV-2.4.6-android-sdk/sdk/native/libs/armeabi-v7a/libopencv_java.so ../../android/OpenCV-2.4.6-android-sdk/sdk/native/libs/armeabi-v7a/libopencv_info.so

