#include "clientnetworkinterface.h"
#include <QByteArray>
#include <QDataStream>
#include <vector>

ClientNetworkInterface::ClientNetworkInterface(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    sendString = "";

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(startRead()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
                    this, &ClientNetworkInterface::displayError);

    spliter = new DollarSpliter();
}

ClientNetworkInterface::~ClientNetworkInterface()
{
    delete tcpSocket;
    delete spliter;
}

void ClientNetworkInterface::addString(QString s)
{
    if (sendString == "")
        sendString = s;
    else
        sendString += "$" + s;
}

void ClientNetworkInterface::startLogin(QString userName)
{
    qDebug() << "User " + userName + " start login...";
    tcpSocket->connectToHost("127.0.0.1", 6666);
    addString("login " + userName);
    startSend();
}

void ClientNetworkInterface::startSend()
{
    //qDebug() << "start sending...";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << sendString;
    //qDebug() << "want to send to server: " + sendString;
    sendString = "";
    tcpSocket->write(block);
    startRead();
}

void ClientNetworkInterface::startRead()
{
    //qDebug() << "start reading...";
    QDataStream in;
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    in.startTransaction();
    QString readString;
    in >> readString;
    if (in.commitTransaction())
    {
        //receive completely
        //qDebug() << "read completely : " + readString;
        std::vector<QString> afterSplit = spliter->split(readString);
        for (auto message : afterSplit)
            emit receiveCommand(message);

        startSend();
    }
    else {
        //qDebug() << "read not completely";
    }
}

void ClientNetworkInterface::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
        {
            break;
        }
        case QAbstractSocket::HostNotFoundError:
        {
            qDebug() << "Network Error: server was not found!";
            break;
        }
        default:
        {
            qDebug() << tr("The following error occured : %1").arg(tcpSocket->errorString());
        }
    }
}

QString ClientNetworkInterface::test() {
    qDebug() << "Using test method in qml...";
    return "5";
}

void ClientNetworkInterface::disconnected()
{
    qDebug() << "Socket disconnected...";
}
