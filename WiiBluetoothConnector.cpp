#include "WiiBluetoothConnector.h"
#include <QThread>
#include <QDebug>

WiiBluetoothConnector::WiiBluetoothConnector(QObject *parent) : QObject(parent),
    timeoutMs(20 * 1000)
{    
}

void WiiBluetoothConnector::connectToWii()
{
    timeoutTimer.restart();
    
    QProcess::execute(QStringLiteral("/home/pi/connect_to_wiimote.sh"));

    QThread::currentThread()->sleep(1);
    
    emit timeout();
    return;
}
