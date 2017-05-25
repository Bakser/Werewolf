#include "joinroom.h"
#include "ui_joinroom.h"

joinroom::joinroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::joinroom)
{
    ui->setupUi(this);

}

joinroom::~joinroom()
{
    delete ui;
}

void joinroom::on_pushButton_clicked()
{
    int roomnumber=ui->lineEdit->text().toInt();

}

