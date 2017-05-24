#ifndef Handler_H
#define Handler_H
#include "ServerNetworkInterface.h"
#include "eventhandler.h"
#include "Game.h"
#include "Gamestatus.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
QString IntToStr(int x){
    return QString::number(x);
}
QString nameform(QString x){
    if(x[0]=='@')return x;
    return QString("@")+x+QString("\n");
}
// class EventHandler{
//     protected:
//         ServerNetworkInterface* networkInterface;
//     private:
//         virtual bool canHandle(QString)=0;
//         virtual EventHandler* selectHandler(QString)=0;
//         void sendMessage(QString,QString);
//         virtual void handle(QString,QString)=0;
//         int parseToInt(QString);
//     public:
//         void tryHandle(QString,QString);
// };
class Game;
class ServerCenter:public EventHandler{
    protected:
        std::map<int,EventHandler*> Rooms;
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
    public:
        ServerCenter()=default;
        ServerCenter(ServerNetworkInterface*);
};
class RoomHandler:public EventHandler{
    private:
        int readycnt;
        bool gamestarted;
        QString owner;
        std::map<QString,bool>ready;
        std::vector<int>setting;
        Game* game;
        std::vector<QString> users;
        bool EnterRoom(QString);
        bool LeaveRoom(QString);
        bool canStart();
        QString get_status();
        void flush();
        void buildroom();
        void startgame();
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
    public:
        void broadcast(QString);
        RoomHandler();
        RoomHandler(ServerNetworkInterface*);
};
#endif