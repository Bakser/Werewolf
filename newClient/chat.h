#ifndef CHAT_H
#define CHAT_H


#include <QMainWindow>
#include "clientnetworkinterface.h"

namespace Ui {
class chat;
}

class chat: public QMainWindow
{
    Q_OBJECT

public:
    explicit chat(ClientNetworkInterface*, QWidget *parent = 0);
    ~chat();
    void setRoomEnabled(bool);
    void setWerewolfEnabled(bool);
    void addRoomChat(QString, QString = "black");
    void addWerewolfChat(QString, QString = "black");
private slots:
    void on_werewolfSend_clicked();

    void on_roomSend_clicked();
signals:
    void roommessage();
private:
    Ui::chat *ui;
    ClientNetworkInterface *networkInterface;
};

#endif // CHAT_H
