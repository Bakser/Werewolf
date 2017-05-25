#include "village.h"
#include <QPainter>
#include <QMouseEvent>
#include <QString>
#include <QMessageBox>

int mytable=-1; //-1 表示 “我” 不在那一桌


Village::Village(QWidget *parent):QWidget(parent)
{

}

Village::Village(int id, int number, QWidget *parent):QWidget(parent)
{
    image=QPixmap("/UI/icon.jpg");
    resize(image.width(),image.height());
    numberofjoin=number;
    tabID=id;
    this->setMouseTracking(true);
    bewaited=0;
}

void Village::PaintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,image);
    int texX[2]={23,79};
    int texY[2]={16,142};
    QString tableID=QString::number(tabID);
    painter.setFont(QFont("Arial",10,QFont::Bold));
    painter.drawText(QRect(67,67,24,17),Qt::AlignCenter,tableID);
    painter.setFont(QFont("宋体",10));
}

void Village::mousePressEvent(QMouseEvent * event)
{
    if(bewaited=0)
    {
        numberofjoin++;
        emit changeSeatTo(mytable);//发信号，坐到新位置
    }
    update();
}



