#ifndef VILLAGE_H
#define VILLAGE_H


#include <QObject>
#include <QWidget>
#include <QPushButton>

class Village:public QWidget
{
    Q_OBJECT
public:
    explicit Village(QWidget *parent=0);
    Village(int id,int number, QWidget *parent=0);
    QPixmap image;
    int tabID;
    int numberofjoin;
    bool bewaited;
    QRect pplRect;
protected:
    void PaintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
signals:
    void changeSeatTo(int tabID);//发信号，坐到新位置
public slots:
};

#endif // VILLAGE_H
