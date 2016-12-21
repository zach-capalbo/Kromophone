#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

#include <QObject>
#include <QWebSocket>
#include <QColor>

class RemoteController : public QObject
{
    Q_OBJECT
public:
    explicit RemoteController(QObject *parent = 0);

signals:
    void colorChanged(QColor color);

public slots:
    void connectTo(const QString& address);

protected slots:
    void onTextMessageReceived(const QString& message);
    void onError(QAbstractSocket::SocketError error);
    void onSettingChanged(const QVariant& value);

private:
    QWebSocket* socket;
};

#endif // REMOTECONTROLLER_H