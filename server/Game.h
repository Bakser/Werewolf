/*
名称：Game.h
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：定义游戏逻辑类，所有过程完全异步
版权：全部自行完成
*/
#ifndef Game_H
#define Game_H
#include "eventhandler.h"
#include "RoomHandler.h"
#include "Gamestatus.h"
#include <queue>
class Gamestatus;
class Player;
class Game: public EventHandler{
    protected:
        RoomHandler* room;//这局游戏对应的房间指针，用于调用房间广播等接口
        Gamestatus* status;//指向对应游戏状态类的指针
        std::vector<QString>users;//这局游戏的玩家
        std::vector<Player*> waitVote,waitMessage;//等待收到这些玩家的投票/信息才能进入下一个游戏阶段
        std::vector<QString> deadbuffer;//等待进行死亡结算的玩家
        std::map<QString,bool>poied;//被女巫下毒的玩家
        int stage,round;//当前的阶段/轮数
        std::queue<QString> waitq;//等待发言的玩家队列
        bool hunterflag,capflag,sayflag,voteflag,dclrflag;//当前是否在等待猎人带走人/警长选举/说话/投票/遗言的标记
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
        bool judgewait();//判断是否还在等待事件发生
        void set(QString,bool,bool,QString);//设置客户端对应开关的开闭，参数为 用户ID，是否可以投票，是否可以说话，说话频道
        void report(QString);//向一个指定用户（参数为用户名）报告情况
        void reportall();//向所有用户报告情况
        void broadcast(QString,QString,bool);//游戏内广播信息
        void closeall();//关闭所有客户端的所有功能（投票/说话）
        int deadclr(std::vector<QString>,bool);//死亡结算，返回代表结果的整数值
        int dayround(int);//白天环节
        int nightround(int);//夜晚环节
        void solvecap();//处理警长选举
        void solveq();//处理排队发言
        void solvehunter();//处理猎人崩人
        void gameend(int);//游戏结束结算
        void allvote(QString);//要求全员投票，参数为投票前发送的信息
        QString resforallvote();//全体投票结果
        void askforonevote(QString,QString);//要求某人投票
        QString resforonevote(QString);//某人投票结果
        bool askforonemessage(QString,QString,QString);//要求某人发言
    public:
        Game(std::vector<QString>,std::vector<int>,ServerNetworkInterface*,RoomHandler*);
        void run();
};
#endif
