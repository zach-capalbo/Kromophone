#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T16:11:25
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Kromophone
TEMPLATE = app

target.path = /tmp/
INSTALLS += target


SOURCES += main.cpp\
        MainWindow.cpp \
    Camera.cpp \
    Kromophone.cpp \
    ColorSource.cpp \
    AudioEngine.cpp \
    Sound.cpp \
    Timbre.cpp \
    Transform.cpp

HEADERS  += MainWindow.h \
    Camera.h \
    Kromophone.h \
    ColorSource.h \
    AudioEngine.h \
    Sound.h \
    Timbre.h \
    Transform.h

FORMS    += MainWindow.ui
