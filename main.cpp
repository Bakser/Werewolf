#include "mainwindow.h"
#include "mybutton.h"
#include "village.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen ss(QPixmap("UI/main.jpg"));
    ss.show();
    a.processEvents();
    QThread::sleep(2);
    ss.showMessage("欢迎来到狼人杀的世界", Qt::AlignCenter, Qt::white);
    a.processEvents();
    QThread::sleep(3);

    MainWindow w;
    w.show();


    Village v;
    v.show();




    return a.exec();
}
