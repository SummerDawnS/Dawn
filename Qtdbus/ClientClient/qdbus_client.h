#ifndef QDBUS_CLIENT_H
#define QDBUS_CLIENT_H
#include <QObject>
#include <QCoreApplication>
#include <QtDBus/QtDBus>
#include <QDebug>
#include <thread>
#include <unistd.h>

class Qdbus_client:public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface","org.lfs.test")
public:
    Qdbus_client();
    void InitDbusSignal();
    void InitDbusMethod();
    void createDbusMethod();
    void createInterface();
    void createMethodEx();
    void createInterfaceEx();
public slots:
    void Client_get(QString str);
signals:
    void send_to_service(QString st);
};

void client_listen(void);

#endif // QDBUS_CLIENT_H
