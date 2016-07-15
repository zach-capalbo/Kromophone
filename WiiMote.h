#ifndef WIIMOTE_H
#define WIIMOTE_H

#include <QObject>
#include <QThread>
#include <atomic>

class WiiMote : public QObject
{
    Q_OBJECT
public:
    WiiMote(const QString& device, QObject* parent = nullptr);
    ~WiiMote();
    
    static WiiMote* find();
    
signals:
    void pressed(int code);
    void released(int code);
    void error();
    
public slots:
    void loop();
    void quit();
    
private:
    int fd;
    bool valid;
    std::atomic<bool> shouldStop;
    QString name;
};

class WiiMoteInputController : public QObject
{
    Q_OBJECT
public:
    WiiMoteInputController(QObject* parent = nullptr);
    
public slots:
    void start();
    
    void onReleased(int code);
    
private:
    WiiMote* wiimote;
    QThread loopthread;
};

#endif // WIIMOTE_H
