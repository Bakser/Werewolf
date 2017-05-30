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
    ui->yes->setVisible(false);
    ui->no->setVisible(false);
}

vote::~vote()
{
    delete ui;
}



void vote::update()
{
    ui->listWidget->clear();
    for(int i=0;i<Globals::nplayer;i++)
    {
        if(Globals::player_alive[i]==1)
        {
            ui->listWidget->addItem(Globals::player_id[i]);
        }
    }
}

void vote::on_listWidget_itemClicked(QListWidgetItem *item)
{
    choose=item->text();
}

void vote::on_pushButton_clicked()
{
    if (voteType == "Guard")
    {
        if (choose == Globals::lastDefend)
        {
            ui->label->setText("You can't guard the one you guarded last night.");
        }
        else
        {
            emit voteSuccess(choose);
            ui->pushButton->setEnabled(false);
            ui->label->setText("Voted successfully");
        }
    }
    if (voteType == "Wolf" || voteType == "Poison" || voteType == "Prophet")
    {
        emit voteSuccess(choose);
        ui->pushButton->setEnabled(false);
        ui->label->setText("Voted successfully");
    }

}

void vote::on_yes_clicked()
{
    emit yesOrNo(true);
    ui->yes->setVisible(false);
    ui->no->setVisible(false);
    ui->yes->setEnabled(false);
    ui->no->setEnabled(false);
}

void vote::on_no_clicked()
{
    emit yesOrNo(false);
    ui->yes->setVisible(false);
    ui->no->setVisible(false);
    ui->yes->setEnabled(false);
    ui->no->setEnabled(false);
}

void vote::setVoteType(QString type)
{
    voteType = type;
    if (type == "Guard")
        ui->label->setText("Please choose a player to guard.");
    if (type == "Wolf")
        ui->label->setText("Please choose a player to kill.");
    if (type == "Poison")
        ui->label->setText("Please choose a player to poison.");
    if (type == "Save")
    {
        ui->label->setText("Do you want to save the player?");
        ui->yes->setVisible(true);
        ui->no->setVisible(true);
    }
    if (type == "Prophet")
    {
        ui->label->setText("Please choose a player to check.");
    }
}

void vote::setYesNoEnabled(bool f)
{
    ui->yes->setEnabled(f);
    ui->no->setEnabled(f);
}

void vote::setPushEnabled(bool f)
{
    ui->pushButton->setEnabled(f);
}
