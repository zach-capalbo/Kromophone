#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include "Color.h"

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = 0);
    static const int Port = 7982;

signals:

public slots:
    virtual void processTextMessage(const QString& message);
    virtual void processBinaryMessage(const QByteArray& message);

protected slots:
    void onNewConnection();
    void onConnectionClosed();
    void onColorChanged(const QColor &color);
    void onSettingChanged(const QVariant& value);

protected:
    void broadcast(const QVariantMap& msg);

private:
    QWebSocketServer* server;
    QList<QWebSocket*> clients;
};

#endif // WEBSOCKETSERVER_H
