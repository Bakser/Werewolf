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
    //QSplitter * e=new QSplitter(Qt::Vertical);
    //statusText=new QTextEdit;
    //e->addWidget(statusText);
    label = new QLabel;
    QSplitter *e = new QSplitter(Qt::Vertical);
    e->addWidget(label);
    QSplitter * mainSplitter=new QSplitter(Qt::Horizontal);

    c = new chat(networkInterface);
    mainSplitter->addWidget(c);

    QSplitter * right=new QSplitter(Qt::Vertical);
    right->setOpaqueResize(true);

    n=new night;
    n->resize(400,300);
    right->addWidget(n);

    v=new vote;
    right->addWidget(v);

    mainSplitter->addWidget(right);
    e->addWidget(mainSplitter);
    //statusText = new QTextEdit(this);

    //mainSplitter->setStretchFactor(1,1);
    //e->setStretchFactor(1, 1);
    //QString str="room:";
    //str.append(Globals::roomnumber);
    //mainSplitter->setWindowTitle(str);
    //e->setWindowTitle("room:" + QString::number(Globals::roomnumber));
    //mainSplitter->setStretchFactor(0, 40);
    mainSplitter->setStretchFactor(1, 1);
    //mainSplitter->setAutoFillBackground(true);
    e->setStretchFactor(0, 5);
    e->setStretchFactor(1, 95);
    e->setAutoFillBackground(true);

    setCentralWidget(e);
    e->show();
    //setCentralWidget(mainSplitter);
    //mainSplitter->show();

    death = captain = "";
    captainState = "";

    timer = deadline = NULL;
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
    //accessUnable();
    if (s.mid(0, 6) == "Status")
    {
        //flush status
        Globals::update(s);
        //statusText->setPlainText(s);
        v->update();
        if (!Globals::newGameStarted)
        {
            Globals::newGameStarted = 1;
            //tell you your character
            //qDebug() << "I will tell you your character~";
            setWindowTitle("User : " + Globals::meid + " Room #" + QString::number(Globals::roomnumber) + " Game : Werewolves Hollow Character : " + Globals::meroleString);
            drawcard *t = new drawcard();
            this->hide();
            t->show();
            connect(t, SIGNAL(onclose()), this, SLOT(show()));
        }
    }
    if (s.mid(0, 5) == "Night")
    {
        c->addRoomChat("System: " + s + " is coming...", "blue");
        n->setNight(split(s, " ")[1].toInt());
    }
    if (s.mid(0, 3) == "Day")
    {
        c->addRoomChat("System: " + s + " is coming...", "blue");
        n->setDay(split(s, " ")[1].toInt());
    }
    if (s.mid(0, 11) == "TalkCaptain")
    {
        captainState = "TalkCaptain";
        qDebug() << "TalkCaptain caught";
    }
    if (s.mid(0, 3) == "Set")
    {
        std::vector<QString> saver = split(split(s, "\n")[1], " ");
        for (auto s : saver)
            qDebug() << s;
        //vote access
        if (saver[0] == "1")
        {
            if (captainState == "ChooseCap")
            {
                qDebug() << "ready ChooseCap";
                //vote for caption
                c->addRoomChat("Operate : please select a player to be caption.", "purple");
                captainState = "";
                clearTimer();
                timer = new QTimer(this);
                deadline = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(endVoteSection()));
                connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endVoteSection(QString)));
                connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
                timer->setInterval(10000);
                deadline->setInterval(1000);
                timer->start();
                deadline->start();
                v->setYesNoEnabled(true);
                v->setVoteType("ChooseCap");
            }
            if (v->voteType == "Save" || v->voteType == "Order")
            {
                qDebug() << "begin set v yes/no enabled";
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
        else
        {
            v->setYesNoEnabled(false);
            v->setPushEnabled(false);
        }
        //chat access
        if (saver[1] == "1")
        {
            if (captainState == "TalkCaptain")
            {
                qDebug() << "ready TalkCaptain";
                //speech for the caption
                c->addRoomChat("Operate : please give a speech for becoming captain.", "blue");
                clearTimer();
                timer = new QTimer(this);
                deadline = new QTimer(this);
                //connect(timer, SIGNAL(timeout()), this, SLOT(accessUnable()));
                connect(timer, SIGNAL(timeout()), this, SLOT(MessageNotSended()));
                connect(c, SIGNAL(roommessage()), this, SLOT(accessUnable()));
                connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
                timer->setInterval(10000);
                deadline->setInterval(1000);
                timer->start();
                deadline->start();
                captainState = "";
                c->setRoomEnabled(true);
            }
            if (saver[2] == "Room")
            {
                //c->ui->roomSend->setEnabled(true);
                c->setRoomEnabled(true);
                clearTimer();
                timer = new QTimer(this);
                deadline = new QTimer(this);
                timer->setInterval(15000);
                deadline->setInterval(1000);
                connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
                connect(timer, SIGNAL(timeout()), this, SLOT(sayNothing()));
                c->addRoomChat("System : now you can say something.", "blue");
                timer->start();
                deadline->start();
            }
            else
            {
                //c->ui->werewolfSend->setEnabled(true);
                c->setWerewolfEnabled(true);
                //start wolf section
                c->addWerewolfChat("System : now you can say something.", "blue");
                c->addWerewolfChat("Operate : Please choose a player to kill.", "purple");
                clearTimer();
                timer = new QTimer(this);
                deadline = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(endWolfSection()));
                connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endWolfSection(QString)));
                connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
                timer->setInterval(30000);
                deadline->setInterval(1000);
                timer->start();
                deadline->start();
                v->setVoteType("Wolf");
            }
        }
        else
        {
            c->setRoomEnabled(false);
            c->setWerewolfEnabled(false);
        }
    }
    if (s.mid(0, 5) == "Guard")
    {
        //guard someone at night
        c->addRoomChat("Operate : please select a player to guard this night.", "purple");
        n->setGuard();
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(endGuardSection()));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endGuardSection(QString)));
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        timer->setInterval(30000);
        deadline->setInterval(1000);
        timer->start();
        deadline->start();
        v->setVoteType("Guard");
    }
    if (s.mid(0, 5) == "Witch")
    {
        n->setWitch();
        std::vector<QString> saver = split(s, "\n");
        if (saver.size() == 1)
        {
            //poison session
            c->addRoomChat("Operate : please select a player to sacrifice", "purple");
            clearTimer();
            timer = new QTimer(this);
            deadline = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(endPoisonSection()));
            connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endPoisonSection(QString)));
            connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
            timer->setInterval(30000);
            deadline->setInterval(1000);
            timer->start();
            deadline->start();
            v->setVoteType("Poison");
        }
        else
        {
            //save session
            if (saver[1] != "@")
            {
            death = saver[1].mid(1, saver[1].length() - 1);
            c->addRoomChat("Operate : Do you want to save player " + death + "?", "purple");
            clearTimer();
            timer = new QTimer(this);
            deadline = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(endSaveSection()));
            connect(v, SIGNAL(yesOrNo(bool)), this, SLOT(endSaveSection(bool)));
            connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
            timer->setInterval(30000);
            deadline->setInterval(1000);
            timer->start();
            deadline->start();
            v->setVoteType("Save");
            }
            else
            {
                networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@");
            }
        }
    }
    if (s.mid(0, 7) == "Prophet")
    {
        n->setFore();
        c->addRoomChat("Operate : please select a player to check.", "purple");
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(endProphetSection()));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endProphetSection(QString)));
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        timer->setInterval(30000);
        deadline->setInterval(1000);
        timer->start();
        deadline->start();
        v->setVoteType("Prophet");
    }
    if (s.mid(0, 3) == "Bad")
    {
        //label->setText("result : BAD");
        c->addRoomChat("result : Bad", "blue");
    }
    if (s.mid(0, 4) == "Good")
    {
        //label->setText("result : GOOD");
        c->addRoomChat("result : Good", "blue");
    }
    if (s.mid(0, 3) == "Die") {
        std::vector<QString> temp = split(s, "\n");
        for (int i = 1; i < temp.size(); ++i)
        {
            Globals::dieUpdate(temp[i].mid(1, temp[i].length() - 1));
            c->addRoomChat("System : " + temp[i].mid(1, temp[i].length() - 1) + "Died last night.", "blue");
        }
        v->update();
    }
    if (s.mid(0, 6) == "Youdie")
    {
        c->addRoomChat("Fatal : You died last night.", "red");
    }
    if (s.mid(0, 9) == "ChooseCap")
    {
        c->addRoomChat("System : Now choosing captain...", "blue");
        captainState = "ChooseCap";
    }
    if (s.mid(0, 7) == "Captain")
    {
        std::vector<QString> temp = split(s, "\n");
        if (temp[1] == "@")
        {
            c->addRoomChat("System : Captain destroyed the emblem.", "blue");
            captain = "";
        }
        else
        {
            c->addRoomChat("System : Now player " + temp[1].mid(1, temp[1].length() - 1) + " become captain.", "blue");
            captain = temp[1].mid(1, temp[1].length() - 1);
        }
    }
    if (s.mid(0, 5) == "Order")
    {
        c->addRoomChat("Operate : Do you want players to speak in clockwise order?", "purple");
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        timer->setInterval(10000);
        deadline->setInterval(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(endOrderSection()));
        connect(v, SIGNAL(yesOrNo(bool)), this, SLOT(endOrderSection(bool)));
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        timer->start();
        deadline->start();
        v->setVoteType("Order");
    }

    if (s.mid(0, 7) == "Tellsth")
    {
        c->addRoomChat("Operate : You died, please tell something to survival players.", "purple");
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        //connect(timer, SIGNAL(timeout()), this, SLOT(accessUnable()));
        connect(timer, SIGNAL(timeout()), this, SLOT(sayNothing()));
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        timer->setInterval(10000);
        deadline->setInterval(1000);
        timer->start();
        deadline->start();
    }
    if (s.mid(0, 8) == "roomchat")
    {
        std::vector<QString> temp = split(s, "\n");
        std::vector<QString> saver = split(temp[1], "@");
        if (saver.size() == 2)
            c->addRoomChat(saver[1] + " said : " + saver[0]);
    }
    if (s.mid(0, 8) == "wolfchat")
    {
        std::vector<QString> temp = split(s, "\n");
        std::vector<QString> saver = split(temp[1], "@");
        if (saver.size() == 2)
            c->addWerewolfChat(saver[1] + " said : " + saver[0]);
    }
    if (s.mid(0, 4) == "Vote")
    {
        c->addRoomChat("System : start voting.", "blue");
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(endVoteSection()));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endVoteSection(QString)));
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        timer->setInterval(10000);
        deadline->setInterval(1000);
        v->setVoteType("Vote");
        timer->start();
        deadline->start();
    }
    if (s.mid(0, 5) == "Carry")
    {
        n->setHunter();
        c->addRoomChat("System : Do you want to carry a player away?", "blue");
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        timer->setInterval(10000);
        deadline->setInterval(1000);
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        connect(timer, SIGNAL(timeout()), this, SLOT(endCarrySection()));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endCarrySection(QString)));
        timer->start();
        deadline->start();
        v->setVoteType("Carry");
    }
    if (s.mid(0, 6) == "Hunter")
    {
        std::vector<QString> temp = split(s, "\n");
        c->addRoomChat("System : Hunter " + temp[1].mid(1, temp[1].length() - 1) + " died last night. Now he wants to carry player " + temp[2].mid(1, temp[2].length() - 1) + ".", "blue");
    }
    if (s.mid(0, 4) == "Pass")
    {
        c->addRoomChat("Operate : You died as a captain. Select a player to be the new captain.", "blue");
        clearTimer();
        timer = new QTimer(this);
        deadline = new QTimer(this);
        timer->setInterval(10000);
        deadline->setInterval(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(endPassSection()));
        connect(v, SIGNAL(voteSuccess(QString)), this, SLOT(endPassSection(QString)));
        connect(deadline, SIGNAL(timeout()), this, SLOT(flushRemainingTime()));
        timer->start();
        deadline->start();
        v->setVoteType("Pass");
    }
    if (s.mid(0, 10) == "Captaindie")
    {
        c->addRoomChat("System : Captain died.", "blue");
    }
    if (s.mid(0, 9) == "GameEnded")
    {
        c->addRoomChat("Fatal : GameEnded.", "red");
    }
    if (s.mid(0, 6) == "YouWin")
    {
        c->addRoomChat("Fatal : You win!", "red");
        n->setWin();
    }
    if (s.mid(0, 7) == "YouLose")
    {
        c->addRoomChat("Fatal : You lose!", "red");
        n->setLose();
    }
    if (s.mid(0, 9) == "EndStatus")
    {
        std::vector<QString> temp = split(s, "\n");
        for (int i = 1; i < temp.size(); ++i)
        {
            std::vector<QString> saver = split(temp[i], " ");
            c->addRoomChat("System : player " + saver[0] + " is " + saver[1] + ".", "blue");
        }
    }
}

