#include "vote.h"
#include "ui_vote.h"
#include <QResizeEvent>
#include <QDebug>
#include "globals.h"
#include <QPushButton>
#include <QListWidgetItem>

vote::vote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vote)
{
    ui->setupUi(this);
    for(int i=0;i<Globals::nplayer;i++)
    {
        if(Globals::player_alive[i]==1)
        {
            ui->listWidget->addItem(Globals::player_id[i]);
        }
    }

}

vote::~vote()
{
    delete ui;
}



void vote::on_listWidget_itemClicked(QListWidgetItem *item)
{
    choose=item->text();
}

void vote::on_pushButton_clicked()
{
    //send choose
}
