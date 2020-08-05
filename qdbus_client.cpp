#include "qdbus_client.h"


Qdbus_client::Qdbus_client()
{

}

void Qdbus_client::InitDbusSignal()
{
    QDBusConnection::sessionBus().unregisterService("org.lfs.manager");
    QDBusConnection::sessionBus().registerService("org.lfs.manager");
    QDBusConnection::sessionBus().registerObject("/opt/lfs",this,QDBusConnection::ExportAllSlots|QDBusConnection::ExportAllSignals);
    QDBusConnection::sessionBus().connect(QString(),QString("/opt/lfs"),"org.lfs.manager", "send_to_client",this,SLOT(Client_get(QString)));
}

void Qdbus_client::Client_get(QString str)
{
    qDebug() << "Client Get!" <<str;
}

void client_listen()
{
    while(true)
    {
        getchar();
        qDebug() << "client Message Send!";
        QDBusMessage message = QDBusMessage::createSignal(QString("/opt/lfs"),QString("org.lfs.manager"),QString("send_to_service"));
        message << "this is client to you了";
        QDBusConnection::sessionBus().send(message);
    }
}

void Qdbus_client::InitDbusMethod()
{
    QDBusConnection::sessionBus().unregisterService("org.lfs.managerM");
    QDBusConnection::sessionBus().registerService("org.lfs.managerM");
    QDBusConnection::sessionBus().registerObject("/opt/lfs",this);
}


void Qdbus_client::createDbusMethod()
{

    while(true)
    {
        qDebug() << "start to create method call";
        QDBusMessage msg = QDBusMessage::createMethodCall("org.lfs.managerM","/opt/lfs","org.lfs.test","event_callback");

        QString strTime = QDateTime::currentDateTime().toString("hh:MM:ss");
        strTime.append(QString("this is Client send to you"));
        msg << strTime;
        QDBusMessage response = QDBusConnection::sessionBus().call(msg);
        if(response.type() == QDBusMessage::ReplyMessage)
        {
            qDebug()<< response.arguments().takeFirst().toString();
        }
        else
            qDebug()<< "the resposne is else" << response.arguments().takeFirst().toString();
        getchar();
    }
}

void Qdbus_client::createInterface()
{
    while (true)
    {
        qDebug() << "start to create interface call";
        QDBusInterface iface("org.lfs.managerM","/opt/lfs","org.lfs.test",QDBusConnection::sessionBus());
        if(iface.isValid())
        {
            QString str = "this is Interface call";
            QDBusReply<QString> reply = iface.call("event_callback",str);
            if(reply.isValid())
            {
                qDebug() << "Revevied the reply"<<reply.value();
            }
            else
                qDebug() << QString("Interface Call failed");
        }
        else
            qDebug() << "the iterface create failed "<< qPrintable(QDBusConnection::sessionBus().lastError().message());
        getchar();
    }
}


void Qdbus_client::createMethodEx()
{

    while(true)
    {
        qDebug() << "start to create method call";
        QDBusMessage msg = QDBusMessage::createMethodCall("org.lfs.managerM","/opt/lfs","org.lfs.test","event_callbackEx");

        QString strTime = QDateTime::currentDateTime().toString("hh:MM:ss");
        strTime.append(QString("this is Client send to you"));
        msg << 12345 << 321;
        QDBusPendingCall response = QDBusConnection::sessionBus().asyncCall(msg,100);
//        if(response.type() == QDBusMessage::ReplyMessage)
//        {
//            qDebug()<< "the method call reply"<<response.arguments().takeFirst().toInt();
//        }
//        else
//            qDebug()<< "the resposne is else" << response.arguments().takeFirst().toString();

        //response.waitForFinished();
        for(int i = 0; i < 99;i++)
        {
            QString strTime = QDateTime::currentDateTime().toString("hh:MM:ss");
            strTime.append(QString("wait for finished"));
            qDebug() << strTime << response.isFinished();
            if(response.isFinished())
                break;
            sleep(1);
        }
        qDebug() << "async call is end";
        getchar();
    }
}

void Qdbus_client::createInterfaceEx()
{
    while (true)
    {
        qDebug() << "start to create interfaceEx call";
        QDBusInterface iface("org.lfs.managerM","/opt/lfs","org.lfs.test",QDBusConnection::sessionBus());
        if(iface.isValid())
        {
            QString str = "this is InterfaceEx call";
            QList<QVariant> LVarlist;
            LVarlist.push_back(111);
            LVarlist.push_back(222);
            QDBusReply<int> reply = iface.asyncCallWithArgumentList("event_callbackEx",LVarlist);
            if(reply.isValid())
            {
                qDebug() << "Revevied the Ex reply"<<reply.value();
            }
            else
                qDebug() << QString("InterfaceEx Call failed");
        }
        else
            qDebug() << "the iterfaceEx create failed "<< qPrintable(QDBusConnection::sessionBus().lastError().message());
        getchar();
    }
}
