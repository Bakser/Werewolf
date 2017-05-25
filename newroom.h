#ifndef NEWROOM_H
#define NEWROOM_H

#include <QDialog>

namespace Ui {
class newroom;
}

class newroom : public QDialog
{
    Q_OBJECT

public:
    explicit newroom(QWidget *parent = 0);
    ~newroom();

private slots:
    //void on_commandLinkButton_clicked();

private:
    Ui::newroom *ui;
};

#endif // NEWROOM_H
