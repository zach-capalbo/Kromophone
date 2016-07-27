#include "Platform.h"

#include <QSysInfo>

Platform::Platform(QObject *parent) : QObject(parent)
{
    
}

const Platform &Platform::currentPlatform()
{
    static Platform platform;
    return platform;
}

bool Platform::isAndroid() const
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

bool Platform::isEmbedded() const
{
#ifndef Q_OS_ANDROID
    static bool embedded = QSysInfo::buildCpuArchitecture().startsWith("arm");
    return embedded;
#else
    return false;
#endif
}

bool Platform::isUnix() const
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

bool Platform::isWindows() const
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

bool Platform::isDesktop() const
{
    return !isEmbedded() && !isAndroid();
}

