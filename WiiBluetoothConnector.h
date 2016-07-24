#ifndef WIIBLUETOOTHCONNECTOR_H
#define WIIBLUETOOTHCONNECTOR_H

#include <QObject>
#include <QProcess>
#include <QElapsedTimer>

class WiiBluetoothConnector : public QObject
{
    Q_OBJECT
public:
    explicit WiiBluetoothConnector(QObject *parent = 0);
    
signals:
    void connected();
    void timeout();
    
public slots:
    void connectToWii();
private:
    int timeoutMs;
    QElapsedTimer timeoutTimer;
};

#endif // WIIBLUETOOTHCONNECTOR_H
