#include "mainwindow.h"
#include "mybutton.h"
#include "village.h"
#include "drawcard.h"
#include "globals.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
//#include <clientnetworkinterface.h>


int main(int argc, char *argv[])
{
    enum _identity{VILLAGER,WOLF,HUNTER,GUARD,WITCH,FORESEE};
    //ClientNetworkInterface *clientNetworkInterface = new clientNetworkInterface();
    QApplication a(argc, argv);
    QSplashScreen ss(QPixmap("/Users/flyingturtle/Wolf_2/UI/main.jpg"));
    ss.show();
    a.processEvents();
    QThread::sleep(2);
    ss.showMessage("欢迎来到狼人杀的世界", Qt::AlignCenter, Qt::white);
    a.processEvents();
    QThread::sleep(3);

    MainWindow w;
    w.show();





    return a.exec();
}
