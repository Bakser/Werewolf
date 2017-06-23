#ifndef CHAT_H
#define CHAT_H


#include <QMainWindow>
#include "clientnetworkinterface.h"

//聊天窗口设计
namespace Ui {
class chat;
}

class chat: public QMainWindow
{
    Q_OBJECT

public:
    explicit chat(ClientNetworkInterface*, QWidget *parent = 0);
    ~chat();
    void setRoomEnabled(bool);//设置房间频道聊天按钮可用性
    void setWerewolfEnabled(bool);//设置狼人频道聊天按钮可用性
    void addRoomChat(QString, QString = "black");//在房间频道聊天框附加消息
    void addWerewolfChat(QString, QString = "black");//在狼人频道聊天框附加消息
private slots:
    void on_werewolfSend_clicked();//点击房间频道聊天按钮

    void on_roomSend_clicked();//点击狼人频道聊天按钮
signals:
    void roommessage();
private:
    Ui::chat *ui;
    ClientNetworkInterface *networkInterface;
};

#endif // CHAT_H
