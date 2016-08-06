HEADERS += \
    $$PWD/include/AbstractAppender.h \
    $$PWD/include/AbstractStringAppender.h \
    $$PWD/include/ConsoleAppender.h \
    $$PWD/include/CuteLogger_global.h \
    $$PWD/include/FileAppender.h \
    $$PWD/include/Logger.h \
    $$PWD/include/RollingFileAppender.h

SOURCES += \
    $$PWD/src/AbstractAppender.cpp \
    $$PWD/src/AbstractStringAppender.cpp \
    $$PWD/src/ConsoleAppender.cpp \
    $$PWD/src/FileAppender.cpp \
    $$PWD/src/Logger.cpp \    
    $$PWD/src/RollingFileAppender.cpp

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

android {
HEADERS += $$PWD/include/AndroidAppender.h
SOURCES += $$PWD/src/AndroidAppender.cpp
}

win32 {
HEADERS += $$PWD/include/OutputDebugAppender.h
SOURCES += $$PWD/src/OutputDebugAppender.cpp 
}
