#ifndef CLIENTNETWORKINTERFACE_H
#define CLIENTNETWORKINTERFACE_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <spliter.h>
#include <dollarspliter.h>

class ClientNetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetworkInterface(QObject *parent = 0);
    ~ClientNetworkInterface();
    Q_INVOKABLE void addString(QString);
    Q_INVOKABLE QString test();
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
    void startSend();
    Spliter *spliter;
};

#endif // CLIENTNETWORKINTERFACE_H
