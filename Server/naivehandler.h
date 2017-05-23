#ifndef NAIVEHANDLER_H
#define NAIVEHANDLER_H

#include "eventhandler.h"
#include "servernetworkinterface.h"
class NaiveHandler : public EventHandler
{
public:
    NaiveHandler();
    ~NaiveHandler();
    void setNetworkInterface(ServerNetworkInterface*);
private:
    bool canHandle(QString);
    void Handle(QString, QString);
    EventHandler* selectHandler(QString);
};

#endif // NAIVEHANDLER_H
