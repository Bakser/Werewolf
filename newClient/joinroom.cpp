#include "joinroom.h"
#include "ui_joinroom.h"
#include "newroom.h"
#include "drawcard.h"
#include "waitroom.h"
#include "globals.h"
#include <QDebug>

joinroom::joinroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::joinroom)
{
    ui->setupUi(this);
    ui->label_2->setVisible(false);

}

joinroom::~joinroom()
{
    delete ui;
}

void joinroom::on_pushButton_clicked()
{
    Globals::roomnumber=ui->lineEdit->text().toInt();// toInt();
    qDebug()<<"want to join roomnumber:"<<Globals::roomnumber<<endl;
    //join roomnumber
    //以下测试用，正式版需要删掉
    if(1)//(receive)owner
    {
        newroom *r=new newroom;
        this->close();
        r->show();
        r->exec();
    }
    else if(0)//(receive)full
    {
        ui->label_2->setVisible(true);
    }
    else if(0)//(receive)success
    {
        waitroom *dr=new waitroom;
        this->close();
        dr->show();
        dr->exec();
    }
}

void joinroom::owner()
{
    newroom *r=new newroom;
    this->close();
    r->show();
    r->exec();
}

void joinroom::full()
{
    ui->label_2->setVisible(true);
}

void joinroom::success()
{
    waitroom *dr=new waitroom;
    this->close();
    dr->show();
    dr->exec();
}
