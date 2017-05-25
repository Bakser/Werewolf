#include "master.h"
#include "ui_master.h"
#include "newroom.h"
#include "joinroom.h"

master::master(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::master)
{
    ui->setupUi(this);
}

master::~master()
{
    delete ui;
}

void master::on_pushButton_clicked()
{
    newroom *roomview=new newroom;
    this->close();
    roomview->show();
    roomview->exec();
    this->show();
}

void master::on_pushButton_2_clicked()
{
    joinroom * join=new joinroom;
    this->close();
    join->show();
    join->exec();
}
