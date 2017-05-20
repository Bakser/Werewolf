#include "ServerNetworkInterface.h"
#include <map>
#include <vector>
#include <iostream>
Qstring IntToStr(int x){
    stringstream ss;//会否内存泄漏？
    ss<<x;
    return ss.str();
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
        RoomHandler(ServerNetworkInterface*);
};