#ifndef NEWROOM_H
#define NEWROOM_H

#include <QDialog>
#include "globals.h"
#include "clientnetworkinterface.h"
#include <QCloseEvent>

//游戏参数设置界面设计
namespace Ui {
class newroom;
}

class newroom : public QDialog
{
    Q_OBJECT

public:
    explicit newroom(ClientNetworkInterface*, QWidget *parent = 0);
    ~newroom();
    int nvillager;
    int nwolf;
    bool bwitch;
    bool bhunter;
    bool bforesee;
    bool bguard;
    bool bpolice;//各种类型角色数目


private slots:

    void on_pushButton_clicked();

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_5_clicked();//控制调整各种角色数目

private:
    Ui::newroom *ui;
    ClientNetworkInterface *networkInterface;
    void closeEvent(QCloseEvent *);

signals:
    void onclose();
};

#endif // NEWROOM_H
