#include "chat.h"
#include "ui_chat.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

chat::chat(ClientNetworkInterface *_networkInterface, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chat),
    networkInterface(_networkInterface)
{
    ui->setupUi(this);
    ui->roomSend->setEnabled(false);
    ui->werewolfSend->setEnabled(false);
}

chat::~chat()
{
    delete ui;
}


void chat::on_werewolfSend_clicked()
{
    QString message;
    QString roomnumberchar=QString::number(Globals::roomnumber);
    message.append("wolfchat ");
    message.append(roomnumberchar);
    message.append("\n");
    message.append(ui->werewolfMessageEdit->text());
    message.append("@");
    message.append(Globals::meid);
    networkInterface->addString(message);
    qDebug()<<Globals::meid<<": "<<message<<endl;
    ui->werewolfMessageEdit->clear();
}

void chat::on_roomSend_clicked()
{
    QString message;
    QString roomnumberchar=QString::number(Globals::roomnumber);
    message.append("roomchat ");
    message.append(roomnumberchar);
    message.append("\n");
    message.append(ui->roomMessageEdit->text());
    message.append("@");
    message.append(Globals::meid);
    networkInterface->addString(message);
    emit roommessage();
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

void chat::addRoomChat(QString s, QString color)
{
    //QString temp = "<font color=\'" + color + "'>" + s + "</font>";
    //QString temp = "<font color='";
    //ui->roomMessage->addItem(tr(temp));
    //ui->roomMessage->addItem(tr(QString("<font color='") + color + QString("'>") + s + QString("</font>")));
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(s);
    item->setTextColor(QColor(color));
    ui->roomMessage->addItem(item);
    ui->roomMessage->setCurrentRow(ui->roomMessage->count() - 1);
}

void chat::addWerewolfChat(QString s, QString color)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(s);
    item->setTextColor(QColor(color));
    ui->werewolfMessage->addItem(item);
    ui->werewolfMessage->setCurrentRow(ui->werewolfMessage->count() - 1);
}
