#ifndef ServerCenter_H
#define ServerCenter_H
#include "servernetworkinterface.h"
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
QString IntToStr(int);
QString nameform(QString x);
class Game;
class RoomHandler;
//服务器数据交换中心
class ServerCenter:public EventHandler{
    protected:
        std::map<int,RoomHandler*> Rooms;             //保存RoomHandler的map
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
    public:
        ServerCenter()=default;
        ServerCenter(ServerNetworkInterface*);
};
#endif
