#include "eventhandler.h"

EventHandler::EventHandler(QObject *parent) : QObject(parent)
{

}

EventHandler::EventHandler(ServerNetworkInterface *_networkInterface)
{
    networkInterface = _networkInterface;
}

void EventHandler::tryHandle(QString userName, QString message)
{
    if (canHandle(message))
        handle(userName, message);
    else
        selectHandler(message)->tryHandle(userName, message);
}

void EventHandler::sendMessage(QString userName, QString message)
{
    networkInterface->sendMessage(userName, message);
}
void EventHandler::setNetworkInterface(ServerNetworkInterface* _networkInterface){
    networkInterface=_networkInterface;
}
int EventHandler::parseToInt(QString message){
    bool flag=0;
    int res=1;
    for(auto c:message)
        if(c==' ')flag=1;
        else if(c=='\n')return res;
        else if (flag)
            res=res*(c.unicode()-'0');
    return res;
}
