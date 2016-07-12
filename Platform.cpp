#include "Platform.h"

#include <QSysInfo>

Platform::Platform(QObject *parent) : QObject(parent)
{
    
}

bool Platform::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

bool Platform::isEmbedded()
{
#ifndef Q_OS_ANDROID
    static bool embedded = QSysInfo::buildCpuArchitecture().startsWith("arm");
    return embedded;
#else
    return false;
#endif
}

bool Platform::isUnix()
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

bool Platform::isWindows()
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

bool Platform::isDesktop()
{
    return !isEmbedded() && !isAndroid();
}

