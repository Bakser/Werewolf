#include "waitroom.h"
#include "ui_waitroom.h"
#include "joinroom.h"
#include "globals.h"
#include "drawcard.h"
#include <QDebug>
#include "stringoperate.h"

namespace
{
    int roomnumber;
}

waitroom::waitroom(ClientNetworkInterface *_networkInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitroom),
    EventHandler(_networkInterface)
{
    ui->setupUi(this);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    //正式版改成true
    ui->pushButton_3->setVisible(false);
    //ui->pushButton_3->setVisible(true);
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
    networkInterface->addString("up " + QString::number(Globals::roomnumber));
}

void waitroom::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(true);
    //down roomnumber;
    qDebug()<<"down roomnumber:"<<Globals::roomnumber;
    networkInterface->addString("down " + QString::number(Globals::roomnumber));
}

void waitroom::on_commandLinkButton_clicked()
{
    //leave roomnumber
    qDebug()<<"leave roomnumber:"<<Globals::roomnumber;
    networkInterface->addString("leave " + QString::number(Globals::roomnumber));
    //joinroom *j=new joinroom(networkInterface);
    this->close();
    //j->show();
    //j->exec();
}

void waitroom::on_pushButton_3_clicked()
{
    //信号槽接受0/1指令变换visible
    //start
    qDebug()<<"start "<<Globals::roomnumber<<endl;
    networkInterface->addString("start " + QString::number(Globals::roomnumber));
    /*
    drawcard *n=new drawcard;
    this->close();
    n->show();
    n->exec();
    */
}

void waitroom::start()
{
    ui->pushButton_3->setVisible(true);
}

bool waitroom::canHandle(QString s)
{
    qDebug() << "can waitroom handle?";
    if (s.mid(0, 8) == "OwnerNew")
        return true;
    if (s.mid(0, 11) == "StartButton")
        return true;
    if (s.mid(0, 11) == "Gamestarted")
        return true;
    if (s.mid(0, 6) == "Status")
    {
        qDebug() << "waitroom handle status";
        std::vector<QString> temp = split(s, "\n");
        for (auto p : temp)
            qDebug() << p;
        std::vector<QString> saver = split(temp[1], " ");
        for (auto p : saver)
            qDebug() << p;
        return saver.size() == 7;
    }
    return false;
}

void waitroom::handle(QString s)
{
    qDebug() << "waitroom received " << s;
    if (s.mid(0, 11) == "StartButton")
    {
        if (s[12] == '0')
            ui->pushButton_3->setVisible(false);
        else
            ui->pushButton_3->setVisible(true);
    }
    else if (s.mid(0, 8) == "OwnerNew")
    {
        //暂不处理
    }
    else if (s.mid(0, 11) == "Gamestarted")
    {
        qDebug() << "fuck GameStarted!";
        Globals::reset();
        p = new MainWindowplay(networkInterface);
        this->hide();
        p->show();
    }
    else if (s.mid(0, 6) == "Status")
    {
        ui->statusLabel->setText(s);
    }
}

EventHandler* waitroom::selectHandler(QString s)
{
    return p;
}

void waitroom::closeEvent(QCloseEvent *event)
{
    emit onclose();
    QDialog::closeEvent(event);
}
