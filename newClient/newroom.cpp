#include "newroom.h"
#include "ui_newroom.h"
#include "drawcard.h"
#include "waitroom.h"
#include <QDebug>

newroom::newroom(ClientNetworkInterface *_networkInterface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newroom),
    networkInterface(_networkInterface)
{
    ui->setupUi(this);
    ui->spinBox->setValue(3);
    ui->spinBox_3->setValue(3);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    bwitch = bhunter = bforesee = bguard = bpolice = false;
}

newroom::~newroom()
{
    delete ui;
}



void newroom::on_pushButton_clicked()
{
    int total=nvillager+nwolf+bwitch+bforesee+bhunter+bguard;
    //将新建房间信息传回服务器
    qDebug()<<"bulid "<<Globals::roomnumber<<" "<<total<<" "<<nwolf<<" "<<(int)bforesee<<" "<<(int)bwitch<<" "<<(int)bguard<<" "<<(int)bhunter<<" "<<(int)bpolice<<endl;
    networkInterface->addString("build " + QString::number(Globals::roomnumber) + "\n" + QString::number(total) + " "
                                + QString::number(nwolf) + " " + QString::number((int)bforesee) + " "
                                + QString::number((int)bwitch) + " " + QString::number((int)bguard) + " "
                                + QString::number((int)bhunter) + " " + QString::number((int)bpolice));
    this->close();
    //waitroom *dr=new waitroom;
    //this->close();
    //dr->show();
    //dr->exec();
}


void newroom::on_spinBox_3_valueChanged(int arg1)
{
    nwolf=arg1;
    //qDebug()<<nwolf<<" "<<bforesee<<" "<<bwitch<<" "<<bguard<<" "<<bhunter<<endl;
}

void newroom::on_spinBox_valueChanged(int arg1)
{
    nvillager=arg1;
    //qDebug()<<nwolf<<" "<<bforesee<<" "<<bwitch<<" "<<bguard<<" "<<bhunter<<endl;
}

void newroom::on_checkBox_clicked()
{
    bwitch=ui->checkBox->isChecked();
    //qDebug()<<nwolf<<" "<<bforesee<<" "<<bwitch<<" "<<bguard<<" "<<bhunter<<endl;
}

void newroom::on_checkBox_2_clicked()
{
    bhunter=ui->checkBox_2->isChecked();
    //qDebug()<<nwolf<<" "<<bforesee<<" "<<bwitch<<" "<<bguard<<" "<<bhunter<<endl;
}

void newroom::on_checkBox_4_clicked()
{
    bforesee=ui->checkBox_4->isChecked();
    //qDebug()<<nwolf<<" "<<bforesee<<" "<<bwitch<<" "<<bguard<<" "<<bhunter<<endl;
}

void newroom::on_checkBox_3_clicked()
{
    bguard=ui->checkBox_3->isChecked();
    //qDebug()<<nwolf<<" "<<bforesee<<" "<<bwitch<<" "<<bguard<<" "<<bhunter<<endl;
}



void newroom::on_checkBox_5_clicked()
{
    bpolice=ui->checkBox_5->isChecked();
}

void newroom::closeEvent(QCloseEvent *event)
{
    emit onclose();
    QDialog::closeEvent(event);
}
