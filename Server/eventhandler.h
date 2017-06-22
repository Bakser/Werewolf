/*
名称：eventhandler.h
作者：计62 王晓智 2016011257，计62 吴一凡 2016011269
时间：2017.5.30
内容：定义服务器逻辑采用的责任链模式的抽象类EventHandler，定义了基础的接口方便子类使用
版权：全部自行完成
*/
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "servernetworkinterface.h"
#include <QString>

class ServerNetworkInterface;

class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject* parent = 0);
    virtual ~EventHandler() = default;
    EventHandler(ServerNetworkInterface*);
    void tryHandle(QString userName, QString message);//尝试处理用户传来的包，格式规范见“逻辑主文档.md”
    void setNetworkInterface(ServerNetworkInterface*);//指定调用的网络接口
    void sendMessage(QString,QString);//向客户端发送信息
protected:
    ServerNetworkInterface *networkInterface;
    int parseToInt(QString);//将客户端传来的包中的数字提取出来
private:
    virtual bool canHandle(QString) = 0;//判断这个包能否被这个类处理
    virtual void handle(QString, QString) = 0;//具体处理这个包的内容
    virtual EventHandler* selectHandler(QString) = 0;//挑选责任链的后继节点，交给它处理

};

#endif // EVENTHANDLER_H
