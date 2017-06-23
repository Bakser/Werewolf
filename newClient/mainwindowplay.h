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
//游戏界面设计
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
    EventHandler* selectHandler(QString);//责任链模式纯虚函数
    vote *v;//投票模块
    night *n;//贴图模块
    chat *c;//交流模块
    QTimer *timer;//计时器
    QTimer *deadline;//倒计时提醒
    QLabel *label;//状态栏
    QString death;//死亡
    QString captain;//警长
    QString captainState;//警长状态
private slots:
    void endGuardSection(QString = "");//守卫投票结束
    void endWolfSection(QString = "");//狼人投票结束
    void endSaveSection(bool = false);//女巫解药使用结束
    void endPoisonSection(QString = "");//女巫毒药使用结束
    void endProphetSection(QString = "");//预言家选择验人结束
    void endVoteSection(QString = "");//玩家投票结束
    void endCarrySection(QString = "");//猎人选择带走一人结束
    void endOrderSection(bool = false);//警长选择发言顺序结束
    void endPassSection(QString = "");//警长更换警徽所有者结束
    void MessageNotSended();//消息未发送
    void accessUnable();//将所有按钮变为不可用
    void flushRemainingTime();//倒计时提醒：刷新屏幕显示
    void sayNothing();//什么都不说
    void clearTimer();//重置计时器
};

#endif // MAINWINDOWPLAY_H
