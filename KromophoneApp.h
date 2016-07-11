#ifndef KROMOPHONEAPP_H
#define KROMOPHONEAPP_H

#include <QObject>

class KromophoneApp : public QObject
{
    Q_OBJECT
public:
    explicit KromophoneApp(QObject *parent = 0);
    
signals:
    
public slots:
};

#endif // KROMOPHONEAPP_H