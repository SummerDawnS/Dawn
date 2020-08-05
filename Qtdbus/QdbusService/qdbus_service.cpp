#include "qdbus_service.h"

qdbus_service::qdbus_service(QObject *parent) : QObject(parent)
{


}

void qdbus_service::init_qdbus_signal()
{
    QDBusConnection::sessionBus().unregisterService("org.lfs.manager");
    QDBusConnection::sessionBus().registerService("org.lfs.manager");
    QDBusConnection::sessionBus().registerObject("/opt/lfs",this,QDBusConnection::ExportAllSlots|QDBusConnection::ExportAllSignals);
    QDBusConnection::sessionBus().connect(QString(),QString("/opt/lfs"),"org.lfs.manager","send_to_service",this,SLOT(service_get(QSting)));
}

void qdbus_service::init_qdbus_method()
{
    QDBusConnection::sessionBus().unregisterService("org.lfs.managerM");
    QDBusConnection::sessionBus().registerService("org.lfs.managerM");
    QDBusConnection::sessionBus().registerObject("/opt/lfs",this,QDBusConnection::ExportAllSlots);
}

QString qdbus_service::event_callback(QString str)
{
    qDebug() << "qdbus Service is received message "<<str;
    return QString("the qdbus Service return to you");
}

int qdbus_service::event_callbackEx(int EventID,int unPtr_char)
{
    for(int i = 0; i< 10; i++)
    {
        QDateTime ltime = QDateTime::currentDateTime();
        QString strinfo = ltime.toString("hh:MM:ss");
        qDebug() << strinfo << "Running...";
        sleep(rand()%3);
    }
    qDebug() << "qdbus Service is Received message Ex "<<EventID <<"pointer"<<unPtr_char;
    return 9999;
}

QString qdbus_service::service_get(QString str)
{
    qDebug() << "Service Message get from client" << str;
    return "Service message is send by service";
}

void service_listen()
{
    while (true) {
        getchar();
        qDebug()<<"Service Message send!";
        QDBusMessage message = QDBusMessage::createSignal("/opt/lfs","org.lfs.manager","send_to_client");
        message << "this is Service send to you";
        QDBusConnection::sessionBus().send(message);
    }

}
