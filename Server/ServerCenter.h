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
#endif