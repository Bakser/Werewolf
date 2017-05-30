#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "clientnetworkinterface.h"

class ClientNetworkInterface;

class EventHandler
{
public:
    EventHandler(ClientNetworkInterface*);
    void tryHandle(QString);
protected:
    ClientNetworkInterface *networkInterface;
private:
    virtual EventHandler* selectHandler(QString) = 0;
    virtual bool canHandle(QString) = 0;
    virtual void handle(QString) = 0;
};

#endif // EVENTHANDLER_H
