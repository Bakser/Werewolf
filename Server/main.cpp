#include "maindialog.h"
#include <QApplication>
#include "naivehandler.h"
#include "RoomHandler.h"
#include "ServerCenter.h"
#include "Game.h"
#include "Gamestatus.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    w.show();

    EventHandler *servercenter = new ServerCenter();
    ServerNetworkInterface *networkInterface = new ServerNetworkInterface(servercenter);
    servercenter->setNetworkInterface(networkInterface);

    return a.exec();
}
