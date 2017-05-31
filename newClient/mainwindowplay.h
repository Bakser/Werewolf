#ifndef MAINWINDOWPLAY_H
#define MAINWINDOWPLAY_H

#include <QMainWindow>
#include <QTextEdit>
#include "eventhandler.h"
#include "vote.h"
#include "night.h"
#include "chat.h"
#include <QTimer>
#include <QLabel>
namespace Ui {
class MainWindowplay;
}

class MainWindowplay : public QMainWindow, public EventHandler
{
    Q_OBJECT

public:
    explicit MainWindowplay(ClientNetworkInterface*, QWidget *parent = 0);
    ~MainWindowplay();

private:
    Ui::MainWindowplay *ui;
    void handle(QString);
    bool canHandle(QString);
    EventHandler* selectHandler(QString);
    //QTextEdit *statusText;
    vote *v;
    night *n;
    chat *c;
    QTimer *timer;
    QTimer *deadline;
    QLabel *label;
    QString death;
    QString captain;
    QString captainState;
private slots:
    void endGuardSection(QString = "");
    void endWolfSection(QString = "");
    void endSaveSection(bool = false);
    void endPoisonSection(QString = "");
    void endProphetSection(QString = "");
    void endVoteSection(QString = "");
    void endCarrySection(QString = "");
    void endOrderSection(bool = false);
    void endPassSection(QString = "");
    void MessageNotSended();
    void accessUnable();
    void flushRemainingTime();
};

#endif // MAINWINDOWPLAY_H
