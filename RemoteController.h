#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

#include <QObject>
#include <QWebSocket>
#include "MessageProcessor.h"

class RemoteController : public MessageProcessor
{
    Q_OBJECT

public:
    explicit RemoteController(QObject *parent = 0);

public slots:
    void connectTo(const QString& address);

protected slots:
    void sendMessage(const QVariantMap &message);
private:
    QWebSocket* socket;
};

#endif // REMOTECONTROLLER_H
