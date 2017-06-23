#include "mainwindow.h"
#include "mybutton.h"
#include "village.h"
#include "drawcard.h"
#include "globals.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include "handle1.cpp"
#include "clientnetworkinterface.h"
#include <QString>


int main(int argc, char *argv[])
{
    enum _identity{VILLAGER,WOLF,HUNTER,GUARD,WITCH,FORESEE};
    QApplication a(argc, argv);
    QSplashScreen ss(QPixmap(":new/prefix1/UI/main.jpg"));
    ss.show();
    a.processEvents();
    QThread::sleep(1);
    ss.showMessage("欢迎来到狼人杀的世界", Qt::AlignCenter, Qt::white);
    a.processEvents();
    QThread::sleep(1);

    ClientNetworkInterface *networkInterface = new ClientNetworkInterface();
    MainWindow *w = new MainWindow(networkInterface);
    networkInterface->setMainHandler(w);
    w->show();
    return a.exec();
}
