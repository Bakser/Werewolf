#ifndef SERVERNETWORKINTERFACE_H
#define SERVERNETWORKINTERFACE_H

#include <QObject>
#include <eventhandler.h>
#include <map>
#include <QTcpSocket>
#include <QTcpServer>
#include <spliter.h>
#include <clientstatus.h>
#include <dollarspliter.h>

class EventHandler;
class ServerNetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerNetworkInterface(EventHandler*, QObject* = 0);
    ~ServerNetworkInterface();
    void sendMessage(QString, QString);
signals:

private slots:
    void startRead();
    void handleConnection();
    void disconnected();
private:
    EventHandler* mainHandler;
    QTcpServer *tcpServer;
    std::map<QString, QTcpSocket*> userNameSocket;
    std::map<QTcpSocket*, ClientStatus> socketClientStatus;
    Spliter *spliter;

    void startSend(QTcpSocket*);
    void startRead(QTcpSocket*);
};

#endif // SERVERNETWORKINTERFACE_H
