#ifndef CLIENTSTATUS_H
#define CLIENTSTATUS_H

#include <QString>

class ClientStatus
{
public:
    ClientStatus();
    ClientStatus(QString);
    ~ClientStatus();
    void addSendString(QString);
    void clearString();
    QString getNextSendString();
    QString getUserName();
private:
    QString userName, nextSendString;
};

#endif // CLIENTSTATUS_H
