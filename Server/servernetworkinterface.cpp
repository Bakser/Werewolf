#include "servernetworkinterface.h"
#include <QSignalMapper>
#include <QDataStream>
#include <QByteArray>

ServerNetworkInterface::ServerNetworkInterface(EventHandler* handler, QObject* parent) : QObject(parent)
{
    mainHandler = handler;
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::LocalHost, 6666);
    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                   "Run the Fortune Client example now.")
                .arg(ipAddress).arg(tcpServer->serverPort());
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
        //qDebug() << "start reading from user " + socketClientStatus[tcpSocket].getUserName();
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
            qDebug() << "#Receive message : " + readString + " from user " + socketClientStatus[tcpSocket].getUserName();
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
                    socketClientStatus[tcpSocket] = ClientStatus(userName);
                    sendMessage(userName, "login ok");
                    //qDebug() << "Line 81";
                }
            }
            else
            {
                //have logged in successfully, handle commands
                std::vector<QString> afterSplit = spliter->split(readString);
                QString userName = socketClientStatus[tcpSocket].getUserName();
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
    socketClientStatus[userNameSocket[userName]].addSendString(message);
}

void ServerNetworkInterface::startSend(QTcpSocket *tcpSocket)
{
    //qDebug() << "start sending...";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    ClientStatus &clientStatus = socketClientStatus[tcpSocket];
    out << clientStatus.getNextSendString();
    clientStatus.clearString();
    tcpSocket->write(block);
    startRead(tcpSocket);
}

void ServerNetworkInterface::disconnected()
{

    //QTcpSocket *tcpSocket = qobject_cast<QTcpSocket*>(object);
    QTcpSocket *tcpSocket = (QTcpSocket*)sender();
    QString userName = socketClientStatus[tcpSocket].getUserName();
    qDebug() << "User " + userName + " disconnected from server.";
    tcpSocket->deleteLater();
    //update map
    userNameSocket.erase(userNameSocket.find(userName));
    socketClientStatus.erase(socketClientStatus.find(tcpSocket));
}
