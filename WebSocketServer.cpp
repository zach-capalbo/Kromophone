#include "WebSocketServer.h"
#include "Kromophone.h"
#include "Settings.h"
#include "Logger.h"
#include "Settings.h"
#include <QWebSocket>
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

void WebSocketServer::processTextMessage(const QString &message)
{
    QJsonDocument json = QJsonDocument::fromJson(message.toUtf8());
    QVariantMap msg = json.toVariant().toMap();

    LOG_TRACE() << msg;

    if (msg["type"] == "color")
    {
        Color color(msg["value"].value<QColor>());

        Kromophone* app = qobject_cast<Kromophone*>(parent());
        app->onColorChanged(color);
    }
    else if (msg["type"] == "settings")
    {
        QVariantMap settings = msg["settings"].toMap();

        for (auto it = settings.cbegin(); it != settings.cend(); ++it)
        {
            LOG_INFO() << it.key() << it.value();
            lastKnownSettings[it.key()] = it.value();
            SettingsCreator::get(it.key()).set(it.value());
        }
    }
}

void WebSocketServer::processBinaryMessage(const QByteArray &message)
{
    LOG_TRACE() << "BMsg: " << message.toHex();
}

void WebSocketServer::onNewConnection()
{
    QWebSocket* socket = server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
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

    broadcast(msg);
}

void WebSocketServer::onSettingChanged(const QVariant &value)
{
    Setting* setting = qobject_cast<Setting*>(sender());

    if (lastKnownSettings[setting->name()] != value)
    {
        QVariantMap msg {
            {"type", "settings"},
            {"settings", QVariantMap{
                {setting->name(), value}
            }}
        };

        broadcast(msg);
    }
}

void WebSocketServer::broadcast(const QVariantMap &msg)
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