EventHandler* MainWindowplay::selectHandler(QString)
{
    return NULL;
}

void MainWindowplay::endGuardSection(QString guardChoose)
{
    qDebug() << "endGuardSection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" + guardChoose);
    Globals::lastDefend = guardChoose;
}

void MainWindowplay::endPoisonSection(QString poisonChoose)
{
    qDebug() << "endPoisonSection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" + poisonChoose);
}

void MainWindowplay::endWolfSection(QString wolfChoose)
{
    qDebug() << "endWolfSection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" + wolfChoose);
}

void MainWindowplay::endSaveSection(bool save)
{
    qDebug() << "endSaveSection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                (save ? death : ""));
}

void MainWindowplay::endProphetSection(QString prophetChoose)
{
    qDebug() << "endProphetSection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                prophetChoose);
}


void MainWindowplay::clearTimer()
{
    qDebug() << "go into clearTimer";
    label->setText("");
    qDebug() << "timer begin...";
    if (timer != NULL)
    {
        qDebug() << "timer not null";
        timer->stop();
        delete timer;
        timer = NULL;
    }
    qDebug() << "timer end...";
    qDebug() << "deadline begin...";
    if (deadline != NULL)
    {
        qDebug() << "deadline not null";
        deadline->stop();
        delete deadline;
        deadline = NULL;
    }
    qDebug() << "deadline end...";
    qDebug() << "go out of clearTimer";
}

