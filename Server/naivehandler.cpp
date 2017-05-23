#include "naivehandler.h"

NaiveHandler::NaiveHandler()
{

}

NaiveHandler::~NaiveHandler()
{

}

void NaiveHandler::setNetworkInterface(ServerNetworkInterface *_networkInterface)
{
    networkInterface = _networkInterface;
}

bool NaiveHandler::canHandle(QString s)
{
    return true;
}

void NaiveHandler::Handle(QString userName, QString message)
{
    if (message != "")
        qDebug() << "User " << userName << " said : " << message << ".";
}

EventHandler* NaiveHandler::selectHandler(QString message)
{
    return NULL;
}
