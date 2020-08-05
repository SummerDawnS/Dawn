#include <QCoreApplication>
#include "qdbus_service.h"

void client_func();
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    class qdbus_service lService;
    //lService.init_qdbus_method();
    lService.init_qdbus_signal();

    std::thread lThread(service_listen);
    lThread.detach();
    return a.exec();
}

void client_func()
{

}
