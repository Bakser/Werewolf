#include "night.h"
#include "ui_night.h"
#include "globals.h"
#include <QThread>
#include <QObject>
#include <QPixmap>
#include <QLabel>

night::night(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::night)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/background.jpeg"));
    ui->label->setScaledContents(true);
    //ui->label->resize(ui->mainwindow->size());
}

night::~night()
{
    delete ui;
}


void night::setNight(int day)
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/background.jpeg"));
    ui->label->setScaledContents(true);

}

void night::setDay(int day)
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/day.jpg"));
    ui->label->setScaledContents(true);
}

void night::setGuard()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/_guard.jpg"));
    ui->label->setScaledContents(true);
}

void night::setWitch()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/_witch.jpg"));
    ui->label->setScaledContents(true);
}

void night::setFore()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/_foresee.jpg"));
    ui->label->setScaledContents(true);
}

void night::setCap()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/_sheriff.jpg"));
    ui->label->setScaledContents(true);
}

void night::setLose()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/lose.jpg"));
    ui->label->setScaledContents(true);
}

void night::setWin()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/win.jpg"));
    ui->label->setScaledContents(true);
}

void night::setCapPass()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/_sheriff.jpg"));
    //ui->label->setScaledContents(true);
}

void night::setHunter()
{
    ui->label->setPixmap(QPixmap(":new/prefix1/UI/_hunter.jpg"));
    ui->label->setScaledContents(true);
}
