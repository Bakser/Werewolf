#ifndef CLIENTNETWORKINTERFACE_H
#define CLIENTNETWORKINTERFACE_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include "eventhandler.h"
//#include <spliter.h>
//#include <dollarspliter.h>

class EventHandler;

//客户端网络接口
class ClientNetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetworkInterface(QObject *parent = 0);
    ~ClientNetworkInterface();
    void addString(QString);//客户端通过此接口给服务器发送字符串
    void setMainHandler(EventHandler*);//设置主处理器
signals:
    void receiveCommand(QString message);//收到服务器传来的字符串调用此函数
public slots:
    void startRead();//开始接受服务器传来的字符串
    void startLogin(QString);//开始登录
    void displayError(QAbstractSocket::SocketError);//出现网络错误
    void disconnected();//从服务器上断开连接

private:
    QTcpSocket *tcpSocket;
    QString sendString;
    void startSend(QString = "");
    EventHandler *mainHandler;
    //Spliter *spliter;
};

#endif // CLIENTNETWORKINTERFACE_H
