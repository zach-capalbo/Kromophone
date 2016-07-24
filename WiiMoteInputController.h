#ifndef WIIMOTEINPUTCONTROLLER_H
#define WIIMOTEINPUTCONTROLLER_H

#include "WiiMote.h"
#include "WiiBluetoothConnector.h"

#include <QThread>
#include <QTimer>

class WiiMoteInputController : public QObject
{
    Q_OBJECT
public:
    WiiMoteInputController(QObject* parent = nullptr);
    
public slots:
    void start();
    
    void onReleased(int code);
    
    void doSearch();
    
private slots:
    void findWiiMote();
    
private:
    WiiMote* wiimote;
    WiiBluetoothConnector* blueToothConnector;
    QThread loopthread;
    QThread searchThread;
    QTimer searchTimer;
};

#endif // WIIMOTEINPUTCONTROLLER_H
