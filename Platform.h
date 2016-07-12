#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAndroid READ isAndroid NOTIFY started)
    Q_PROPERTY(bool isEmbedded READ isEmbedded NOTIFY started)
    Q_PROPERTY(bool isUnix READ isEmbedded NOTIFY started)
    Q_PROPERTY(bool isWindows READ isEmbedded NOTIFY started)
public:
    explicit Platform(QObject *parent = 0);
    
    bool isAndroid();
    bool isEmbedded();
    bool isUnix();
    bool isWindows();
    bool isDesktop();
    
signals:
    void started();
    
public slots:
};

#endif // PLATFORM_H
