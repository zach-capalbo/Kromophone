#include "WebSocketServer.h"
#include "Kromophone.h"
#include "Settings.h"
#include <QWebSocket>
#include <QDebug>
#include <QJsonDocument>

WebSocketServer::WebSocketServer(QObject *parent)
    : QObject(parent),
      server(nullptr)
{
    server = new QWebSocketServer(QStringLiteral("Kromophone"), QWebSocketServer::NonSecureMode);

    if (server->listen(QHostAddress::Any, WebSocketServer::Port))
    {
        connect(server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
        connect(server, &QWebSocketServer::closed, this, &WebSocketServer::onConnectionClosed);
    }
    else
    {
        qWarning() << "Could not start websocket server";
    }

    Kromophone* app = qobject_cast<Kromophone*>(parent);

    if (app != nullptr)
    {
        connect(app, &Kromophone::colorChanged, this, &WebSocketServer::onColorChanged);
    }

    foreach (Setting* setting, SettingsCreator::settingsList())
    {
        connect(setting, &Setting::valueChanged, this, &WebSocketServer::onSettingChanged);
    }
}

void WebSocketServer::processTextMessage(const QString &message)
{
    qDebug() << "Msg: " << message;
}

void WebSocketServer::processBinaryMessage(const QByteArray &message)
{
    qDebug() << "BMsg: " << message.toHex();
}

void WebSocketServer::onNewConnection()
{
    QWebSocket* socket = server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    clients << socket;
}

void WebSocketServer::onConnectionClosed()
{
    QWebSocket* socket = qobject_cast<QWebSocket*>(sender());

    clients.removeAll(socket);
    socket->deleteLater();
}

void WebSocketServer::onColorChanged(const QColor &color)
{
    QVariantMap msg {
      {"type", "color"},
      {"value", color}
    };

    broadcast(msg);
}

void WebSocketServer::onSettingChanged(const QVariant &value)
{
    Setting* setting = qobject_cast<Setting*>(sender());

    QVariantMap msg {
        {"type", "setting"},
        {"name", setting->name()},
        {"value", value}
    };

    broadcast(msg);
}

void WebSocketServer::broadcast(const QVariantMap &msg)
{
    QByteArray json = QJsonDocument::fromVariant(msg).toJson();
    foreach (QWebSocket* client, clients)
    {
        client->sendTextMessage(json);
    }
}

