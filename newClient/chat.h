#ifndef CHAT_H
#define CHAT_H


#include <QMainWindow>

namespace Ui {
class chat;
}

class chat: public QMainWindow
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = 0);
    ~chat();

private slots:
    void on_werewolfSend_clicked();

    void on_roomSend_clicked();

private:
    Ui::chat *ui;
};

#endif // CHAT_H
