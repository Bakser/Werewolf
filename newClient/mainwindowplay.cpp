#include "mainwindowplay.h"
#include "globals.h"
#include <QSplitter>
#include <QDialog>
#include <QObject>
#include <QTextEdit>
#include "night.h"
#include "vote.h"
#include "chat.h"
#include <QLineEdit>
#include "drawcard.h"
#include "stringoperate.h"
MainWindowplay::MainWindowplay(ClientNetworkInterface *_networkInterface, QWidget *parent) :
    QMainWindow(parent),
    EventHandler(_networkInterface)

{


    setGeometry(300,200,800,600);
    QSplitter * e=new QSplitter(Qt::Vertical);
    label=new QLabel;
    e->addWidget(label);

    QSplitter * mainSplitter=new QSplitter(Qt::Horizontal,e);

    c = new chat;
    mainSplitter->addWidget(c);

    QSplitter * right=new QSplitter(Qt::Vertical,mainSplitter);
    right->setOpaqueResize(true);

    n=new night;
    n->resize(400,300);
    right->addWidget(n);

    v=new vote;
    right->addWidget(v);

    statusText = new QTextEdit(this);

    mainSplitter->setStretchFactor(1,1);
    QString str="room:";
    str.append(Globals::roomnumber);
    mainSplitter->setWindowTitle(str);
    setCentralWidget(mainSplitter);
    mainSplitter->show();
}

MainWindowplay::~MainWindowplay()
{

}

bool MainWindowplay::canHandle(QString s)
{
    qDebug() << "can mainWindowplay handle?";
    return true;
}

void MainWindowplay::handle(QString s)
{
    qDebug() << "MainWindowplay received " << s;
    if (s.mid(0, 6) == "Status")
    {
        //flush status
        Globals::update(s);
        statusText->setPlainText(s);
        v->update();
        if (!Globals::newGameStarted)
        {
            Globals::newGameStarted = 1;
            //tell you your character
            //qDebug() << "I will tell you your character~";
            drawcard *t = new drawcard();
            this->hide();
            t->show();
            connect(t, SIGNAL(onclose()), this, SLOT(show()));
        }
    }
    if (s.mid(0, 5) == "Night")
    {
        n->setNight(split(s, " ")[1].toInt());
    }
    if (s.mid(0, 3) == "Day")
    {
        n->setDay(split(s, " ")[1].toInt());
    }
    if (s.mid(0, 3) == "Set")
    {
        std::vector<QString> saver = split(split(s, "\n")[1], " ");
        //vote access
        if (saver[0] == "1")
        {
            if (v->voteType == "Save")
            {
                //v->ui->yes->setEnabled(true);
                //v->ui->no->setEnabled(true);
                v->setYesNoEnabled(true);
            }
            else
            {
                //v->ui->pushButton->setEnabled(true);
                v->setPushEnabled(true);
            }
        }
        //chat access
        if (saver[1] == "1")
        {
            if (saver[2] == "Room")
            {
                //c->ui->roomSend->setEnabled(true);
                c->setRoomEnabled(true);
            }
            else
            {
                //c->ui->werewolfSend->setEnabled(true);
                c->setWerewolfEnabled(true);
                //start wolf section
                timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(endWolfSection(QString)));
                connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endWolfSection(QString)));
                timer->setInterval(30000);
                timer->start();
                v->setVoteType("Wolf");
            }
        }
    }
    if (s.mid(0, 5) == "Guard")
    {
        //guard someone at night
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(endGuardSection(QString)));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endGuardSection(QString)));
        timer->setInterval(10000);
        timer->start();
        v->setVoteType("Guard");
    }
    if (s.mid(0, 5) == "Witch")
    {
        std::vector<QString> saver = split(s, " ");
        if (saver.size() == 1)
        {
            //poison session
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(endPoisonSection(QString)));
            connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endPoisonSection(QString)));
            timer->setInterval(10000);
            timer->start();
            v->setVoteType("Poison");
        }
        else
        {
            //save session
            death = saver[1].mid(1, saver[1].length() - 1);
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(endSaveSection(bool)));
            connect(v, SIGNAL(yesOrNo(bool)), this, SLOT(endSaveSection(bool)));
            //connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endSaveSection(QString)));
            timer->setInterval(10000);
            timer->start();
            v->setVoteType("Save");
        }
    }
    if (s.mid(0, 7) == "Prophet")
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(endProphetSection(QString)));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endProphetSection(QString)));
        timer->setInterval(10000);
        timer->start();
        v->setVoteType("Prophet");
    }
    if (s.mid(0, 3) == "BAD")
    {
        label->setText("result : BAD");
    }
    if (s.mid(0, 4) == "GOOD")
    {
        label->setText("result : GOOD");
    }
}

EventHandler* MainWindowplay::selectHandler(QString)
{
    return NULL;
}

void MainWindowplay::endGuardSection(QString guardChoose)
{
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" + guardChoose);
    Globals::lastDefend = guardChoose;
}

void MainWindowplay::endPoisonSection(QString poisonChoose)
{
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" + poisonChoose);
}

void MainWindowplay::endSaveSection(bool save)
{
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                (save ? death : ""));
}

void MainWindowplay::endProphetSection(QString prophetChoose)
{
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                prophetChoose);
}

void MainWindowplay::accessUnable()
{
    timer->stop();
    delete timer;
    /*
    v->ui->pushButton->setEnabled(false);
    v->ui->yes->setEnabled(false);
    v->ui->no->setEnabled(false);
    c->ui->roomSend->setEnabled(false);
    c->ui->werewolfSend->setEnabled(false);
    */
    v->setPushEnabled(false);
    v->setYesNoEnabled(false);
    c->setRoomEnabled(false);
    c->setWerewolfEnabled(false);
}