void MainWindowplay::accessUnable()
{
    qDebug() << "go into accessUnable()...";
    clearTimer();
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
    qDebug() << "go out of accessUnable()...";
}

void MainWindowplay::endVoteSection(QString voteChoose)
{
    qDebug() << "end vote section : " << voteChoose;
    accessUnable();
    QString addString = "vote " + QString::number(Globals::roomnumber) + "\n@" + voteChoose;
    qDebug() << addString;
    networkInterface->addString(addString);
}

void MainWindowplay::endCarrySection(QString carryChoose)
{
    qDebug() << "endCarrySection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                carryChoose);
}

void MainWindowplay::endOrderSection(bool clockwise)
{
    qDebug() << "endOrderSection";
    accessUnable();
    //networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                (clockwise ? "1" : "0"));

}

void MainWindowplay::endPassSection(QString passChoose)
{
    qDebug() << "endPassSection";
    accessUnable();
    networkInterface->addString("vote " + QString::number(Globals::roomnumber) + "\n@" +
                                passChoose);
}

void MainWindowplay::flushRemainingTime()
{
    label->setText("Time Remained: " + QString::number(timer->remainingTime() / 1000) + " seconds.");
}

void MainWindowplay::MessageNotSended()
{
    qDebug() << "MessageNotSender";
    accessUnable();
    networkInterface->addString("roomchat " + QString::number(Globals::roomnumber) + "\n@" + Globals::meid);
}

void MainWindowplay::sayNothing()
{
    qDebug() << "sayNothing";
    accessUnable();
    networkInterface->addString("roomchat " + QString::number(Globals::roomnumber) + "\n@" + Globals::meid);
}
