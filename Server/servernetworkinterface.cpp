#include "servernetworkinterface.h"
#include <QSignalMapper>
#include <QDataStream>
#include <QByteArray>
#include <cassert>

ServerNetworkInterface::ServerNetworkInterface(EventHandler* handler, QObject* parent) : QObject(parent)
{
    mainHandler = handler;
    tcpServer = new QTcpServer(this);
    //tcpServer->listen(QHostAddress::LocalHost, 6666);
    tcpServer->listen(QHostAddress("101.6.163.75"), 6666);
    //QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    /*
    qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                   "Run the Fortune Client example now.")
                .arg(ipAddress).arg(tcpServer->serverPort());
    */
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(handleConnection()));
    spliter = new DollarSpliter();
}

ServerNetworkInterface::~ServerNetworkInterface()
{
    delete tcpServer;
    delete spliter;
}

void ServerNetworkInterface::handleConnection()
{
    qDebug() << "A new connection found...";
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    //get socket
    //QSignalMapper *signalMapper;
    /*
    signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(tcpSocket, tcpSocket);
    connect(tcpSocket, SIGNAL(disconnected()), signalMapper, SLOT(map()));
    connect(signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(disconnected(QObject*)));
    delete signalMapper;
    */
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    /*
    signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(tcpSocket, tcpSocket);
    connect(tcpSocket, SIGNAL(readyRead()), signalMapper, SLOT(map()));
    connect(signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(startRead(QObject*)));
    delete signalMapper;
    */
    //link connections
    //connect(tcpSocket, SIGNAL(disconnected()), tcpSocket, SLOT(deleteLater()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(startRead()));
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
                    this, &ServerNetworkInterface::displayError);
    qDebug() << "Socket connected successfully...";
    //delete after disconnected
}

void ServerNetworkInterface::startRead()
{
    QTcpSocket *tcpSocket = (QTcpSocket*)sender();
    startRead(tcpSocket);
}

void ServerNetworkInterface::startRead(QTcpSocket* tcpSocket)
{
    //qDebug() << "start reading...";
    //QTcpSocket *tcpSocket = qobject_cast<QTcpSocket*>(object);
    //QTcpSocket *tcpSocket = (QTcpSocket*)sender();
    if (tcpSocket)
    {
        //qDebug() << "start reading from user " + socketUserName[tcpSocket];
        QDataStream in;
        in.setVersion(QDataStream::Qt_4_0);
        in.setDevice(tcpSocket);
        in.startTransaction();
        QString readString;
        in >> readString;
        //qDebug() << "Receive " << readString << " from client.";
        if (!in.commitTransaction())
        {
            //qDebug() << "Not complete!";
            return;
        }
        //qDebug() << "Read all OK!";
        if (readString != "")
        {
            if (socketUserName.find(tcpSocket) != socketUserName.end())
                qDebug() << "#Receive message : " + readString + " from user " + socketUserName[tcpSocket];
            //handle login session...
            if (readString.mid(0, 5) == "login") {
                qDebug() << "Login command found...";
                QString userName = readString.mid(6, readString.length() - 6);
                //collison check
                if (userNameSocket.find(userName) != userNameSocket.end())
                {
                    qDebug() << "Same username has existed!";
                    //collide!
                    //for now, just disconnect at once
                    tcpSocket->disconnectFromHost();
                }
                else
                {
                    //create user and update map
                    userNameSocket[userName] = tcpSocket;
                    socketUserName[tcpSocket] = userName;
                    sendMessage(userName, "login ok");
                    //qDebug() << "Line 81";
                }
            }
            else
            {
                //have logged in successfully, handle commands
                std::vector<QString> afterSplit = spliter->split(readString);
                QString userName = socketUserName[tcpSocket];
                for (auto message : afterSplit)
                    mainHandler->tryHandle(userName, message);
            }
        }

        //complete reading, start writing
        startSend(tcpSocket);
    }
    else
    {
        //never use
        qDebug() << "TcpSocket isn't exist...";
    }

}

void ServerNetworkInterface::sendMessage(QString userName, QString message)
{
    qDebug() << "Send message " + message + " to user " + userName;
    /*
    //assert(userNameSocket.find(userName) != userNameSocket.end());
    qDebug() << "1";
    //for (auto c : userNameSocket)
    //    qDebug() << c.first << " " << c.second;
    QTcpSocket *tcpSocket = userNameSocket[userName];
    qDebug() << "2";
    assert(socketClientStatus.find(tcpSocket) != socketClientStatus.end());
    qDebug() << "2";
    qDebug() << "pre sendString = " + socketClientStatus[tcpSocket].getNextSendString();
    qDebug() << "3";
    socketClientStatus[userNameSocket[userName]].addSendString(message);
    qDebug() << "4";
    qDebug() << "end sendString = " + socketClientStatus[tcpSocket].getNextSendString();
    */

    QTcpSocket *tcpSocket = userNameSocket[userName];
    startSend(tcpSocket, message);
    /*
    qDebug() << "~Send message " << tcpSocket->bytesToWrite() << " bytes to write...";
    if (tcpSocket->isWritable())
        qDebug() << "writable";
    else
        qDebug() << "not writable";
    if (tcpSocket->errorString() != "")
        qDebug() << "Error: " << tcpSocket->errorString();
    */
}

void ServerNetworkInterface::startSend(QTcpSocket *tcpSocket, QString message)
{
    //qDebug() << "start sending...";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    /*
    if (message != "")
    {
        qDebug() << "case0";
    }
    */
    out << message;
    /*
    if (message != "")
    {
        qDebug() << "case1";
        qDebug() << "~Send message " << tcpSocket->bytesToWrite() << " bytes to write...";
        if (tcpSocket->isWritable())
            qDebug() << "writable";
        else
            qDebug() << "not writable";
        if (tcpSocket->errorString() != "")
            qDebug() << "Error: " << tcpSocket->errorString();
    }
    */
    tcpSocket->write(block);
    /*
    if (message != "")
    {
        qDebug() << "~Send message " << tcpSocket->bytesToWrite() << " bytes to write...";
        if (tcpSocket->isWritable())
            qDebug() << "writable";
        else
            qDebug() << "not writable";
        if (tcpSocket->errorString() != "")
            qDebug() << "Error: " << tcpSocket->errorString();
    }
    */
    startRead(tcpSocket);
}

void ServerNetworkInterface::disconnected()
{

    //QTcpSocket *tcpSocket = qobject_cast<QTcpSocket*>(object);
    QTcpSocket *tcpSocket = (QTcpSocket*)sender();
    QString userName = socketUserName[tcpSocket];
    qDebug() << "User " + userName + " disconnected from server.";
    //update map
    userNameSocket.erase(userNameSocket.find(userName));
    socketUserName.erase(socketUserName.find(tcpSocket));
    tcpSocket->deleteLater();
}

void ServerNetworkInterface::displayError(QAbstractSocket::SocketError socketError)
{
    QTcpSocket *tcpSocket = (QTcpSocket*)sender();
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
