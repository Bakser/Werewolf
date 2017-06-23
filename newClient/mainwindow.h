#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globals.h"
#include "clientnetworkinterface.h"
#include "eventhandler.h"
#include "joinroom.h"

//主游戏界面设计
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public EventHandler
{
    Q_OBJECT

public:
    explicit MainWindow(ClientNetworkInterface *networkInterface, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void handle(QString);
    bool canHandle(QString);
    EventHandler* selectHandler(QString);
    joinroom *mast;
};

#endif // MAINWINDOW_H
