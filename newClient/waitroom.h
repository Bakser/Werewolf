#ifndef WAITROOM_H
#define WAITROOM_H

#include <QDialog>

namespace Ui {
class waitroom;
}

class waitroom : public QDialog
{
    Q_OBJECT

public:
    explicit waitroom(QWidget *parent = 0);
    ~waitroom();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::waitroom *ui;
};

#endif // WAITROOM_H
