#ifndef QDBUS_SERVICE_H
#define QDBUS_SERVICE_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QDebug>
#include <thread>
#include <unistd.h>

class qdbus_service : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface","org.lfs.test")
public:
    explicit qdbus_service(QObject *parent = nullptr);

    void init_qdbus_signal();
    void init_qdbus_method();

public slots:
    QString service_get(QString str);
    QString event_callback(QString str);
    int event_callbackEx(int EventID,int unPtr_char);

signals:
    void send_to_service(QString str);
};

void service_listen();

#endif // QDBUS_SERVICE_H
