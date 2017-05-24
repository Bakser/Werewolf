#include "drawcard.h"
#include "ui_drawcard.h"
#include <time.h>

drawcard::drawcard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawcard)
{
    ui->setupUi(this);
}

drawcard::~drawcard()
{
    delete ui;
}

void drawcard::on_pushButton_clicked()
{
    srand(unsigned(time(0)));
    int n=10;//此处需要传人数（几人局）
    bool seat[n];//从server传递
    int card=rand()/n;
    while(seat[card]==1)
    {
        card=card++;
        if(seat[card]==0)
        {

        }
    }
}

