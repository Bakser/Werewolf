#ifndef VOTE_H
#define VOTE_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QListWidgetItem>

//投票界面设计
namespace Ui {
class vote;
}

class vote : public QDialog
{
    Q_OBJECT

public:
    explicit vote(QWidget *parent = 0);
    ~vote();
    QString choose;//选择的玩家
    void update();//更新显示
    void setVoteType(QString);//设置投票类型
    QString voteType;//投票类型
    void setYesNoEnabled(bool);//更改Yes/No按钮的可用性
    void setPushEnabled(bool);//更改Push按钮的可用性
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);//选择listItem

    void on_pushButton_clicked();//按下按钮
    void on_yes_clicked();//按下yes按钮
    void on_no_clicked();//按下no按钮
private:
    Ui::vote *ui;
signals:
    void voteSuccess(QString);//信号：投票成功
    void yesOrNo(bool);//信号：点击了yes或no按钮
};

#endif // VOTE_H
