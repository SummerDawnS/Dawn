#include <QCoreApplication>
#include "qdbus_client.h"

void method_func();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Qdbus_client client;
    client.InitDbusSignal();

    std::thread lThread(client_listen);
    lThread.detach();

//    std::thread lThread(method_func);
//    lThread.detach();
    return a.exec();
}

void method_func()
{
    Qdbus_client client;
    client.InitDbusMethod();
    if(!QDBusConnection::sessionBus().isConnected())
    {
        qDebug() << QString("cannot connect to the bus daemon");
    }
    //client.createDbusMethod();
    //client.createInterface();
    client.createMethodEx();
    //client.createInterfaceEx();
}
