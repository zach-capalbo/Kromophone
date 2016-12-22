#include "MessageProcessor.h"
#include "Settings.h"
#include "Logger.h"
#include "Color.h"

#include <QJsonDocument>
#include <QColor>

MessageProcessor::MessageProcessor(QObject *parent) : QObject(parent)
{
    foreach (Setting* setting, SettingsCreator::settingsList())
    {
        connect(setting, &Setting::valueChanged, this, &MessageProcessor::onSettingChanged);
    }
}

void MessageProcessor::connectSignals(const QWebSocket *socket)
{
    connect(socket, &QWebSocket::textMessageReceived, this, &MessageProcessor::onTextMessageReceived);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

void MessageProcessor::onTextMessageReceived(const QString &message)
{
    QJsonDocument json = QJsonDocument::fromJson(message.toUtf8());
    QVariantMap msg = json.toVariant().toMap();

    LOG_TRACE() << msg;

    if (msg["type"] == "color")
    {
        Color color(msg["value"].value<QColor>());

        colorChanged(color);
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

void MessageProcessor::onError(QAbstractSocket::SocketError error)
{
    LOG_ERROR() << "SocketError: " << error;
}

void MessageProcessor::onSettingChanged(const QVariant &value)
{
    Setting* setting = qobject_cast<Setting*>(sender());
    q_check_ptr(setting);

    if (value != lastKnownSettings[setting->name()])
    {
        lastKnownSettings[setting->name()] = value;

        QVariantMap msg {
            {"type", "settings"},
            {"settings", QVariantMap{
                {setting->name(), value}
            }}
        };

        sendMessage(msg);
    }
}
