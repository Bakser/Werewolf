#ifndef JOINROOM_H
#define JOINROOM_H

#include <QDialog>
#include "globals.h"
#include "eventhandler.h"
#include "waitroom.h"
#include "newroom.h"

//等待房间的界面设计
namespace Ui {
class joinroom;
}

class joinroom : public QDialog, public EventHandler
{
    Q_OBJECT

public:
    explicit joinroom(ClientNetworkInterface*, QWidget *parent = 0);
    ~joinroom();

private slots:
    void on_pushButton_clicked();//点击按钮
    void success();//成功加入房间
    void full();//房间已经满了
    void owner();//第一个加入房间，成为房主

private:
    Ui::joinroom *ui;
    void handle(QString s);
    bool canHandle(QString s);
    EventHandler* selectHandler(QString s);//实现责任链模式的纯虚函数
    waitroom *dr;
};

#endif // JOINROOM_H
