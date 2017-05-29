#ifndef JOINROOM_H
#define JOINROOM_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class joinroom;
}

class joinroom : public QDialog
{
    Q_OBJECT

public:
    explicit joinroom(QWidget *parent = 0);
    ~joinroom();

private slots:
    void on_pushButton_clicked();
    void success();
    void full();
    void owner();

    //void on_lineEdit_editingFinished();

private:
    Ui::joinroom *ui;
};

#endif // JOINROOM_H
