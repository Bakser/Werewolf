#ifndef CLIENTNETWORKINTERFACE_H
#define CLIENTNETWORKINTERFACE_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include "eventhandler.h"
//#include <spliter.h>
//#include <dollarspliter.h>

class EventHandler;

class ClientNetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetworkInterface(QObject *parent = 0);
    ~ClientNetworkInterface();
    void addString(QString);
    void setMainHandler(EventHandler*);
signals:
    void receiveCommand(QString message);
public slots:
    void startRead();
    void startLogin(QString);
    void displayError(QAbstractSocket::SocketError);
    void disconnected();

private:
    QTcpSocket *tcpSocket;
    QString sendString;
    void startSend(QString = "");
    EventHandler *mainHandler;
    //Spliter *spliter;
};

#endif // CLIENTNETWORKINTERFACE_H
