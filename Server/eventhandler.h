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
    void tryHandle(QString userName, QString message);
    void setNetworkInterface(ServerNetworkInterface*);
    void sendMessage(QString,QString);
protected:
    ServerNetworkInterface *networkInterface;
    int parseToInt(QString);
    //void sendMessage(QString, QString);
private:
    virtual bool canHandle(QString) = 0;
    virtual void handle(QString, QString) = 0;
    virtual EventHandler* selectHandler(QString) = 0;
};

#endif // EVENTHANDLER_H
