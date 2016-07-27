#include "WiiMoteInputController.h"
#include "Settings.h"
#include "Platform.h"

#include <QDebug>

WiiMoteInputController::WiiMoteInputController(QObject* parent) : QObject(parent), 
    wiimote(nullptr),
    blueToothConnector(nullptr)
{
}

void WiiMoteInputController::start()
{
    if (wiimote != nullptr)
    {
        delete wiimote;
        wiimote = nullptr;
    }
    
    findWiiMote();
}

void WiiMoteInputController::findWiiMote()
{
    if (!Platform::currentPlatform().isEmbedded())
    {
        // Currently, we only support finding the wiimote for RPI
        return;
    }

    if (wiimote != nullptr)
    {
        qDebug() << "Already found wii mote";
        return;
    }
    
    wiimote = WiiMote::find();
    
    if (wiimote == nullptr)
    {
        qDebug() << "Could not find wiimote. Starting search thread.";
        
        if (blueToothConnector == nullptr)
        {
            blueToothConnector = new WiiBluetoothConnector;
            blueToothConnector->moveToThread(&searchThread);
            
            searchTimer.setInterval(5000);
            searchTimer.setSingleShot(true);
            connect(&searchTimer, SIGNAL(timeout()), this, SLOT(doSearch()));
            connect(blueToothConnector, SIGNAL(connected()), this, SLOT(findWiiMote()));
            connect(blueToothConnector, SIGNAL(timeout()), this, SLOT(findWiiMote()));
            
            searchThread.start();
        }
        
        searchTimer.start();
        return;
    }
    
    wiimote->moveToThread(&loopthread);
    connect(wiimote, &WiiMote::released, this, &WiiMoteInputController::onReleased);
    connect(&loopthread, &QThread::started, wiimote, &WiiMote::loop);
    loopthread.start();
}

void WiiMoteInputController::onReleased(int code)
{
    switch (code)
    {
    case 304: //A Button
        Settings::lockExposure().toggle();
        break;
    case 305: // B Trigger
        Settings::sweep().toggle();
        break;
    case 316: // Home Button
        Settings::average().toggle();
        break;
    }
    
    // If we have a window, then these are already mapped to keypresses
    if (Settings::headless().value().toBool())
    {
        switch (code)
        {
        case 106: //right
            Settings::sweepSize().increment(3);
            break;
        case 105: //left
            Settings::sweepSize().decrement(3);
            break;
        case 103: // up
            Settings::averageSize().increment(3);
            break;
        case 108: // down
            Settings::averageSize().decrement(3);
            break;
        }
    }
}

void WiiMoteInputController::doSearch()
{
    if (wiimote == nullptr)
    {
        QMetaObject::invokeMethod(blueToothConnector, "connectToWii");
    }
}
