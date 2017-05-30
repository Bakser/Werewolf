#ifndef VOTE_H
#define VOTE_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QListWidgetItem>

namespace Ui {
class vote;
}

class vote : public QDialog
{
    Q_OBJECT

public:
    explicit vote(QWidget *parent = 0);
    ~vote();
    QString choose;
    void update();
    void setVoteType(QString);
    QString voteType;
    void setYesNoEnabled(bool);
    void setPushEnabled(bool);
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();
    void on_yes_clicked();
    void on_no_clicked();
private:
    Ui::vote *ui;
signals:
    void voteSuccess(QString);
    void yesOrNo(bool);
};

#endif // VOTE_H
