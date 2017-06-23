#ifndef NIGHT_H
#define NIGHT_H
#include "globals.h"
#include <QDialog>

//右上角贴图界面设计
namespace Ui {
class night;
}

class night : public QDialog
{
    Q_OBJECT

public:
    explicit night(QWidget *parent = 0);
    ~night();

public slots:
    //按照角色、时间不同更换贴图
    void setNight(int day);
    void setDay(int day);
    void setGuard();
    void setWitch();
    void setFore();
    void setCap();
    void setLose();
    void setWin();
    void setCapPass();
    void setHunter();


private:
    Ui::night *ui;
};

#endif // NIGHT_H
