#include "joinroom.h"
#include "ui_joinroom.h"
#include "drawcard.h"
#include "globals.h"
#include <QDebug>

joinroom::joinroom(ClientNetworkInterface *_networkInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::joinroom),
    EventHandler(_networkInterface)
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
    networkInterface->addString("join " + QString::number(Globals::roomnumber));
    /*
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
    */
}

void joinroom::owner()
{
    qDebug() << "joinroom::owner()";
    newroom *r=new newroom(networkInterface);
    this->hide();
    r->show();
    //r->exec();
    dr = new waitroom(networkInterface);
    connect(r, SIGNAL(onclose()), dr, SLOT(show()));
    //dr->show();
    connect(dr, SIGNAL(onclose()), this, SLOT(show()));
    //dr->exec();
}

void joinroom::full()
{
    ui->label_2->setVisible(true);
}

void joinroom::success()
{
    dr=new waitroom(networkInterface);
    this->hide();
    dr->show();
    connect(dr, SIGNAL(onclose()), this, SLOT(show()));
    //dr->exec();
}

bool joinroom::canHandle(QString s)
{
    qDebug() << "can joinroom handle?";
    return s == "Success" || s == "Full" || s == "Owner";
}

void joinroom::handle(QString s)
{
    qDebug() << "joinroom received " << s;
    if (s == "Success")
        success();
    else if (s == "Full")
        full();
    else
        owner();
}

EventHandler* joinroom::selectHandler(QString s)
{
    return dr;
}
