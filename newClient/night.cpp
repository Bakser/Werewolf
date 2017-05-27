#include "night.h"
#include "ui_night.h"
#include "globals.h"
#include <QThread>

night::night(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::night)
{
    ui->setupUi(this);
    this->setStyleSheet("background-image:url(/Users/flyingturtle/Wolf_2/UI/background.jpeg)");
}

night::~night()
{
    delete ui;
}

void night::operate()
{
    QThread::sleep(3);
    if(1)//接收到信号进入相应身份环节
    {
        int idk=3;
        switch(idk)
        {
            case 0://villager
            {
                break;
            }
            case 1://foresee
            {
                break;
            }
            case 2://witch
            {
                break;
            }
            case 3://wolf
            {
                break;
            }
            case 4://hunter
            {
                break;
            }
            case 5://guard
            {
                break;
            }
        }
    }
}
