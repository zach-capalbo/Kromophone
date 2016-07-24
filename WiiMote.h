#ifndef WIIMOTE_H
#define WIIMOTE_H

#include <QObject>
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
    QString device;
};



#endif // WIIMOTE_H
