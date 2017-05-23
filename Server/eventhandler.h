#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "servernetworkinterface.h"
#include <QString>

class ServerNetworkInterface;

class EventHandler
{
public:
    EventHandler();
    virtual ~EventHandler() = default;
    EventHandler(ServerNetworkInterface*);
    void tryHandle(QString userName, QString message);

protected:
    ServerNetworkInterface *networkInterface;
private:
    virtual bool canHandle(QString) = 0;
    virtual void Handle(QString, QString) = 0;
    virtual EventHandler* selectHandler(QString) = 0;
    void sendMessage(QString, QString);
};

#endif // EVENTHANDLER_H
