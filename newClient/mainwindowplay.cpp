#include "mainwindowplay.h"
#include "globals.h"
#include <QSplitter>
#include <QDialog>
#include <QObject>
#include <QTextEdit>
#include "night.h"
#include "vote.h"
#include "chat.h"

MainWindowplay::MainWindowplay(QWidget *parent) :
    QMainWindow(parent)
{
    setGeometry(300,200,800,600);
    QSplitter * mainSplitter=new QSplitter(Qt::Horizontal);

    chat * c=new chat;
    mainSplitter->addWidget(c);



    QSplitter * right=new QSplitter(Qt::Vertical,mainSplitter);
    right->setOpaqueResize(true);

    night *n=new night;
    n->resize(400,300);
    right->addWidget(n);

    vote *v=new vote;
    right->addWidget(v);



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
