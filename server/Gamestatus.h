/*
名称：Gamestatus.h
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：定义游戏状态类，存储游戏目前状态的同时支持一些操作，以实现完全异步
版权：全部自行完成
*/
#ifndef Gamestatus_H
#define Gamestatus_H
#include "eventhandler.h"
#include "ServerCenter.h"
#include "RoomHandler.h"
#include "Game.h"
class Game;
class Player{//玩家类，用于存储一个玩家对应的信息
    private:
        QString role;//角色
    public:
        bool said,voted;//是否说过话/投过票（为了支持异步处理）
        QString username,lastvote;//用户ID，上次投票结果
        Player(QString,QString);
        void handle(QString);
};
class Gamestatus{
    private:
        Game* game;//对应的游戏指针
    public:
        std::vector<int>setting;//游戏设置
        std::map<QString,bool>cap;//每个人是不是警长
        std::vector<QString>playerid;//用户ID
        std::map<QString,bool>alive,used1,used2;//每个人是否活着，有没有用过一技能/二技能
        std::map<QString,Player*>player;//用户ID和用户指针对应关系
        std::map<QString,std::vector<Player*> >roleplayer;//每个角色和对应的用户列表
        std::map<QString,QString>role;//用户ID与角色对应关系
        Gamestatus(std::vector<QString>,std::vector<int>,Game*);
        QString showonestatus(QString);//返回一个角色的状态
        QString showalivestatus();//返回活着的人的状态
        QString showallstatus();//返回所有人的状态
        bool canbroad(QString,QString,bool);//判断这条消息逻辑上是否能对该用户播报
        int judgeend();//判断游戏是否结束
        int die(QString);//处理某个用户死亡
        void changecap(QString);//更换警长
        QString vote(std::vector<Player*>);//结算一些用户投票的结果
};
#endif
