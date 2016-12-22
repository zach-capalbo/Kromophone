#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include "MessageProcessor.h"
#include "Color.h"

class WebSocketServer : public MessageProcessor
{
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = 0);
    static const int Port = 7982;

signals:

public slots:

protected slots:
    void onNewConnection();
    void onConnectionClosed();
    void onColorChanged(const QColor &color);

protected:
    void sendMessage(const QVariantMap& msg);
    void sendSettings(QWebSocket* client);

private:
    QWebSocketServer* server;
    QList<QWebSocket*> clients;
};

#endif // WEBSOCKETSERVER_H
