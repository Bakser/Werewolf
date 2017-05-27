#ifndef NEWROOM_H
#define NEWROOM_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class newroom;
}

class newroom : public QDialog
{
    Q_OBJECT

public:
    explicit newroom(QWidget *parent = 0);
    ~newroom();
    int nvillager;
    int nwolf;
    bool bwitch;
    bool bhunter;
    bool bforesee;
    bool bguard;
    bool bpolice;


private slots:

    void on_pushButton_clicked();

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::newroom *ui;
};

#endif // NEWROOM_H
