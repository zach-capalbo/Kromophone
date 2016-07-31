#include "RemoteController.h"
#include "WebSocketServer.h"
#include "Logger.h"

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

    LOG_INFO() << msg;

    if (msg["type"] == "color")
    {
        emit colorChanged(msg["value"].value<QColor>());
    }
}

void RemoteController::onError(QAbstractSocket::SocketError error)
{
    LOG_INFO() << "SocketError: " << error;
}
