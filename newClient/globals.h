#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <vector>
//客户端的全局状态
class Globals
{
public:
    static QString meid;//自己的id
    static int roomnumber;//自己所在房间的号码
    static QString player_id[50];//自己所在房间的玩家列表
    static bool player_alive[50];//自己所在房间玩家的存活情况，1-alive;0-died
    static int nplayer;//自己所在房间玩家数目
    static int merole;//自己的身份
    static bool newGameStarted;//新游戏是否已经开始
    static QString master;//警长id
    static QString lastDefend;//如果是守卫上一晚守了哪位玩家
    static QString meroleString;//自己身份的字符串表示
    static void update(QString);//更新全局状态
    static void reset();//全局状态重置
    static void dieUpdate(QString);
};



#endif // GLOBALS_H
