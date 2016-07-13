#include "WiiMote.h"
#include "Settings.h"

#include <QThread>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

WiiMote::WiiMote(const QString& device, QObject* parent) : QObject(), valid(false), shouldStop(false)
{
}

void WiiMote::loop()
{
    int fd = open("/dev/input/event16", O_RDONLY);
    
    if (fd != -1)
    {
        valid = true;
        
        char rawname[256];
        ioctl (fd, EVIOCGNAME (sizeof (rawname)), rawname);
        
        name = QString::fromLatin1(rawname);        
    }
    
    if (!valid)
    {
        qDebug() << "Cannot start invalid wiimote";
        emit error();
        return;
    }
    
    struct input_event ev[64];
    const int size = sizeof(struct input_event);
    while (!shouldStop.load())
    {
        if (read (fd, ev, size * 64) < size)
        {
            qDebug() << "Error reading from input";
            emit error();
            return;
        }
        
        if (ev[0].value == 1)
        {
            emit pressed(ev[0].code);
        }
        else
        {
            emit released(ev[0].code);
        }
    }
}

void WiiMote::quit()
{
    shouldStop = true;
}

WiiMoteInputController::WiiMoteInputController(QObject* parent) : QObject(parent), wiimote(nullptr)
{
}

void WiiMoteInputController::start()
{
    wiimote = new WiiMote("/dev/input/event16");
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
        Settings::average().toggle();
        break;
    case 305: // B Trigger
        Settings::sweep().toggle();
        break;
    case 316: // Home Button
        Settings::autoExposure().toggle();
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
