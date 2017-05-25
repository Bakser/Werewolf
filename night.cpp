#include "night.h"
#include "ui_night.h"

night::night(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::night)
{
    ui->setupUi(this);
}

night::~night()
{
    delete ui;
}
