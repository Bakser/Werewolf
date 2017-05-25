#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "master.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //传递id给服务器
    master *mast=new master;
    this->close();
    mast->show();
    mast->exec();
}
