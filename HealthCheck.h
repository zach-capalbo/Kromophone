#ifndef HEALTHCHECK_H
#define HEALTHCHECK_H

#include <QObject>

class HealthCheck : public QObject
{
    Q_OBJECT
public:
    explicit HealthCheck(QObject *parent = 0);

signals:

public slots:
    void timerEvent(QTimerEvent* event);
};

#endif // HEALTHCHECK_H
