#ifndef NIGHT_H
#define NIGHT_H

#include <QMainWindow>

namespace Ui {
class night;
}

class night : public QMainWindow
{
    Q_OBJECT

public:
    explicit night(QWidget *parent = 0);
    ~night();

private:
    Ui::night *ui;
};

#endif // NIGHT_H
