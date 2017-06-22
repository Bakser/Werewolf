/*
名称：ServerCenter.h
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：定义服务器逻辑的中心类，用于处理创建和选择房间的请求，整个架构完全异步，因此可以同时处理多个房间
版权：全部自行完成
*/
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
QString IntToStr(int);      //将数字转换成QString
QString nameform(QString x);//将用户ID转换成标准向客户端传递的格式
class Game;
class RoomHandler;
class ServerCenter:public EventHandler{
    protected:
        std::map<int,RoomHandler*> Rooms; //房间号和每个房间对应的RoomHandler的映射关系
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
    public:
        ServerCenter()=default;
        ServerCenter(ServerNetworkInterface*);
};
#endif
