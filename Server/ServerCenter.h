#ifndef ServerCenter_H
#define ServerCenter_H
#include "ServerNetworkInterface.h"
#include "eventhandler.h"
#include "Game.h"
#include "Gamestatus.h"
#include "RoomHandler.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
/*
QString IntToStr(int x){
    return QString::number(x);
}
QString nameform(QString x){
    if(x[0]=='@')return x;
    return QString("@")+x+QString("\n");
}
*/
QString IntToStr(int);
QString nameform(QString x);
class Game;
class RoomHandler;
class ServerCenter:public EventHandler{
    protected:
        std::map<int,RoomHandler*> Rooms;
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
        //ServerNetworkInterface *networkInterface;
    public:
        ServerCenter()=default;
        ServerCenter(ServerNetworkInterface*);
        //void sendMessage(QString, QString);
};
#endif
