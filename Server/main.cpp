#include "maindialog.h"
#include <QApplication>
#include "naivehandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    w.show();

    NaiveHandler *naiveHandler = new NaiveHandler();
    ServerNetworkInterface *networkInterface = new ServerNetworkInterface(naiveHandler);
    naiveHandler->setNetworkInterface(networkInterface);

    return a.exec();
}
