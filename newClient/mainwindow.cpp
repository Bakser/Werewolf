#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "joinroom.h"
#include <QDebug>

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
    Globals::id=ui->lineEdit->text().toInt();
    joinroom *mast=new joinroom;
    this->close();
    mast->show();
    mast->exec();
}
