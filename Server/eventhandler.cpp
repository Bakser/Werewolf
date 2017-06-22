/*
名称：eventhandler.cpp
作者：计62 王晓智 2016011257，计62 吴一凡 2016011269
时间：2017.5.30
内容：实现抽象类EventHandler
版权：全部自行完成

每个函数的功能参见eventhandler.h
*/
#include "eventhandler.h"

EventHandler::EventHandler(QObject *parent) : QObject(parent){

}

EventHandler::EventHandler(ServerNetworkInterface *_networkInterface)
{
    networkInterface = _networkInterface;
}

void EventHandler::tryHandle(QString userName, QString message){
    if (canHandle(message))
        handle(userName, message);
    else
        selectHandler(message)->tryHandle(userName, message);
}

void EventHandler::sendMessage(QString userName, QString message){
    networkInterface->sendMessage(userName, message);
}
void EventHandler::setNetworkInterface(ServerNetworkInterface* _networkInterface){
    networkInterface=_networkInterface;
}
int EventHandler::parseToInt(QString message){
    bool flag=0;
    int res=0;
    for(auto c:message)//从前往后扫描message中字符（QChar类型），以空格和换行为界提取出数
        if(c==' ')flag=1;
        else if(c=='\n')return res;
        else if (flag)
            res=res*10+(c.toLatin1()-'0');
    return res;
}
