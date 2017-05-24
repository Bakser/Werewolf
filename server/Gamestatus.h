#ifndef Gamestatus_H
#define Gamestatus_H
#include "eventhandler.h"
#include "Handler.h"
#include "Game.h"
class Game;
class Player{
    private:
        QString role;
    public:
        bool said,voted,special;
        QString lastvote,username;
        Player(QString,QString);
        void handle(QString);
};
class Gamestatus{
    private:
        std::vector<int>setting;
        std::map<QString,bool>cap;
        Game* game;
    public:
        std::vector<QString>playerid;
        std::map<QString,bool>alive,used1,used2;
        std::map<QString,Player*>player;
        std::map<QString,std::vector<Player*>>roleplayer;
        std::map<QString,QString>role;
        Gamestatus(std::vector<QString>,std::vector<int>,Game*);
        QString showonestatus(QString);
        QString showalivestatus();
        QString showallstatus();
        bool canbroad(QString,QString,bool=0);
        int judgeend();
        int die(QString,bool,int);
        void changecap(QString);
        QString vote(std::vector<Player*>);
};
#endif