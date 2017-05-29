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


private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::vote *ui;
};

#endif // VOTE_H
