#include "RemoteController.h"
#include "WebSocketServer.h"
#include "Logger.h"
#include "Kromophone.h"
#include "Settings.h"

#include <QJsonDocument>
#include <QColor>

RemoteController::RemoteController(QObject *parent)
    : QObject(parent),
      socket(nullptr)
{
}

void RemoteController::connectTo(const QString &address)
{
    if (socket != nullptr)
    {
        socket->deleteLater();
    }

    socket = new QWebSocket(QStringLiteral("Kromophone"));
    connect(socket, &QWebSocket::textMessageReceived, this, &RemoteController::onTextMessageReceived);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    QUrl url;
    url.setScheme("ws");
    url.setHost(address);
    url.setPort(WebSocketServer::Port);
    url.setPath("/");
    LOG_INFO() << "Connecting to: " << url;
    socket->open(url);
}

void RemoteController::onTextMessageReceived(const QString &message)
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
            SettingsCreator::get(it.key()).set(it.value());
        }
    }
}

void RemoteController::onError(QAbstractSocket::SocketError error)
{
    LOG_ERROR() << "SocketError: " << error;
}

void RemoteController::onSettingChanged(const QVariant &value)
{

}
