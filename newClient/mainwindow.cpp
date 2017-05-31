#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
MainWindow::MainWindow(ClientNetworkInterface *_networkInterface, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    EventHandler(_networkInterface)
{
    ui->setupUi(this);
    setWindowTitle("Login");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Globals::meid=ui->lineEdit->text();
    //joinroom *mast=new joinroom;
    //this->close();
    //this->hide();
    //mast->show();
    //mast->exec();
    networkInterface->startLogin(Globals::meid);
}

void MainWindow::handle(QString s)
{
    qDebug() << "MainWindow received " << s;
    mast = new joinroom(networkInterface);
    mast->setWindowTitle("Select Room");
    this->hide();
    mast->show();
    //mast->exec();
}

bool MainWindow::canHandle(QString s)
{
    qDebug() << "can MainWindow handle?";
    if (s == "login ok")
        return true;
    else
        return false;
}

EventHandler* MainWindow::selectHandler(QString s)
{
    return mast;
}
