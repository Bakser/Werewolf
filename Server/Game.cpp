#include "Game.h"
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include <qtimer.h>
#include <queue>
#include <qeventloop.h>
const int DebugMulti=10;
Game::Game(std::vector<QString> _users,std::vector<int> setting,ServerNetworkInterface* _networkInterface,RoomHandler* _room){
    networkInterface=_networkInterface;
    room=_room;
    users=_users;
    status=new Gamestatus(_users,setting,this);
    stage=round=0;
    hunterflag=capflag=sayflag=voteflag=0;
}

/*
void Game::sendMessage(QString username, QString message){
    //room->sendMessage(username,message);
    networkInterface->sendMessage(username, message);
}
*/
bool Game::canHandle(QString message){
    return 1;
}
EventHandler* Game::selectHandler(QString message){
    qDebug()<<"Yao Shou La";
    return this;
}
bool Game::judgewait(){
    for(auto i:waitVote)
        if(!i->voted)
            return 0;
    for(auto i:waitMessage)
        if(!i->said)
            return 0;
    for(auto i:waitVote)
        i->voted=0;
    for(auto i:waitMessage)
        i->said=0;
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
/*
void Game::startAwaitsession(int msec){
    msec*=DebugMulti;
    QTimer *timer = new QTimer(this);
    timer->setInterval(msec);
    QEventLoop *loop = new QEventLoop(this);
    timer->start();
    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
    connect(this, SIGNAL(receiveOK()), loop, SLOT(quit()));
    qDebug() << "connect loop-end signal successfully";
    loop->exec();
    delete timer;
    delete loop;
}*/
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
    if(judgewait()){
        sayflag=0;
        if(hunterflag)solvehunter();
        if(capflag)solvecap();
        if(!waitq.empty())solveq();
        if(!capflag&&!hunterflag&&waitq.empty()){
            stage+=2;
            run();
        }
    }
}
void Game::askforonevote(QString username,QString info,int msec=10000){//这里的计时请client调小点自己计，务必不要在计时结束后发包
    set(username,1,0);
    waitVote=waitMessage=std::vector<Player*>();
    waitVote.push_back(status->player[username]);
    if(info.length())
        sendMessage(username,info);
    //startAwaitsession(msec);
    //set(username,0,0);
    //return status->player[username]->lastvote;
}
QString Game::resforonevote(QString username){
    set(username,0,0);
    return status->player[username]->lastvote;
}
bool Game::askforonemessage(QString username,QString channel,QString info,int msec=10000){
    set(username,0,1,channel);
    waitVote=waitMessage=std::vector<Player*>();
    waitMessage.push_back(status->player[username]);
    if(info.length())
        sendMessage(username,info);
    //startAwaitsession(msec);
    //set(username,0,0);
    return 1;
}
/*
void Game::resforonemessage(QString username){
    set(username,0,0);
}*/
void Game::closeall(){
    qDebug()<<"closeall "<<users.size();
    for(auto c:users)
        set(c,0,0);
}
int Game::deadclr(std::vector<QString> buffer,bool flag=0){
    if(buffer.empty())return 0;
    QString tmp=QString("Die\n");
    for(auto c:buffer){
        tmp+=nameform(c);
        sendMessage(c,"Youdie");
    }
    room->broadcast(tmp);
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:buffer)
        if(status->role[c]==QString("hunter")&&!poied[c]){
            sendMessage(c,"Carry");
            set(c,1,0);
            hunterflag=1;
            waitVote.push_back(status->player[c]);
        }
    for(auto c:buffer)
        if(status->cap[c]){
            room->broadcast("Captaindie");
            sendMessage(c,"Pass");
            set(c,1,0);
            capflag=1;
            waitVote.push_back(status->player[c]);
        }
    int res=0;
    for(auto c:buffer)
        res=std::max(res,status->die(c));
    reportall();
    if(flag){
        for(auto c:buffer){
            sendMessage(c,"Tellsth");
            set(c,((status->role[c]==QString("hunter")&&!poied[c])||status->cap[c]),1,"Room");
            sayflag=1;
            waitMessage.push_back(status->player[c]);
        }
    }
    return res;
}
void Game::solvehunter(){
    for(auto c:users)
        if(status->role[c]==QString("hunter")){
            hunterflag=0;
            QString x=status->player[c]->lastvote;
            if(x.length()){
                room->broadcast(QString("Hunter\n")+nameform(c)+nameform(x));
                deadclr(std::vector<QString>(1,x),1);
            }
        }
}
void Game::solvecap(){
    for(auto c:users)
        if(status->cap[c]){
            capflag=0;
            QString x=status->player[c]->lastvote;
            room->broadcast(QString("Captian\n")+nameform(x));
            if(x.length())
                status->changecap(x);
        }
}
void Game::solveq(){
    QString x=waitq.front();waitq.pop();
    if(waitMessage.size()){
        set(waitMessage[0]->username,0,0);
        waitMessage.clear();
    }
    waitMessage.push_back(status->player[x]);
    set(x,0,1,"Room");
}
void Game::allvote(QString info,int msec){
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:users)
        if(status->alive[c])
            waitVote.push_back(status->player[c]);
    if(info.length())
        broadcast("Allalive",info);
    broadcast("Allalive","Set\n1 0 Room");
    //startAwaitsession(10000);
}
QString Game::resforallvote(){
    broadcast("Allalive","Set\n0 0 Room");
    return status->vote(waitVote);
}
//spflag 1-hunter 2-capdie 3-choose cap 4-equal
int Game::dayround(int rn){
    srand(time(0));
    int order=rand()&1,s=0,n=users.size();
    QString cap("");
    if(stage==1){
        qDebug() << "dayround #" << rn;
        room->broadcast(QString("Day ")+IntToStr(rn>>1));
        closeall();
        int tmp=deadclr(deadbuffer,rn==1);
        deadbuffer.clear();
        if(tmp)return tmp;
        if(rn==1){
            while(!waitq.empty())waitq.pop();
            for(int i(0);i<n;i++)
                waitq.push(users[i]);
            solveq();
        }
        return 0;
    }
    if(stage==3){
        if(rn==1&&!voteflag){
            allvote("ChooseCap",10000);
            voteflag=1;
            return 0;
        }
        if(rn==1&&voteflag){
            voteflag=0;
            QString t=resforallvote();
            if(t[0]=='@')
                t=QString("");
            else status->changecap(t);
            broadcast("Allalive",QString("Captain\n")+nameform(t));
        }
        for(auto c:users)
            if(status->alive[c]&&status->cap[c]){
                cap=c;
                askforonevote(c,"Order");
            }
        return 0;
    }
    if(stage==5){
        for(auto c:users)
            if(status->alive[c]&&status->cap[c])
                cap=c;
        if(cap.length()){
            order=status->player[cap]->lastvote[0]=='1';
            for(int i(0);i<n;i++)
                if(users[i]==cap)
                    s=i;
        }
        order=!order?-1:1;
        while(!waitq.empty())waitq.pop();
        for(int i((s+order+n)%n);i!=s;i=(i+order+n)%n)
            waitq.push(users[i]);
            //askforonemessage(users[i],"Room","");
        if(cap.length()) waitq.push(cap);
        else waitq.push(users[0]);
        solveq();
        return 0;
    }
    if(stage==7){
        if(!voteflag){
            allvote("Vote",10000);
            voteflag=1;
            return 0;
        }
        if(voteflag){
            voteflag=0;
            QString t=resforallvote();
            if(t[0]=='@'){
                broadcast("Allalive",QString("Equal\n")+t);
                voteflag=1;
                allvote("Vote",10000);
                return 0;
            }
            else deadbuffer.push_back(t);
            return 0;
        }
    }
    if(stage==9){
        int tmp=deadclr(deadbuffer,1);
        stage=0;
        round++;
        if(tmp)return tmp;
        return 0;
    }
}
int Game::nightround(int rn){
    static std::map<QString,bool> guarded,killed,saved,poisoned;
    //guarded.clear();killed.clear();saved.clear();poisoned.clear();
    if(stage==0){
        qDebug() << "nightround #" << rn;
        room->broadcast(QString("Night ")+IntToStr(rn>>1));
        reportall();
        closeall();
    //守卫
        for(auto c:status->roleplayer[QString("defender")])
            if(status->alive[c->username]){
                askforonevote(c->username,QString("Guard"));
                //if(tmp.length())
                    //guarded[tmp]=1;
            }
        return 0;
    }
    if(stage==2){
        for(auto c:status->roleplayer[QString("defender")])
            if(status->alive[c->username]){
                QString tmp=resforonevote(c->username);
                if(tmp.length())
                    guarded[tmp]=1;
            }
        qDebug()<<"Guarded";
        waitVote=waitMessage=std::vector<Player*>();
        for(auto c:status->roleplayer[QString("werewolf")])
            if(status->alive[c->username])
                waitVote.push_back(c);
        for(auto c:waitVote)
            set(c->username,1,1,QString("Wolf"));
        return 0;
    }
    if(stage==4){
        //startAwaitsession(30000);
        for(auto c:waitVote)
            set(c->username,0,0);
        QString tmp=status->vote(waitVote);
        if(tmp[0]!='@')
            killed[tmp]=1;
        else tmp=QString("");
        qDebug()<<"Wolfed";
        QString killd=tmp;
       for(auto c:status->roleplayer[QString("witch")])
            if(status->alive[c->username]&&!status->used1[c->username])
                askforonevote(c->username,QString("Witch\n@")+killd);
       return 0;
     }
    if(stage==6){
        for(auto c:status->roleplayer[QString("witch")])
            if(status->alive[c->username]&&!status->used1[c->username]){
                QString tmp=resforonevote(c->username);
                if(tmp.length())
                    saved[tmp]=1,status->used1[c->username]=1;
            }
        qDebug()<<"Witch1";
        for(auto c:status->roleplayer[QString("witch")])
            if(status->alive[c->username]&&!status->used2[c->username])
                askforonevote(c->username,QString("Witch"));\
        return 0;
    }
    if(stage==8){
       for(auto c:status->roleplayer[QString("witch")])
           if(status->alive[c->username]&&!status->used2[c->username]){
               QString tmp=resforonevote(c->username);
               if(tmp.length())
                   poisoned[tmp]=1,status->used2[c->username]=1;
           }
        qDebug()<<"Witched2";
        for(auto c:status->roleplayer[QString("prophet")])
            if(status->alive[c->username])
                askforonevote(c->username,QString("Prophet"));
        return 0;
    }
    if(stage==10){
        for(auto c:status->roleplayer[QString("prophet")])
            if(status->alive[c->username]){
                QString tmp=resforonevote(c->username);
                if(tmp.length())
                    sendMessage(c->username,((status->role[tmp]==QString("werewolf"))?QString("Bad"):QString("Good")));
            }
        qDebug()<<"Propheted";
        for(auto c:users)
            if((killed[c]&&(int(guarded[c])+int(saved[c])!=1))||poisoned[c])
                deadbuffer.push_back(c),poied[c]=poisoned[c];
        stage=1;
        round++;
        guarded.clear();killed.clear();saved.clear();poisoned.clear();
        return 0;
    }
}
void Game::gameend(int res){
    room->broadcast("GameEnded");
    this->broadcast("werewolf",res==1?"YouWin":"YouLose",1);
    for(auto c:users)
        if(!status->canbroad(c,"werewolf",1))
            sendMessage(c,res==1?"YouLose":"YouWin");
    room->broadcast(QString("EndStatus\n")+status->showallstatus());
}
void Game::run(){
    qDebug()<<"Run";
    int res=0;
    /*
    for(int round=0;;round++){
        if(round&1)res=dayround(round);
        else res=nightround(round);
        if(res)
            break;
    }*/
    if(stage&1)res=dayround(round);
    else res=nightround(round);
    if(!res)return;
    gameend(res);
}
