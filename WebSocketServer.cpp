#include "WebSocketServer.h"
#include "Kromophone.h"
#include "Settings.h"
#include "Logger.h"
#include "Settings.h"
#include <QWebSocket>
#include <QJsonDocument>

WebSocketServer::WebSocketServer(QObject *parent)
    : MessageProcessor(parent),
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
        LOG_WARNING() << "Could not start websocket server";
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


void WebSocketServer::onNewConnection()
{
    QWebSocket* socket = server->nextPendingConnection();

    connectSignals(socket);
    clients << socket;

    sendSettings(socket);
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

    sendMessage(msg);
}

void WebSocketServer::sendMessage(const QVariantMap &msg)
{
    QByteArray json = QJsonDocument::fromVariant(msg).toJson();
    foreach (QWebSocket* client, clients)
    {
        client->sendTextMessage(json);
    }
}

void WebSocketServer::sendSettings(QWebSocket *client)
{
    QVariantMap settings;
    foreach (auto setting, SettingsCreator::displayedSettings())
    {
        settings[setting] = SettingsCreator::get(setting).value();
    }

    QVariantMap msg {
        {"type", "settings"},
        {"settings", settings}
    };

    QByteArray json = QJsonDocument::fromVariant(msg).toJson();
    client->sendTextMessage(json);
}
