#include "newroom.h"
#include "ui_newroom.h"

newroom::newroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newroom)
{
    ui->setupUi(this);
}

newroom::~newroom()
{
    delete ui;
}


