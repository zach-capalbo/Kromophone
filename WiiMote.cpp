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

#include <QDir>

WiiMote::WiiMote(const QString& device, QObject* parent) : QObject(parent), valid(false), shouldStop(false), fd(-1), device(device)
{
}

WiiMote::~WiiMote()
{
    if (fd != -1)
    {
        close(fd);
    }
}

WiiMote* WiiMote::find()
{
    QDir dir("/dev/input");
    
    foreach(const QString& entry, dir.entryList(QStringList {"event*"}, QDir::System | QDir::AllEntries | QDir::Hidden))
    {
        int fd = open(QString("/dev/input/%1").arg(entry).toLocal8Bit(), O_RDONLY);
        
        if (fd == -1)
        {
            int err = errno;
            qDebug() << "Could not open " << entry << " becase " << err << strerror(err);
            continue;
        }
        
        char rawname[256];
        ioctl (fd, EVIOCGNAME (sizeof (rawname)), rawname);
        
        QString name = QString::fromLatin1(rawname);
        
        if (name != "Nintendo Wii Remote")
        {
            continue;
        }
        
        close(fd);
        
        return new WiiMote(QString("/dev/input/%1").arg(entry));
    }
    
    return nullptr;
}

void WiiMote::loop()
{
    int fd = open(device.toLocal8Bit(), O_RDONLY);
    
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
            int err = errno;
            qDebug() << "Error reading from input" << err << strerror(err);
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
