#include "eventhandler.h"

EventHandler::EventHandler(ClientNetworkInterface *_networkInterface)
{
    networkInterface = _networkInterface;
}

void EventHandler::tryHandle(QString s)
{
    if (canHandle(s))
        handle(s);
    else
        selectHandler(s)->tryHandle(s);
}
