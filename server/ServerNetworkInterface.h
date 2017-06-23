#ifndef SERVERNETWORKINTERFACE_H
#define SERVERNETWORKINTERFACE_H

#include <QObject>
#include <eventhandler.h>
#include <map>
#include <QTcpSocket>
#include <QTcpServer>
#include <spliter.h>
#include <clientstatus.h>
#include <dollarspliter.h>

class EventHandler;
class ServerNetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerNetworkInterface(EventHandler*, QObject* = 0);
    ~ServerNetworkInterface();
	void sendMessage(QString, QString);      //通过服务器网络接口给指定用户发送指定指令
signals:

private slots:
	void startRead();//开始读入用户发过来的指令
	void handleConnection();//开始接受新连接
	void disconnected();//发现某个客户端连接中断
	void displayError(QAbstractSocket::SocketError);//发现某个客户端网络错误
private:
    EventHandler* mainHandler;
    QTcpServer *tcpServer;
    std::map<QString, QTcpSocket*> userNameSocket;
	std::map<QTcpSocket*, QString> socketUserName;
    Spliter *spliter;

	void startSend(QTcpSocket*, QString = "");
    void startRead(QTcpSocket*);
};

#endif // SERVERNETWORKINTERFACE_H
