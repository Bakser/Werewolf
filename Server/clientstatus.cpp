#include "clientstatus.h"

ClientStatus::ClientStatus()
{

}

ClientStatus::ClientStatus(QString _userName)
{
    userName = _userName;
    nextSendString = "";
}

ClientStatus::~ClientStatus()
{

}

void ClientStatus::addSendString(QString s)
{
    if (nextSendString == "")
        nextSendString = s;
    else
        nextSendString += "$" + s;
}

void ClientStatus::clearString()
{
    nextSendString = "";
}

QString ClientStatus::getNextSendString()
{
    return nextSendString;
}

QString ClientStatus::getUserName()
{
    return userName;
}
