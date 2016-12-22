#include "RemoteController.h"
#include "WebSocketServer.h"
#include "Logger.h"
#include "Kromophone.h"
#include "Settings.h"

#include <QJsonDocument>
#include <QColor>

RemoteController::RemoteController(QObject *parent)
    : MessageProcessor(parent),
      socket(nullptr)
{
    Kromophone* app = qobject_cast<Kromophone*>(parent);
    connect(this, SIGNAL(colorChanged(Color)), app, SLOT(onColorChanged(Color)));
}

void RemoteController::connectTo(const QString &address)
{
    if (socket != nullptr)
    {
        socket->deleteLater();
    }

    socket = new QWebSocket(QStringLiteral("Kromophone"), QWebSocketProtocol::VersionLatest, this);
    connectSignals(socket);

    QUrl url;
    url.setScheme("ws");
    url.setHost(address);
    url.setPort(WebSocketServer::Port);
    url.setPath("/");
    LOG_INFO() << "Connecting to: " << url;
    socket->open(url);
}

void RemoteController::sendMessage(const QVariantMap& message)
{
    QByteArray json = QJsonDocument::fromVariant(message).toJson();
    socket->sendTextMessage(json);
}
