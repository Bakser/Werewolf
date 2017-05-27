#ifndef NIGHT_H
#define NIGHT_H
#include "globals.h"
#include <QDialog>

namespace Ui {
class night;
}

class night : public QDialog
{
    Q_OBJECT

public:
    explicit night(QWidget *parent = 0);
    ~night();
    void operate();

private:
    Ui::night *ui;
    int _id;
};

#endif // NIGHT_H
