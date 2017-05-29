#include "drawcard.h"
#include "ui_drawcard.h"
#include "globals.h"
#include <qapplication.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <QLabel>
#include "night.h"
#include "mainwindowplay.h"

drawcard::drawcard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawcard)
{
    ui->setupUi(this);
    ui->commandLinkButton->setVisible(false);
}

drawcard::~drawcard()
{
    delete ui;
}



void drawcard::on_pushButton_clicked()
{
    QPixmap pix;
    //获取身份牌信息
    //根据身份给id赋值
    switch(Globals::merole)
    {
    case 0://villager=0
    {
        this->setStyleSheet("background-image:url(:new/prefix1/UI/_villager.jpg)");
        ui->commandLinkButton->setVisible(true);
        break;
    }
    case 1://foresee=1
    {
        this->setStyleSheet("background-image:url(:new/prefix1/UI/_foresee.jpg)");
        ui->commandLinkButton->setVisible(true);
        break;
    }
    case 2://witch=2
    {
        this->setStyleSheet("background-image:url(:new/prefix1/UI/_witch.jpg)");
        ui->commandLinkButton->setVisible(true);
        break;
    }
    case 3://wolf=3
    {
        this->setStyleSheet("background-image:url(:new/prefix1/UI/_wolf.jpg)");
        ui->commandLinkButton->setVisible(true);
        break;
    }
    case 4://hunter=4
    {
        this->setStyleSheet("background-image:url(:new/prefix1/UI/_hunter.jpg)");
        ui->commandLinkButton->setVisible(true);
        break;
    }
    case 5://guard=5
    {
        this->setStyleSheet("background-image:url(:new/prefix1/UI/_guard.jpg)");
        ui->commandLinkButton->setVisible(true);
        break;
    }
    }

}

void drawcard::on_commandLinkButton_clicked()
{
    MainWindowplay *p=new MainWindowplay;
    this->close();
    p->show();
}
