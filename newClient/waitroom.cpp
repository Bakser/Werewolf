#include "waitroom.h"
#include "ui_waitroom.h"
#include "joinroom.h"
#include "globals.h"
#include "drawcard.h"
#include <QDebug>

namespace
{
    int roomnumber;
}

waitroom::waitroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitroom)
{
    ui->setupUi(this);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
}

waitroom::~waitroom()
{
    delete ui;
}

void waitroom::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(false);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(false);
    //up roomnumber;
    qDebug()<<"up roomnumber:"<<Globals::roomnumber;
}

void waitroom::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(true);
    //down roomnumber;
    qDebug()<<"down roomnumber:"<<Globals::roomnumber;
}

void waitroom::on_commandLinkButton_clicked()
{
    //leave roomnumber
    qDebug()<<"leave roomnumber:"<<Globals::roomnumber;
    joinroom *j=new joinroom;
    this->close();
    j->show();
    j->exec();
}

void waitroom::on_pushButton_3_clicked()
{
    //信号槽接受0/1指令变换visible
    //start
    qDebug()<<"start "<<Globals::roomnumber<<endl;
    drawcard *n=new drawcard;
    this->close();
    n->show();
    n->exec();
}
