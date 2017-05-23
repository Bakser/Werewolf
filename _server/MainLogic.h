#include "ServerNetworkInterface.h"
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
Qstring IntToStr(int x){
    stringstream ss;//会否内存泄漏？
    ss<<x;
    return ss.str();
}
Qstring nameform(Qstring x){
    if(x[0]=='@')return x;
    return Qstring("@")+x+Qstring("\n");
}
class EventHandler{
    protected:
        ServerNetworkInterface* networkInterface;
    private:
        virtual bool canHandle(Qstring)=0;
        virtual EventHandler* selectHandler(Qstring)=0;
        void sendMessage(Qstring,Qstring);
        virtual void handle(Qstring,Qstring)=0;
        int parseToInt(Qstring);
    public:
        void tryHandle(Qstring,Qstring);
};
class ServerCenter:public EventHandler{
    protected:
        map<int,EventHandler*> Rooms;
    private:
        virtual bool canHandle(Qstring);
        virtual EventHandler* selectHandler(Qstring);
        virtual void handle(Qstring,Qstring);
    public:
        ServerCenter(ServerNetworkInterface*);
};
class RoomHandler:public EventHandler{
    private:
        int readycnt;
        bool gamestarted;
        Qstring owner;
        map<Qstring,bool>ready;
        vector<int>setting;
        Game* game;
        vector<Qstring> users;
        bool EnterRoom(Qstring);
        bool LeaveRoom(Qstring);
        bool canStart();
        Qstring get_status();
        void flush();
        void buildroom();
        void startgame();
        virtual bool canHandle(Qstring);
        virtual EventHandler* selectHandler(Qstring);
        virtual void handle(Qstring,Qstring);
    public:
        void broadcast(Qstring);
        RoomHandler(ServerNetworkInterface*);
};
class Player{
    private:
        Qstring role;
    public:
        bool said,voted,special;
        Qstring lastvote,username;
        Player(Qstring,Qstring);
        void handle(Qstring);
};
class Gamestatus{
    private:
        vector<int>setting;
        map<Qstring,bool>cap;
        Game* game;
    public:
        vector<Qstring>playerid;
        map<Qstring,bool>alive,used1,used2;
        map<Qstring,Player*>player;
        map<Qstring,vector<Player*>>roleplayer;
        map<Qstring,Qstring>role;
        Gamestatus(vector<Qstring>,vector<int>,Game*);
        Qstring showonestatus(Qstring);
        Qstring showalivestatus();
        Qstring showallstatus();
        bool canbroad(Qstring,Qstring,bool=0);
        int judgeend();
        int die(Qstring,bool,int);
        void changecap(Qstring);
        Qstring vote(vector<Player*>);
};
class Game:public EventHandler{
    Q_OBJECT
    protected:
        ServerNetworkInterface* networkInterface;
        EventHandler* room;
        Gamestatus* status;
        vector<Qstring>users;
        vector<Player*>waitVote,waitMessage,waitSpecial;
        vector<Qstring>deadbuffer;
        map<Qstring,bool>poied;
    private:
        virtual bool canHandle(Qstring);
        virtual EventHandler* selectHandler(Qstring);
        virtual void handle(Qstring,Qstring);
        bool judgewait();
        void set(Qstring,bool,bool,Qstring channel=Qstring("Room"));//vote say
        void report(Qstring);
        void reportall(Qstring);
        void startAwaitsession(int);
        void broadcast(Qstring,Qstring,bool=0);
        void closeall();
        int deadclear(vector<Qstring>,bool);
        int dayround(int);
        int nightround(int);
        Qstring Game::allvote(Qstring,int);
    public:
        Game(vector<Qstring>,vector<int>,ServerNetworkInterface*,EventHandler*);
        Qstring askforonevote(Qstring,Qstring,int=10000);//user info
        bool askforonemessage(Qstring,Qstring,Qstring,int=10000);//username channel info
        void run();
    signal:
        void receiveOK();
};