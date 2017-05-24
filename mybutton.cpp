#include "mybutton.h"
#include <QPainter>
#include <QMouseEvent>
MyButton::MyButton(QWidget *parent):QPushButton(parent)
{

}

MyButton::MyButton(QString& path, QString text, QWidget *parent):QPushButton(parent)
{
    Img=QPixmap(path);
    QSize sz=Img.size();
    setFixedSize(QSize(sz.height(),sz.width()/3));
    txt=text;
}


void MyButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int W=Img.width()/3;
    int H=Img.height();
    switch(m_status)
    {
    case NORMAL:
        break;
    case HOVER:
        painter.drawPixmap(rect(), Img,QRect(W,0,W,H));
        break;
    case PRESSED:
        painter.drawPixmap(rect(),Img,QRect(2*W, 0,W, H));
    }
    painter.drawPixmap(rect(),Img,QRect(0,0,W,H));
    painter.setFont(QFont("宋体",10));
    painter.setPen(Qt::white);
    painter.drawText(QRect(14,48,40,14),Qt::AlignCenter,txt);
}

void MyButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton && m_status==PRESSED)
    {
        m_status=HOVER;
        emit clicked();//change screen , into room
        update();
    }
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_status=PRESSED;
        update();
    }
}
