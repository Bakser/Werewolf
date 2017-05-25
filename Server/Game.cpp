#include "Game.h"
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include <qtimer.h>
#include <qeventloop.h>
Game::Game(std::vector<QString> _users,std::vector<int> setting,ServerNetworkInterface* _networkInterface,RoomHandler* _room){
    networkInterface=_networkInterface;
    room=_room;
    users=_users;
    status=new Gamestatus(_users,setting,this);
}
bool Game::canHandle(QString message){
    return 1;
}
EventHandler* Game::selectHandler(QString message){
    std::cerr<<"Yao Shou La"<<std::endl;
    return this;
}
bool Game::judgewait(){
    for(auto i:waitVote)
        if(!i->voted)
            return 0;
    for(auto i:waitMessage)
        if(!i->said)
            return 0;
    for(auto i:waitSpecial)
        if(!i->special)
            return 0;
    for(auto i:waitVote)
        i->voted=0;
    for(auto i:waitMessage)
        i->said=0;
    for(auto i:waitSpecial)
        i->special=0;
    //waitVote=waitMessage=waitSpecial=std::vector<Player*>();
    return 1;
}
void Game::set(QString username,bool vote,bool say,QString channel=QString("Room")){
    sendMessage(username,QString("Set\n")+(vote?QString("1 "):QString("0 "))+(say?QString("1 "):QString("0 "))+channel);
}
void Game::report(QString username){
    sendMessage(username,QString("Status\n")+status->showonestatus(username)+status->showalivestatus());
}
void Game::reportall(){
    for(auto c:status->playerid)
        report(c);
}
void Game::startAwaitsession(int msec){
    QTimer *timer = new QTimer(this);
    timer->setInterval(msec);
    QEventLoop *loop = new QEventloop(this);
    timer->start();
    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
    connect(this, SIGNAL(receiveOK()), loop, SLOT(quit()));
    loop->exec();
}
void Game::broadcast(QString type,QString message,bool f=0){
    if(type==QString("Allalive")){
        for(auto c:users)
            if(status->alive[c])
                sendMessage(c,message);
        return;
    }
    for(auto c:users)
        if(status->canbroad(c,type,f))
            sendMessage(c,message);
}
void Game::handle(QString username,QString message){
    if(message[0]=='w'&&message[4]=='c')
        broadcast(QString("werewolf"),message,1);
    status->player[username]->handle(message);
    if(judgewait())
        emit receiveOK();
}
QString Game::askforonevote(QString username,QString info,int msec=10000){//这里的计时请client调小点自己计，务必不要在计时结束后发包
    set(username,1,0);
    waitVote=waitMessage=std::vector<Player*>();
    waitVote.push_back(status->player[username]);
    if(info.length())
        sendMessage(username,info);
    startAwaitsession(msec);
    set(username,0,0);
    return status->player[username]->lastvote;
}
bool Game::askforonemessage(QString username,QString channel,QString info,int msec=10000){
    set(username,0,1,channel);
    waitVote=waitMessage=std::vector<Player*>();
    waitMessage.push_back(status->player[username]);
    if(info.length())
        sendMessage(username,info);
    startAwaitsession(msec);
    set(username,0,0);
    return 1;
}
void Game::closeall(){
    for(auto c:users)
        set(c,0,0);
}
int Game::deadclear(std::vector<QString> buffer,int say){
    if(buffer.empty())return 0;
    QString tmp=QString("Die\n");
    for(auto c:buffer){
        tmp+=nameform(c);
        sendMessage(c,"Youdie");
    }
    if(say!=2)room->broadcast(tmp);
    for(auto c:buffer)
        if(status->role[c]==QString("hunter")&&!poied[c]){
            QString tmp=askforonevote(c,"Carry");

            if(tmp.length()){
                deadclear(std::vector<QString>(1,tmp),2);
                room->broadcast(QString("Hunter\n")+nameform(c)+nameform(tmp));
            }
        }
    for(auto c:buffer)
        if(status->cap[c]){
            room->broadcast("Captaindie");
            QString tmp=askforonevote(c,"Pass");
            room->broadcast(QString("Captian\n")+nameform(tmp));
            if(tmp.length())
                status->changecap(tmp);
        }
    if(say){
        for(auto c:buffer)
            askforonemessage(c,"Room","Tellsth");
    }
    int res=0;
    for(auto c:buffer)
        res=std::max(res,status->die(c));
    reportall();
    return res;
}
QString Game::allvote(QString info,int msec){
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:users)
        if(status->alive[c])
            waitVote.push_back(status->player[c]);
    if(info.length())
        broadcast("Allalive",info);
    broadcast("Allalive","Set\n1 0 Room");
    startAwaitsession(10000);
    broadcast("Allalive","Set\n0 0 Room");
    return status->vote(waitVote);
}
int Game::dayround(int rn){
    room->broadcast(QString("Day ")+IntToStr(rn>>1));
    closeall();
    int tmp=deadclear(deadbuffer,rn==1);
    deadbuffer.clear();
    QString t;
    if(tmp)return tmp;
    tmp=deadclear(deadbuffer,1);
    if(rn==1){
        t=allvote("",10000);
        if(t[0]=='@')
            t=QString("");
        else status->changecap(t);
        broadcast("Allalive",QString("Captain\n")+nameform(t));
    }
    srand(time(0));
    int order=rand()&1,s=0,n=users.size();QString cap("");
    for(auto c:users)
        if(status->alive[c]&&status->cap[c]){
            cap=c;
            askforonevote(c,"Order");
            order=status->player[c]->lastvote[0]=='1';
        }
    if(cap.length()){
        for(int i(0);i<n;i++)
            if(users[i]==cap)
                s=i;
    }
    order=!order?-1:1;
    for(int i((s+order+n)%n);i!=s;i=(i+order+n)%n)
        askforonemessage(users[i],"Room","",15000);
    if(cap.length()) askforonemessage(cap,"Room","",20000);
    else askforonemessage(users[0],"Room","",15000);
    t=allvote("Vote",10000);
    if(t[0]=='@'){
        broadcast("Allalive",QString("Equal\n")+t);
        t=allvote("Vote",10000);
        if(t[0]!='@')
            deadbuffer.push_back(t);
    }
    else deadbuffer.push_back(t);
    tmp=deadclear(deadbuffer,1);
    if(tmp)return tmp;
}
int Game::nightround(int rn){
    room->broadcast(QString("Night ")+IntToStr(rn>>1));
    reportall();
    closeall();
    static std::map<QString,bool> guarded,killed,saved,poisoned;
    guarded.clear();killed.clear();saved.clear();poisoned.clear();
    static QString tmp;
    //守卫
    for(auto c:status->roleplayer[QString("defender")])
        if(status->alive[c->username]){
            tmp=askforonevote(c->username,QString("Guard"));
            if(tmp.length())
                guarded[tmp]=1;
        }
    //狼人
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:status->roleplayer[QString("werewolf")])
        if(status->alive[c->username])
            waitVote.push_back(c);
    for(auto c:waitVote)
        set(c->username,1,1,QString("Wolf"));
    startAwaitsession(30000);
    for(auto c:waitVote)
        set(c->username,0,0);
    tmp=status->vote(waitVote);
    if(tmp[0]!='@')
        killed[tmp]=1;
    //女巫
    static QString killd=tmp;
    for(auto c:status->roleplayer[QString("witch")])
        if(status->alive[c->username]){
            if(!status->used1[c->username]){
                tmp=askforonevote(c->username,QString("Witch\n@")+killd);
                if(tmp.length())
                    saved[tmp]=1,status->used1[c->username]=1;
            }
            if(!status->used2[c->username]){
                tmp=askforonevote(c->username,QString("Witch"));
                if(tmp.length())
                    poisoned[tmp]=1,status->used2[c->username]=1;
            }
        }
    //预言家
    for(auto c:status->roleplayer[QString("prophet")])
        if(status->alive[c->username]){
            tmp=askforonevote(c->username,QString("Prophet"));
            if(tmp.length())
                sendMessage(c->username,(status->role[tmp]==QString("werewolf")?QString("Bad"):QString("Good")));
        }
    for(auto c:users)
        if((killed[c]&&(int(guarded[c])+int(saved[c])!=1))||poisoned[c])
            deadbuffer.push_back(c),poied[c]=1;
    return 0;
}
void Game::run(){
    int res=0;
    for(int round=0;;round++){
        if(round&1)res=dayround(round);
        else res=nightround(round);
        if(res)
            break;
    }
    room->broadcast("GameEnded");
    this->broadcast("werewolf",res==1?"YouWin":"YouLose",1);
    for(auto c:users)
        if(!status->canbroad(c,"werewolf",1))
            sendMessage(c,res==1?"YouLose":"YouWin");
    room->broadcast(QString("EndStatus\n")+status->showallstatus());
}
