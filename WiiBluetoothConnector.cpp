#include "WiiBluetoothConnector.h"
#include "Platform.h"
#include <QThread>
#include "Logger.h"

WiiBluetoothConnector::WiiBluetoothConnector(QObject *parent) : QObject(parent),
    timeoutMs(20 * 1000)
{    
}

void WiiBluetoothConnector::connectToWii()
{
    if (Platform::currentPlatform().isEmbedded())
    {
        // Since you can't do any of this manually on an RPi in your pocket
        timeoutTimer.restart();
        QProcess::execute(QStringLiteral("/home/pi/connect_to_wiimote.sh"));
        QThread::currentThread()->sleep(1);
    }
    
    emit timeout();
    return;
}
