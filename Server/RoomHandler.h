/*
名称：RoomHandler.cpp
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：定义类RoomHandler（继承EventHandler），用于处理房间阶段的用户请求并给出指示
版权：全部自行完成
*/
#ifndef RoomHandler_H
#define RoomHandler_H
#include "servernetworkinterface.h"
#include "eventhandler.h"
#include "Game.h"
#include "Gamestatus.h"
#include "ServerCenter.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
class Game;
class RoomHandler:public EventHandler{
    private:
        int readycnt;               //计数有多少用户已经准备好
        bool gamestarted;           //标记游戏是否已经开始
        QString owner;              //存储房主姓名
        std::map<QString,bool>ready;//记录每个用户是否已经准备
        std::vector<int>setting;    //记录房主指定的游戏设置（各角色人数等）
        Game* game;                 //Game类的指针，指向这个房间正在进行的游戏
        std::vector<QString> users; //记录房间内用户ID
        bool EnterRoom(QString);    //处理用户进入房间
        void LeaveRoom(QString);    //处理用户离开房间
        bool canStart();            //判断是否满足游戏开始条件
        QString get_status();       //生成当前状态，用于向客户端报告
        void flush();               //向客户端报告状态信息
        void buildroom(QString);    //处理房主建立房间的过程
        void startgame();           //处理游戏开始
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
    public:
        void broadcast(QString);    //房间内广播信息
        RoomHandler();
        RoomHandler(ServerNetworkInterface*);
};
#endif
