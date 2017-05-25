#ifndef MASTER_H
#define MASTER_H

#include <QDialog>

namespace Ui {
class master;
}

class master : public QDialog
{
    Q_OBJECT

public:
    explicit master(QWidget *parent = 0);
    ~master();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::master *ui;
};

#endif // MASTER_H
