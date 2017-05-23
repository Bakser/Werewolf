#include "eventhandler.h"

EventHandler::EventHandler()
{

}



EventHandler::EventHandler(ServerNetworkInterface *_networkInterface)
{
    networkInterface = _networkInterface;
}

void EventHandler::tryHandle(QString userName, QString message)
{
    if (canHandle(message))
        Handle(userName, message);
    else
        selectHandler(message)->tryHandle(userName, message);
}

void EventHandler::sendMessage(QString userName, QString message)
{
    networkInterface->sendMessage(userName, message);
}


