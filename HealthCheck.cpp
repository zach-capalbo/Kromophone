#include "HealthCheck.h"
#include "Logger.h"
#include <QFile>

HealthCheck::HealthCheck(QObject *parent) : QObject(parent)
{
    this->startTimer(1000);
}

void HealthCheck::timerEvent(QTimerEvent *event)
{
    QFile file("/proc/meminfo");
    if (file.open(QFile::ReadOnly))
    {
        LOG_INFO() << file.readLine();
        LOG_INFO() << file.readLine();
    }
}
