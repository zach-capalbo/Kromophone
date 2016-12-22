#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include <QWebSocket>
#include "Color.h"

class MessageProcessor : public QObject
{
    Q_OBJECT

    QVariantMap lastKnownSettings;
public:
    explicit MessageProcessor(QObject *parent = 0);

signals:
    void colorChanged(const Color& color);

public slots:

protected slots:
    void connectSignals(const QWebSocket* socket);
    void onTextMessageReceived(const QString& message);
    void onError(QAbstractSocket::SocketError error);
    void onSettingChanged(const QVariant& value);
    virtual void sendMessage(const QVariantMap &message) = 0;
};

#endif // MESSAGEPROCESSOR_H
