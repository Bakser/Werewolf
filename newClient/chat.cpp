#include "chat.h"
#include "ui_chat.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

chat::chat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
}

chat::~chat()
{
    delete ui;
}


void chat::on_werewolfSend_clicked()
{
    QString message;
    QString roomnumberchar=QString::number(Globals::roomnumber);
    message.append("roomchat ");
    message.append(roomnumberchar);
    message.append("\n");
    message.append(ui->werewolfMessageEdit->text());
    message.append("@");
    message.append(Globals::meid);
    //networkInterface->sendMessage(Globals::id, message);
    qDebug()<<Globals::meid<<": "<<message<<endl;
    ui->werewolfMessageEdit->clear();
}

void chat::on_roomSend_clicked()
{
    QString message;
    QString roomnumberchar=QString::number(Globals::roomnumber);
    message.append("wolfchat ");
    message.append(roomnumberchar);
    message.append("\n");
    message.append(ui->roomMessageEdit->text());
    message.append("@");
    message.append(Globals::meid);
    //networkInterface->sendMessage(Globals::id, message);
    qDebug()<<Globals::meid<<": "<<message<<endl;
    ui->roomMessageEdit->clear();
}

void chat::setRoomEnabled(bool f)
{
    ui->roomSend->setEnabled(f);
}

void chat::setWerewolfEnabled(bool f)
{
    ui->werewolfSend->setEnabled(f);
}
